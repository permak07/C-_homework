#include "rational.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

Rational::Rational()
{
    numer = 0;
    denom = 1;
}

Rational::Rational(int number)
{
    numer = number;
    denom = 1;
}

Rational::Rational(int n, int d)
{
    numer = n;
    denom = d;
    simplify();
}

// Оператор Добавление
Rational &Rational::operator+=(const Rational &r)
{
    numer = (numer * r.denom + denom * r.numer);
    denom *= r.denom;
    simplify(); // упрощение
    return *this;
}

// Оператор Умножения
Rational &Rational::operator*=(const Rational &r)
{
    numer *= r.numer;
    denom *= r.denom;
    simplify();
    return *this;
}

// оператор уменьшения
Rational &Rational::operator-=(const Rational &r)
{
    return (*this += (-r));
}

// Cложение
Rational Rational::operator+(const Rational &r) const
{
    // this - указатель на себя
    // *this - ссылка на себя
    Rational res(*this);
    // Используем готовую операцию добавления
    return res += r;
}

// Деление
Rational Rational::operator/(const Rational &r) const
{
    Rational res(*this);
    res.numer *= r.denom;
    res.denom *= r.numer;
    res.simplify();
    return res;
}

// вычитание
Rational Rational::operator-(const Rational &r) const
{
    Rational res(*this);
    res -= r;
    return res;
}

// Умножение
Rational Rational::operator*(const Rational &r) const
{
    Rational res(*this);
    res *= r;
    return res;
}

// Упрощение
void Rational::simplify()
{
    if (denom < 0)
    {
        numer = -numer;
        denom = -denom;
    }
    for (int i = 2; i <= abs(denom) && i <= abs(numer); i++)
        if (numer % i == 0 && denom % i == 0)
        {
            numer /= i;
            denom /= i;
            i--;
        }
}

// Оператор отрицания
Rational Rational::operator-() const
{
    Rational r(-numer, denom);
    return r;
}

// префикс
Rational &Rational::operator++()
{
    numer += denom;
    return *this;
}

// постфикс
Rational Rational::operator++(int)
{
    Rational r(*this);
    numer += denom;
    return r;
}

// ==
bool Rational::operator==(const Rational &r) const
{
    return (numer == r.numer) && (denom == r.denom);
}

// !=
bool Rational::operator!=(const Rational &r) const
{
    return !(*this == r);
}

// int
Rational::operator int() const
{
    return numer / denom;
}

// double
Rational::operator double() const
{
    return ((double)numer) / denom;
}

// ввод
istream &operator>>(istream &in, Rational &r)
{
    in >> r.numer >> r.denom;
    return in;
}

// вывод
ostream &operator<<(ostream &out, const Rational &r)
{
    out << r.numer << "/" << r.denom;
    return out;
}

// int * Rational
Rational operator*(int i, const Rational &j)
{
    return Rational(i * j.numer, j.denom);
}

// Квадратичное уравнение
void Rational::square(const Rational &a, const Rational &b, const Rational &c)
{
    Rational D = b * b - (4 * a * c);
    cout << "Quadratic equation: (" << a << ")x^2 + (" << b << ")x + (" << c << ") = 0" << endl;
    cout << "Discriminant D = " << D << endl;

    if (double(D) < 0.0)
    {
        cout << "No real roots (D < 0)" << endl;
        return;
    }

    int num = D.numer;
    int den = D.denom;

    int sqrt_num = (int)sqrt(abs(num));
    int sqrt_den = (int)sqrt(den);

    if (sqrt_num * sqrt_num == abs(num) && sqrt_den * sqrt_den == den)
    {
        Rational sqrtD((num >= 0 ? sqrt_num : -sqrt_num), sqrt_den);
        Rational two_a = Rational(2) * a;
        Rational x1 = (-b + sqrtD) / two_a;
        Rational x2 = (-b - sqrtD) / two_a;

        cout << "Rational roots:" << endl;
        if (x1 == x2)
            cout << "x = " << x1 << " (double root)" << endl;
        else
            cout << "x1 = " << x1 << "\nx2 = " << x2 << endl;
    }
    else
    {
        cout << "Roots are irrational (discriminant is not a perfect square rational)" << endl;
    }
}