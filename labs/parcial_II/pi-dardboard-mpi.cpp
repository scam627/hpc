/*
 ███████╗████████╗██╗██╗   ██╗███████╗███╗   ██╗     ██████╗ █████╗ ██████╗ ██████╗  ██████╗ ███╗   ██╗ █████╗ 
 ██╔════╝╚══██╔══╝██║██║   ██║██╔════╝████╗  ██║    ██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔═══██╗████╗  ██║██╔══██╗
 ███████╗   ██║   ██║██║   ██║█████╗  ██╔██╗ ██║    ██║     ███████║██████╔╝██║  ██║██║   ██║██╔██╗ ██║███████║
 ╚════██║   ██║   ██║╚██╗ ██╔╝██╔══╝  ██║╚██╗██║    ██║     ██╔══██║██╔══██╗██║  ██║██║   ██║██║╚██╗██║██╔══██║
 ███████║   ██║   ██║ ╚████╔╝ ███████╗██║ ╚████║    ╚██████╗██║  ██║██║  ██║██████╔╝╚██████╔╝██║ ╚████║██║  ██║
 ╚══════╝   ╚═╝   ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝     ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝
 
                                                                PRESENTA
                       _____________________________________________________________________________________________

                                    _                                                                  
                            /|     | \  _. ._ _| |_   _   _. ._ _|    /\  |  _   _  ._ o _|_ |_  ._ _  
                             | o   |_/ (_| | (_| |_) (_) (_| | (_|   /--\ | (_| (_) |  |  |_ | | | | | 
                                                                             _|                        

 Con este código, escrito en C++, vamos calcular pi utilizando el método que se usó para hacer ciertos cálculos en el desarrollo del proyecto Manhattan: el método
 de Montecarlo.
 
 Si quieres saber las ideas básicas de este algoritmo o no sabes como pu***s has llegado aquí y qué es este código revisa este link de
 quantum fracture
 -->  https://youtu.be/DQ5qqHukkAc  <--.

 
 Sabemos que vamos a calcular pi a partir de la proporción entre puntos aleatorios dentro de un círculo y los totales (ya que todos caen dentro del cuadrado). Puesto en ecuaciones:
 
                                            4  (nº de puntos dentro del circulo)
                                    pi = -----------------------------------------
                                                (nº de puntos "lanzados")
 
 Pille puess: en vez de medir las proporciones en un circulo entero vamos a calcularlo para un CUADRANTE de este circulo; un cuarto de él, 
 como una porción de una pizza partida en cuatro.
 Con más exactitud: tenemos un cuadrado de lado r. Dentro está inscrita tal porción del circulo, cuyo centro estaría ubicado en uno de 
 los vertices del cuadrado, que designamos con coordenadas (x=0 , y=0). Vamos a dividir el numero de puntos que caigan dentro de 
 esa porción (es decir que verifican que x^2 + y^2 < r^2) entre el numero de puntos totales lanzados.
 
 Además, no solo vamos a hacer esto una vez: se realizaran varias tandas de tiradas, cada una con el mismo número de puntos aleatorios 
 a lanzar. Dado que los resultados del dardboard algorithm  no son los mismos en cada ejecución del programa (debido a que es un metodo de montecarlo y
 posee una  naturaleza aleatoria del cálculo), haremos que el código repita el método un cierto número de veces para hacer estadística con los varios 
 pi's que nos saque. Obtendremos media y desviación estándar, con lo que tendremos una estimación del error del método. En pocas palabras: tendremos 
 un pi fiable, no tan dependiente de la ejecución y con un error que nos permita limitar el valor exacto.
 
 Así nombre cada variable:
 
   *  r     : el radio del circulo.
   *  N     : el número total de puntos a lanzar. Es un input.
   *  x     : posición del punto aleatorio en el eje X.
   *  y     : posición del punto aleatorio en el eje Y.
   *  iter  : es el número de veces que queremos que se repita internamente Montecarlo para tener una estimación del error.
   *  c     : número de puntos que han caido dentro de la porción.
   *  pi_ar : array (como un vector) de valores de pi recogidos en cada tanda de tiradas. Sus dimensiones son "iter".
   *  pi    : valor de pi obtenido como la media de los valores de "pi_ar".
   *  err   : error en el valor de pi obtenido como la desviación estándar de los valores de "pi_ar".

 
 */

#include <iostream> // Libreria para el manejo de entrada y salida de texto y otras cositas
#include <cmath>    // "cmath" es una colección de funciones matemáticas que necesito, como elevar al cuadrado y hacer la raiz cuadrada.
#include <fstream>
#include <random>
#include <mpi.h>
#include "../../src/timer.hh"

using namespace std; // Para no tener que poner "std" cada 2*3

class UniformDistribution
{
public:
    UniformDistribution() 
        : generator(),
          distribution(-1.0, 1.0)
    {
        int seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);
    }

    double sample() 
    {
        return distribution(generator);
    }
    
    UniformDistribution(const UniformDistribution& ) = delete;
    UniformDistribution& operator()(const UniformDistribution& ) = delete;
    UniformDistribution(UniformDistribution&& ) = delete;
    UniformDistribution& operator()(UniformDistribution&& ) = delete;

private:
    std::default_random_engine generator;
    
    std::uniform_real_distribution<double> distribution;
};

