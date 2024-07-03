#include "funciones_genericas.h"

bool _ampliarCapVector(Vector* vector);
void* _buscarMenor(void* ini, void* fin, size_t tamElem, Cmp cmp);
void _buscarMenorYMayor(void* ini, void* fin, void** pDMenor, void** pDMayor, size_t tamElem, Cmp cmp);
bool _vectorOrdBuscar(const Vector* vector, const void* elem, void** pos, Cmp cmp);

bool vectorCrear(Vector* vector, size_t tamElem)
{
    vector->vec = malloc(CAP_INI * tamElem);

    if(!vector->vec)
        return false;

    vector->ce = 0;
    vector->cap = CAP_INI;
    vector->tamElem = tamElem;
    return true;
}

int vectorInsertarAlFinal(Vector* vector, const void* elem)
{
    if(vector->ce == vector->cap)
    {
        if(!_ampliarCapVector(vector))
            return SIN_MEM;
    }

    void* posIns = vector->vec + vector->ce * vector->tamElem;
    memcpy(posIns, elem, vector->tamElem);
    vector->ce++;

    return TODO_OK;
}

bool _ampliarCapVector(Vector* vector)
{
    size_t nCap = vector->cap * 1.5;
    void *nVec = realloc(vector->vec, nCap * vector->tamElem);

    if(!nVec)
        return false;

    vector->vec = nVec;
    vector->cap = nCap;

    return true;
}

int vectorOrdBuscar(const Vector* vector, void* elem, Cmp cmp)
{
    void* pos;
    bool existe = _vectorOrdBuscar(vector, elem, &pos, cmp);

    if(existe)
        memcpy(elem, pos, vector->tamElem);

    return existe ? (pos - vector->vec) / vector->tamElem : -1;
}

void vectorOrdenarSeleccion(Vector* vector, Cmp cmp)
{
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;
    void* m;
    for(void* i = vector->vec; i < ult; i += vector->tamElem)
    {
        m = _buscarMenor(i, ult, vector->tamElem, cmp);
        intercambiar(m, i, vector->tamElem);
    }
}

void* _buscarMenor(void* ini, void* fin, size_t tamElem, Cmp cmp)
{
    void* m = ini;

    for(void* j = ini + tamElem; j <= fin; j += tamElem)
    {
        if(cmp(j, m) < 0)
        {
            m = j;
        }
    }

    return m;
}

void intercambiar(void* a, void* b, size_t tamElem)
{
    void* aTemp = malloc(tamElem);

    memcpy(aTemp, a, tamElem);
    memcpy(a, b, tamElem);
    memcpy(b, aTemp, tamElem);

    free(aTemp);
}

void vectorOrdenarSeleccionV2(Vector* vector, Cmp cmp)
{
    void* ult = vector->vec + (vector->ce + 1) * vector->tamElem;
    void* menor, *mayor;
    void* i1 = vector->vec;
    void* i2 = ult;

    while(i1 < i2)
    {
        _buscarMenorYMayor(i1, i2, &menor, &mayor, vector->tamElem, cmp);

        intercambiar(menor, i1, vector->tamElem);

        if(mayor == i1)
            mayor = menor;

        intercambiar(mayor, i2, vector->tamElem);

        i1 += vector->tamElem;
        i2 -= vector->tamElem;
    }
}

void _buscarMenorYMayor(void* ini, void* fin, void** pDMenor, void** pDMayor, size_t tamElem, Cmp cmp)
{
    void* menor = ini;
    void* mayor = ini;
    for(void* j = ini + tamElem; j <= fin; j += tamElem)
    {
        if(cmp(j, menor) < 0)
            menor = j;

        if(cmp(j, mayor) > 0)
            mayor = j;
    }

    *pDMenor = menor;
    *pDMayor = mayor;
}

void vectorVaciar(Vector* vector)
{
    vector->cap = CAP_INI;
    vector->ce = 0;
    vector->vec = realloc(vector->vec, CAP_INI * vector->tamElem);
}

int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp)
{
    if(vector->ce == vector->cap)
    {
        if(!_ampliarCapVector(vector))
            return SIN_MEM;
    }

    void* posIns;
    bool existe = _vectorOrdBuscar(vector, elem, &posIns, cmp);

    if(existe)
        return DUPLICADO;

    for(void* i = vector->vec + (vector->ce - 1)* vector->tamElem; i >= posIns; i -= vector->tamElem)
        memcpy(i + vector->tamElem, i, vector->tamElem);

    memcpy(posIns, elem, vector->tamElem);
    vector->ce++;

    return TODO_OK;
}

bool _vectorOrdBuscar(const Vector* vector, const void* elem, void** pos, Cmp cmp)
{
    void* li = vector->vec, * ls = vector->vec + (vector->ce - 1) * vector->tamElem, * m;
    int comp;

    while(li <= ls)
    {
        m = li + (ls - li) / vector->tamElem / 2;
        comp = cmp(elem, m);

        if(comp == 0)
        {
            *pos = m;
            return true;
        }

        if(comp < 0)
            ls = m -1;
        else
            li = m +1;
    }

    *pos = li;

    return false;
}

bool vectorOrdEliminarElem(Vector* vector, void* elem, Cmp cmp)
{
    void* posElim;
    bool existe = _vectorOrdBuscar(vector, elem, &posElim, cmp);

    if(!existe)
        return false;

    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;
    for(void* i = posElim; i < ult; i += vector->tamElem)
        memcpy(i, i + vector->tamElem, vector->tamElem);

    vector->ce--;

    if(vector->ce > CAP_INI && (float)vector->ce / vector->cap <= FACTOR_OCUP)
    {
        vector->cap *= FACTOR_DECR;
        vector->vec = realloc(vector->vec, vector->cap * vector->tamElem);
    }

    return true;
}

void vectorInsertarRandom(Vector* vector, int ce)
{
    srand(time(NULL));

    int e;
    for(int i = 1; i <= ce; i++)
    {
        e = 1 + rand() % 30;
        vectorInsertarAlFinal(vector, &e);
    }
}

void vectorMostrar(Vector* vector, Imprimir imprimir)
{
    void* ult = vector->vec + (vector->ce - 1) * vector->tamElem;

    for(void* i = vector->vec; i <= ult; i += vector->tamElem)
    {
        imprimir(i);
        putchar('\n');
    }

    putchar('\n');
}

void vectorDestruir(Vector* vector)
{
    free(vector->vec);
    vector->vec = NULL;
}
