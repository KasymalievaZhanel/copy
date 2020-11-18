#include <iostream>

int main() {
    int value = 7;
    const int &ref = value; // создаем константную ссылку на переменную value

    value = 8; // ок: value - это не константа
    std:: cout << ref;
    return 0;
}
