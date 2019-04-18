#include <iostream>
#include <iomanip>
#include "../../src/hpc.hh"

using namespace std;

int main()
{
    vector<int> sizes;
    for (int i = 1; i <= 5; i++)
        sizes.push_back(100 * i);
    int n;
    cin >> n;
    //parallel_test(sizes, n);
    serial_test(sizes, n);
    return 0;
}