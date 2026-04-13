#include <iostream>
#include <cmath>
using namespace std;

int n;
int redx[10], redy[10];
int bluex[10], bluey[10];
bool used[10];
double min_sum = 1000000.0;

void func(int k, double current_sum);

int main(void)
{
    cout << "Enter n dots: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter x and y " << i + 1 << " red dots: ";
        cin >> redx[i] >> redy[i];
        cout << "Enter x and y " << i + 1 << " blue dots: ";
        cin >> bluex[i] >> bluey[i];
        used[i] = false;
    }
    func(0, 0.0);

    cout << "Minimum sum: " << min_sum << endl;
    return 0;
}

void func(int k, double current_sum)
{
    if (current_sum >= min_sum)
        return;
    if (k == n)
    {
        min_sum = current_sum;
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        if (!used[i])
        {
            used[i] = true;
            double dist = sqrt(pow(redx[k] - bluex[i], 2) + pow(redy[k] - bluey[i], 2));
            func(k + 1, current_sum + dist);
            used[i] = false;
        }
    }
}