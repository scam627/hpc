#include <iostream>
#include "src/hpc.hh"

using namespace std;

int main()
{
    matrix<int> a(3);
    matrix<int> b(3);
    matrix<int> c = a * b;
    matrix<int> d(3, 0);
    mult(a, b, d);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << c[i][j] << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << d[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}