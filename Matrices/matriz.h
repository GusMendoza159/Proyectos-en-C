#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void** crearMatriz(size_t filas, size_t columnas, size_t tamElem);
void cargarMatriz(int** matriz, size_t filas, size_t columnas);
void liberarMatriz(int** matriz, size_t filas);
void mostrarMatriz(int** matriz, size_t filas, size_t columnas);

#endif // MATRIZ_H_INCLUDED
