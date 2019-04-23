#include <chrono>
#include <functional>
#include <iostream>
#include <iomanip>

using namespace std;

class Timer
{
  private:
    chrono::high_resolution_clock::time_point start;
    int name;

  public:
    Timer(int n)
        : start(chrono::high_resolution_clock::now()), name(n) {}
    ~Timer(void)
    {
        auto end = chrono::high_resolution_clock::now();
        auto duration =
            chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        cout << name << " " << setprecision(6) << fixed<< duration * 1.0 / 1.0e9 << "\n";
    }
};