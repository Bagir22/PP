#include <deque>
#include <iostream>
#include <time.h>

using namespace std;

#define width 5
#define height 10


void printField(vector<vector<char> > const &field) {
    for (vector<char> row: field)
    {
        for (char val: row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<char> > field(width);
    for (int i = 0 ; i < width ; i++) {
        field[i].resize(height, '.');
    }
 
    srand(time(0));
    char apple = 'o';
    int appleWidth = (rand() % width);
    int appleHeight = (rand() % height);
    field.at(appleWidth).at(appleWidth) = apple;

    deque <pair<int, int> > snake;
    snake.push_back(std::make_pair(0, 0));
    snake.push_back(std::make_pair(1, 0));

    for (pair<int, int> segment : snake) {
        int x = segment.first;
        int y = segment.second;
        field[x][y] = '#';
    }

    printField(field);
    
    return 0;
}