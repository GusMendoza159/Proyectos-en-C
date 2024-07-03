#include <stdio.h>
#include <stdlib.h>

#include "empleados.h"

int main(int argc, const char* argv[])
{
    if(argc - 1 != CANT_ARG)
    {
        puts("hellow my argc\n");
        return ERR_ARG;
    }

    int ret = generarArchEmpleados(argv[EMPL_ARCH]);
//    printf("return de generar arch = %d\n", ret);

    ret = actualizarSueldos(argv[EMPL_ARCH], 100);
//    printf("return de actualizar sueldos = %d\n", ret);

    puts("ARCHIVO EMPLEADOS:\n");
    ret = mostrarArchivoEmpleados(argv[EMPL_ARCH]);
//    printf("return de mostrar arch = %d\n", ret);

    ret = generarIndiceEmpleados(argv[EMPL_ARCH], argv[IDX_ARCH]);
//    printf("return de generar indice = %d\n", ret);

    puts("ARCHIVO INDICE:\n");
    ret = mostrarIndice(argv[IDX_ARCH]);
//    printf("return de mostrar indice = %d\n", ret);

    return 0;
}
