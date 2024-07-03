/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
*
* DNI:
*
***************************************************************************************/
/***************************************************************************************
********************* Descomente la solución que quiere probar: ************************
***************************************************************************************/
//#define SOLUCION_DOC
#define SOLUCION_ALU
/***************************************************************************************
************************************ Corrección ****************************************
****************************************************************************************
*
****************************************************************************************
* Nota:
***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Vector/Vector.h"
#include "../SolucionParcialDeliveryTopicos/TiposDelivery.h"
#include "../SolucionParcialDeliveryTopicos/SolucionDelivery.h"
#include "../UtilitariasTopicos/Utilitarias.h"

#define TAM_NOMBRE_ARCHIVO 50
#define TAM_LINEA_PEDIDO 50
#define TAM_COD_RECETA 11

void obtenerNombreIndice_ALU(const char* nombreArch, char* nombreArchIdx);
int cargarProximoPedido_ALU(char* linea, Pedido* p);
int cargarReceta_ALU(char* codReceta, Receta* receta, Vector* vector, FILE* archRecetas, FILE* archRecetasIdx);
int actualizarIngredientes_ALU(Vector* vector, int cantidad, FILE* archIngredientes, FILE* archIngredientesIdx);

int main()
{
	generarArchivoPedidos();
	generarArchivoRecetas();
	generarArchivoIngredientes();

	mostrarArchivoPedidos("Pedidos.txt");
	mostrarArchivoRecetas("Recetas.dat");

	puts("Ingredientes antes de la actualizacion");
	mostrarArchivoIngredientes("Ingredientes.dat");

	int resp;

#ifdef SOLUCION_DOC
	resp = satisfacerPedidos("Pedidos.txt", "Recetas.dat", "Ingredientes.dat");
#else
	resp = satisfacerPedidos_ALU("Pedidos.txt", "Recetas.dat", "Ingredientes.dat");
#endif

	if(resp != TODO_OK)
	{
		puts("Error actualizando los pedidos.");
		return resp;
	}

	puts("Ingredientes despues de la actualizacion");
	mostrarArchivoIngredientes("Ingredientes.dat");

	return TODO_OK;
}


///Procesa los pedidos del archivo Pedidos.txt, actualizando el archivo Ingredientes.dat, para que éste refleje la cantidad que queda en stock luego de despachar los pedidos.
int satisfacerPedidos_ALU(const char* nombreArchPedidos, const char* nombreArchRecetas, const char* nombreArchIngredientes)
{
    FILE* archPedidos = fopen(nombreArchPedidos, "rt");
    if (!archPedidos)
    {
        return ERR_ARCHIVO;
    }

    FILE* archRecetas = fopen(nombreArchRecetas, "rb");
    if (!archRecetas)
    {
        fclose(archPedidos);
        return ERR_ARCHIVO;
    }

    FILE* archIngredientes = fopen(nombreArchIngredientes, "r+b");
    if (!archIngredientes)
    {
        fclose(archPedidos);
        fclose(archRecetas);
        return ERR_ARCHIVO;
    }

    char nombreArchRecetasIdx[TAM_NOMBRE_ARCHIVO];
    obtenerNombreIndice_ALU(nombreArchRecetas, nombreArchRecetasIdx);
    FILE* archRecetasIdx = fopen(nombreArchRecetasIdx, "rb");
    if (!archRecetasIdx)
    {
        fclose(archPedidos);
        fclose(archRecetas);
        fclose(archIngredientes);
        return ERR_ARCHIVO;
    }

    char nombreArchIngredientesIdx[TAM_NOMBRE_ARCHIVO];
    obtenerNombreIndice_ALU(nombreArchIngredientes, nombreArchIngredientesIdx);
    FILE* archIngredientesIdx = fopen(nombreArchIngredientesIdx, "rb");
    if (!archIngredientesIdx)
    {
        fclose(archPedidos);
        fclose(archRecetas);
        fclose(archIngredientes);
        fclose(archRecetasIdx);
        return ERR_ARCHIVO;
    }


    int ret = TODO_OK;
    char linea[TAM_LINEA_PEDIDO];
    Pedido pedido;
    Receta receta;

    Vector vector;
    vectorCrear(&vector, sizeof(Receta));

    fgets(linea, TAM_LINEA_PEDIDO, archPedidos);
    while (!feof(archPedidos) && ret == TODO_OK)
    {
        ret = cargarProximoPedido_ALU(linea, &pedido);
        if (ret == TODO_OK)
            ret = cargarReceta_ALU(pedido.codReceta, &receta, &vector, archRecetas, archRecetasIdx);
        if (ret == TODO_OK)
            ret = actualizarIngredientes_ALU(&vector, pedido.cantidad, archIngredientes, archIngredientesIdx);

        fgets(linea, TAM_LINEA_PEDIDO, archPedidos);
    }


    fclose(archPedidos);
    fclose(archRecetas);
    fclose(archIngredientes);
    fclose(archRecetasIdx);
    fclose(archIngredientesIdx);

	return ret;
}

void obtenerNombreIndice_ALU(const char* nombreArch, char* nombreArchIdx)
{
    strcpy(nombreArchIdx, nombreArch);
    char* separador = strrchr(nombreArchIdx, '.');
    if (!separador)
        return;

    *separador = '\0';
    strcat(nombreArchIdx, ".idx\0");
}

int cargarProximoPedido_ALU(char* linea, Pedido* p)
{
    char separador = '	';
    char* act = strchr(linea, '\n');

    *act = '\0';
    act = strrchr(linea, separador);
    sscanf(act + 1, "%d", &p->cantidad);

    *act = '\0';
    act = strrchr(linea, separador);
    strncpy(p->codReceta, act + 1, TAM_COD_RECETA);

    *act = '\0';
    sscanf(linea, "%d", &p->nroPedido);

    return TODO_OK;
}

int cargarReceta_ALU(char* codReceta, Receta* receta, Vector* vector, FILE* archRecetas, FILE* archRecetasIdx)
{
    IndReceta idxReceta;

    //BUSCO EN EL INDICE
    fseek(archRecetasIdx, 0, SEEK_SET);
    while (!feof(archRecetasIdx))
    {
        fread(&idxReceta, sizeof(IndReceta), 1, archRecetasIdx);
        if (strcmp(idxReceta.codReceta, codReceta) == 0)
            break;
    }

    //SI FINALIZO EL ARCHIVO, NO EXISTE
    if (feof(archRecetasIdx))
        return ERR_RECETA_NO_ENCONTRADA;

    //SEGUN EL INDICE, VOY DIRECTO A LA POSICION
    fseek(archRecetas, idxReceta.nroReg * sizeof(Receta), SEEK_SET);
    while (!feof(archRecetas))
    {
        fread(receta, sizeof(Receta), 1, archRecetas);

        //SI YA NO HAY MAS INGREDIENTES DE ESA RECETA, PARO DE ITERAR
        if (strcmp(receta->codReceta, codReceta) != 0)
            break;

        vectorInsertarAlFinal(vector, receta);
    }

    return TODO_OK;
}

int actualizarIngredientes_ALU(Vector* vector, int cantidad, FILE* archIngredientes, FILE* archIngredientesIdx)
{
    Receta* receta;
    Ingrediente ingrediente;
    IndIngrediente idxIngrediente;
    VectorIterador vectorIterador;

    vectorItCrear(&vectorIterador, vector);
    receta = vectorItPrimero(&vectorIterador);

    //ITERO CON EL VECTOR TDA
    while (!vectorItFin(&vectorIterador))
    {
        //BUSCO EN EL INDICE
        fseek(archIngredientesIdx, 0, SEEK_SET);
        while (!feof(archIngredientesIdx))
        {
            fread(&idxIngrediente, sizeof(IndIngrediente), 1, archIngredientesIdx);
            if (strcmp(idxIngrediente.codIngr, receta->codIngr) == 0)
                break;
        }

        //SEGUN EL INDICE, VOY DIRECTO A LA POSICION
        fseek(archIngredientes, idxIngrediente.nroReg * sizeof(Ingrediente), SEEK_SET);
        fread(&ingrediente, sizeof(Ingrediente), 1, archIngredientes);

        ingrediente.stock -= (receta->cantidad * cantidad);

        fseek(archIngredientes, idxIngrediente.nroReg * sizeof(Ingrediente), SEEK_SET);
        fwrite(&ingrediente, sizeof(ingrediente), 1, archIngredientes);

        receta = vectorItSiguiente(&vectorIterador);
    }

    vectorVaciar(vector);

    return TODO_OK;
}
