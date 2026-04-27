#include <iostream>
using namespace std;

// Константы игрового поля
const int FIELD_WIDTH = 7;
const int FIELD_HEIGHT = 6;
const int WIN_LENGTH = 4;

// Ячейка
enum Cell
{
    EMPTY,
    RED,
    YELLOW
};

class Field
{
    // Игрового поле
    Cell cells[FIELD_WIDTH][FIELD_HEIGHT];
    // Очередь хода
    bool isRedTurn;
    // Кто на данный момент выиграл
    Cell winner;
    void checkWinner();

public:
    Field(bool isRedFirst);
    void clear(bool isRedFirst);
    bool makeTurn(int column);
    bool isWon(bool red) const;
    bool isOver() const;
    Cell getCell(int i, int j) const;
    bool isRedTurnNow() const;
    void print() const;
    void printResult() const;
};