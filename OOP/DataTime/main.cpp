#include <iostream>
#include "datatime.h"

using namespace std;

int main()
{
    DataTime date1(10, 3, 2025, 14, 30, 0);
    DataTime date2("2025-12-25T08:15:45");

    cout << "date1: " << date1 << endl;
    cout << "date2: " << date2 << endl;
    cout << endl;

    cout << "Date only: " << date1.toStringDate() << endl;
    cout << "Time only: " << date1.toStringTime() << endl;
    cout << endl;

    double diff = date2 - date1;
    cout << "date2 - date1: " << diff << endl;
    cout << endl;

    DataTime date3 = date1 + 0.25;
    cout << "date1 + 6 hours: " << date3 << endl;
    DataTime date4 = date3 + 2;
    cout << "date3 + 2 days: " << date4 << endl;
    cout << endl;

    DataTime early(10, 3, 2025, 9, 0, 0);
    DataTime late(10, 3, 2025, 18, 0, 0);

    cout << "Same day, 9:00 < 18:00? " << (early < late ? "yes" : "no") << endl;
    cout << endl;

    cout << "Day of week for date1: " << date1.day_of_week() << endl;
    cout << endl;

    DataTime date5("2024-06-15");
    cout << "From string '2024-06-15': " << date5 << endl;
    cout << endl;

    DataTime date6;
    cout << "Enter your date: ";
    cin >> date6;
    cout << "You date: " << date6 << endl;
    cout << "Date: " << date6.toStringDate() << endl;
    cout << "Time: " << date6.toStringTime() << endl;
    return 0;
}