#include <set>
#include <iostream>

using namespace std;

int main() {
    set <int> st;
    string cmd;
    int val;
    
    while (true) {
        cout << "Введите команду: " << endl;
        cin >> cmd >> val; 
        if (cmd == "push") {
            if (st.find(val) != st.end()) {
                cout << "Такое значение уже есть в множестве" << endl;
            } else {
                st.insert(val);
                set <int> :: iterator it = st.begin();

                cout << "Множество: " << endl;
                for (int i = 1; it != st.end(); i++, it++) {
                    cout << *it << " ";
                }
                cout << endl << "Добавлено значение " << val << endl;
            }            
        } else if (cmd == "delete") {
            if (st.find(val) == st.end()) {
                cout << "Такого значения нет в множестве" << endl;
            } else {
                st.erase(val);
                set <int> :: iterator it = st.begin();

                cout << "Множество: " << endl;
                for (int i = 1; it != st.end(); i++, it++) {
                    cout << *it << " ";
                }
                cout << endl << "Удалено значение " << val << endl;
            }            
        } else {
            break;
        }
    }

    return 0;
}