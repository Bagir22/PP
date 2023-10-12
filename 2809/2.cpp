#include <iostream>
using namespace std;

void insert(string s)
{
    string changedStr = s;
    int index;
    cout << "Введите индекс вставки подстроки:" << endl;
    cin >> index;
    string s1;
    cout << "Введите подстроку:" << endl;
    cin >> s1;
    changedStr.insert(index, s1);
    cout << "Исходная строка: " << s << endl;
    cout << "Измененая строка: " << changedStr << endl << endl;
}

void erase(string s)
{
    string changedStr = s;
    int index, count;
    cout << "Введите позицию старта удаления:" << endl;
    cin >> index;
    cout << "Введите, сколько символов нужно удалить:" << endl;
    cin >> count;
    changedStr.erase(index, count);
    cout << "Исходная строка: " << s << endl;
    cout << "Измененая строка: " << changedStr << endl << endl;
}

void replace(string s)
{
    string changedStr = s;
    int index, count;
    cout << "Введите позицию старта замены:" << endl;
    cin >> index;
    cout << "Введите, сколько символов нужно заменить:" << endl;
    cin >> count;
    string s1;
    cout << "Введите, подстроку для замены:" << endl;
    cin >> s1;
    changedStr.replace(index, count, s1);
    cout << "Исходная строка: " << s << endl;
    cout << "Измененая строка: " << changedStr << endl << endl;
}

void find(string s)
{
    string sFind;
    cout << "Введите, строку для поиска:" << endl;
    cin >> sFind;
    int index = s.find(sFind);
    if (index != -1)
    {
        cout << "Индекс 1го вхождения подстроки: " << index << endl << endl;
    } 
    else
    {
        cout << "Подстрока не найдена" << endl << endl;
    }
}

int main() {
    string s, command;
    cout << "Введите исходную строку: " << endl;
    getline(cin, s);
   

    while (true) 
    {
        cout << "Введите комманду: " << endl;
        cin >> command;
        if (command == "insert")
        {
            insert(s);
        }
        else if (command == "erase") 
        {
            erase(s);
        }
        else if (command == "replace") 
        {
            replace(s);
        }
        else if (command == "find") 
        {
            find(s);
        }
        else 
        {
            cout << "Неизвестная команда" << endl;
            break;
        }
    }

    return 0;
}