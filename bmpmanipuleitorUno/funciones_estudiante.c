/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Ayala
    Nombre: Federico
    DNI: 43729037
    Entrega: Si
    -----------------
    Apellido: Mendoza
    Nombre: Gustavo
    DNI: 41691972
    Entrega: Si
*/
#include "funciones_estudiante.h"
#include "estructuras.h"
#include "constantes.h"

unsigned char ajustarContraste(unsigned char pixel, float factor_contraste);
unsigned char** crearMatriz(unsigned int filas, unsigned int columnas);
int cargarMatriz(char* filename, unsigned char** matriz, unsigned int filas, unsigned int columnas);
void liberarMatriz(unsigned char** matriz, unsigned int fila);
unsigned char** rotarMatrizDerecha(unsigned char** matriz, unsigned int filas, unsigned int columnas);
unsigned char** rotarMatrizIzquierda(unsigned char** matriz, unsigned int filas, unsigned int columnas);



int solucion(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Distinto de ARGC!!!\n\n");
        return ARCHIVO_NO_ENCONTRADO;
    }

    char* archivoImagen = argv[argc - 2];
    char* archivoDos = argv[argc - 1];

    // CARGA DE LA ESTRUCTURA METADATA
    t_metadata metadata;
    int result = cargarEstrucImg(archivoImagen, &metadata);
    if (result != TODO_OK)
        return ARCHIVO_NO_ENCONTRADO;

    // CREACION Y CARGA DE LA MATRIZ
    unsigned char** matriz = crearMatriz(metadata.alto, metadata.ancho);
    if (!matriz)
        return MATRIZ_NO_CREADA;

    result = cargarMatriz(archivoImagen, matriz, metadata.alto, metadata.ancho);
    if (result != TODO_OK) {
        liberarMatriz(matriz, metadata.alto);
        return ARCHIVO_NO_ENCONTRADO;
    }

    // CREACION DE LAS IMAGENES

    char* archivoSalida = NULL;

    for (int i = 1; i < argc - 2; i++) {
        char* comando = argv[i];

        if (strcmp(comando, "--escala-de-grises") == 0) {
            archivoSalida = "ImgGris.bmp";
            result = modPixeles(archivoImagen, archivoSalida, pixelesGrises);
            if(result != TODO_OK)
            {
                puts("ARCHIVO NO ENCONTRADO");
                return ARCHIVO_NO_ENCONTRADO;
            }

        } else if (strcmp(comando, "--aumentar-contraste") == 0) {
            archivoSalida = "ImgAumentarContraste.bmp";
            result = modPixeles(archivoImagen, archivoSalida, aumentarContraste);
            if(result != TODO_OK)
            {
                puts("ARCHIVO NO ENCONTRADO");
                return ARCHIVO_NO_ENCONTRADO;
            }

        } else if (strcmp(comando, "--reducir-contraste") == 0) {
            archivoSalida = "ImgReducirContraste.bmp";
            result = modPixeles(archivoImagen, archivoSalida, reducirContraste);
            if(result != TODO_OK)
            {
                puts("ARCHIVO NO ENCONTRADO");
                return ARCHIVO_NO_ENCONTRADO;
            }

        } else if (strcmp(comando, "--tonalidad-azul") == 0) {
            archivoSalida = "ImgAzul.bmp";
            result = modPixeles(archivoImagen, archivoSalida, aumentarAzul);
            if(result != TODO_OK)
            {
                puts("ARCHIVO NO ENCONTRADO");
                return ARCHIVO_NO_ENCONTRADO;
            }

        } else if (strcmp(comando, "--tonalidad-verde") == 0) {
            archivoSalida = "ImgVerde.bmp";
            result = modPixeles(archivoImagen, archivoSalida, aumentarVerde);
            if(result != TODO_OK)
            {
                puts("ARCHIVO NO ENCONTRADO");
                return ARCHIVO_NO_ENCONTRADO;
            }

        } else if (strcmp(comando, "--tonalidad-roja") == 0) {
            archivoSalida = "ImgRojo.bmp";
            result = modPixeles(archivoImagen, archivoSalida, aumentarRojo);
            if(result != TODO_OK)
            {
                puts("ARCHIVO NO ENCONTRADO");
                return ARCHIVO_NO_ENCONTRADO;
            }

        } else if (strcmp(comando, "--recortar") == 0) {
            archivoSalida = "ImgRecortada.bmp";
            result = imgRecortar(archivoImagen, archivoSalida, matriz, metadata.alto, metadata.ancho);
            if(result != TODO_OK)
            {
                puts("ARCHIVO NO ENCONTRADO");
                return ARCHIVO_NO_ENCONTRADO;
            }

        } else if (strcmp(comando, "--rotar-izquierda") == 0) {
            archivoSalida = "ImgRotarIzquierda.bmp";
            result = rotarImagen(archivoImagen, archivoSalida, matriz, metadata.alto, metadata.ancho, rotarMatrizIzquierda);
            if(result != TODO_OK)
            {
                puts("ARCHIVO NO ENCONTRADO");
                return ARCHIVO_NO_ENCONTRADO;
            }

        } else if (strcmp(comando, "--rotar-derecha") == 0) {
            archivoSalida = "ImgRotarDerecha.bmp";
            result = rotarImagen(archivoImagen, archivoSalida, matriz, metadata.alto, metadata.ancho, rotarMatrizDerecha);
            if(result != TODO_OK)
            {
                puts("ARCHIVO NO ENCONTRADO");
                return ARCHIVO_NO_ENCONTRADO;
            }

        } else if (strcmp(comando, "--comodin") == 0) {
            archivoSalida = "ImgComodin.bmp";
            result = modPixeles(archivoImagen, archivoSalida, comodin);
            if(result != TODO_OK)
            {
                puts("ARCHIVO NO ENCONTRADO");
                return ARCHIVO_NO_ENCONTRADO;
            }

        } else if (strcmp(comando, "--concatenar") == 0){
            archivoSalida = "ImgConcatenada.bmp";
            result = concatenar(archivoImagen, archivoDos, archivoSalida);
            if(result != TODO_OK)
            {
                puts("ARCHIVO NO ENCONTRADO");
                return ARCHIVO_NO_ENCONTRADO;
            }

        } else {
            printf("Comando no reconocido: %s\n", comando);
            printf("Comandos válidos: \n--escala-de-grises\n--aumentar-contraste\n--tonalidad-azul\n--tonalidad-verde\n--tonalidad-roja\n--recortar\n--rotar-derecha\n--rotar-izquierda\n--comodin\n");
            printf("Error al ejecutar el comando: %s\n", comando);
            return ARCHIVO_NO_ENCONTRADO;
        }
    }

    liberarMatriz(matriz, metadata.alto);

    return result;
}

