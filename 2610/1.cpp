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
    char apple = '#';
    int appleWidth = (rand() % width);
    int appleHeight = (rand() % height);
    field.at(appleWidth).at(appleWidth) = apple;

    printField(field);
    
    return 0;
}