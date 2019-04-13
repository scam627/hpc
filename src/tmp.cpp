#include <iostream>
#include "hpc.hh"

using namespace std;

int main()
{
    matrix<int> a(3);
    matrix<int> b(3);
    matrix<int> c = a * b;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << c[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}