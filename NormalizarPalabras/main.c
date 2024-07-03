#include <stdio.h>
#include <stdlib.h>
#include "cadena.h"

#include <string.h>
//int cantChar = strlen(const char* cad); devuelve cantidad de caracteres
//char* cadCopia = strcpy(char* cadDest, const char* cad); copia la cadena
//char* posSubCad = strstr(const char* cad, const char* subCad); devuelve la posición de donde empieza la subcadena encontrada
//char* strcat(char* cad1, const char* sub2); concatena en la primera cadena lo de la segunda

#include <ctype.h>
//toupper() pasa a mayuscula
//tolower() pasa a minuscula


int main()
{
    char cadANormalizar[] = "!#$&$#% esTA&$%(%$ES%#$% unA!#$&caDEna%&(/$A &&%NorMALIZAR&%$&";
    char cadNormalizada[101];

    printf("%s\n", normalizarCadena(cadNormalizada, cadANormalizar));
    return 0;
}
