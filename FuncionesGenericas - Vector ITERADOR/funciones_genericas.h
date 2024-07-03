#ifndef FUNCIONES_GENERICAS_H_INCLUDED
#define FUNCIONES_GENERICAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <time.h>

#define CAP_INI 10
#define FACTOR_OCUP 0.25
#define FACTOR_DECR 0.5

#define TODO_OK 0
#define SIN_MEM 1
#define DUPLICADO 2

typedef struct
{
    void* vec;
    size_t ce;
    size_t cap;
    size_t tamElem;
}Vector;

typedef struct
{
    void* primero;
    void* ultimo;
    void* actual;
    size_t tamElem;
}VectorIterador;

typedef int (*Cmp)(const void* e1, const void* e2);
typedef void (*Imprimir)(const void* e);

bool vectorCrear(Vector* vector, size_t tamElem);
int vectorInsertarAlFinal(Vector* vector, const void* elem);
int vectorOrdBuscar(const Vector* vector, void* elem, Cmp cmp);
void vectorOrdenarSeleccion(Vector* vector, Cmp cmp);
void vectorOrdenarSeleccionV2(Vector* vector, Cmp cmp);
void intercambiar(void* a, void* b, size_t tamElem);
int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp);
void vectorVaciar(Vector* vector);
void vectorDestruir(Vector* vector);
void vectorMostrar(Vector* vector, Imprimir imprimir);

void vectorItCrear(VectorIterador* it, Vector* vec);
void* vectorItPrimero(VectorIterador* it);
void* vectorItSiguiente(VectorIterador* it);
bool vectorItFin(VectorIterador* it);

#endif // FUNCIONES_GENERICAS_H_INCLUDED
