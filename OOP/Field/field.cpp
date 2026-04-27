#include "field.h"
using namespace std;

// Конструктор
Field::Field(bool isRedFirst)
{
    clear(isRedFirst);
}

// Очистка
void Field::clear(bool isRedFirst)
{
    isRedTurn = isRedFirst;
    winner = EMPTY;
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            cells[i][j] = EMPTY;
}

// Выполнение хода
bool Field::makeTurn(int column)
{
    if (winner != EMPTY ||
        column < 1 || column > FIELD_WIDTH)
        return false;
    int i = column - 1;
    for (int j = 0; j < FIELD_HEIGHT; j++)
        if (cells[i][j] == EMPTY)
        {
            cells[i][j] = isRedTurn ? RED : YELLOW;
            checkWinner(); // Победа?
            isRedTurn = !isRedTurn;
            return true;
        }
    return false;
}

// Определение победителя
const int DIR_NUMBER = 4;
const int di[] = {1, 0, 1, 1};
const int dj[] = {0, 1, -1, 1};

void Field::checkWinner()
{
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
        {
            Cell start = cells[i][j];
            if (start == EMPTY)
                continue;
            for (int dir = 0; dir < DIR_NUMBER; dir++)
            {
                int length = 0, iline = i, jline = j;
                while (++length < WIN_LENGTH)
                {
                    iline += di[dir];
                    jline += dj[dir];
                    if (iline < 0 || iline >= FIELD_WIDTH ||
                        jline < 0 || jline >= FIELD_HEIGHT)
                        break;
                    if (cells[iline][jline] != start)
                        break;
                }
                if (length == WIN_LENGTH)
                {
                    winner = start;
                    return;
                }
            }
        }
}
// Контроль оконачания игры
bool Field::isOver() const
{
    if (winner != EMPTY)
        return true;
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            // Если хоть одна ячейка свободна,
            // игра не окончена
            if (cells[i][j] == EMPTY)
                return false;
    // Все ячейки заняты
    return true;
}

// Победил ли игрок red?
bool Field::isWon(bool red) const
{
    return red ? (winner == RED) : (winner == YELLOW);
}

// Получить содержимое ячейки
Cell Field::getCell(int i, int j) const
{
    return cells[i][j];
}

// Чей ход?
bool Field::isRedTurnNow() const
{
    return isRedTurn;
}

// Вывод поля в консоль
void Field::print() const
{
    cout << "\n   ";
    for (int i = 0; i < FIELD_WIDTH; ++i)
        cout << "  " << i + 1 << " ";
    cout << "\n";

    for (int j = FIELD_HEIGHT - 1; j >= 0; --j)
    {
        cout << j + 1 << "  ";
        for (int i = 0; i < FIELD_WIDTH; ++i)
        {
            char move = ' ';
            if (cells[i][j] == RED)
                move = 'R';
            else if (cells[i][j] == YELLOW)
                move = 'Y';
            cout << "| " << move << " ";
        }
        cout << "|\n";
    }
    cout << "   ";
    for (int i = 0; i < FIELD_WIDTH; ++i)
        cout << " ---";
    cout << "\n";
}

// Объявлкние результатов игры
void Field::printResult() const
{
    if (winner == RED)
        cout << "Red player wins!\n";
    else if (winner == YELLOW)
        cout << "Yellow player wins!\n";
    else
        cout << "It's a draw!\n";
}