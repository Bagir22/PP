#include <deque>
#include <iostream>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <termios.h>
#include <fcntl.h>
#include <vector>

using namespace std;

#define WIDTH 15
#define HEIGHT 15

struct segment {
    int x;
    int y;
    char symbol;
};

struct apple {
    int x;
    int y;
};

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)     {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

void printField(vector<vector<char> > &field) {
    usleep(500000);
    system("clear");
    for (const vector<char>& row: field) {
        for (char val: row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void addApple(vector<vector<char>> &field, deque<segment> &snake, apple &apple) {
    srand(time(0));
    apple.x = (rand() % WIDTH);
    apple.y = (rand() % HEIGHT);
    for (segment segment : snake) {
        int x = segment.x;
        int y = segment.y;
        if (apple.x == x && apple.y == y) {
            addApple(field, snake, apple);
            return;
        }
    }

    field[apple.x][apple.y] = 'o';
}

void init(vector<vector<char>> &field, deque<segment> &snake, apple &apple) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            field[i][j] = '.';
        }
    }

    snake.push_front(segment{0, 0, '>'});
    addApple(field, snake, apple);
}

void checkDirection(bool& directionChanged, int& direction) {
    if (kbhit()) {
        char pressed = getchar();
        if (pressed == 'w' && direction != 4) {
            directionChanged = true;
            direction = 3;
        } else if (pressed == 's' && direction != 3) {
            directionChanged = true;
            direction = 4;
        }  else if (pressed == 'd' && direction != 2) {
            directionChanged = true;
            direction = 1;
        } else if (pressed == 'a' && direction != 1) {
            directionChanged = true;
            direction = 2;
        }
    } else {
        directionChanged = false;
    }
}

bool checkBorder(int pos, int border) {
    if (border != -1 && pos >= border) {
        return true;
    } else if (border == -1 && pos <= border) {
        return true;
    }

    return false;
}

bool checkSnakeCrash(vector<vector<char>> &field, int x, int y) {
    if (field[x][y] == '#') {
        return true;
    }

    return false;
}

void move(vector<vector<char>> &field, deque<segment> &snake, apple &apple, int direction, bool& crash) {
    // direction 1 - > || 2 - < || 3 - ^ || 4 - V
    int x = snake.front().x;
    int y = snake.front().y;

    bool crashBorder;
    bool crashSnake;
    if (direction == 1) {
        crashBorder = checkBorder(y+1, HEIGHT);
        crashSnake = checkSnakeCrash(field, x, y+1);
        snake.push_front(segment{x, y+1, '#'});
        snake.pop_back();
    } else if (direction == 2) {
        crashBorder = checkBorder(y-1, -1);
        crashSnake = checkSnakeCrash(field, x, y-1);
        snake.push_front(segment{x, y-1, '#'});
        snake.pop_back();
    } else if (direction == 3) {
        crashBorder = checkBorder(x-1, -1);
        crashSnake = checkSnakeCrash(field, x-1, y);
        snake.push_front(segment{x-1, y, '#'});
        snake.pop_back();
    } else {
        crashBorder = checkBorder(x+1, WIDTH);
        crashSnake = checkSnakeCrash(field, x+1, y);
        snake.push_front(segment{x+1, y, '#'});
        snake.pop_back();
    }

    crash = crashBorder || crashSnake;
    if (crash) {
        return;
    }

    for (int i = 0 ; i < WIDTH ; i++) {
        for (int j = 0 ; j < HEIGHT ; j++) {
            field[i][j] = '.';
        }
    }

    field[apple.x][apple.y] = 'o';

    for (segment segment : snake) {
        x = segment.x;
        y = segment.y;
        field[x][y] = segment.symbol;
    }
}

void checkEatApple(vector<vector<char>> &field, deque<segment> &snake, apple &apple, int direction) {
    int headX = snake.front().x;
    int headY = snake.front().y;

    if (headX == apple.x && headY == apple.y) {
        int tailX = snake.back().x;
        int tailY = snake.back().y;

        if (direction == 1) {
            snake.push_back(segment{tailX, tailY-1, '#'});
        } else if (direction == 2) {
            snake.push_back(segment{tailX, tailY+1, '#'});
        } else if (direction == 3) {
            snake.push_back(segment{tailX+1, tailY, '#'});
        } else {
            snake.push_back(segment{tailX-1, tailY, '#'});
        }

        addApple(field, snake, apple);
    }
}

void start(vector<vector<char>> &field, deque<segment> &snake, apple &apple) {
    bool crash = false;
    bool directionChanged = false;
    int direction = 1; // 1 - > || 2 - < || 3 - ^ || 4 - V

    while (!crash) {
        if (snake.size() == WIDTH * HEIGHT) {
            system("reset");
            cout << "Win:" << endl;
            cout << "Score: " << snake.size() << endl;

            return;
        }

        checkDirection(directionChanged, direction);
        move(field, snake, apple, direction, crash);
        checkEatApple(field, snake, apple, direction);
        printField(field);
    }

    if (crash) {
        cout << "Lose:" << endl;
        cout << "Score: " << snake.size() << endl;
    }
}

int main() {
    vector<vector<char>> field(WIDTH, vector<char>(HEIGHT));
    deque<segment> snake;
    apple apple{};

    init(field, snake, apple);
    start(field, snake, apple);

    return 0;
}
