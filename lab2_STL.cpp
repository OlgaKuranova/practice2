#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>


using namespace std;

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<char> v;
    string str;

    cout << "Введите строку: " << endl;
    cin >> str;

    for (string::size_type i = 0; i < str.size(); ++i) //string::size_type хранит длину строки
        v.push_back(str[i]); //добавляет ячейку в конец вектора

    while (!v.empty()) { //пока вектор не пуст
        cout << v.back(); //просмотр и вывод на экран последней ячейки
        v.pop_back(); // удаляет ячейку из конца вектора
    }
}
