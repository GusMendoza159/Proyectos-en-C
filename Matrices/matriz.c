#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

//    unsigned char** matriz = malloc(filas * sizeof(unsigned char*));
//    if(!matriz)
//    {
//        puts("Malloc no reservo memoria!!!");
//        return NULL;
//    }
//    for (int i = 0; i < filas; i++) {
//        matriz[i] = (unsigned char*)malloc(columnas  * 3*sizeof(unsigned char));
//        if(!matriz)
//        {
//            puts("Malloc no reservo memoria!!!");
//            return NULL;
//        }
//    }
//    return matriz;

void** crearMatriz(size_t filas, size_t columnas, size_t tamElem)
{
    void** matriz = malloc(filas * sizeof(void*));

    if(!matriz)
        return NULL;

    void** ult = matriz + filas - 1;

    for(void** i = matriz; i <= ult; i++)
    {
        *i = malloc(columnas * tamElem);
        if(!i)
        {
            printf("\n gdsgds\n");
//            int filasCreadas = i - matriz;
//            liberarMatriz((int**)matriz, filasCreadas);
        }
    }

    return matriz;
}


void cargarMatriz(int** matriz, size_t filas, size_t columnas)
{
    int cont = 0;
    for(int i = 0; i < filas; i++)
        for(int j = 0; j < columnas; j++)
        {
            cont++;
            matriz[i][j]= cont;
        }
}

void liberarMatriz(int** matriz, size_t filas)
{
    for(int i = 0; i < filas; i++)
        free(matriz[i]);

    free(matriz);
}


void mostrarMatriz(int** matriz, size_t filas, size_t columnas)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            printf("% 3d ", matriz[i][j]);
        }
        puts("\n");
    }
}