int cargarEstrucImg(const char *archImagen, t_metadata* metadata) {
    FILE *file = fopen(archImagen, "rb");
    if (!file) {
        printf("No abrio la imagen");
        return ARCHIVO_NO_ENCONTRADO;
    }

    fseek(file, 2, SEEK_SET);

    fread(&metadata->tamArchivo, sizeof(unsigned int), 1, file);

    fseek(file, 8, SEEK_CUR);

    fread(&metadata->tamEncabezado, sizeof(unsigned int), 1, file);

    fread(&metadata->ancho, sizeof(unsigned int), 1, file);

    fread(&metadata->alto, sizeof(unsigned int), 1, file);

    fseek(file, 2, SEEK_CUR);

    fread(&metadata->profundidad, sizeof(unsigned short), 1, file);

    printf("Tamaño del archivo: %u bytes\n", metadata->tamArchivo);
    printf("Tamaño del encabezado: %u bytes\n", metadata->tamEncabezado);
    printf("Ancho de la imagen: %u píxeles\n", metadata->ancho);
    printf("Alto de la imagen: %u píxeles\n", metadata->alto);
    printf("Profundidad de color: %hu bits por píxel\n\n", metadata->profundidad);

    fclose(file);

    return TODO_OK;
}

int modPixeles(const char *archImagen, const char *archCopia, void (*funcionPixel)(t_pixel*)) {
    FILE* file = fopen(archImagen, "rb");
    if (!file) {
        printf("No abrió la imagen");
        return ARCHIVO_NO_ENCONTRADO;
    }

    FILE* fileCopia = fopen(archCopia, "wb");
    if (!fileCopia) {
        fclose(file);
        printf("No abrió la imagen");
        return ARCHIVO_NO_ENCONTRADO;
    }

    unsigned char encabezado[138];

    fread(encabezado, sizeof(unsigned char), 138, file);

    fwrite(encabezado, sizeof(unsigned char), 138, fileCopia);

    t_pixel pixel;

    while (fread(&pixel.pixel, sizeof(pixel.pixel), 1, file)) {
        funcionPixel(&pixel);
        fwrite(&pixel.pixel, sizeof(pixel.pixel), 1, fileCopia);
    }

    fclose(file);
    fclose(fileCopia);
    return TODO_OK;
}

