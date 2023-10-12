#include <iostream>
using namespace std;

int main() {
    string s1, s2;
    cout << "Введите 1ю строку: ";
    getline(cin, s1);
    cout << "Введите 2ю строку: ";
    getline(cin, s2);

    int result = s1.compare(s2);
    if (result == 0) {
        cout << "Строки равны" << endl;
    } else if (result > 0) {
        cout << s1 << " больше " << s2 << endl;
    } else {
       cout << s1 << " меньше " << s2 << endl; 
    }

    return 0;
}