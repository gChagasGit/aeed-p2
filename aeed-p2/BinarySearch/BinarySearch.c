// Código base para o BinarySearch

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../aeed-p2/input.h"

///////////////
// GLOBAL    //
///////////////
unsigned int counter_comparacao = 0;
unsigned int counter_movimentacao = 0;

///////////////
// ALGORITMO //
///////////////

#define NIL -1

typedef int TChave;

typedef struct
{
    TChave Chave;
    /* outros componentes */
} TItem;

typedef int TApontador;

typedef struct
{
    TItem *Item;
    int n, max;
} TDicionario;

/* Procedimentos e funções do TAD */

TDicionario *TDicionario_Inicia();
TApontador TDicionario_Pesquisa(TDicionario *D, TChave c);
int TDicionario_Insere(TDicionario *D, TItem x);
int TDicionario_Retira(TDicionario *D, TChave c);

/* Inicia um dicionário vazio */
TDicionario *TDicionario_Inicia()
{
    TDicionario *D;
    D = (TDicionario *)malloc(sizeof(TDicionario));
    D->n = 0;
    D->max = 10;
    D->Item = (TItem *)malloc(D->max * sizeof(TItem));
    return D;
}

/* Retorna um apontador para o item com chave c no dicionário */
TApontador TDicionario_Pesquisa(TDicionario *D, TChave c)
{
    TApontador meio, esq, dir;
    esq = 0;
    dir = D->n - 1;
    while (esq <= dir)
    {
        counter_comparacao++;
        meio = (esq + dir) / 2;
        if (c > D->Item[meio].Chave)
            esq = meio + 1;
        else if (c < D->Item[meio].Chave)
            dir = meio - 1;
        else
            return meio;
    }
    return NIL; // retorna -1 caso a chave não seja encontrada
}

/* Insere um item no dicionário */
int TDicionario_Insere(TDicionario *D, TItem x)
{
    TApontador i;
    if (TDicionario_Pesquisa(D, x.Chave) != NIL)
        return 0; // retorna 0 caso o item já estiver no dicionário

    if (D->n == D->max)
    {
        D->max *= 2;
        D->Item = (TItem *)realloc(D->Item, D->max * sizeof(TItem));
    }

    i = D->n - 1;
    while ((i >= 0) && (x.Chave < D->Item[i].Chave))
    {
        D->Item[i + 1] = D->Item[i];
        i--;
        counter_movimentacao++;
    }

    D->Item[i + 1] = x;
    D->n++;
    counter_movimentacao++;
    return 1;
}

/* Retira o item com chave c do dicionário */
int TDicionario_Retira(TDicionario *D, TChave c)
{
    TApontador i;
    i = TDicionario_Pesquisa(D, c);
    if (i == NIL)
        return 0; // retorna 0 caso o item não esteja no dicionário

    while (i < D->n - 1)
    {
        D->Item[i] = D->Item[i + 1];
        i++;
        counter_movimentacao++;
    }

    D->n--;
    if (4 * D->n == D->max)
    {
        D->max /= 2;
        D->Item = (TItem *)realloc(D->Item, D->max * sizeof(TItem));
    }
    return 1;
}

////////////////
// AUXILIARES //
////////////////

// Função para imprimir um array de TItem
void printArray(TItem *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i].Chave);
    }
    printf("\n");
}

////////////////
//    MAIN    //
////////////////
int main(int argc, char *argv[])
{
    clock_t start, end;
    double cpu_time_used;
    int N_array = 0;
    int *point;

    // Receber input
    if (argc < 3)
    {
        fprintf(stderr, "Uso: %s <modo> <quantidade>\n", argv[0]);
        return -1;
    }

    // Selecionar lista
    int seletor_modo = atoi(argv[1]);
    int seletor_qtde = atoi(argv[2]);
    point = selecionarArray(seletor_modo, seletor_qtde);
    N_array = getTamanhoArray(seletor_qtde);

    // Inicializar dicionário
    TDicionario *dicionario = TDicionario_Inicia();

    // Rodar algoritmo de inserção no dicionário
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TItem item;
        item.Chave = point[i];
        TDicionario_Insere(dicionario, item);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de inserção
    printf("TEMPO_INSERCAO=%f; COMP_INSERCAO=%u; REGIS_INSERCAO=%u\n", cpu_time_used, counter_comparacao, counter_movimentacao);

    // Imprimir estado do Dicionario apos inserção
    // printf("Dicionario apos insercao: (n=%d) ", dicionario->n);
    // printArray(dicionario->Item, dicionario->n);

    // Reset counters for search
    counter_comparacao = 0;
    counter_movimentacao = 0;

    // Rodar algoritmo de busca no dicionário
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TDicionario_Pesquisa(dicionario, point[i]);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de busca
    printf("TEMPO_BUSCA=%f; COMP_BUSCA=%u; REGIS_BUSCA=%u\n", cpu_time_used, counter_comparacao, counter_movimentacao);

    // Reset counters for delete
    counter_comparacao = 0;
    counter_movimentacao = 0;

    // Rodar algoritmo de remoção no dicionário
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TDicionario_Retira(dicionario, point[i]);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de remoção
    printf("TEMPO_REMOCAO=%f; COMP_REMOCAO=%u; REGIS_REMOCAO=%u\n", cpu_time_used, counter_comparacao, counter_movimentacao);

    // Imprimir estado do Dicionario apos remoção
    // printf("Dicionario apos remocao: (n=%d) ", dicionario->n);
    // printArray(dicionario->Item, dicionario->n);

    // Liberar memória
    free(dicionario->Item);
    free(dicionario);

    return 0;
}
