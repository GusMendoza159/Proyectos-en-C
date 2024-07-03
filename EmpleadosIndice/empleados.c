#include "empleados.h"

int generarArchEmpleados(const char* archEmpleado)
{
    Empleado empleados[CANT_EMPL]=
    {
        {5, "Juan Perez", 240000},
        {1, "Micaela Caseres", 240000},
        {3, "Belen Barrionuevo", 240000},
        {8, "Tomas Balvusa", 240000},
        {6, "Roman Riquelme", 240000},
        {4, "Tyron Gonzales", 240000},
        {2, "Luca Proda", 240000},
        {7, "Jesus Dejerusalen", 240000},
    };

    FILE* arch = fopen(archEmpleado, "wb");
    if(!arch)
        return ERR_ARCH;
    fwrite(empleados, sizeof(Empleado), CANT_EMPL, arch);
    fclose(arch);
    return TODO_OK;
}


int mostrarArchivoEmpleados(const char* archEmpleado)
{
    FILE* arch = fopen(archEmpleado, "rb");
    if(!arch)
        return ERR_ARCH;
    Empleado empleado;
    fread(&empleado, sizeof(Empleado), 1, arch);
    while(!feof(arch))
    {
        printf("%02d, %-20s, %08.2f\n", empleado.legajo, empleado.nombre, empleado.sueldo);
        fread(&empleado, sizeof(Empleado), 1, arch);
    }
    puts("\n");
    fclose(arch);
    return TODO_OK;
}


int actualizarSueldos(const char* archEmpleados, float porc)
{
    FILE* arch = fopen(archEmpleados, "r+b");
    if(!arch)
        return ERR_ARCH;
    Empleado empleado;
    float porProd = 1 + (float)porc/100;

    fread(&empleado, sizeof(Empleado), 1, arch);
    while(!feof(arch))
    {
        empleado.sueldo *= porProd;
        fseek(arch, -sizeof(Empleado), SEEK_CUR);
        fwrite(&empleado, sizeof(Empleado), 1, arch);
        fseek(arch, 0L, SEEK_CUR);
        fread(&empleado, sizeof(Empleado), 1, arch);
    };
    fclose(arch);
    return TODO_OK;
}


int generarIndiceEmpleados(const char* archEmpleados, const char* archEmplIdx)
{
    EmpleadoIdx emplIdx;
    FILE* arch = fopen(archEmpleados, "rb");
    if(!arch)
        return ERR_ARCH;
    FILE* archIdx = fopen(archEmplIdx, "wb");
    if(!archIdx)
    {
        fclose(arch);
        return ERR_ARCH;
    }
    Empleado empleado;
    long nroReg = 1;
    fread(&empleado, sizeof(Empleado), 1, arch);
    while(!feof(arch))
    {
        emplIdx.leg = empleado.legajo;
        emplIdx.nroReg = nroReg;
        nroReg++;
        fwrite(&emplIdx, sizeof(EmpleadoIdx), 1, archIdx);
        fread(&empleado, sizeof(Empleado), 1, arch);
    }
    fclose(arch);
    fclose(archIdx);
    return TODO_OK;
}


int mostrarIndice(const char* archEmplIdx)
{
    FILE* archIdx = fopen(archEmplIdx, "rb");
    if(!archIdx)
        return ERR_ARCH;
    EmpleadoIdx idx;
    fread(&idx, sizeof(EmpleadoIdx), 1, archIdx);
    while(!feof(archIdx))
    {
        printf("%2d, %02d\n", idx.leg, (int)idx.nroReg);
        fread(&idx, sizeof(EmpleadoIdx), 1, archIdx);
    }
    fclose(archIdx);
    return TODO_OK;
}
