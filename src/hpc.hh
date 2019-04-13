#ifndef __HPC_HH__
#define __HPC_HH__

#include <vector>
#include <time.h>

using namespace std;

template <typename T>
class matrix
{
  private:
    vector<vector<T>> storage;
    size_t s = 0;
    int mx = 10;

  public:
    //__Constructors__
    matrix(size_t sz) : s(sz)
    {
        srand(time(NULL));
        storage.assign(sz, vector<T>(sz));
        for (auto &vect : storage)
            for (auto &elem : vect)
                elem = rand() % mx;
    }
    matrix(size_t sz, int value)
    {
        s = sz;
        storage.assign(sz, vector<T>(sz, value));
    }

    //__Operators__
    vector<T> &
    operator[](int i)
    {
        return storage[i];
    }
    void operator=(matrix<T> b)
    {
        for (int i = 0; i < s; i++)
            for (int j = 0; j < s; j++)
                storage[i][j] = b[i][j];
    }
    matrix<T> operator*(matrix<T> b)
    {
        matrix<T> mat(s, 0);
        for (int i = 0; i < s; i++)
            for (int j = 0; j < s; j++)
                for (int k = 0; k < s; k++)
                    mat[i][j] += storage[i][k] * b[k][j];
        return mat;
    }

    //__Methods__
    size_t size()
    {
        return s;
    }
};

#endif