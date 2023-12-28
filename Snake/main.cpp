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


const char SNAKE_SYMBOL = '#';
const char FIELD_SYMBOL = '.';
const char APPLE_SYMBOL = 'o';
const int WIDTH = 15;
const int HEIGHT = 15;
const string LOSE_STRING = "Lose: ";
const string WIN_STRING = "Win: ";
const string SCORE_STRING = "Score: ";
const char UP_KEY = 'w';
const char DOWN_KEY = 's';
const char RIGHT_KEY = 'd';
const char LEFT_KEY = 'a';
const int RIGHT = 1;
const int LEFT = 2;
const int UP = 3;
const int DOWN = 4;
const int SLEEP = 500000;

struct Segment {
    int x;
    int y;
    char symbol;
};

struct Apple {
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

void PrintField(vector<vector<char> > &field) {
    usleep(SLEEP);
    system("clear");
    for (const vector<char>& row: field) {
        for (char val: row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void AddApple(vector<vector<char>> &field, deque<Segment> &snake, Apple &apple) {
    srand(time(0));
    apple.x = (rand() % WIDTH);
    apple.y = (rand() % HEIGHT);
    for (Segment segment : snake) {
        if (apple.x == segment.x && apple.y == segment.y) {
            AddApple(field, snake, apple);
            return;
        }
    }

    field[apple.x][apple.y] = APPLE_SYMBOL;
}

void Init(vector<vector<char>> &field, deque<Segment> &snake, Apple &apple) {
    for (int i = 0; i < WIDTH; i++) {
        field[i].resize(HEIGHT, FIELD_SYMBOL);
    }

    snake.push_front(Segment{0, 0, SNAKE_SYMBOL});
    AddApple(field, snake, apple);
}

void CheckDirection(bool& directionChanged, int& direction) {
    if (kbhit()) {
        char pressed = getchar();
        if (pressed == UP_KEY && direction != DOWN) {
            directionChanged = true;
            direction = UP;
        } else if (pressed == DOWN_KEY && direction != UP) {
            directionChanged = true;
            direction = DOWN;
        }  else if (pressed == RIGHT_KEY && direction != LEFT) {
            directionChanged = true;
            direction = RIGHT;
        } else if (pressed == LEFT_KEY && direction != RIGHT) {
            directionChanged = true;
            direction = LEFT;
        }
    } else {
        directionChanged = false;
    }
}

bool CheckBorder(int pos, int border) {
    if (border != -1 && pos >= border) {
        return true;
    } else if (border == -1 && pos <= border) {
        return true;
    }

    return false;
}

bool CheckSnakeCrash(vector<vector<char>> &field, int x, int y) {
    if (x == -1 || x == WIDTH || y == -1 || y == HEIGHT) {
        return  true;
    }
    if (field[x][y] == SNAKE_SYMBOL) {
        return true;
    }

    return false;
}

void UpdateField(vector<vector<char>> &field, deque<Segment> &snake, Apple &apple) {
    for (int i = 0 ; i < WIDTH ; i++) {
        for (int j = 0 ; j < HEIGHT ; j++) {
            field[i][j] = FIELD_SYMBOL;
        }
    }

    field[apple.x][apple.y] = APPLE_SYMBOL;

    for (Segment segment : snake) {
        int x = segment.x;
        int y = segment.y;
        field[x][y] = segment.symbol;
    }
}

bool CheckCrash(bool& crash, vector<vector<char>> &field, int& x, int& y, int direction) {
    bool crashBorder;
    bool crashSnake;

    if (direction == RIGHT) {
        y += 1;
        crashBorder = CheckBorder(y, HEIGHT);
    } else if (direction == LEFT) {
        y -= 1;
        crashBorder = CheckBorder(y, -1);
    } else if (direction == UP) {
        x -= 1;
        crashBorder = CheckBorder(x, -1);
    } else {
        x += 1;
        crashBorder = CheckBorder(x, WIDTH);
    }

    crashSnake = CheckSnakeCrash(field, x, y);

    crash = crashBorder || crashSnake;
    return crash;
}

void Move(vector<vector<char>> &field, deque<Segment> &snake, Apple &apple, int direction, bool& crash) {
    int x = snake.front().x;
    int y = snake.front().y;

    if (CheckCrash(crash, field, x, y, direction)) {
        return;
    }

    snake.push_front(Segment{x, y, SNAKE_SYMBOL});
    snake.pop_back();

    UpdateField(field, snake, apple);
}

void CheckEatApple(vector<vector<char>> &field, deque<Segment> &snake, Apple &apple, int direction) {
    int headX = snake.front().x;
    int headY = snake.front().y;

    if (headX == apple.x && headY == apple.y) {
        int tailX = snake.back().x;
        int tailY = snake.back().y;

        int newX = tailX;
        int newY = tailY;

        switch(direction) {
            case RIGHT:
                newY -= 1;
            case LEFT:
                newY += 1;
            case UP:
                newX += 1;
            case DOWN:
                newX -=1;
        }

        snake.push_back(Segment{newX, newY, SNAKE_SYMBOL});

        AddApple(field, snake, apple);
    }
}

void Start(vector<vector<char>> &field, deque<Segment> &snake, Apple &apple) {
    bool crash = false;
    bool directionChanged = false;
    int direction = RIGHT;

    while (!crash) {
        if (snake.size() == WIDTH * HEIGHT) {
            system("reset");
            cout << WIN_STRING << endl;
            cout << SCORE_STRING << snake.size() << endl;

            return;
        }

        CheckDirection(directionChanged, direction);
        Move(field, snake, apple, direction, crash);
        CheckEatApple(field, snake, apple, direction);
        PrintField(field);
    }

    if (crash) {
        cout << LOSE_STRING << endl;
        cout << SCORE_STRING << snake.size() << endl;
    }
}

int main() {
    vector<vector<char>> field(WIDTH, vector<char>(HEIGHT));
    deque<Segment> snake;
    Apple apple{};

    Init(field, snake, apple);
    Start(field, snake, apple);

    return 0;
}