void pixelesGrises(t_pixel *pixel) {
    unsigned char gris = (pixel->pixel[0] + pixel->pixel[1] + pixel->pixel[2]) / 3;
    pixel->pixel[0] = gris;
    pixel->pixel[1] = gris;
    pixel->pixel[2] = gris;
}

void aumentarContraste(t_pixel *pixel) {
    float factor_contraste = 1.50;
    pixel->pixel[0] = ajustarContraste(pixel->pixel[0], factor_contraste);
    pixel->pixel[1] = ajustarContraste(pixel->pixel[1], factor_contraste);
    pixel->pixel[2] = ajustarContraste(pixel->pixel[2], factor_contraste);
}

void reducirContraste(t_pixel *pixel) {
    float factor_contraste = 0.50;
    pixel->pixel[0] = ajustarContraste(pixel->pixel[0], factor_contraste);
    pixel->pixel[1] = ajustarContraste(pixel->pixel[1], factor_contraste);
    pixel->pixel[2] = ajustarContraste(pixel->pixel[2], factor_contraste);
}

unsigned char ajustarContraste(unsigned char pixel, float factor_contraste) {
    float nuevo_valor = (float)pixel;
    nuevo_valor = nuevo_valor - 128;
    nuevo_valor = nuevo_valor * factor_contraste;
    nuevo_valor = nuevo_valor + 128;
    if (nuevo_valor > 255) nuevo_valor = 255;
    if (nuevo_valor < 0) nuevo_valor = 0;
    return (unsigned char)nuevo_valor;
}

void aumentarAzul(t_pixel *pixel) {
    float nuevo_valor = (float)pixel->pixel[0];
    nuevo_valor = nuevo_valor * 1.5;
    if (nuevo_valor > 255) nuevo_valor = 255;
    pixel->pixel[0] = nuevo_valor;
}

void aumentarVerde(t_pixel *pixel) {
    float nuevo_valor = (float)pixel->pixel[1];
    nuevo_valor = nuevo_valor * 1.5;
    if (nuevo_valor > 255) nuevo_valor = 255;
    pixel->pixel[1] = nuevo_valor;
}

void aumentarRojo(t_pixel *pixel) {
    float nuevo_valor = (float)pixel->pixel[2];
    nuevo_valor = nuevo_valor * 1.5;
    if (nuevo_valor > 255) nuevo_valor = 255;
    pixel->pixel[2] = nuevo_valor;
}

void comodin(t_pixel *pixel) {
    // La función comodín realizará un cambio básico en los píxeles, por ejemplo, invertir los colores.
    pixel->pixel[0] = 255 - pixel->pixel[0];
    pixel->pixel[1] = 255 - pixel->pixel[1];
    pixel->pixel[2] = 255 - pixel->pixel[2];
}

unsigned char** crearMatriz(unsigned int filas, unsigned int columnas)
{
    unsigned char** matriz = malloc(filas * sizeof(unsigned char*));
    if(!matriz)
    {
        puts("Malloc no reservo memoria!!!");
        return NULL;
    }
    for (int i = 0; i < filas; i++) {
        matriz[i] = (unsigned char*)malloc(columnas  * 3*sizeof(unsigned char));
        if(!matriz)
        {
            puts("Malloc no reservo memoria!!!");
            return NULL;
        }
    }
    return matriz;
}

int cargarMatriz(char* filename, unsigned char** matriz, unsigned int filas, unsigned int columnas)
{
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("No se puede abrir el archivo.\n");
        return ARCHIVO_NO_ENCONTRADO;
    }

    // Saltar la cabecera del archivo BMP
    fseek(file, 138, SEEK_SET);

    int padding = (4 - ((columnas * 3) % 4))%4;
//    int padding = 4 - columnas % 4;
//    printf("\n padding de cargar matriz: %d\n", padding);

    // Leer los píxeles de la imagen BMP y guardarlos en la matriz
    for (int i = 0; i < filas; i++)
    {
        fread(matriz[i], 3*sizeof(unsigned char), columnas, file);
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
    return TODO_OK;
}

