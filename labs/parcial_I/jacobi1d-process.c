#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <sys/mman.h>
#include "timing.h"

// #include "../../src/timer.hh"

double *u, *utmp, *f;

/* --
 * Do nsweeps sweeps of Jacobi iteration on a 1D Poisson problem
 * 
 *    -u'' = f
 *
 * discretized by n+1 equally spaced mesh points on [0,1].
 * u is subject to Dirichlet boundary conditions specified in
 * the u[0] and u[n] entries of the initial vector.
 */

void process(int init, int fact, int h2, int n)
{
    int mmin = (n - 1 < init + fact ? n - 1 : init + fact);
    for (int i = init; i < mmin; i++)
    {
        if (i > 0)
        {
            utmp[i] = (u[i - 1] + u[i + 1] + h2 * f[i]) / 2;
        }
    }
}

void jacobi(int npr, int nsweeps, int n)
{
    int i, sweep;
    double h = 1.0 / n;
    double h2 = h * h;
    utmp = (double *)mmap(NULL, sizeof(double) * (n + 1), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    /* Fill boundary conditions into utmp */
    utmp[0] = u[0];
    utmp[n] = u[n];

    int fact = n / npr + n % npr;
    pid_t pid[npr];

    for (sweep = 0; sweep < nsweeps; sweep += 2)
    {

        int status[npr];
        /* Old data in u; new data in utmp */
        for (i = 0; i < npr; ++i)
        {
            if ((pid[i] = fork()) == 0)
            {
                process(i * fact, fact, h2, n);
                exit(0);
            }
            else if (pid[i] < 0)
            {
                printf("No se pudo crear el proceso\n");
                exit(0);
            }
        }
        for (int i = 0; i < npr; i++)
        {
            waitpid(pid[i], &status[i], 0);
        }

        /* Old data in utmp; new data in u */
        for (i = 1; i < n; ++i)
            u[i] = (utmp[i - 1] + utmp[i + 1] + h2 * f[i]) / 2;
    }
}

void write_solution(int n, const char *fname)
{
    int i;
    double h = 1.0 / n;
    FILE *fp = fopen(fname, "w+");
    for (i = 0; i <= n; ++i)
        fprintf(fp, "%g %g\n", i * h, u[i]);
    fclose(fp);
}

int main(int argc, char **argv)
{
    int i;
    int n, nsteps, npr;
    double h;
    char *fname;
    timing_t tstart, tend;

    /* Process arguments */
    n = (argc > 1) ? atoi(argv[1]) : 100;
    nsteps = (argc > 2) ? atoi(argv[2]) : 500;
    fname = (argc > 3) ? argv[3] : NULL;
    h = 1.0 / n;

    /* Allocate and initialize arrays */
    u = (double *)mmap(NULL, sizeof(double) * (n + 1), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    f = (double *)mmap(NULL, sizeof(double) * (n + 1), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    memset(u, 0, (n + 1) * sizeof(double));
    for (i = 0; i <= n; ++i)
        f[i] = i * h;

    /* Run the solver */
    get_time(&tstart);
    jacobi(log(nsteps), nsteps, n);
    get_time(&tend);

    /* Run the solver */
    printf("%d"
           ",%d"
           ",%Lg\n",
           n, nsteps, timespec_diff(tstart, tend));

    /* Write the results */
    if (fname)
        write_solution(n, fname);

    //free(f);
    //free(u);
    return 0;
}
