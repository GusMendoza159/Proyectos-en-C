#include <stdio.h>
#include "Fecha.h"

int cantDiasMes(int mes, int anio);
bool esBisiesto(int anio);

Fecha ingresarFecha()
{
    Fecha fecha;
    puts("Ingrese una fecha (D/M/A):");
    scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);

    while(!esFechaValida(&fecha))
    {
        puts("Fecha invalida. Ingrese nuevamente (D/M/A)");
        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
    }

    return fecha;
}


bool esFechaValida(const Fecha* f)
{
    if(f->anio<1601)
        return false;

    if(f->mes<1 || f->mes>12)
        return false;

    if(f->dia<1 || f->dia>cantDiasMes(f->mes, f->anio))
        return false;

    return true;
}


int cantDiasMes(int mes, int anio)
{
    int cdm [13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(mes == 2 && esBisiesto(anio))
        return 29;

    return cdm[mes];
}


bool esBisiesto(int anio)
{
    return anio % 2 == 0 && (anio % 100 != 0 || anio % 400 == 0);
}


void mostrarFecha(const Fecha* f)
{
    printf("\n%02d/%02d/%d\n", f->dia, f->mes, f->anio);
}


Fecha sumarDiasAFecha(const Fecha* f, int dias)
{
    Fecha fsuma = *f;
    fsuma.dia += dias;
    while(fsuma.dia > cantDiasMes(fsuma.mes, fsuma.anio))
    {
        fsuma.dia -= cantDiasMes(fsuma.mes, fsuma.anio);
        if (fsuma.mes == 12)
        {
            fsuma.mes = 1;
            fsuma.anio ++;
        }
        else
        {
            fsuma.mes ++;
        }
    }
    puts("\nFecha Suma :");
    return fsuma;
}

 int cargarDias()
 {
     int dias;
     puts("\nIngrese una cantidad de dias");
     scanf("%d", &dias);
     return dias;
 }


 Fecha restarDiasAFecha(const Fecha* f, int dias)
 {
    Fecha fresta = *f;
    fresta.dia -= dias;
    while(fresta.dia <= 0)
    {
        fresta.dia += cantDiasMes(fresta.mes, fresta.anio);
        fresta.mes --;
        if (fresta.mes == 0)
        {
            fresta.mes = 12;
            fresta.anio --;
        }
    }
    puts("\nFecha Resta :");
    return fresta;
}


int difEntreFechas(const Fecha* f1, const Fecha* f2)
{
    int i, difEnDias;

    int diasF1 = f1->dia;
    for(i=1; i < f1->mes; i++)
        diasF1 += cantDiasMes(i, f1->anio);
    if(esBisiesto(f1->anio))
        diasF1 += 366;
    else
        diasF1 += 365;

    printf("\ndiasfechauno: %d", diasF1);

    int diasF2 = f2->dia;
    for(i=1; i < f2->mes; i++)
        diasF2 += cantDiasMes(i, f2->anio);
    if(esBisiesto(f2->anio))
        diasF2 += 366;
    else
        diasF2 += 365;

    printf("\ndiasfechados: %d", diasF2);


    if(diasF1 >= diasF2)
        difEnDias = diasF1 - diasF2;
    else
        difEnDias = diasF2 - diasF1;

    return difEnDias;
}


int diaDelAnio(const Fecha* f)
{
    int i, diaAnio = f->dia;
    for(i=1; i < f->mes; i++)
        diaAnio += cantDiasMes(i, f->anio);
    return diaAnio;
}


Fecha diaDelAnioAFecha(int diaDelAnio, int anio)
{
    Fecha fechaDelDia;
    fechaDelDia.dia = 1;
    fechaDelDia.mes = 1;
    fechaDelDia.anio = anio;

    int diasEnMes = cantDiasMes(fechaDelDia.mes, anio);

    while(diaDelAnio > diasEnMes)
    {
        diaDelAnio -= cantDiasMes(fechaDelDia.mes, anio);
        fechaDelDia.mes ++;
    }
    fechaDelDia.dia = diaDelAnio;

    return fechaDelDia;
}


int diaDeLaSemana(const Fecha* f)
{
    int diaDel_Anio = diaDelAnio(f);
    while(diaDel_Anio > 7)
    {
        diaDel_Anio -= 7;
    }
    return diaDel_Anio;
}
