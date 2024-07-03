#ifndef EMPLEADOS_H_INCLUDED
#define EMPLEADOS_H_INCLUDED

#include <stdio.h>

#define CANT_ARG 2
#define EMPL_ARCH 1
#define IDX_ARCH 2

#define TODO_OK 0
#define ERR_ARG 1
#define ERR_ARCH 2

#define CANT_EMPL 8
#define TAM_NOMBRE 51

typedef struct
{
    int legajo;
    char nombre[TAM_NOMBRE];
    float sueldo;
}Empleado;

typedef struct
{
    int leg;
    long nroReg;
}EmpleadoIdx;

int generarArchEmpleados(const char* archEmpleado);
int mostrarArchivoEmpleados(const char* archEmpleado);
int actualizarSueldos(const char* archEmpleados, float porc);
int generarIndiceEmpleados(const char* archEmpleados, const char* archEmplIdx);
int mostrarIndice(const char* archEmplIdx);

#endif // EMPLEADOS_H_INCLUDED
