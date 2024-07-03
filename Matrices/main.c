#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main()
{
    int** matriz = (int**)crearMatriz(4, 4, sizeof(int));

    cargarMatriz(matriz, 4, 4);

    mostrarMatriz(matriz, 4, 4);

    liberarMatriz(matriz, 4);

    return 0;
}
