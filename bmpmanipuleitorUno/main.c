#include "funciones_estudiante.h"
#include "constantes.h"

int main(int argc, char* argv[])
{
    int result = solucion(argc, argv);
    if(result!=TODO_OK)
        return ARCHIVO_NO_ENCONTRADO;

    return TODO_OK;
}
