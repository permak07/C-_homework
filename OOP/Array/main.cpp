#include "array.h"
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;
using namespace chrono;

int main()
{
    // setlocale(LC_ALL, "Russian");
    // try
    // {
    //     Array arr(4);
    //     for (int i = 0; i < 4; i++)
    //         arr.insert(i + 1);
    //     cout << arr << endl;

    //     for (int i = 0; i < 8; i += 2)
    //         arr.insert(10 + i, i);
    //     cout << arr << endl;

    //     for (int i = 1; i < 8; i += 2)
    //         arr[i] = 20 + i;
    //     cout << arr << endl;

    //     for (int i = 6; i >= 0; i -= 3)
    //         arr.remove(i);
    //     cout << arr << endl;

    //     cout << "Trying to get the element at index 10" << endl;
    //     int x = arr[10];
    //     cout << "x = " << x << endl;
    // }
    // catch (const ArrayException &e)
    // {
    //     cerr << "Exception caught: " << e.what() << endl;
    // }
    const int k = 2;
    int n[7] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    double time_ms[7];
    int result[7];
    for (int i = 0; i < 7; i++)
    {
        auto start = high_resolution_clock::now();
        result[i] = Iosif_Flavia(n[i], k);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        time_ms[i] = duration.count() / 1000.0;

        cout << "n = " << n[i]
             << ", result = " << result[i]
             << ", time = " << time_ms[i] << " ms" << endl;
    }
    return 0;
}