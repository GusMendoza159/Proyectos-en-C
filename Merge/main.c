#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANT_ARG 2
#define ARG_PRODUCTOS 1
#define ARG_MOVIMIENTOS 2

#define TODO_OK 0
#define ERR_ARG 1
#define ERR_ARCHIVO 2

#define CANT_PRODS 6
#define CANT_MOVS 8

#define NOM_ARCH_PROD_TMP "Productos.tmp"

//MERGE Productos.dat Movimientos.dat


typedef struct
{
    char codigo[7];
    char descripcion[21];
    int stock;
}Producto;


typedef struct
{
    char codigo[7];
    int cantidad;
}Movimiento;


int generarProductos(const char* nomArchProd);
int generarMovimientos(const char* nomArchMov);
int mostrarProductos(const char* nomArchProd);
int actualizarProductos(const char* nomArchProd, const char* nomArchMov);
void procesarProductoNuevo(Movimiento* mov, FILE* archMov, FILE* archProdTmp);

int main(int argc, const char* argv[])
{
    if(argc - 1 != CANT_ARG)
        return ERR_ARG;

    int ret;

    ret = generarProductos(argv[ARG_PRODUCTOS]);

    if(ret != TODO_OK)
        return ret;

    ret = generarMovimientos(argv[ARG_MOVIMIENTOS]);

    if(ret != TODO_OK)
        return ret;

    puts("Antes:\n");
    mostrarProductos(argv[ARG_PRODUCTOS]);
    putchar('\n');

    ret = actualizarProductos(argv[ARG_PRODUCTOS], argv[ARG_MOVIMIENTOS]);

    if(ret != TODO_OK)
        return ret;

    puts("Despues:\n");
    mostrarProductos(argv[ARG_PRODUCTOS]);
    putchar('\n');

    return TODO_OK;
}


int generarProductos(const char* nomArchProd)
{
    Producto productos[CANT_PRODS] =
    {
        {"00", "Higo", 100},
        {"04", "Banana", 100},
        {"07", "Pera", 50},
        {"09", "Manzana", 70},
        {"14", "Durazno", 90},
        {"16", "Sandia", 90}
    };

    FILE* archProd = fopen(nomArchProd, "wb");
    if(!archProd)
        return ERR_ARCHIVO;

    fwrite(productos, sizeof(Producto), CANT_PRODS, archProd);

    fclose(archProd);
    return TODO_OK;
}


int generarMovimientos(const char* nomArchMov)
{
    Movimiento movimientos[CANT_MOVS] =
    {
        {"01", 20},
        {"07", 20},
        {"07", -10},
        {"08", 40},
        {"12", 60},
        {"12", -10},
        {"15", 80},
        {"15", 40},
    };

    FILE* archMov = fopen(nomArchMov, "wb");
    if(!archMov)
        return ERR_ARCHIVO;

    fwrite(&movimientos, sizeof(Movimiento), CANT_MOVS, archMov);

    fclose(archMov);

    return TODO_OK;
}

int mostrarProductos(const char* nomArchProd)
{
    FILE* archProd = fopen(nomArchProd, "rb");
    if(!archProd)
        return ERR_ARCHIVO;

    Producto prod;

    fread(&prod, sizeof(Producto), 1, archProd);
    while(!feof(archProd))
    {
        printf("%-6s %-20s %03d\n", prod.codigo, prod.descripcion, prod.stock);
        fread(&prod, sizeof(Producto), 1, archProd);
    }

    fclose(archProd);
    return TODO_OK;
}


int actualizarProductos(const char* nomArchProd, const char* nomArchMov)
{
    FILE* archProd = fopen(nomArchProd, "rb");
    if(!archProd)
        return ERR_ARCHIVO;

    FILE* archMov = fopen(nomArchMov, "rb");
    if(!archMov)
    {
        fclose(archProd);
        return ERR_ARCHIVO;
    }

    FILE* archProdTmp = fopen(NOM_ARCH_PROD_TMP, "wb");
    if(!archProdTmp)
    {
        fclose(archMov);
        fclose(archProd);
        return ERR_ARCHIVO;
    }

    Producto prod;

    Movimiento mov;

    int comp;

    fread(&prod, sizeof(Producto), 1, archProd);
    fread(&mov, sizeof(Movimiento), 1, archMov);
    while(!feof(archProd) && !feof(archMov))
    {
        comp = strcmp(prod.codigo, mov.codigo);

        if(comp == 0) //Movimiento (cambio en el stock)
        {
            prod.stock += mov.cantidad;
            fread(&mov, sizeof(Movimiento), 1, archMov);
        }

        if(comp < 0)  //Producto sin movimiento
        {
            fwrite(&prod, sizeof(Producto), 1, archProdTmp);
            fread(&prod, sizeof(Producto), 1, archProd);
        }

        if(comp > 0)  //Producto nuevo
        {
            procesarProductoNuevo(&mov, archMov, archProdTmp);
        }
    }

    while(!feof(archProd))
    {
        fwrite(&prod, sizeof(Producto), 1, archProdTmp);
        fread(&prod, sizeof(Producto), 1, archProd);
    }

    while(!feof(archMov))
    {
        procesarProductoNuevo(&mov, archMov, archProdTmp);
    }

    fclose(archProd);
    fclose(archMov);
    fclose(archProdTmp);

    remove(nomArchProd);
    rename(NOM_ARCH_PROD_TMP, nomArchProd);

    return TODO_OK;
}


void procesarProductoNuevo(Movimiento* mov, FILE* archMov, FILE* archProdTmp)
{
    Producto prodNew;
    strcpy(prodNew.codigo, mov->codigo);
    *prodNew.descripcion = '\0';
    prodNew.stock = mov->cantidad;

    fread(mov, sizeof(Movimiento), 1, archMov);
    while(!feof(archMov) && strcmp(prodNew.codigo, mov->codigo) == 0)
    {
        prodNew.stock += mov->cantidad;
        fread(mov, sizeof(Movimiento), 1, archMov);
    }
    fwrite(&prodNew, sizeof(Producto), 1, archProdTmp);
}
