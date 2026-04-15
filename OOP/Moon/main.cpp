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

    string dateStr = date.toStringDateOnly();
    int year = stoi(dateStr.substr(0, 4));

    cout << "\nDate: " << date.toStringDate() << endl;
    string filename = getMoonFilename(year);
    ifstream test(filename.c_str());
    if (!test.is_open())
    {
        cout << "ERROR: Cannot open file " << filename << endl;
        return 1;
    }
    cout << "Opening file: " << filename << endl;

    auto start = chrono::high_resolution_clock::now();
    MoonEvents events = findMoonEvents(filename.c_str(), date);

    if (events.found)
    {
        cout << "\nMoon Events:" << endl;
        cout << "Rise:           " << events.rise.toStringTime() << endl;
        cout << "Culmination:    " << events.culmination.toStringTime() << endl;
        cout << "Set:            " << events.set.toStringTime() << endl;
    }
    else
        cout << "\nCould not find all moon events for this date." << endl;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "\nProgram execution time: " << elapsed.count() << " seconds." << endl;

    return 0;
}