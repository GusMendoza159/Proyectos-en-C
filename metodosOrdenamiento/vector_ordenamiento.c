#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector_ordenamiento.h"

void intercambiar(int* a, int* b);
int* buscarMenor(int* ini, int* fin);

void vectorOrdenarBurbujeo(Vector* vector)
{
    int* ult = vector->vec + vector->ce - 1;

    for(int i = 1, *limJ = ult-1; i < vector->ce; i++, limJ--)
    {
        for(int *j = vector->vec; j <= limJ; j++)
        {
            if(*j > *(j+1))
            {
                intercambiar(j, j+1);
            }
        }
    }
}

void intercambiar(int* a, int* b)
{
    int aTemp = *a;
    *a = *b;
    *b = aTemp;
}


void vectorOrdenarSeleccion(Vector* vector)
{
    int* ult = vector->vec + vector->ce - 1;
    int* menor;

    for(int* i = vector->vec; i < ult; i++)
    {
        menor = buscarMenor(i, ult);
        intercambiar(menor, i);
    }
}

int* buscarMenor(int* ini, int* fin)
{
   int* menor = ini;

   for(int* j = ini + 1; j <= fin; j++)
   {
       if(*j < *menor)
       {
           menor = j;
       }
   }

   return menor;
}


void vectorOrdenarInsercion(Vector* vector)
{
    int* ult = vector->vec + vector->ce -1;
    int* j;
    int elemAInsert;

    for(int* i = vector->vec; i <= ult; i++)
    {
        j = i - 1;
        elemAInsert = *i;

        while(elemAInsert < *j && j >= vector->vec)
        {
            *(j+1) = *j;
            j--;
        }
        *(j+1) = elemAInsert;
    }
}

