// Código base para o BinarySearchTree adaptado ao modelo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../aeed-p2/input.h" // Implementa as funções selecionarArray e getTamanhoArray

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

typedef struct SNo *TArvBin;

typedef struct SNo
{
    TItem Item;
    TArvBin Esq, Dir;
} TNo;

typedef TArvBin TApontador;

typedef struct
{
    TArvBin Raiz;
    int n, max;
} TDicionario;

/* Procedimentos e funções do TAD */

TDicionario *TAD_ArvBin_Inicia();
TApontador TAD_ArvBin_Pesquisa(TDicionario *D, TChave c);
int TAD_ArvBin_Insere(TDicionario *D, TItem x);
int TAD_ArvBin_Retira(TDicionario *D, TChave c);

/* Inicia um dicionário vazio */
TDicionario *TAD_ArvBin_Inicia()
{
    TDicionario *D;
    D = (TDicionario *)malloc(sizeof(TDicionario));
    D->n = 0;
    D->max = 10;
    D->Raiz = NULL;
    return D;
}

TApontador Pesquisa(TArvBin Raiz, TChave c)
{
    TArvBin No;

    No = Raiz;
    while ((No != NULL) && (c != No->Item.Chave))
    {
        counter_comparacao++;
        if (c < No->Item.Chave)
            No = No->Esq;
        else if (c > No->Item.Chave)
            No = No->Dir;
    }

    return No;
}

int Insere(TArvBin *pRaiz, TItem x)
{
    TArvBin *pNo;
    pNo = pRaiz;
    while ((*pNo != NULL) && (x.Chave != (*pNo)->Item.Chave))
    {
        counter_comparacao++;
        if (x.Chave < (*pNo)->Item.Chave)
            pNo = &(*pNo)->Esq;
        else if (x.Chave > (*pNo)->Item.Chave)
            pNo = &(*pNo)->Dir;
    }
    if (*pNo == NULL)
    {
        *pNo = (TArvBin)malloc(sizeof(TNo));
        (*pNo)->Item = x;
        (*pNo)->Esq = NULL;
        (*pNo)->Dir = NULL;
        return 1;
    }
    return 0; // retorna 0 caso o item já esteja na árvore
}

void Predecessor(TArvBin *q, TArvBin *r)
{
    if ((*r)->Dir != NULL)
        Predecessor(q, &(*r)->Dir);
    else
    {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Esq;
        counter_movimentacao++;
    }
}

void Sucessor(TArvBin *q, TArvBin *r)
{
    if ((*r)->Esq != NULL)
        Sucessor(q, &(*r)->Esq);
    else
    {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Dir;
        counter_movimentacao++;
    }
}

int Retira(TArvBin *pRaiz, TChave c)
{
    TArvBin *p, q;
    p = pRaiz;
    while ((*p != NULL) && (c != (*p)->Item.Chave))
    {
        counter_comparacao++;
        if (c < (*p)->Item.Chave)
            p = &(*p)->Esq;
        else if (c > (*p)->Item.Chave)
            p = &(*p)->Dir;
    }
    if (*p != NULL)
    {
        q = *p;
        if (q->Esq == NULL)
            *p = q->Dir;
        else if (q->Dir == NULL)
            *p = q->Esq;
        else
            Sucessor(&q, &q->Dir);
        free(q);
        counter_movimentacao++;
        return 1;
    }
    return 0; // retorna 0 caso o item não esteja na árvore
}

/* Retorna um apontador para o item com chave c no dicionário */
TApontador TAD_ArvBin_Pesquisa(TDicionario *D, TChave c)
{
    return Pesquisa(D->Raiz, c);
}

/* Insere um item no dicionário */
int TAD_ArvBin_Insere(TDicionario *D, TItem x)
{
    if (!Insere(&D->Raiz, x))
        return 0; // retorna 0 caso o item já esteja no dicionário

    D->n++;
    return 1;
}

/* Retira o item com chave c do dicionário */
int TAD_ArvBin_Retira(TDicionario *D, TChave c)
{
    if (!Retira(&D->Raiz, c))
        return 0; // retorna 0 caso o item não esteja no dicionário

    D->n--;
    return 1;
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
    TDicionario *dicionario = TAD_ArvBin_Inicia();

    // Rodar algoritmo de inserção no dicionário
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TItem item;
        item.Chave = point[i];
        TAD_ArvBin_Insere(dicionario, item);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de inserção
    printf("TEMPO_INSERCAO=%f; COMP_INSERCAO=%u; REGIS_INSERCAO=%u\n", cpu_time_used, counter_comparacao, counter_movimentacao);

    // Reset counters for search
    counter_comparacao = 0;
    counter_movimentacao = 0;

    // Rodar algoritmo de busca no dicionário
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TAD_ArvBin_Pesquisa(dicionario, point[i]);
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
        TAD_ArvBin_Retira(dicionario, point[i]);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de remoção
    printf("TEMPO_REMOCAO=%f; COMP_REMOCAO=%u; REGIS_REMOCAO=%u\n", cpu_time_used, counter_comparacao, counter_movimentacao);

    // Liberar memória
    free(dicionario);

    return 0;
}
