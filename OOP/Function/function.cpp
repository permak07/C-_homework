#include "function.h"

using namespace std;

// Вывод значения функции в точке x
void Function::print(double x) const
{
    cout << "f(" << x << ") = " << evaluate(x) << endl;
}

// Минимум
double Function::findMin(double a, double b, int steps) const
{
    double minVal = evaluate(a);
    double step = (b - a) / steps;
    for (int i = 0; i <= steps; i++)
    {
        double x = a + i * step;
        double val = evaluate(x);
        if (val < minVal)
        {
            minVal = val;
        }
    }
    return minVal;
}

// Максимум
double Function::findMax(double a, double b, int steps) const
{
    double maxVal = evaluate(a);
    double step = (b - a) / steps;
    for (int i = 0; i <= steps; i++)
    {
        double x = a + i * step;
        double val = evaluate(x);
        if (val > maxVal)
        {
            maxVal = val;
        }
    }
    return maxVal;
}

// Интегрирование через площадь трапеции
double Function::integrate(double a, double b, int steps) const
{
    double step = (b - a) / steps;
    double sum = 0.0;
    for (int i = 0; i < steps; i++)
    {
        double x1 = a + i * step;
        double x2 = a + (i + 1) * step;
        // Площадь трапеции = (f(x1) + f(x2)) / 2 * ширина
        sum += (evaluate(x1) + evaluate(x2)) / 2.0 * step;
    }
    return sum;
}

// Дифференцирование: f'(x) ≈ (f(x+h) - f(x-h)) / (2*h)
double Function::differentiate(double x, double h) const
{
    return (evaluate(x + h) - evaluate(x - h)) / (2.0 * h);
}

// Parabola
Parabola::Parabola(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

double Parabola::evaluate(double x) const
{
    return a * x * x + b * x + c;
}

// Hiperbola
Hiperbola::Hiperbola(double a_, double b_) : a(a_), b(b_) {}

double Hiperbola::evaluate(double x) const
{
    // Проверка на деление на ноль
    if (x == 0.0)
    {
        cerr << "Error: division by zero in hyperbola!" << endl;
        return 0.0;
    }
    return a / x + b;
}

// Exponenta
Exponenta::Exponenta(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

double Exponenta::evaluate(double x) const
{
    return a * exp(b * x) + c;
}