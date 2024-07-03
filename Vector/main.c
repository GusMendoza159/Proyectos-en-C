#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"

int main()
{
    Vector unVec = {{1, 2, 3, 4, 6, 7}, 6};
//    vectorCrear(&unVec);


    int resInsert = vectorInsertarElem(&unVec, 5);
    resultadoDeInsert(resInsert);

    bool existe = vectorBuscarElem(&unVec, 7);
    existeElem(existe);

    mostrarVector(&unVec);

    vectorEliminar(&unVec);

    return 0;
}

//eliminar:
//    {
//        por valor
//        por posición
//        primero ultimo
//        duplicado: orde, desorde
//    }
//buscar: ord, desord
