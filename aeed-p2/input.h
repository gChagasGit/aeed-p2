#pragma once

#include "../aeed-p2/listas_header/lista_aleatoria_10.h"
#include "../aeed-p2/listas_header/lista_aleatoria_100.h"
#include "../aeed-p2/listas_header/lista_aleatoria_1000.h"
#include "../aeed-p2/listas_header/lista_aleatoria_10000.h"
#include "../aeed-p2/listas_header/lista_aleatoria_100000.h"
#include "../aeed-p2/listas_header/lista_aleatoria_1000000.h"
#include "../aeed-p2/listas_header/lista_inversa_10.h"
#include "../aeed-p2/listas_header/lista_inversa_100.h"
#include "../aeed-p2/listas_header/lista_inversa_1000.h"
#include "../aeed-p2/listas_header/lista_inversa_10000.h"
#include "../aeed-p2/listas_header/lista_inversa_100000.h"
#include "../aeed-p2/listas_header/lista_inversa_1000000.h"
#include "../aeed-p2/listas_header/lista_ordenada_10.h"
#include "../aeed-p2/listas_header/lista_ordenada_100.h"
#include "../aeed-p2/listas_header/lista_ordenada_1000.h"
#include "../aeed-p2/listas_header/lista_ordenada_10000.h"
#include "../aeed-p2/listas_header/lista_ordenada_100000.h"
#include "../aeed-p2/listas_header/lista_ordenada_1000000.h"
#include "../aeed-p2/listas_header/lista_quase_10.h"
#include "../aeed-p2/listas_header/lista_quase_100.h"
#include "../aeed-p2/listas_header/lista_quase_1000.h"
#include "../aeed-p2/listas_header/lista_quase_10000.h"
#include "../aeed-p2/listas_header/lista_quase_100000.h"
#include "../aeed-p2/listas_header/lista_quase_1000000.h"

int getTamanhoArray(int seletor_qtde)
{
    if (seletor_qtde == 1)
    {
        return 10;
    }
    if (seletor_qtde == 2)
    {
        return 100;
    }
    if (seletor_qtde == 3)
    {
        return 1000;
    }
    if (seletor_qtde == 4)
    {
        return 10000;
    }
    if (seletor_qtde == 5)
    {
        return 100000;
    }
    if (seletor_qtde == 6)
    {
        return 1000000;
    }
}

int *selecionarArray(int seletor_modo, int seletor_qtde)
{
    switch (seletor_modo)
    {
    case 1:
        if (seletor_qtde == 1)
        {
            return ordenada_10;
        }
        if (seletor_qtde == 2)
        {
            return ordenada_100;
        }
        if (seletor_qtde == 3)
        {
            return ordenada_1000;
        }
        if (seletor_qtde == 4)
        {
            return ordenada_10000;
        }
        if (seletor_qtde == 5)
        {
            return ordenada_100000;
        }
        if (seletor_qtde == 6)
        {
            return ordenada_1000000;
        }

        break;
    case 2:
        if (seletor_qtde == 1)
        {
            return inversa_10;
        }
        if (seletor_qtde == 2)
        {
            return inversa_100;
        }
        if (seletor_qtde == 3)
        {
            return inversa_1000;
        }
        if (seletor_qtde == 4)
        {
            return inversa_10000;
        }
        if (seletor_qtde == 5)
        {
            return inversa_100000;
        }
        if (seletor_qtde == 6)
        {
            return inversa_1000000;
        }
        break;
    case 3:
        if (seletor_qtde == 1)
        {
            return quase_10;
        }
        if (seletor_qtde == 2)
        {
            return quase_100;
        }
        if (seletor_qtde == 3)
        {
            return quase_1000;
        }
        if (seletor_qtde == 4)
        {
            return quase_10000;
        }
        if (seletor_qtde == 5)
        {
            return quase_100000;
        }
        if (seletor_qtde == 6)
        {
            return quase_1000000;
        }
        break;
    case 4:
        if (seletor_qtde == 1)
        {
            return aleatoria_10;
        }
        if (seletor_qtde == 2)
        {
            return aleatoria_100;
        }
        if (seletor_qtde == 3)
        {
            return aleatoria_1000;
        }
        if (seletor_qtde == 4)
        {
            return aleatoria_10000;
        }
        if (seletor_qtde == 5)
        {
            return aleatoria_100000;
        }
        if (seletor_qtde == 6)
        {
            return aleatoria_1000000;
        }
        break;
    default:
        return -2;
    }
}