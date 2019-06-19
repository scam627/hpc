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
#include "../../src/timer.hh"

using namespace std; // Para no tener que poner "std" cada 2*3

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

     long long N; // NÚMERO DE PUNTOS ALEATORIOS A LANZAR. ¡ESTA ES LA BAINA QUE PODEMOS CAMBIAR PARA MEJORAR LA PRECISION DEL CALCULO!
     N = (argc > 1) ? atoi(argv[1]) : 100;
     //cin >> N;
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

     double c = 0; // Defino el número de puntos dentro del círculo (de la porción). Partimos de 0.

     int iter = 10; // iter. NÚMERO DE REPETICIONES DEL MÉTODO. Podes cambiar este número si lo deseas.

     double pi_ar[iter]; // Defino el arreglo que voy a llenar de los distintos pi's que obtenga.

     for (int j = 0; j < iter; j++)
     { // Primer BUCLE. Repetirá el dardboard algorithm "iter" veces.

          for (int i = 0; i < N; i++)
          { // Segundo BUCLE. En cada vuelta, lanza un dardo.

               x = (double)rand() / (double)RAND_MAX; // Generamos dos números aleatorios desde 0 a 1. Nótese que en los siguientes
               y = (double)rand() / (double)RAND_MAX; // lanzamientos estos números serán reescritos.

               x = x * r; // Dimensiono estos números en base a el radio. Ahora van de 0 a "r". Estas son las coordenadas
               y = y * r; // en las que ha caido un dardo.

               if (x * x + y * y < r * r)
               { // Compruebo si el dardo está o no dentro del circulo. Si es así, c aumentará en uno.
                    c++;
               }
          } // FIN Segundo BUCLE

          pi_ar[j] = 4 * c / N; // Calculo el pi generado en esta tanda y lo guardo en el arreglo.
          c = 0;                // Reinicio el contador de los disparos que cayeron dentro de la circunferencia.

     } // FIN Primer BUCLE

     double pi = 0; // Defino pi y el error de pi. Los inicializo a cero por el método para obtener la media y la SD.
     double err = 0;

     for (int j = 0; j < iter; j++)
     {
          pi = pi_ar[j] / iter + pi; // Hago la media de todos los pi's calculados
     }

     for (int j = 0; j < iter; j++)
     {
          err = err + pow(pi - pi_ar[j], 2) / iter; // Calculo la desviación estándar de los pi's calculados. Consulta su definición
     }                                             // para más info, pero es sumar estos términos y...

     err = sqrt(err); // ... hacer la raiz cuadrada de lo que te salga.

     cout.precision(15); // Establesco el número de digito de presicion que deseo ver en la pantalla.
     /* Si quieres ver algo cool quita este comentario con su respectivo par de cierre 
               // Mostramos los resultados en pantalla para que se los gozen :3 :

               cout << endl
                    << "  ╔════════════════════════════════════════════════════════════════════════════════════════╗";
               cout << endl
                    << "  ║                       "
                    << "Pi = " << pi << "  +/-  " << err;
               cout << endl
                    << "  ║";
               cout << endl
                    << "  ║                "
                    << "o, dicho de otra manera, el valor de pi se encuentra entre";
               cout << endl
                    << "  ║                       " << pi + err << "   y   " << pi - err;
               cout << endl
                    << "  ╚════════════════════════════════════════════════════════════════════════════════════════╝" << endl
                    << endl;
     */
     cout << pi << " , " << err << " , ";
     return 0; // Y listo cerramos la funcion principal con un return.
}
