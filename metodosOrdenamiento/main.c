#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"
#include "vector_ordenamiento.h"

#define TODO_MAL 2

int main()
{
    Vector miVec;
	if(!vectorCrear(&miVec))
		return TODO_MAL;

    vectorInizialicarRandom(&miVec, 10);
    mostrarVec(&miVec);


//    vectorOrdenarBurbujeo(&miVec);

//    vectorOrdenarSeleccion(&miVec);

    vectorOrdenarInsercion(&miVec);

    mostrarVec(&miVec);
    return 0;
}
