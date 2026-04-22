#ifndef MOON_H
#define MOON_H
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include "datatime.h"
using namespace std;

class MoonRecord
{
    DataTime dateTime;
    double T;
    double R;
    double El;
    double Az;
    double FI;
    double LG;

public:
    DataTime getDateTime() const { return dateTime; }
    double getEl() const { return El; }

    friend istream &operator>>(istream &in, MoonRecord &record);
    friend ostream &operator<<(ostream &out, const MoonRecord &record);
};

string getMoonFilename(int year);

struct MoonEvents
{
    DataTime rise;
    DataTime culmination;
    DataTime set;
    bool found;
};

MoonEvents findMoonEvents(const char *fileName, const DataTime &searchDate);

#endif