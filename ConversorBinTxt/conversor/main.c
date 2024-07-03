#include <stdio.h>
#include <stdlib.h>

#define CANT_ARG 4
#define ARG_ARCH_ENT 1
#define ARG_TIPO_ARCH_ENT 2
#define ARG_ARCH_SAL 3
#define ARG_TIPO_ARCH_SAL 4

#define ERR_ARG 1
#define TODO_OK 0
#define ERR_ARCH 2
#define ERR_MEM 3
#define ERR_LINEA_LARGA 4

#define TAM_NOMBRE 20
#define CANT_EMPL 8
#define TAM_LINEA 501

typedef struct
{
    int dia;
    int mes;
    int anio;
}Fecha;

typedef struct
{
    int legajo;
    char nombre[TAM_NOMBRE +1];
    char sexo;
    Fecha fechaIngr;
    float sueldo;
}Empleado;

typedef void (*BinATxt)(const void* reg, FILE* archTxt);
typedef void (*TxtABin)(char* linea, void* reg);

void empleadoBinATxtV(const void* reg, FILE* archTxt);
void empleadoBinATxtF(const void* reg, FILE* archTxt);
int empleadoTxtVABin(char* linea, void* reg);
int empleadoTxtFABin(char* linea, void* reg);
int convertirBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt binATxt);
int convertirTxtABin(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, TxtABin txtABin);
int generarEmpleados(const char* nomArchEmpleados);

//conversor de binario a texto

//ConversorBinTxt Empleados.dat B Empleados.txt V/F
int main(int argc, char* argv[])
{
    generarEmpleados(argv[ARG_ARCH_ENT]);

    if(argc -1 != CANT_ARG)
        return ERR_ARG;

    char tipoArchEnt = *argv[ARG_TIPO_ARCH_ENT]; //obtenemos B
    char tipoArchSal = *argv[ARG_TIPO_ARCH_SAL]; //obtenemos V


    switch(tipoArchEnt)
    {
    case 'B':
        int ret = convertirBinATxt(argv[ARG_TIPO_ARCH_ENT], argv[ARG_TIPO_ARCH_SAL], sizeof(Empleado),tipoArchSal == 'V' ? empleadoBinATxtV : empleadoBinATxtF);
        break;

    case 'V':
    case 'F':
        ret = convertirTxtABin(argv[ARG_TIPO_ARCH_ENT], argv[ARG_TIPO_ARCH_SAL], sizeof(Empleado),tipoArchEnt == 'V' ? empleadoTxtVABin : empleadoTxtFABin);
        break;
    }

    return ret;
}

int convertirBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt binATxt)
{
    void* reg = malloc(tamReg);
    if(!reg)
        return ERR_MEM;

    FILE* archBin = fopen(nomArchBin, "rb");
    if(!archBin)
    {
        free(reg);
        return ERR_ARCH;
    }

    FILE* archTxt = fopen(archTxt, "wb");
    if(!archTxt)
    {
        free(reg);
        fclose(archBin);
        return ERR_ARCH;
    }

    fread(reg, tamReg, 1, archBin);
    while(!feof(archBin))
    {
        binATxt(reg, archTxt);
        fread(reg, tamReg, 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    free(reg);
    return TODO_OK;
}

int empleadoTxtVABin(char* linea, void* reg)
{
    Empleado empl = reg;

    char* act = strchr(linea, '\n'); //funcion para buscar un caracter
    if(!act)
        return ERR_LINEA_LARGA;

    *act = '\0';
    *act = strrchr(linea, '|'); //funcion para buscar caracter hacia atras
    sscanf(acr+1, "%f", &empl->sueldo);

    *act = '\0';
    *act = strrchr(linea, '|');
    sscanf(act + 1 "%d/%d/%d", &empl->fechaIngr.dia, &empl->fechaIngr.mes, &empl->fechaIngr.anio); //guarda los valores del registro en la estructura

    *act = '\0';
    *act = strrchr(linea, '|');
    empl->sexo = *(act +1);

    *act = '\0';
    *act = strrchr(linea, '|');
    strncpy(empl->nombre, act + 1, TAM_NOMBRE); //strncpy copia pero con la cantidad que yo le diga
    *(empl->nombre + TAM_NOMBRE) = '\0';

    *act = '\0';
    sscanf(linea, "%d", &empl->legajo);

    return TODO_OK;
}


int empleadoTxtFABin(char* linea, void* reg)
{

    return TODO_OK;
}


int generarEmpleados(const char* nomArchEmpleados)
{
    FILE* arch = fopen(nomArchEmpleados, "wb");

    Empleado empleados[CANT_EMPL] =
    {
        (1', "fede", 'M',21/20/2021,45.25)
    };

}

void empleadoBinATxtV(const void* reg, FILE* archTxt)
{
    const Empleado* empl = reg;

    fprintf
    (
        archTxt,
        "%d|%s|%c|%d/%d/%d|%f\n",
         empl->legajo,
         empl->nombre,
         empl->sexo,
         empl->fechaIngr.dia, empl->fechaIngr.mes, empl->fechaIng.anio,
         empl->sueldo
    ); //version de printf que imprimer en un archivo de txt
}


void empleadoBinATxtF(const void* reg, FILE* archTxt)
{
    const Empleado* empl = reg;

    fprintf
    (
        archTxt,
        "%08d|%-20s|%c|%02d/%02d/%04d|%09.2f\n",
         empl->legajo,
         empl->nombre,
         empl->sexo,
         empl->fechaIngr.dia, empl->fechaIngr.mes, empl->fechaIng.anio,
         empl->sueldo
    ); //version de printf que imprimer en un archivo de txt
}

int convertirTxtABin(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, TxtABin txtABin)
{
     void* reg = malloc(tamReg);
    if(!reg)
        return ERR_MEM;

    FILE* archTxt = fopen(nomArchTxt, "rt");
    if(!archTxt)
    {
        free(reg);
        return ERR_ARCH;
    }

    FILE* archBin = fopen(archBin, "wb");
    if(!archTxt)
    {
        free(reg);
        fclose(archTxt);
        return ERR_ARCH;
    }

    char linea[TAM_LINEA];

    fgets(linea, TAM_LINEA, archTxt); //funciona para leer archivos de txt
    while(!feof(archTxt))
    {
        txtABin(linea, reg, archTxt);
        fwrite(reg, tamReg, 1, archBin);
        fgets(linea, TAM_LINEA, archTxt);
    }



    fclose(archBin);
    fclose(archTxt);

    free(reg);
    return TODO_OK;
}

