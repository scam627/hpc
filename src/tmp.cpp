#include <bits/stdc++.h>
#include "hpc.hh"

using namespace std;

int main()
{
    matrix<int> a(2);
    matrix<int> b(2);
    matrix<int> c = a * b;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << c[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}