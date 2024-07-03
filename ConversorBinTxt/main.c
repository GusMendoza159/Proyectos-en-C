#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANT_ARG 4
#define ARG_ARCH_ENT 1
#define ARG_TIPO_ARCH_ENT 2
#define ARG_ARCH_SAL 3
#define ARG_TIPO_ARCH_SAL 4

#define TODO_OK 0
#define ERR_ARG 1
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
}
Fecha;

typedef struct
{
    int legajo;
    char nombre[TAM_NOMBRE + 1];
    char sexo;
    Fecha fechaIngr;
    float sueldo;
}
Empleado;


typedef void (*BinATxt)(const void* reg, FILE* archTxt);
typedef int (*TxtABin)(char* linea, void* reg);

void empleadoBinATxtV(const void* reg, FILE* archTxt);
void empleadoBinATxtF(const void* reg, FILE* archTxt);
int empleadoTxtVABin(char* linea, void* reg);
int empleadoTxtFABin(char* linea, void* reg);
int convertirBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt BinATxt);
int convertirTxtABin(const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin TxtABin);
int generarEmpleadosBin(const char* nomArchEmpleados);
int mostrarEmpleadosBin(const char* nomArch);
//int generarEmpleadosTxtF(const char* nomArchTxt);

// ConversorBinTxt Empleados.dat B Empleados.txt V
// ConversorBinTxt Empleados.txt V Empleados.dat B

int main(int argc, const char* argv[])
{
//    generarEmpleadosBin(argv[ARG_ARCH_ENT]);

    if(argc-1 != CANT_ARG)
    {
        printf("ARGC!!\n");
        return ERR_ARG;
    }


    char tipoArchEnt = *argv[ARG_TIPO_ARCH_ENT];
    char tipoArchSal = *argv[ARG_TIPO_ARCH_SAL];
    int ret;

    switch(tipoArchEnt)
    {
        case 'B':
            generarEmpleadosBin(argv[ARG_ARCH_ENT]);
            ret = convertirBinATxt(argv[ARG_ARCH_ENT], argv[ARG_ARCH_SAL], sizeof(Empleado), tipoArchSal == 'V'? empleadoBinATxtV : empleadoBinATxtF);
            printf("BinATxt %d\n", ret);
            mostrarEmpleadosBin(argv[ARG_ARCH_ENT]);
            break;
        case 'V':
        case 'F':
            ret = convertirTxtABin(argv[ARG_ARCH_ENT], argv[ARG_ARCH_SAL], sizeof(Empleado), tipoArchEnt == 'V'? empleadoTxtVABin : empleadoTxtFABin);
            printf("TxtABin %d\n", ret);
            mostrarEmpleadosBin(argv[ARG_ARCH_SAL]);
            break;
    }
    return 0;
}


int convertirBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt BinATxt)
{
    void* reg = malloc(tamReg);
    if(!reg)
    {
        free(reg);
        return ERR_MEM;
    }

    FILE* archBin = fopen(nomArchBin, "rb");
    if(!archBin)
    {
        free(reg);
        return ERR_ARCH;
    }

    FILE* archTxt = fopen(nomArchTxt, "wt");
    if(!archTxt)
    {
        free(reg);
        fclose(archBin);
        return ERR_ARCH;
    }

    fread(reg, tamReg, 1, archBin);
    while(!feof(archBin))
    {
        BinATxt(reg, archTxt);
        fread(reg, tamReg, 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    free(reg);
    return TODO_OK;
}


void empleadoBinATxtV(const void* reg, FILE* archTxt)
{
    const Empleado* empl = reg;
    fprintf
    (
        archTxt,
        "%d|%s|%c|%d/%d/%d|%.2f\n",
        empl->legajo,
        empl->nombre,
        empl->sexo,
        empl->fechaIngr.dia, empl->fechaIngr.mes, empl->fechaIngr.anio,
        empl->sueldo
        );
}


void empleadoBinATxtF(const void* reg, FILE* archTxt)
{
    const Empleado* empl = reg;
    fprintf
    (
        archTxt,
        "%8d%-20s%c%02d%02d%04d%10.2f\n",
        empl->legajo,
        empl->nombre,
        empl->sexo,
        empl->fechaIngr.dia, empl->fechaIngr.mes, empl->fechaIngr.anio,
        empl->sueldo
        );
}


int convertirTxtABin(const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin TxtABin)
{
    void* reg = malloc(tamReg);
    if(!reg)
    {
        free(reg);
        return ERR_MEM;
    }

    FILE* archTxt = fopen(nomArchTxt, "rt");
    if(!archTxt)
    {
        free(reg);
        return ERR_ARCH;
    }

    FILE* archBin = fopen(nomArchBin, "wb");
    if(!archBin)
    {
        free(reg);
        fclose(archTxt);
        return ERR_ARCH;
    }

    char linea[TAM_LINEA];

    fgets(linea, TAM_LINEA, archTxt);
    while(!feof(archTxt))
    {
        TxtABin(linea, reg);
        fwrite(reg, tamReg, 1, archBin);
        fgets(linea, TAM_LINEA, archTxt);
    }

    fclose(archBin);
    fclose(archTxt);
    return TODO_OK;
}


int empleadoTxtVABin(char* linea, void* reg)
{
        Empleado* empl = reg;

        char* act = strchr(linea, '\n');

        if(!act)
            return ERR_LINEA_LARGA;

        *act = '\0';
        act = strrchr(linea, '|');
        sscanf(act + 1, "%f", &empl->sueldo);

        *act = '\0';
        act = strrchr(linea, '|');
        sscanf(act + 1, "%d/%d/%d", &empl->fechaIngr.dia, &empl->fechaIngr.mes, &empl->fechaIngr.anio);

        *act = '\0';
        act = strrchr(linea, '|');
        empl->sexo = *(act + 1);

        *act = '\0';
        act = strrchr(linea, '|');
        strncpy(empl->nombre, act + 1, TAM_NOMBRE);
        *(empl->nombre + TAM_NOMBRE) = '\0';

        *act = '\0';
        sscanf(linea, "%d", &empl->legajo);

        return TODO_OK;
}


int empleadoTxtFABin(char* linea, void* reg)
{
    Empleado* empl = reg;

// "%8d%-20s%c%02d%02d%04d%10.2f\n",
    char act[100];

    // Legajo
    strncpy(act, linea, 8);
    act[8] = '\0';
    sscanf(act, "%d", &empl->legajo);

    // Nombre
    strncpy(act, linea + 8, 20);
    act[20] = '\0';
    strcpy(empl->nombre, act);

    // Sexo
    empl->sexo = linea[28];

    // Día
    strncpy(act, linea + 29, 2);
    act[2] = '\0';
    sscanf(act, "%d", &empl->fechaIngr.dia);

    // Mes
    strncpy(act, linea + 31, 2);
    act[2] = '\0';
    sscanf(act, "%d", &empl->fechaIngr.mes);

    // Año
    strncpy(act, linea + 33, 4);
    act[4] = '\0';
    sscanf(act, "%d", &empl->fechaIngr.anio);

    // Sueldo
    strncpy(act, linea + 37, 10);
    act[10] = '\0';
    sscanf(act, "%f", &empl->sueldo);

    return TODO_OK;
}


int generarEmpleadosBin(const char* nomArchEmpleados)
{
    Empleado empleados[CANT_EMPL] =
    {
        {1, "Juan Perez", 'M', {12,3,1999}, 240000},
        {2, "Micaela Caseres", 'F', {5,5,2002}, 240000},
        {3, "Belen Barrionuevo", 'F', {17,10,1996}, 240000},
        {4, "Tomas Balvusa", 'M', {29,4,2001}, 240000},
        {5, "Roman Riquelme", 'M', {13,8,2004}, 240000},
        {6, "Tyron Gonzales", 'M', {24,2,1999}, 240000},
        {7, "Luca Proda", 'M', {8,7,2000}, 240000},
        {8, "Jesus Dejerusalen", 'M', {1,12,1998}, 240000},
    };

    FILE* arch = fopen(nomArchEmpleados, "wb");
    if(!arch)
        return ERR_ARCH;

    fwrite(empleados, sizeof(Empleado), CANT_EMPL, arch);
    fclose(arch);
    return TODO_OK;
}


int mostrarEmpleadosBin(const char* nomArch)
{
    FILE* arch = fopen(nomArch, "rb");
    if(!arch)
        return ERR_ARCH;

    Empleado empl;
    fread(&empl, sizeof(Empleado), 1, arch);
    while(!feof(arch))
    {
        printf("%02d, %-20s, %c, %02d/%02d/%d, %08.2f\n", empl.legajo, empl.nombre, empl.sexo, empl.fechaIngr.dia, empl.fechaIngr.mes, empl.fechaIngr.anio, empl.sueldo);
        fread(&empl, sizeof(Empleado), 1, arch);
    }
    fclose(arch);

    return TODO_OK;
}


//int generarEmpleadosTxtF(const char* nomArchTxt)
//{
//    Empleado empleados[CANT_EMPL] =
//    {
//        {1, "Juan Perez", 'M', {12,3,1999}, 240000},
//        {2, "Micaela Caseres", 'F', {5,5,2002}, 240000},
//        {3, "Belen Barrionuevo", 'F', {17,10,1996}, 240000},
//        {4, "Tomas Balvusa", 'M', {29,4,2001}, 240000},
//        {5, "Roman Riquelme", 'M', {13,8,2004}, 240000},
//        {6, "Tyron Gonzales", 'M', {24,2,1999}, 240000},
//        {7, "Luca Proda", 'M', {8,7,2000}, 240000},
//        {8, "Jesus Dejerusalen", 'M', {1,12,1998}, 240000},
//    };
//
//    FILE* archTxt = fopen(nomArchTxt, "wt");
//    if(!archTxt)
//        return ERR_ARCH;
//
//    for(int i = 0; i < CANT_EMPL; i++)
//    {
//        fprintf
//        (
//            archTxt,
//            "%8d%-20s%c%02d%02d%04d%10.2f\n",
//            empleados[i].legajo,
//            empleados[i].nombre,
//            empleados[i].sexo,
//            empleados[i].fechaIngr.dia, empleados[i].fechaIngr.mes, empleados[i].fechaIngr.anio,
//            empleados[i].sueldo
//        );
//    }
//    fclose(archTxt);
//    return TODO_OK;
//}
