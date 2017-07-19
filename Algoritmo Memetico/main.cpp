#include "poblacion.h"
#include <time.h>

int main()
{
    poblacion P(4,900,0.9,0.4);
    P.cargar_cadenas("MSA_16507.txt");
    P.mostrar_poblacion();
    clock_t t;
    t = clock();
    P.ejecucion(800);
  	t = clock() - t;
  	cout << "tiempo de demora: " << (float)t/CLOCKS_PER_SEC<< endl;
    return 0;
}
