#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <stdbool.h>

// TDA: Tipo de Dato Abstracto

typedef struct
{
    int dia;
    int mes;
    int anio;
}
Fecha;

// Primitivas

Fecha ingresarFecha();
bool esFechaValida(const Fecha* f);
bool esFechaValida(const Fecha* f);
void mostrarFecha(const Fecha* f);
Fecha sumarDiasAFecha(const Fecha* f, int dias);
Fecha restarDiasAFecha(const Fecha* f, int dias);
int difEntreFechas(const Fecha* f1, const Fecha* f2);
int diaDelAnio(const Fecha* f);
Fecha diaDelAnioAFecha(int diaDelAnio, int anio);
int diaDeLaSemana(const Fecha* f);

int cargarDias();

#endif // FECHA_H_INCLUDED
