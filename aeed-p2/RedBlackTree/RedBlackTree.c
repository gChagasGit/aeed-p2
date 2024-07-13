#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../aeed-p2/input.h" // Implementa as funções selecionarArray e getTamanhoArray

///////////////
// GLOBAL    //
///////////////
unsigned int counter_comparacao = 0;

///////////////
// ALGORITMO //
///////////////

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
    int cor; // cor: 0, se for negro; 1, se for rubro
} TNo;

int EhNegro(TArvBin No)
{
    return (No == NULL) || (No->cor == 0);
}

int EhRubro(TArvBin No)
{
    return (No != NULL) && (No->cor == 1);
}

void InverteCor(TArvBin No)
{
    if (No != NULL)
        No->cor = !No->cor;
}

void TrocaCores(TArvBin No)
{
    InverteCor(No);
    InverteCor(No->Esq);
    InverteCor(No->Dir);
}

void RotacaoDireita(TArvBin *pA)
{
    TArvBin pB = (*pA)->Esq;
    (*pA)->Esq = pB->Dir;
    pB->Dir = *pA;
    *pA = pB;
}

void RotacaoEsquerda(TArvBin *pA)
{
    TArvBin pB = (*pA)->Dir;
    (*pA)->Dir = pB->Esq;
    pB->Esq = *pA;
    *pA = pB;
}

void BalancaNo(TArvBin *pA)
{
    if (EhRubro((*pA)->Dir) && EhNegro((*pA)->Esq))
        RotacaoEsquerda(pA);
    if (EhRubro((*pA)->Esq) && EhRubro((*pA)->Esq->Esq))
        RotacaoDireita(pA);
    if (EhRubro((*pA)->Esq) && EhRubro((*pA)->Dir))
        TrocaCores(*pA);
}

void TDicionario_InsereRecursivo(TArvBin *pA, TArvBin *pC, TItem x)
{
    if (*pA == NULL)
    {
        *pA = (TArvBin)malloc(sizeof(TNo));
        (*pA)->Item = x;
        (*pA)->Esq = NULL;
        (*pA)->Dir = NULL;
        (*pA)->cor = 1; // o novo nó é rubro
    }
    else if (x.Chave < (*pA)->Item.Chave)
    {
        counter_comparacao++;
        TDicionario_InsereRecursivo(&(*pA)->Esq, pA, x);
        BalancaNo(pA);
    }
    else if (x.Chave > (*pA)->Item.Chave)
    {
        counter_comparacao++;
        TDicionario_InsereRecursivo(&(*pA)->Dir, pA, x);
        BalancaNo(pA);
    }
}

void TDicionario_Insere(TArvBin *pRaiz, TItem x)
{
    TDicionario_InsereRecursivo(pRaiz, NULL, x);
    (*pRaiz)->cor = 0; // a raiz é negra
}

int TDicionario_Pesquisa(TArvBin No, int x)
{
    while (No != NULL)
    {
        counter_comparacao++;
        if (x == No->Item.Chave)
        {
            return 1; // elemento encontrado
        }
        else if (x < No->Item.Chave)
        {
            No = No->Esq; // busca na subárvore esquerda
        }
        else
        {
            No = No->Dir; // busca na subárvore direita
        }
    }
    return 0; // elemento não encontrado
}

void Sucessor(TArvBin *q, TArvBin *r)
{
    if ((*r)->Esq != NULL)
    {
        Sucessor(q, &(*r)->Esq);
        BalancaNo(r);
    }
    else
    {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Dir;
    }
}

int RetiraRecursivo(TArvBin *p, TChave x)
{
    TArvBin q;
    if (*p == NULL)
        return 0; // item não encontrado

    if (x < (*p)->Item.Chave)
    {
        counter_comparacao++;
        if (RetiraRecursivo(&(*p)->Esq, x))
            BalancaNo(p);
    }
    else if (x > (*p)->Item.Chave)
    {
        counter_comparacao++;
        if (RetiraRecursivo(&(*p)->Dir, x))
            BalancaNo(p);
    }
    else
    {
        q = *p;
        if (q->Esq == NULL)
        {
            *p = q->Dir;
            free(q);
        }
        else if (q->Dir == NULL)
        {
            *p = q->Esq;
            free(q);
        }
        else
        {
            Sucessor(&q, &q->Dir);
            free(q);
        }
    }
    return 1;
}

int Retira(TArvBin *p, TChave x)
{
    if (*p == NULL)
        return 0; // árvore vazia

    if (EhNegro(*p) && EhNegro((*p)->Esq) && EhNegro((*p)->Dir))
    {
        (*p)->cor = 1;
        int res = RetiraRecursivo(p, x);
        if (*p != NULL)
            (*p)->cor = 0;
        return res;
    }
    else
    {
        return RetiraRecursivo(p, x);
    }
}

void printInOrder(TArvBin No)
{
    if (No != NULL)
    {
        printInOrder(No->Esq);
        printf("%d ", No->Item.Chave);
        printInOrder(No->Dir);
    }
}

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
    TArvBin dicionario = NULL;

    // Rodar algoritmo de inserção no dicionário
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TItem item;
        item.Chave = point[i];
        TDicionario_Insere(&dicionario, item);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de inserção
    printf("TEMPO_INSERCAO=%f; COMP_INSERCAO=%u\n", cpu_time_used, counter_comparacao);

    // Reset counters for search
    counter_comparacao = 0;

    // Rodar algoritmo de busca no dicionário
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TDicionario_Pesquisa(dicionario, point[i]);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de busca
    printf("TEMPO_BUSCA=%f; COMP_BUSCA=%u\n", cpu_time_used, counter_comparacao);

    // Reset counters for delete
    counter_comparacao = 0;

    // Rodar algoritmo de remoção no dicionário
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        Retira(&dicionario, point[i]);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de remoção
    printf("TEMPO_REMOCAO=%f; COMP_REMOCAO=%u\n", cpu_time_used, counter_comparacao);

    // Liberar memória
    free(point);

    return 0;
}
