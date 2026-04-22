#ifndef DATATIME_H
#define DATATIME_H
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

public:
    DataTime(int day = 1, int month = 1, int year = 2000);
    DataTime(int day, int month, int year, int hour, int minute, int second);
    DataTime(const string &iso_string);

    void input();
    void inputTime();
    void inputDateTime();
    bool check(int day, int month, int year) const;
    bool checkTime(int hour, int minute, int second) const;

    // Получение юлианской даты для луны
    double getValue() const { return value; }
    void Julian_to_date(int &day, int &month, int &year) const;

    double operator-(const DataTime &other) const;
    DataTime operator+(int days) const;
    DataTime operator+(double days) const;
    DataTime operator-(int days) const;
    DataTime operator-(double days) const;

    bool operator>(const DataTime &other) const;
    bool operator<(const DataTime &other) const;
    bool operator>=(const DataTime &other) const;
    bool operator<=(const DataTime &other) const;
    bool operator==(const DataTime &other) const;
    bool operator!=(const DataTime &other) const;

    string day_of_week() const;
    string toStringDate() const;     // dd.MM.yyyy
    string toStringTime() const;     // hh:mm:ss
    string toStringISO() const;      // yyyy-MM-ddThh:mm:ss
    string toStringDateOnly() const; // yyyy-MM-dd

    friend ostream &operator<<(ostream &out, const DataTime &dt);
    friend istream &operator>>(istream &in, DataTime &dt);
};
#endif