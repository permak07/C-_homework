#include <iostream>
#include <vector>
#include <cmath>

class Function
{
public:
    virtual double evaluate(double x) const = 0;
    virtual void print(double x) const;
    virtual double findMin(double a, double b, int steps = 1000) const;
    virtual double findMax(double a, double b, int steps = 1000) const;
    virtual double integrate(double a, double b, int steps = 1000) const;
    virtual double differentiate(double x, double h = 1e-5) const;

    // Виртуальный деструктор
    virtual ~Function() {}
};

// Парабола: y = a*x^2 + b*x + c
class Parabola : public Function
{
private:
    double a, b, c;

public:
    Parabola(double a_, double b_, double c_);
    double evaluate(double x) const override;
};

// Гипербола: y = a / x + b
class Hiperbola : public Function
{
private:
    double a, b;

public:
    Hiperbola(double a_, double b_);
    double evaluate(double x) const override;
};

// Экспонента: y = a * e^(b*x) + c
class Exponenta : public Function
{
private:
    double a, b, c;

public:
    Exponenta(double a_, double b_, double c_);
    double evaluate(double x) const override;
};