void liberarMatriz(unsigned char** matriz, unsigned int fila)
{
    for (int i = 0; i < fila; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int imgRecortar(char* archImg, char* archRecorte, unsigned char** matriz, int filas, unsigned int columnas)
{
    FILE* file = fopen(archImg, "rb");
    if (!file) {
        printf("No se puede abrir el archivo de entrada.\n");
        return ARCHIVO_NO_ENCONTRADO;
    }

    FILE* fileRecorte = fopen(archRecorte, "wb");
    if (!fileRecorte) {
        printf("No se puede crear el archivo de salida.\n");
        fclose(file);
        return ARCHIVO_NO_ENCONTRADO;
    }

    // Leer y copiar la cabecera del archivo BMP
    unsigned char cabecera[138];
    fread(cabecera, sizeof(unsigned char), 138, file);
    fwrite(cabecera, sizeof(unsigned char), 138, fileRecorte);

    // Actualizar las dimensiones en la cabecera
    int nuevaAltura = filas / 2;
    int nuevaAnchura = columnas / 2;
    fseek(fileRecorte, 18, SEEK_SET);
    fwrite(&nuevaAnchura, sizeof(unsigned int), 1, fileRecorte);
    fwrite(&nuevaAltura, sizeof(unsigned int), 1, fileRecorte);

//    printf("\n NUEVA ANCHURA: %d", nuevaAnchura);


    int padding = (4 - ((nuevaAnchura * 3) % 4))%4;
    unsigned char padding_byte = 0;


//    int padding = 4 - nuevaAnchura % 4;

//    printf("\n padding img recortar: %d\n", padding);


    // Escribir la nueva imagen recortada
    fseek(fileRecorte, 138, SEEK_SET);
    for (int i = nuevaAltura; i < filas; i++)
    {
        fwrite(matriz[i], 3*sizeof(unsigned char), nuevaAnchura, fileRecorte);

        fwrite(&padding_byte, sizeof(unsigned char), padding, fileRecorte);

//        fwrite(pix.pixel, sizeof(unsigned char), padding, fileRecorte);
    }

    fclose(file);
    fclose(fileRecorte);
    return TODO_OK;
}


int rotarImagen(const char* archImg, const char* archRotada, unsigned char** matriz, int filas, int columnas, unsigned char** (*rotarMatriz)(unsigned char**, unsigned int, unsigned int))
{
    FILE* file = fopen(archImg, "rb");
    if (!file) {
        printf("No se puede abrir el archivo de entrada.\n");
        return ARCHIVO_NO_ENCONTRADO;
    }

    FILE* fileRotada = fopen(archRotada, "wb");
    if (!fileRotada) {
        printf("No se puede crear el archivo de salida.\n");
        fclose(file);
        return ARCHIVO_NO_ENCONTRADO;
    }

    unsigned char cabecera[138];
    fread(cabecera, sizeof(unsigned char), 138, file);
    fwrite(cabecera, sizeof(unsigned char), 138, fileRotada);

    fseek(fileRotada, 18, SEEK_SET);
    fwrite(&filas, sizeof(unsigned int), 1, fileRotada);
    fwrite(&columnas, sizeof(unsigned int), 1, fileRotada);

    unsigned char** matrizRotada = rotarMatriz(matriz, filas, columnas);



    fseek(fileRotada, 138, SEEK_SET);


     for (int i = 0; i < columnas; i++) {
        fwrite(matrizRotada[i], sizeof(unsigned char), filas * 3, fileRotada);
    }


    liberarMatriz(matrizRotada, filas);
    fclose(file);
    fclose(fileRotada);
    return TODO_OK;
}


unsigned char** rotarMatrizIzquierda(unsigned char** matriz, unsigned int filas, unsigned int columnas)
{
    unsigned char** matrizRotada = crearMatriz(columnas, filas);

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matrizRotada[j][(filas - 1 - i) * 3] = matriz[i][j * 3];
            matrizRotada[j][(filas - 1 - i) * 3 + 1] = matriz[i][j * 3 + 1];
            matrizRotada[j][(filas - 1 - i) * 3 + 2] = matriz[i][j * 3 + 2];
            }
        }

    return matrizRotada;
}


unsigned char** rotarMatrizDerecha(unsigned char** matriz, unsigned int filas, unsigned int columnas)
{
    unsigned char** matrizRotada = crearMatriz(columnas, filas);

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matrizRotada[columnas - 1 - j][i * 3] = matriz[i][j * 3];
            matrizRotada[columnas - 1 - j][i * 3 + 1] = matriz[i][j * 3 + 1];
            matrizRotada[columnas - 1 - j][i * 3 + 2] = matriz[i][j * 3 + 2];
            }
        }

    return matrizRotada;
}


