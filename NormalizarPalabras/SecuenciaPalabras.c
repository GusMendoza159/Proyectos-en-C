#include <stdio.h>
#include "cadena.h"
#include "SecuenciaPalabras.h"

void secuenciaCrear(SecuenciaPalabra* sec, const char* cadena)
{
    sec->cursor = (char*)cadena;
    sec->finSec = false;
}


bool leerPalabra(SecuenciaPalabra* sec, Palabra* pal)
{
    while(*(sec->cursor) != '\0' && !esLetra(*(sec->cursor)))
    {
        sec->cursor++;
    }

    if(*(sec->cursor) == '\0')
    {
        sec->finSec = true;
        return false;
    }

    char* actPal = pal->vec;

    while(*(sec->cursor) != '\0' && esLetra(*(sec->cursor)))
    {
        *actPal = *(sec->cursor);
        actPal++;
        sec->cursor++;
    }

    *actPal = '\0';

    return true;
}


void escribirPalabra(SecuenciaPalabra* sec, const Palabra* pal)
{
    const char* actPal = pal->vec;

    while(*actPal)
    {
        *sec->cursor = *actPal;
        actPal++;
        sec->cursor++;
    }
}


bool finSecuencia(const SecuenciaPalabra* sec)
{
    return sec->finSec;
}


void mostrarPalabra(const Palabra* pal)
{
    const char* i = pal->vec;

    while(*i != '\0')
    {
        putchar(*i);
        i++;
    }
}

void aTitulo(Palabra* pal)
{
    char* actPal = pal->vec;

    *actPal = aMayuscula(*actPal);
    actPal++;

    while(*actPal)
    {
        *actPal = aMinuscula(*actPal);
        actPal++;
    }
}


void escribirCaracter(SecuenciaPalabra* sec, char car)
{
    *sec->cursor = car;
    sec->cursor++;
}


void secuenciaCerrar(SecuenciaPalabra* sec)
{
    *sec->cursor = '\0';
}


void secuenciaReposicionar(SecuenciaPalabra* sec, int despl)
{
    sec->cursor += despl;
}
