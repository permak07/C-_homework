#include "rational.h"
#include <iostream>
#include <cmath>
using namespace std;
int main(void)
{
    Rational a, b, c;
    do
    {
        cout << "Enter a: ";
        cin >> a;
        cout << "Enter b: ";
        cin >> b;
        cout << "Enter c: ";
        cin >> c;
    } while (a == 0 || b == 0 || c == 0);
    cout << "This program solves quadratic equations with perfect square only" << endl;
    // Работающие a , b , c: -3, 1/4 , 5/8
    square(a, b, c);
    return 0;
}