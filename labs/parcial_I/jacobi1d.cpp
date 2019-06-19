#include <vector>
#include <iostream>
#include <math.h>
#include "../../src/timer.hh"
#include <thread>

using namespace std;

void eval(int start, int fact, double h2, vector<double> &curr, vector<double> &prev, vector<double> &f)
{
    for (int i = start; i < start + fact; ++i)
        if (i > 0)
            curr[i] = (prev[i - 1] + prev[i + 1] + h2 * f[i]) / 2;
}

void jacobi_serial(int nsweeps, int n, vector<double> &u, vector<double> f)
{
    int i, sweep;
    double h = 1.0 / n;
    double h2 = h * h;
    vector<double> utmp(n + 1);

    /* Fill boundary conditions into utmp */
    utmp[0] = u[0];
    utmp[n] = u[n];

    for (sweep = 0; sweep < nsweeps; sweep += 2)
    {
        /* Old data in u; new data in utmp */
        for (i = 1; i < n; ++i)
            utmp[i] = (u[i - 1] + u[i + 1] + h2 * f[i]) / 2;

        /* Old data in utmp; new data in u */
        for (i = 1; i < n; ++i)
            u[i] = (utmp[i - 1] + utmp[i + 1] + h2 * f[i]) / 2;
    }
}

void jacobi_parallel(int SZ, int nsweeps, int n, vector<double> &u, vector<double> f)
{
    int i, sweep;
    double h = 1.0 / n;
    double h2 = h * h;
    vector<double> utmp(n + 1);

    /* Fill boundary conditions into utmp */
    utmp[0] = u[0];
    utmp[n] = u[n];

    vector<thread> threads(SZ);

    int fact = n / SZ;

    for (sweep = 0; sweep < nsweeps; sweep += 2)
    {
        /* Old data in u; new data in utmp */
        for (int i = 0; i < SZ; ++i)
            threads[i] = std::thread(eval, i * fact, fact, h2, ref(utmp), ref(u), ref(f));
        for (auto &t : threads)
            t.join();

        /* Old data in utmp; new data in u */
        for (int i = 0; i < SZ; ++i)
            threads[i] = std::thread(eval, i * fact, fact, h2, ref(u), ref(utmp), ref(f));
        for (auto &t : threads)
            t.join();
    }
}

void write_solution(int n, vector<double> u, const char *fname)
{
    double h = 1.0 / n;
    FILE *fp = fopen(fname, "w+");
    for (int i = 0; i <= n; ++i)
        fprintf(fp, "%g %2.09g\n", i * h, u[i]);
    fclose(fp);
}

int main(int argc, char **argv)
{
    int i, n, nsteps;
    bool serial;
    double h;
    char *fname;
    n = (argc > 1) ? atoi(argv[1]) : 100;
    nsteps = (argc > 2) ? atoi(argv[2]) : 100;
    serial = (argc > 3) ? atoi(argv[3]) : false;
    fname = (argc > 4) ? argv[4] : NULL;
    h = 1.0 / n;
    vector<double> u(n + 1);
    vector<double> f(n + 1);
    for (int i = 0; i <= n; ++i)
        f[i] = i * h;
    Timer t(nsteps);
    if (serial)
        jacobi_serial(nsteps, n, u, f);
    else
        jacobi_parallel(log(nsteps), nsteps, n, u, f);
    write_solution(n, u, fname);
    cout << n << ",";
    return 0;
}