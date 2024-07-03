#include "vector.h"
#include <stdio.h>
#define TodoOk 0
#define Duplicado 1
#define vecLleno 2


void vectorCrear(Vector* vec)
{
    vec->ce=0;
}


int vectorInsertarElem(Vector* vector, int elem)
{
    if(vector->ce == TAM)
        return vecLleno;

    int posIni=0;

    while(elem > vector->vec[posIni]  &&  posIni < vector->ce)
        posIni++;

    if(posIni < vector->ce  &&  elem == vector->vec[posIni])
        return Duplicado;

    for(int i=vector->ce-1; i >= posIni; i--)
        vector->vec[i+1]=vector->vec[i];

    vector->vec[posIni] = elem;
    vector->ce++;

    return TodoOk;
}


void mostrarVector(Vector* vec)
{
    puts("Su vector es:");
    for(int i=0; i < vec->ce; i++)
        printf("%d", vec->vec[i]);
    puts("\n");
}

void resultadoDeInsert(int resInsert)
{
    if(resInsert == 0)
        puts("Todo ok hermanito\n");

    if(resInsert == 1)
        puts("Duplicado bro\n");

    if(resInsert == 2)
        puts("Te quedaste corto con el vector\n");
}


bool vectorBuscarElem(Vector* vec, int elem)
{
    for(int i = 0; i < vec->ce; i++)
        if(elem == vec->vec[i])
            return true;

    return false;
}


void existeElem(bool existe)
{
    if(existe)
        puts("Ese elemento esta\n");
    else
        puts("Ese elemento no esta\n");
}


void vectorEliminar(Vector* vec)
{
    for (int i = 0; i < TAM; i++)
        vec->vec[i] = 0;

    vec->ce=0;
}
