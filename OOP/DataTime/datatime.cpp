#include "datatime.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
bool DataTime::vis_year(int year) const
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int DataTime::days_in_month(int month, int year) const
{
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && vis_year(year))
        return 29;
    return days[month - 1];
}

double DataTime::date_to_Julian(int day, int month, int year, int hour, int minute, int second) const
{
    long totaldays = day;
    for (int i = 1; i < year; ++i)
        totaldays += vis_year(i) ? 366 : 365;
    for (int i = 1; i < month; ++i)
        totaldays += days_in_month(i, year);

    double time_fraction = (hour * 3600 + minute * 60 + second) / 86400.0;
    return (double)totaldays + time_fraction;
}

void DataTime::Julian_to_date(int &day, int &month, int &year, int &hour, int &minute, int &second) const
{
    long total = (long)value;
    double fraction = value - total;

    int total_seconds = (int)(fraction * 86400 + 0.5);
    hour = total_seconds / 3600;
    minute = (total_seconds % 3600) / 60;
    second = total_seconds % 60;

    if (hour >= 24)
    {
        hour = 0;
        total++;
    }

    year = 1;
    while (total > (vis_year(year) ? 366 : 365))
    {
        total -= vis_year(year) ? 366 : 365;
        year++;
    }
    month = 1;
    while (total > days_in_month(month, year))
    {
        total -= days_in_month(month, year);
        month++;
    }
    day = (int)total;
}

void DataTime::Julian_to_date(int &day, int &month, int &year) const
{
    int hour, minute, second;
    Julian_to_date(day, month, year, hour, minute, second);
}

// Конструкторы
DataTime::DataTime(int day, int month, int year)
{
    value = date_to_Julian(day, month, year, 0, 0, 0);
}

DataTime::DataTime(int day, int month, int year, int hour, int minute, int second)
{
    if (!checkTime(hour, minute, second))
    {
        hour = minute = second = 0;
    }
    value = date_to_Julian(day, month, year, hour, minute, second);
}

DataTime::DataTime(const string &iso_string)
{
    int day = 1, month = 1, year = 2000, hour = 0, minute = 0, second = 0;

    size_t t_pos = iso_string.find('T');
    size_t dash1 = iso_string.find('-');

    if (dash1 != string::npos)
    {
        year = stoi(iso_string.substr(0, 4));
        month = stoi(iso_string.substr(5, 2));
        day = stoi(iso_string.substr(8, 2));

        if (t_pos != string::npos)
        {
            hour = stoi(iso_string.substr(t_pos + 1, 2));
            minute = stoi(iso_string.substr(t_pos + 4, 2));
            second = stoi(iso_string.substr(t_pos + 7, 2));
        }
    }
    else if (iso_string.find(':') != string::npos)
    {
        hour = stoi(iso_string.substr(0, 2));
        minute = stoi(iso_string.substr(3, 2));
        second = stoi(iso_string.substr(6, 2));
    }

    value = date_to_Julian(day, month, year, hour, minute, second);
}

bool DataTime::check(int day, int month, int year) const
{
    if (year < 1 || month < 1 || day < 1 || month > 12)
        return false;
    if (day > days_in_month(month, year))
        return false;
    return true;
}

bool DataTime::checkTime(int hour, int minute, int second) const
{
    return (hour >= 0 && hour < 24 &&
            minute >= 0 && minute < 60 &&
            second >= 0 && second < 60);
}

void DataTime::input()
{
    int day, month, year;
    do
    {
        cout << "Enter date (day month year): ";
        cin >> day >> month >> year;
    } while (!check(day, month, year));

    int hour = 0, minute = 0, second = 0;
    Julian_to_date(day, month, year, hour, minute, second);
    value = date_to_Julian(day, month, year, 0, 0, 0);
}

void DataTime::inputTime()
{
    int hour, minute, second;
    do
    {
        cout << "Enter time (hour minute second): ";
        cin >> hour >> minute >> second;
    } while (!checkTime(hour, minute, second));

    int day, month, year;
    Julian_to_date(day, month, year);
    value = date_to_Julian(day, month, year, hour, minute, second);
}

void DataTime::inputDateTime()
{
    cout << "Enter date and time (yyyy-MM-ddThh:mm:ss): ";
    string input;
    cin >> input;
    *this = DataTime(input);
}

// Операторы
double DataTime::operator-(const DataTime &other) const
{
    return this->value - other.value;
}

DataTime DataTime::operator+(int days) const
{
    DataTime result;
    result.value = this->value + days;
    return result;
}

DataTime DataTime::operator+(double days) const
{
    DataTime result;
    result.value = this->value + days;
    return result;
}

DataTime DataTime::operator-(int days) const
{
    return operator+(-days);
}

DataTime DataTime::operator-(double days) const
{
    return operator+(-days);
}

bool DataTime::operator>(const DataTime &other) const { return value > other.value; }
bool DataTime::operator<(const DataTime &other) const { return value < other.value; }
bool DataTime::operator>=(const DataTime &other) const { return value >= other.value; }
bool DataTime::operator<=(const DataTime &other) const { return value <= other.value; }
bool DataTime::operator==(const DataTime &other) const { return abs(value - other.value) < 1e-9; }
bool DataTime::operator!=(const DataTime &other) const { return !(*this == other); }

string DataTime::day_of_week() const
{
    long days = (long)value;
    int day_of_week = days % 7;
    string days_names[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return days_names[day_of_week];
}

// Форматирование вывода
string DataTime::toStringDate() const
{
    int day, month, year, hour, minute, second;
    Julian_to_date(day, month, year, hour, minute, second);
    char buf[20];
    sprintf(buf, "%02d.%02d.%04d", day, month, year);
    return string(buf);
}

string DataTime::toStringTime() const
{
    int day, month, year, hour, minute, second;
    Julian_to_date(day, month, year, hour, minute, second);
    char buf[20];
    sprintf(buf, "%02d:%02d:%02d", hour, minute, second);
    return string(buf);
}

string DataTime::toStringISO() const
{
    int day, month, year, hour, minute, second;
    Julian_to_date(day, month, year, hour, minute, second);
    char buf[30];
    sprintf(buf, "%04d-%02d-%02dT%02d:%02d:%02d", year, month, day, hour, minute, second);
    return string(buf);
}

string DataTime::toStringDateOnly() const
{
    int day, month, year, hour, minute, second;
    Julian_to_date(day, month, year, hour, minute, second);
    char buf[20];
    sprintf(buf, "%04d-%02d-%02d", year, month, day);
    return string(buf);
}

ostream &operator<<(ostream &out, const DataTime &date)
{
    out << date.toStringISO();
    return out;
}

istream &operator>>(istream &in, DataTime &date)
{
    int day, month, year, hour = 0, minute = 0, second = 0;

    string input;
    getline(in, input);

    size_t start = input.find_first_not_of(" ");
    if (start != string::npos)
        input = input.substr(start);

    if (input.find('T') != string::npos || (input.find('-') != string::npos && input.find('.') == string::npos))
    {
        date = DataTime(input);
    }
    else
    {
        sscanf(input.c_str(), "%d.%d.%d", &day, &month, &year);
        if (input.find(':') != string::npos)
        {
            size_t space_pos = input.find(' ');
            if (space_pos != string::npos)
            {
                string time_part = input.substr(space_pos + 1);
                sscanf(time_part.c_str(), "%d:%d:%d", &hour, &minute, &second);
            }
        }
        date = DataTime(day, month, year, hour, minute, second);
    }

    return in;
}