#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_genericas.h"

typedef struct
{
    int dia;
    int mes;
    int anio;
}
Fecha;

typedef struct
{
    int legajo;
    char nombre[30];
    Fecha fechaIngr;
    float sueldo;
}Empleado;


int cmpInt(const void* e1, const void* e2);
void imprimirInt(const void* e);

int cmpFechas(const void* e1, const void* e2);
void imprimirFecha(const void* e);

int cmpEmpleadoLegajo(const void* e1, const void* e2);
int cmpEmpleadoNombre(const void* e1, const void* e2);
int cmpEmpleadoSueldoYNombre(const void* e1, const void* e2);
void imprimirEmpleado(const void* e);

int main()
{
    Vector vector;
    vectorCrear(&vector, sizeof(int));

//    vectorInsertarRandom(&vector, 20);

    int e;

    e = 8;
    vectorInsertarAlFinal(&vector, &e);
    e = 2;
    vectorInsertarAlFinal(&vector, &e);
    e = 7;
    vectorInsertarAlFinal(&vector, &e);
    e = 21;
    vectorInsertarAlFinal(&vector, &e);
    e = 5;
    vectorInsertarAlFinal(&vector, &e);
    e = 10;
    vectorInsertarAlFinal(&vector, &e);
    e = 9;
    vectorInsertarAlFinal(&vector, &e);
    e = 1;
    vectorInsertarAlFinal(&vector, &e);
    e = 4;
    vectorInsertarAlFinal(&vector, &e);
    e = 6;
    vectorInsertarAlFinal(&vector, &e);
    e = 3;
    vectorInsertarAlFinal(&vector, &e);

    vectorMostrar(&vector, imprimirInt);

    vectorOrdenarSeleccion(&vector, cmpInt);

    vectorMostrar(&vector, imprimirInt);

    vectorDestruir(&vector);




    // VECTOR FECHA

    Vector vectorFechas;
    vectorCrear(&vectorFechas, sizeof(Fecha));

    Fecha f;

    f.dia = 15;
    f.mes = 12;
    f.anio = 2014;
    vectorInsertarAlFinal(&vectorFechas, &f);

    f.dia = 5;
    f.mes = 3;
    f.anio = 2004;
    vectorInsertarAlFinal(&vectorFechas, &f);

    f.dia = 26;
    f.mes = 6;
    f.anio = 2024;
    vectorInsertarAlFinal(&vectorFechas, &f);

    f.dia = 3;
    f.mes = 8;
    f.anio = 2012;
    vectorInsertarAlFinal(&vectorFechas, &f);

    f.dia = 5;
    f.mes = 1;
    f.anio = 2002;
    vectorInsertarAlFinal(&vectorFechas, &f);

    f.dia = 21;
    f.mes = 7;
    f.anio = 2008;
    vectorInsertarAlFinal(&vectorFechas, &f);


    vectorMostrar(&vectorFechas, imprimirFecha);

    vectorOrdenarSeleccion(&vectorFechas, cmpFechas);

    vectorMostrar(&vectorFechas, imprimirFecha);

    vectorDestruir(&vectorFechas);




    // VECTOR EMPLEADO

    Vector vectorEmpleado;
    vectorCrear(&vectorEmpleado, sizeof(Empleado));

    Empleado emp;

    emp.legajo = 5;
    strcpy(emp.nombre, "Juan Perez");
    emp.fechaIngr.dia = 1;
    emp.fechaIngr.mes = 1,
    emp.fechaIngr.anio = 2020;
    emp.sueldo = 70000;
    vectorInsertarAlFinal(&vectorEmpleado, &emp);

    emp.legajo = 9;
    strcpy(emp.nombre, "Carlos Gomez");
    emp.fechaIngr.dia = 1;
    emp.fechaIngr.mes = 1,
    emp.fechaIngr.anio = 2020;
    emp.sueldo = 80000;
    vectorInsertarAlFinal(&vectorEmpleado, &emp);

    emp.legajo = 3;
    strcpy(emp.nombre, "Maria Lopez");
    emp.fechaIngr.dia = 1;
    emp.fechaIngr.mes = 1,
    emp.fechaIngr.anio = 2020;
    emp.sueldo = 50000;
    vectorInsertarAlFinal(&vectorEmpleado, &emp);

    emp.legajo = 7;
    strcpy(emp.nombre, "Ana Rodriguez");
    emp.fechaIngr.dia = 1;
    emp.fechaIngr.mes = 1,
    emp.fechaIngr.anio = 2020;
    emp.sueldo = 50000;
    vectorInsertarAlFinal(&vectorEmpleado, &emp);


    emp.legajo = 1;
    strcpy(emp.nombre, "Luis Martinez");
    emp.fechaIngr.dia = 1;
    emp.fechaIngr.mes = 1,
    emp.fechaIngr.anio = 2020;
    emp.sueldo = 40000;
    vectorInsertarAlFinal(&vectorEmpleado, &emp);

    vectorMostrar(&vectorEmpleado, imprimirEmpleado);

    vectorOrdenarSeleccion(&vectorEmpleado, cmpEmpleadoSueldoYNombre);

//    vectorMostrar(&vectorEmpleado, imprimirEmpleado);

    VectorIterador it;
    vectorItCrear(&it, &vectorEmpleado);

    Empleado* emplI = vectorItPrimero(&it);
    while(!vectorItFin(&it))
    {
        printf("%02d - %-15s - ", emplI->legajo, emplI->nombre);
        printf("%02d/%02d/%d", emplI->fechaIngr.dia, emplI->fechaIngr.mes, emplI->fechaIngr.anio);
        printf(" - %9.2f\n", emplI->sueldo);
        emplI = vectorItSiguiente(&it);
    }

    vectorDestruir(&vectorEmpleado);

    return 0;
}

int cmpInt(const void* e1, const void* e2)
{
    const int* i1 = e1;
    const int* i2 = e2;

    return *i1 - *i2;
}

void imprimirInt(const void* e)
{
    const int* i = e;

    printf("%02d", *i);
}

int cmpFechas(const void* e1, const void* e2)
{
    const Fecha* f1 = e1;
    const Fecha* f2 = e2;

    int comp = f1->anio - f2->anio;
    if(comp != 0)
        return comp;

    comp = f1->mes - f2->mes;
    if(comp != 0)
        return comp;

    return f1->dia - f2->dia;
}

void imprimirFecha(const void* e)
{
    const Fecha* f= e;

    printf("%02d/%02d/%d", f->dia, f->mes, f->anio);
}

int cmpEmpleadoLegajo(const void* e1, const void* e2)
{
    const Empleado* emp1 = e1;
    const Empleado* emp2 = e2;

    return emp1->legajo - emp2->legajo;
}

int cmpEmpleadoNombre(const void* e1, const void* e2)
{
    const Empleado* emp1 = e1;
    const Empleado* emp2 = e2;

    return strcmp(emp1->nombre, emp2->nombre);
}

int cmpEmpleadoSueldoYNombre(const void* e1, const void* e2)
{
    const Empleado* emp1 = e1;
    const Empleado* emp2 = e2;

    int comp = emp1->sueldo - emp2->sueldo;
    if(comp != 0)
        return comp;

    return strcmp(emp1->nombre, emp2->nombre);
}

void imprimirEmpleado(const void* e)
{
    const Empleado* emp = e;

    printf("%02d - %-15s - ", emp->legajo, emp->nombre);
    printf("%02d/%02d/%d", emp->fechaIngr.dia, emp->fechaIngr.mes, emp->fechaIngr.anio);
    printf(" - %9.2f", emp->sueldo);
}
