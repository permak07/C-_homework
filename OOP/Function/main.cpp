#include <iostream>
#include <vector>
#include "function.h"

using namespace std;

int main()
{
    Function *functions[4];

    functions[0] = new Parabola(2.0, -3.0, 1.0);                      // y = 2x² - 3x + 1
    functions[1] = new Hiperbola(5.0, 2.0);                           // y = 5/x + 2
    functions[2] = new Exponenta(3.0, 0.5, -1.0);                     // y = 3·e^(0.5x) - 1
    functions[3] = new Polinom(vector<double>{2.0, -1.0, 4.0, -3.0}); // y = 2x³ - x² + 4x - 3

    double xValues[4] = {2.0, 2.0, 1.0, 1.0};

    // Интервалы для поиска min/max и интегрирования
    double aValues[4] = {0.0, 1.0, 0.0, 0.0};
    double bValues[4] = {3.0, 5.0, 2.0, 2.0};

    string names[4] = {
        "Parabola: y = 2x^2 - 3x + 1",
        "Hiperbola: y = 5/x + 2",
        "Exponenta: y = 3*e^(0.5x) - 1",
        "Polinom: y = 2x^3 - x^2 + 4x - 3"};

    for (int i = 0; i < 4; i++)
    {
        cout << "=== " << names[i] << " ===" << endl;

        double x = xValues[i];
        double a = aValues[i];
        double b = bValues[i];

        showFunctionInfo(*functions[0], x, a, b);
    }

    // Вычисление f(x) для других x
    double extraX[4] = {-1.0, 3.0, 0.5, -2.0};
    cout << "=== Additional evaluation at different x ===" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << names[i] << ": f(" << extraX[i] << ") = "
             << functions[i]->evaluate(extraX[i]) << endl;
    }

    // Очистка памяти
    for (int i = 0; i < 4; i++)
    {
        delete functions[i];
    }

    return 0;
}