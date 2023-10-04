#include <iostream>
using namespace std;

int main() {
    string s1, s2;
    cout << "Введите 1ю строку: ";
    getline(cin, s1);
    cout << "Введите 2ю строку: ";
    getline(cin, s2);

    cout << "Compare " << s1 << " и " << s2 << " = " << s1.compare(s2) << endl;

    return 0;
}