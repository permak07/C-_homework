#include <iostream>
#include <vector>
#include "function.h"

using namespace std;

void showFunctionInfo(Function &f, double x, double a, double b)
{
    cout << endl;
    cout << "Value x = " << x << ": ";
    f.print(x);
    cout << "Minimum on [" << a << ", " << b << "]: " << f.findMin(a, b) << endl;
    cout << "Maximum on [" << a << ", " << b << "]: " << f.findMax(a, b) << endl;
    cout << "Integral on [" << a << ", " << b << "]: " << f.integrate(a, b) << endl;
    cout << "Derivative at point x = " << x << ": " << f.differentiate(x) << endl;
    cout << endl
         << endl;
}

int main()
{
    double x;

    cout << "Parabola: y = 2x^2 - 3x + 1" << endl;
    Parabola parabola(2.0, -3.0, 1.0);
    cout << "Enter x for Parabola: ";
    cin >> x; // работает при x=2
    showFunctionInfo(parabola, x, 0.0, 3.0);

    cout << "Giperbola: y = 5/x + 2 " << endl;
    Hiperbola hiperbola(5.0, 2.0);
    cout << "Enter x for Hyperbola (x != 0): ";
    cin >> x; // работает при x=2
    showFunctionInfo(hiperbola, x, 1.0, 5.0);

    cout << "Exponenta: y = 3*e^(0.5x) - 1" << endl;
    Exponenta exponenta(3.0, 0.5, -1.0);
    cout << "Enter x for Exponent: ";
    cin >> x; // работает при x=1
    showFunctionInfo(exponenta, x, 0.0, 2.0);

    return 0;
}