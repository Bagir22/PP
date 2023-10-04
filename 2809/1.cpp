#include <iostream>
using namespace std;

int main() {
    string s;
    cout << "Введите строку: ";
    getline(cin, s);
    cout << "Исходная строка: " << s << endl;
    cout << "front: " << s.front() << endl;
    cout << "back: " << s.back() << endl;

    return 0;
}