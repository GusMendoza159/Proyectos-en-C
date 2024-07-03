#include <stdio.h>
#include <stdlib.h>

#include "Fecha.h"

int main()
{

    Fecha fechaIng = ingresarFecha();
    mostrarFecha(&fechaIng);


//Suma y Resta

//    int dias = cargarDias();
//
//    Fecha fechaSuma = sumarDiasAFecha(&fechaIng, dias);
//
//    Fecha fechaResta = restarDiasAFecha(&fechaIng, dias);
//
//    mostrarFecha(&fechaResta);


//Diferencia entre fechas

//    Fecha fechaIng2 = ingresarFecha();
//
//    int difEntreF = difEntreFechas(&fechaIng, &fechaIng2);
//
//    printf("\nDiferencia de dias entre fechas: %d", difEntreF);


//Dia Del Año

//    int diaDel_Anio = diaDelAnio(&fechaIng);
//    printf("\nDia del anio: %d\n", diaDel_Anio);


//Dia del año a fecha

//    Fecha fechaDelDia = diaDelAnioAFecha(diaDel_Anio, fechaIng.anio);
//    mostrarFecha(&fechaDelDia);


//Dia de La Semana

//    int diaDeSemana = diaDeLaSemana(&fechaIng);
//    printf("\nDia de la semana: %d", diaDeSemana);

    return 0;
}
