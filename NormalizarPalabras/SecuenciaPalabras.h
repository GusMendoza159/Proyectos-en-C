#ifndef SECUENCIAPALABRAS_H_INCLUDED
#define SECUENCIAPALABRAS_H_INCLUDED

#include <stdbool.h>

#define TAM_PAL 101

typedef struct
{
    char* cursor;
    bool finSec;
}
SecuenciaPalabra;

typedef struct
{
    char vec[TAM_PAL];
}
Palabra;

void secuenciaCrear(SecuenciaPalabra* sec, const char* cadena);
void escribirPalabra(SecuenciaPalabra* sec, const Palabra* pal);
bool leerPalabra(SecuenciaPalabra* sec, Palabra* pal);
bool finSecuencia(const SecuenciaPalabra* sec);
void mostrarPalabra(const Palabra* pal);
void aTitulo(Palabra* pal);
void escribirCaracter(SecuenciaPalabra* sec, char car);
void secuenciaCerrar(SecuenciaPalabra* sec);
void secuenciaReposicionar(SecuenciaPalabra* sec, int despl);

#endif // SECUENCIAPALABRAS_H_INCLUDED
