#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED
#include "estructuras.h"
#include "constantes.h"

int solucion(int argc, char* argv[]);
int cargarEstrucImg(const char *archImagen, t_metadata* metadata);
int modPixeles(const char *archImagen, const char *archCopia, void (*funcionPixel)(t_pixel*));
void pixelesGrises(t_pixel *pixel);
void aumentarContraste(t_pixel *pixel);
void reducirContraste(t_pixel *pixel);
void aumentarAzul(t_pixel *pixel);
void aumentarVerde(t_pixel *pixel);
void aumentarRojo(t_pixel *pixel);
void comodin(t_pixel *pixel);
unsigned char ajustarContraste(unsigned char pixel, float factor_contraste);
unsigned char** crearMatriz(unsigned int filas, unsigned int columnas);
int cargarMatriz(char* filename, unsigned char** matriz, unsigned int filas, unsigned int columnas);
int imgRecortar(char* input_filename, char* output_filename, unsigned char** matriz, int filas, unsigned int columnas);
int rotarImagen(const char* archImg, const char* archRotada, unsigned char** matriz, int filas, int columnas, unsigned char** (*rotarMatriz)(unsigned char**, unsigned int, unsigned int));
int concatenar(const char* img, const char* imgDos, const char* imgConcatenada);
void cargarMatrizConcatenada(FILE* file, FILE* fileDos, unsigned char** matriz, int filas, int columnas, int filasUno, int columnasUno, int filasDos, int columnasDos);

#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
