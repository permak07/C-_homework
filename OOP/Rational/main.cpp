#include "rational.h"
#include <iostream>
#include <cmath>
using namespace std;
int main(void)
{
    Rational a(1, 2), b(-1, 6);
    cout << "a=" << a << " b=" << b << " a+b=" << a + b << endl;
    cout << "a(" << a << ") *= b(" << b << ")" << endl;
    a *= b;
    cout << "a=" << a << " b=" << b << " a-b=" << a + (-b) << endl;
    Rational c = 3;
    cout << "b=" << b << " c=" << c << " b/c=" << b / c << endl;

    // Тестируем >>, !=
    Rational e(7, 8), f(5, 12);
    cout << "e=" << e << " f=" << f << " e+f=?" << endl;
    cout << "Enter rezult g=m/n for example: m n" << endl;
    Rational g;
    cin >> g;
    if (e + f != g)
        cout << "Not right! e+f=" << e + f << endl;
    else
        cout << "Right!" << endl;
    cout << endl;

    Rational a1(1, 2), b1(1, 2), c1(-1);
    Rational::square(a1, b1, c1);
    return 0;
}