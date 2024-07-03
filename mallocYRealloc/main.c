#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TODO_MAL 1
#define SIN_MEM 1
#define DUPLICADO 1
#define TODO_OK 0

typedef struct
{
	int* vec;
	int ce;
	int cap;
}
Vector;

bool vectorCrear(Vector* vector);
int vectorOrdInsertar(Vector* vector, int elem);
bool vectorOrdEliminarElem(Vector* vector, int elem);
void inicializarVec(Vector* vector);
void mostrarVec(Vector* vector);

int main()
{
	Vector miVec;
	if(!vectorCrear(&miVec))
		return TODO_MAL;

    inicializarVec(&miVec);

    vectorOrdInsertar(&miVec, 6);
    vectorOrdInsertar(&miVec, 8);
    vectorOrdEliminarElem(&miVec, 1);

    mostrarVec(&miVec);

    return 0;
}

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

int vectorOrdInsertar(Vector* vector, int elem)
{
	if(vector->ce == vector->cap) //preguntamos si "cantidad de elementos" es = a "capacidad"
	{
		int nCap = vector->cap*1.5; //incrementamos la capacidad
		int* nVec = realloc(vector->vec, nCap*sizeof(int)); //creamos un nuevo vector con la nueva capacidad

		if(!nVec) //pregunta si hay espacio en la memoria
			return SIN_MEM;

		vector->vec = nVec;
		vector->cap = nCap;
	}
	int* posIns = vector->vec;
	int* ult = vector->vec + vector->ce-1;

	while(posIns <= ult && elem > *posIns) //desreferenciamos posIns para estudiar el contenido
		posIns++;

	if(posIns <= ult && *posIns == elem)
		return DUPLICADO;

	for(int* i = ult; i >= posIns; i--) //corre los elementos para ingresar el nuevo
		*(i+1) = *i;

	*posIns = elem;
	vector->ce++;

	return TODO_OK;
}

bool vectorOrdEliminarElem(Vector* vector, int elem)
{
	int* posElim = vector->vec;
	int* ult = vector->vec + vector->ce-1;

	while(posElim <= ult && elem > *posElim) //buscamos el elemento a eliminar
		posElim++;

	if(posElim > ult || elem != *posElim) //aseguro que el elemento sea igual
		return false;

	for(int *i=posElim; i < ult; i++) //elimina el elemento usando el puntero ult
		*i=*(i+1);

	vector->ce--;

	if(vector->cap >= vector->ce*4) //reducir vector
	{
		vector->cap/=2;
		vector->vec = realloc(vector->vec, vector->cap*sizeof(int));
	}

	return TODO_OK;
}


void inicializarVec(Vector* vector)
{
    vector->ce = 6;

    int valores[] = {1, 2, 3, 4, 5, 7};

    int* ult = vector->vec + vector->ce-1;

    int j = 0;

    for(int* i = vector->vec; i <= ult; i++)
    {
        *i = valores[j];
        j++;
    }
}


void mostrarVec(Vector* vector)
{
	int* ult = vector->vec + vector->ce-1;

	for(int* i = vector->vec; i <= ult; i++)
        printf("%d", *i);
}
