#include <iostream>
#include <string>
using namespace std;

class DataTime
{
    double value;

    bool vis_year(int year) const;
    int days_in_month(int month, int year) const;
    double date_to_Julian(int day, int month, int year, int hour = 0, int minute = 0, int second = 0) const;
    void Julian_to_date(int &day, int &month, int &year, int &hour, int &minute, int &second) const;
    void Julian_to_date(int &day, int &month, int &year) const;

public:
    // Конструкторы
    DataTime(int day = 1, int month = 1, int year = 2000);
    DataTime(int day, int month, int year, int hour, int minute, int second);
    DataTime(const string &iso_string);

    // Ввод и проверка
    void input();
    void inputTime();
    void inputDateTime();
    bool check(int day, int month, int year) const;
    bool checkTime(int hour, int minute, int second) const;

    // + и -
    double operator-(const DataTime &other) const;
    DataTime operator+(int days) const;
    DataTime operator+(double days) const;
    DataTime operator-(int days) const;
    DataTime operator-(double days) const;

    // Сравнение
    bool operator>(const DataTime &other) const;
    bool operator<(const DataTime &other) const;
    bool operator>=(const DataTime &other) const;
    bool operator<=(const DataTime &other) const;
    bool operator==(const DataTime &other) const;
    bool operator!=(const DataTime &other) const;

    // День недели
    string day_of_week() const;

    // форматы выводы
    string toStringDate() const;
    string toStringTime() const;
    string toStringISO() const;
    string toStringDateOnly() const;

    // вывод
    friend ostream &operator<<(ostream &out, const DataTime &dt);
    friend istream &operator>>(istream &in, DataTime &dt);
};