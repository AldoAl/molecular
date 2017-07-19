#include "poblacion.h"
#include <time.h>

int main()
{
    poblacion P(10,900,0.9,0.3);
    P.cargar_cadenas("MSA_16507.txt");
    P.mostrar_poblacion();
    clock_t t;
    t = clock();
    P.ejecucion(500);
  	t = clock() - t;
  	cout << "tiempo de demora: " << (float)t/CLOCKS_PER_SEC<< endl;
    return 0;
}

