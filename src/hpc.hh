#ifndef __HPC_HH__
#define __HPC_HH__

#include <vector>

using namespace std;

template <typename T>
class matrix
{
  private:
    vector<vector<T>> storage;
    size_t s = 0;
    //pair<size_t, size_t> sz(0, 0);

  public:
    // constructors

    matrix(size_t sz)
    {
        storage.assign(sz, vector<T>(sz, 1));
        s = sz;
    }

    // operators
    vector<T> &operator[](int i) { return storage[i]; }
    void operator=(matrix<T> b)
    {
        for (int i = 0; i < s; i++)
            for (int j = 0; j < s; j++)
                storage[i][j] = b[i][j];
    }
    matrix<T> operator*(matrix<T> b)
    {
        matrix<T> mat(s);
        int ans = 0;
        for (int i = 0; i < s; i++)
            for (int j = 0; j < s; j++)
                for (int k = 0; k < s; k++)
                    mat[i][j] += storage[i][k] * b[k][j];

        return mat;
    }

    // methods

    size_t size()
    {
        return s;
    }
};

#endif