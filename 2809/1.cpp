#include <iostream>
using namespace std;

int main() {
    string inputString;
    cout << "Введите строку: ";
    getline(cin, inputString);
    cout << "Исходная строка: " << inputString << endl;
    cout << "front: " << inputString.front() << endl;
    cout << "back: " << inputString.back() << endl;

    return 0;
}