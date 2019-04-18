#ifndef __HPC_HH__
#define __HPC_HH__

#include <vector>
#include <time.h>
#include <thread>
#include <cassert>

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

template <typename T>
void mult(matrix<T> &a, matrix<T> &b, matrix<T> &c)
{
    assert(a.size() == b.size());
    int sz = a.size();
    vector<thread> threads(sz);
    int idx = 0;
    for (int i = 0; i < sz; i++)
    {
        threads[idx++] = thread([](int i, matrix<T> &a, matrix<T> &b, matrix<T> &c) {
            int sz = a.size();
            for (int j = 0; j < sz; j++)
                for (int k = 0; k < sz; k++)
                    c[i][j] += a[i][k] * b[k][j];
        },
                                i, ref(a), ref(b), ref(c));
    }
    for (auto &t : threads)
        t.join();
}

#endif