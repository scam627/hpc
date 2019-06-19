/*
 ███████╗████████╗██╗██╗   ██╗███████╗███╗   ██╗     ██████╗ █████╗ ██████╗ ██████╗  ██████╗ ███╗   ██╗ █████╗ 
 ██╔════╝╚══██╔══╝██║██║   ██║██╔════╝████╗  ██║    ██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔═══██╗████╗  ██║██╔══██╗
 ███████╗   ██║   ██║██║   ██║█████╗  ██╔██╗ ██║    ██║     ███████║██████╔╝██║  ██║██║   ██║██╔██╗ ██║███████║
 ╚════██║   ██║   ██║╚██╗ ██╔╝██╔══╝  ██║╚██╗██║    ██║     ██╔══██║██╔══██╗██║  ██║██║   ██║██║╚██╗██║██╔══██║
 ███████║   ██║   ██║ ╚████╔╝ ███████╗██║ ╚████║    ╚██████╗██║  ██║██║  ██║██████╔╝╚██████╔╝██║ ╚████║██║  ██║
 ╚══════╝   ╚═╝   ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝     ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝
 
                                                                PRESENTA
                       _____________________________________________________________________________________________

                            __                             _                        
                             _)      |\| _  _  _| |  _    |_| |  _  _  ._ o _|_ |_ ._ _ 
                            /__ o    | |(/_(/_(_| | (/_   | | | (_|(_) |  |  |_ | || | |
                                    _                            _|                                       

 Con este código, escrito en C++, vamos calcular pi utilizando el método de las gujas de Buffon
 
 Si quieres saber las ideas básicas de este algoritmo o no sabes como pu***s has llegado aquí y qué es este código puedes enviarme un mensaje
 al siguiente correo stiven.cardona627@gmail.com

 
 Sabemos que vamos a calcular pi a partir de la proporción entre los puntos puntos totales y los puntos aleatorios que cruzan las lineas paralelas 
 dibujadas en nuestro plano. Puesto en ecuaciones:
 
                                            2  (nº de agujas "lanzadas")
                                    pi = -----------------------------------------
                                             (nº de agujas que cruzan una linea)
 
 Pille puess: aquí debemos pensar en una manera de aleatorizar la generación de agujas (needles) de longitud l, mejor dicho dado un angulo
 al que llamaremos alpha y un centro con cordenadas cx, cy haremos una función que nos dira si nuestra aguja cruza alguna linea, lo mejor 
 es  que nuestros calculos solo los hagamos sobre el cuadrante positivo
 
 Además, no solo vamos a hacer esto una vez: se realizaran varias tandas de lanzamientos, cada una con el mismo número de agujas aleatorias 
 a lanzar. Dado que los resultados de Montecarlo no son los mismos en cada ejecución del programa (dada la naturaleza aleatoria 
 del cálculo), haremos que el código repita el método un cierto número de veces para hacer estadística con los varios pi's que nos 
 saque. Obtendremos media y desviación estándar, con lo que tendremos una estimación del error del método. En pocas palabras: tendremos 
 un pi fiable, no tan dependiente de la ejecución y con un error que nos permita acotar el valor exacto.
 
 Así nombre a cada variable:

    *   N = número de aguajas lanzadas
    *   l = largo de la aguja
    *   x = coordenada en x del centro
    *   y = coordenada en y del extremo de la aguja
    *   alpha = angulo de inclinación de la aguja
    *   c = número de agujas que cruzan una linea

*/
#include <iostream>
#include <cmath>
#include <fstream>
#include "../../src/timer.hh"

using namespace std;

const double rpi = 3.1415926535897932384626433832795;

int main(int argc, char **argv)
{
    long long N = 123456;
    N = (argc > 1) ? atoi(argv[1]) : 100;
    Timer t(N);
    double l = 1.0;

    double c = 0;

    srand((unsigned)time(0));

    double x;
    double y;

    int iter = 10;

    double pi_ar[iter];

    for (int j = 0; j < iter; j++)
    {
        for (int i = 0; i < N; i++)
        {
            x = (double)rand() / ((double)RAND_MAX * 2);

            double alpha = ((double)rand() / (double)RAND_MAX) * rpi;

            y = (l / 2.0) * sin(alpha);

            c = c + (x <= y);
        }

        pi_ar[j] = 2.0 * N / c;
        c = 0;
    }

    double pi = 0;
    double err = 0;

    for (int j = 0; j < iter; j++)
    {
        pi = pi_ar[j] / iter + pi;
    }

    for (int j = 0; j < iter; j++)
    {
        err = err + pow(pi - pi_ar[j], 2) / iter;
    }

    err = sqrt(err);

    cout.precision(15);

    cout << pi << " , " << err << " , ";

    return 0;
}