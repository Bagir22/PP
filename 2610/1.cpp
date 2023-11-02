#include <deque>
#include <iostream>
#include <time.h>
#include <conio>

using namespace std;

#define width 5
#define height 10

void printField(vector<vector<char> > &field) {
    for (vector<char> row: field)
    {
        for (char val: row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void addApple(vector<vector<char> > &field) {
    srand(time(0));
    char apple = 'o';
    int appleWidth = (rand() % width);
    int appleHeight = (rand() % height);
    if (appleWidth != 0 && appleHeight != 0) {
        field.at(appleWidth).at(appleWidth) = apple;
    } else {
        addApple(field);
    }    
}

void initField(vector<vector<char> > &field) {
    for (int i = 0 ; i < width ; i++) {
        field[i].resize(height, '.');
    }
 
    deque <pair<int, int> > snake;
    snake.push_back(make_pair(0, 0));

    for (pair<int, int> segment : snake) {
        int x = segment.first;
        int y = segment.second;
        field[x][y] = '#';
    }

    addApple(field);

    printField(field);
}

int main() {
    vector<vector<char> > field(width);
    initField(field);

    return 0;
}