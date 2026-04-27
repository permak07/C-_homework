#include <iostream>
#include <limits>
#include "field.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    Field field(true);

    while (!field.isOver())
    {
        field.print();

        // Цикл для проверки на корректность хода
        while (true)
        {
            cout << (field.isRedTurnNow() ? "Red" : "Yellow")
                 << " player's turn, enter column (1-7): ";

            int column;
            cin >> column;

            // Проверка на некорректный ввод
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            // Пытаемся сделать ход
            if (field.makeTurn(column))
                break; // Если всё нормально выходим
            else
                cout << "Illegal move. Try again.\n"; // неверная колонка или она заполнена
        }
    }

    field.printResult();
    return 0;
}