int main(int argc, char **argv)
{ // ¡Comencemos!

     // Primero lo primero ... la bienvenida ;)
     /* Si quieres ver algo cool quita este comentario con su respectivo par de cierre 
               cout << endl
                    << endl;
               cout << "                       ╔═╗┌┬┐┬┬  ┬┌─┐┌┐┌  ╔═╗┌─┐┬─┐┌┬┐┌─┐┌┐┌┌─┐" << endl;
               cout << "                       ╚═╗ │ │└┐┌┘├┤ │││  ║  ├─┤├┬┘ │││ ││││├─┤" << endl;
               cout << "                       ╚═╝ ┴ ┴ └┘ └─┘┘└┘  ╚═╝┴ ┴┴└──┴┘└─┘┘└┘┴ ┴" << endl;
               cout << "            ______________________________________________________________________     " << endl
                    << endl;
               cout << "                                          PRESENTA...                                  " << endl;
               cout << endl;
               cout << "╔═╗┌─┐┬  ┌─┐┬ ┬┬  ┌─┐  ┌┬┐┌─┐  ╔═╗┬       ╔╦╗┌─┐┬─┐┌┬┐┌┐ ┌─┐┌─┐┬─┐┌┬┐  ╔═╗┬  ┌─┐┌─┐┬─┐┬┌┬┐┬ ┬┌┬┐" << endl;
               cout << "║  ├─┤│  │  │ ││  │ │   ││├┤   ╠═╝│  ───   ║║├─┤├┬┘ ││├┴┐│ │├─┤├┬┘ ││  ╠═╣│  │ ┬│ │├┬┘│ │ ├─┤│││" << endl;
               cout << "╚═╝┴ ┴┴─┘└─┘└─┘┴─┘└─┘  ─┴┘└─┘  ╩  ┴       ═╩╝┴ ┴┴└──┴┘└─┘└─┘┴ ┴┴└──┴┘  ╩ ╩┴─┘└─┘└─┘┴└─┴ ┴ ┴ ┴┴ ┴" << endl;

               cout << "_____________________________________________________________________________________________" << endl
                    << endl;
               cout << "                                         ADVERTENCIA                                     " << endl;
               cout << "Si está usando este código en un compilador online, puede ser que utilizar un número excesivo" << endl;
               cout << " de dardos haga que el cálculo necesite tanto tiempo para ser computado que el compilador lo" << endl;
               cout << "               aborte automáticamente. En ese caso, pruebe un número menor." << endl;

     */
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////

     int master = 0;
     int ierr;
     int process_num;
     int process_rank;
     /* Initialize MPI. */
     ierr = MPI_Init ( &argc, &argv );
     /* Get the number of processes. */
     ierr = MPI_Comm_size ( MPI_COMM_WORLD, &process_num );
     /* Get the rank of this process. */
     ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &process_rank );

     long long N = 10000000; // NÚMERO DE PUNTOS ALEATORIOS A LANZAR. ¡ESTA ES LA BAINA QUE PODEMOS CAMBIAR PARA MEJORAR LA PRECISION DEL CALCULO!
     // N = (argc > 1) ? atoi(argv[1]) : 100;
     // cin >> N;
     Timer t(N);
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////

     // Mostramos el número por teminal:
     /* Si quieres ver algo cool quita este comentario con su respectivo par de cierre
               cout << endl
                    << "  ╔════════════════════════════════════════════════════════════════════════════════════════╗";
               cout << endl
                    << "  ║                         Número de 'dardos' a lanzar :   " << N;
               cout << endl
                    << "  ╚════════════════════════════════════════════════════════════════════════════════════════╝";
               */
     double r = 1; // RADIO DEL CÍRCULO: Podes cambiar este número si lo deseas; el tamaño de la circunferencia no afecta a pi.

     srand((unsigned)time(0)); // Aqui le estamos dando el tiempo de reloj como semilla para que nuestro PC calcule los números aleatorios
                                   // asi aseguramos que se generen números aleatorios distintos.

     double x; // Defino las coordenadas de cada punto aleatorio. No queremos guardarlas; reescribiremos estas variable.
     double y;

     // double c = 0; // Defino el número de puntos dentro del círculo (de la porción). Partimos de 0.

     int iter = 10; // iter. NÚMERO DE REPETICIONES DEL MÉTODO. Podes cambiar este número si lo deseas.
     int c = 0, c_total;
     int chunk = N / process_num;

     // double pi_ar[iter]; // Defino el arreglo que voy a llenar de los distintos pi's que obtenga.
     
     UniformDistribution distribution;
     for (int k = 0; k < N; k++) {
          x = distribution.sample(); // Generamos dos números aleatorios desde 0 a 1. Nótese que en los siguientes
          y = distribution.sample(); // lanzamientos estos números serán reescritos.

          x = x * r; // Dimensiono estos números en base a el radio. Ahora van de 0 a "r". Estas son las coordenadas
          y = y * r; // en las que ha caido un dardo.

          if (x * x + y * y < r * r)
          { // Compruebo si el dardo está o no dentro del circulo. Si es así, c aumentará en uno.
               c++;
          }
     } // FIN Segundo BUCLE

     ierr = MPI_Reduce ( &c, &c_total, 1, MPI_INT, MPI_SUM, master, MPI_COMM_WORLD );

     /* Terminate MPI. */
     ierr = MPI_Finalize ( );

     if (process_rank == 0) {
          double pi_total = (4.0 * c_total) / (N * process_num);
          cout << "PI = " << pi_total << endl;
     }

     cout << 4.0 * c / N << " , ";
     
     return 0; // Y listo cerramos la funcion principal con un return.
}
