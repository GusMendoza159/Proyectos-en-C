#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "vector.h"

bool vectorCrear(Vector* vector)
{
	vector->vec = malloc(10*sizeof(int)); //ingreso la memoria que quiero reservar por parametro

	//pregunta si reserva en memoria
	if(!vector->vec)
		return false;

	vector->ce = 0;
	vector->cap = 10;

	return true;
}


void vectorInizialicarRandom(Vector* vector, int ce)
{
    vector->ce = ce;

    vector->cap = ce;

    vector->vec = realloc(vector->vec, ce*sizeof(int));

    srand(time(NULL));

    int* ult = vector->vec + vector->ce-1;

    for(int* i = vector->vec; i <= ult; i++)
        *i = rand()%10;

//    int* i = vector->vec;
//    *i = 3;
//    i++;
//    *i = 1;
//    i++;
//    *i = 5;
//    i++;
//    *i = 2;
//    i++;
//    *i = 4;
//    i++;
//    *i = 7;
//    i++;
//    *i = 6;
//    i++;
//    *i = 10;
//    i++;
//    *i = 9;
//    i++;
//    *i = 8;
}


void mostrarVec(Vector* vector)
{
	int* ult = vector->vec + vector->ce-1;

	for(int* i = vector->vec; i <= ult; i++)
        printf("%d", *i);

    puts("\n");
}