int concatenar(const char* img, const char* imgDos, const char* imgConcatenada)
{
    FILE* file = fopen(img, "rb");
    if (!file) {
        printf("No se puede abrir el archivo de entrada.\n");
        return ARCHIVO_NO_ENCONTRADO;
    }

    FILE* fileDos = fopen(imgDos, "rb");
    if (!fileDos) {
        printf("No se puede crear el archivo de salida.\n");
        fclose(file);
        return ARCHIVO_NO_ENCONTRADO;
    }

    FILE* fileConcatenar = fopen(imgConcatenada, "wb");
    if (!fileConcatenar) {
        printf("No se puede crear el archivo de salida.\n");
        fclose(file);
        fclose(fileDos);
        return ARCHIVO_NO_ENCONTRADO;
    }

    unsigned char cabecera[138];
    fread(cabecera, sizeof(unsigned char), 138, file);
    fwrite(cabecera, sizeof(unsigned char), 138, fileConcatenar);

    unsigned int filasUno, columnasUno;
    fseek(file, 18, SEEK_SET);
    fread(&columnasUno, sizeof(unsigned int), 1, file);
    fread(&filasUno, sizeof(unsigned int), 1, file);

    unsigned int filasDos, columnasDos;
    fseek(fileDos, 18, SEEK_SET);
    fread(&columnasDos, sizeof(unsigned int), 1, fileDos);
    fread(&filasDos, sizeof(unsigned int), 1, fileDos);

    if(columnasUno < columnasDos)
    {
        unsigned int filas;
        filas = filasUno + filasDos;

        unsigned char** matriz = crearMatriz(filas, columnasDos);

        cargarMatrizConcatenada(file, fileDos, matriz, filas, columnasDos, filasUno, columnasUno, filasDos, columnasDos);

        fseek(fileConcatenar, 18, SEEK_SET);
        fwrite(&columnasDos, sizeof(unsigned int), 1, fileConcatenar);
        fwrite(&filas, sizeof(unsigned int), 1, fileConcatenar);

        int padding = (4 - (columnasDos*3) % 4)%4;
        unsigned char padding_bytes[3] = {0, 0, 0};

        fseek(fileConcatenar, 138, SEEK_SET);
        for (int i = 0; i < filas; i++)
        {
            fwrite(matriz[i], 3*sizeof(unsigned char), columnasDos, fileConcatenar);
            fwrite(padding_bytes, sizeof(unsigned char), padding, fileConcatenar);
        }

    } else{
        unsigned int filas;
        filas = filasUno + filasDos;

        unsigned char** matriz = crearMatriz(filas, columnasUno);

        cargarMatrizConcatenada(fileDos, file, matriz, filas, columnasUno, filasDos, columnasDos, filasUno, columnasUno);

        fseek(fileConcatenar, 18, SEEK_SET);
        fwrite(&columnasUno, sizeof(unsigned int), 1, fileConcatenar);
        fwrite(&filas, sizeof(unsigned int), 1, fileConcatenar);

        int padding = (4 - (columnasUno*3) % 4)%4;
        unsigned char padding_bytes[3] = {0, 0, 0};

        fseek(fileConcatenar, 138, SEEK_SET);
        for (int i = 0; i < filas; i++)
        {
            fwrite(matriz[i], 3*sizeof(unsigned char), columnasUno, fileConcatenar);
            fwrite(padding_bytes, sizeof(unsigned char), padding, fileConcatenar);
        }
    }

    fclose(file);
    fclose(fileDos);
    fclose(fileConcatenar);
    return TODO_OK;
}


void cargarMatrizConcatenada(FILE* file, FILE* fileDos, unsigned char** matriz, int filas, int columnas, int filasUno, int columnasUno, int filasDos, int columnasDos)
{
    // Saltar la cabecera del archivo BMP
    fseek(file, 138, SEEK_SET);
    fseek(fileDos, 138, SEEK_SET);

    // Leer los píxeles de la imagen BMP y guardarlos en la matriz
    t_pixel pix;
    pix.pixel[0]= (unsigned char)0;
    pix.pixel[1]= (unsigned char)0;
    pix.pixel[2]= (unsigned char)0;

    int padding = (4 - (columnasDos * 3) % 4) % 4;
    int paddingDos = (4 - (columnasUno * 3) % 4) %  4;

    for(int i = 0; i < filasUno; i++)
    {
        fread(matriz[i], 3*sizeof(unsigned char), columnasUno, file);
        for(int j = columnasUno; j < columnas; j++)
        {
            matriz[i][3*j] = pix.pixel[0];
            matriz[i][3*j + 1] = pix.pixel[1];
            matriz[i][3*j + 2] = pix.pixel[2];
        }
        fseek(file, paddingDos, SEEK_CUR);

    }

    for(int i = filasUno; i < filas; i++)
    {
        fread(matriz[i], 3*sizeof(unsigned char), columnasDos, fileDos);
        fseek(fileDos, padding, SEEK_CUR);
    }
}
