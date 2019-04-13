#include <iostream>
#include "../../src/hpc.hh"

using namespace std;

void show(matrix<int> &m)
{
    for (int i = 0; i < m[0].size(); i++)
    {
        for (int j = 0; j < m[0].size(); j++)
            cout << m[i][j] << " ";
        cout << "\n";
    }
}

int main()
{
    int n;
    cin >> n;
    matrix<int> a(n);
    matrix<int> b(n);
    matrix<int> c = a * b;
    return 0;
}