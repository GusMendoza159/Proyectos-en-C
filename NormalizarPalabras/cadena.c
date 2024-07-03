#include <stddef.h>
#include <stdio.h>
#include "SecuenciaPalabras.h"


char* normalizarCadena(char* cadNormalizada, const char* cadANormalizar)
{
    SecuenciaPalabra secLect, secEscr;

    secuenciaCrear(&secLect, cadANormalizar);
    secuenciaCrear(&secEscr, cadNormalizada);
    Palabra palabra;

    leerPalabra(&secLect,&palabra);
    while(!finSecuencia(&secLect))
    {
        aTitulo(&palabra);
        escribirPalabra(&secEscr, &palabra);
        escribirCaracter(&secEscr, ' ');
        leerPalabra(&secLect, &palabra);
    }

    secuenciaReposicionar(&secEscr, -1);

    secuenciaCerrar(&secEscr);

    return cadNormalizada;
}


bool esLetra(char car)
{
    return (car >= 'a' && car <= 'z') || (car >= 'A' && car <= 'Z');
}


char aMayuscula(char car)
{
    if(car < 'a' || car > 'z')
        return car;

    return car - ('a' - 'A');
}


char aMinuscula(char car)
{
    if(car < 'A' || car > 'Z')
        return car;

    return car + ('a' - 'A');
}
