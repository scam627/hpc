#include <iostream>
#include <iomanip>
#include "../../src/hpc.hh"

using namespace std;

int main()
{
    vector<int> sizes;
    int n, mx;
    bool state = false;
    cin >> n >> mx;
    for (int i = 1; i <= mx; i++)
        sizes.push_back(100 * i);
    if (state)
        parallel_test(sizes, n);
    else
        serial_test(sizes, n);
    return 0;
}