#include <iostream>
#include <fstream>
#include <chrono>
#include "moon.h"
using namespace std;

int main()
{
    DataTime date;
    cout << "Enter date (dd.MM.yyyy): ";
    cin >> date;

    if (cin.fail())
    {
        cout << "Error: invalid or non-existent date (e.g. 31.02)!" << endl;
        return 1;
    }

    int d, m, year;
    date.Julian_to_date(d, m, year);

    cout << "\nDate: " << date.toStringDate() << endl;
    string filename = getMoonFilename(year);

    // Проверка на существование файла
    ifstream test(filename.c_str());
    if (!test.is_open())
    {
        cout << "ERROR: Cannot open file " << filename << endl;
        return 1;
    }
    test.close();

    // Замеры времени и поиск
    auto start = chrono::high_resolution_clock::now();
    MoonEvents events = findMoonEvents(filename.c_str(), date);
    auto end = chrono::high_resolution_clock::now();

    if (events.found)
    {
        cout << "\nMoon Events:" << endl;
        cout << "Rise:           " << events.rise.toStringTime() << endl;
        cout << "Culmination:    " << events.culmination.toStringTime() << endl;
        cout << "Set:            " << events.set.toStringTime() << endl;
    }
    else
    {
        cout << "\nThere is no such date." << endl;
    }

    chrono::duration<double> elapsed = end - start;
    cout << "\nProgram execution time: " << elapsed.count() << " seconds." << endl;

    return 0;
}