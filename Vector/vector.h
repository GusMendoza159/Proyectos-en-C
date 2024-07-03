#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdbool.h>
#define TAM 100

typedef struct
{
    int vec[TAM];
    int ce;
}Vector;

void vectorCrear(Vector* vec);
int vectorInsertarElem(Vector* vec, int);
void mostrarVector(Vector* vec);
void resultadoDeInsert(int);
bool vectorBuscarElem(Vector* vec, int);
void existeElem(bool);
void vectorEliminar(Vector* vec);

#endif // VECTOR_H_INCLUDED
