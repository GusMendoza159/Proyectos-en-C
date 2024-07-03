#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdbool.h>

typedef struct
{
	int* vec;
	int ce;
	int cap;
}
Vector;

bool vectorCrear(Vector* vector);
void vectorInizialicarRandom(Vector* vec, int ce);
void mostrarVec(Vector* vector);

#endif // VECTOR_H_INCLUDED
