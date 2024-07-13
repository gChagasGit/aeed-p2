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
    int fb; // fator de balanceamento: -1, 0, +1
} TNo;

/* Procedimentos e funções da AVL */

TArvBin Inicializa();
int Altura(TArvBin No);
int FB(TArvBin No);
void LL(TArvBin *pA);
void RR(TArvBin *pA);
void LR(TArvBin *pA);
void RL(TArvBin *pA);
int BalancaEsquerda(TArvBin *pNo);
int BalancaDireita(TArvBin *pNo);
int BalancaNo(TArvBin *pNo);
int Insere(TArvBin *pNo, TItem x);
int Retira(TArvBin *p, TChave c);
int Busca(TArvBin No, TChave c);
int Sucessor(TArvBin *q, TArvBin *r);

/* Inicia uma árvore AVL vazia */
TArvBin Inicializa()
{
    return NULL;
}

int Altura(TArvBin No)
{
    int hEsq, hDir;
    if (No == NULL)
        return -1; // altura de árvore vazia é -1
    hEsq = Altura(No->Esq);
    hDir = Altura(No->Dir);
    return (hEsq > hDir) ? hEsq + 1 : hDir + 1;
}

int FB(TArvBin No)
{
    if (No == NULL)
        return 0;
    return Altura(No->Esq) - Altura(No->Dir);
}

void LL(TArvBin *pA)
{
    TArvBin pB = (*pA)->Esq;
    (*pA)->Esq = pB->Dir;
    pB->Dir = *pA;
    if (pB->fb == 0)
    {
        (*pA)->fb = +1;
        pB->fb = -1;
    }
    else
    {
        (*pA)->fb = 0;
        pB->fb = 0;
    }
    *pA = pB;
}

void RR(TArvBin *pA)
{
    TArvBin pB = (*pA)->Dir;
    (*pA)->Dir = pB->Esq;
    pB->Esq = *pA;
    if (pB->fb == 0)
    {
        (*pA)->fb = -1;
        pB->fb = +1;
    }
    else
    {
        (*pA)->fb = 0;
        pB->fb = 0;
    }
    *pA = pB;
}

void LR(TArvBin *pA)
{
    TArvBin pB = (*pA)->Esq;
    TArvBin pC = pB->Dir;
    pB->Dir = pC->Esq;
    pC->Esq = pB;
    (*pA)->Esq = pC->Dir;
    pC->Dir = *pA;
    if (pC->fb == +1)
        (*pA)->fb = -1;
    else
        (*pA)->fb = 0;
    if (pC->fb == -1)
        pB->fb = +1;
    else
        pB->fb = 0;
    pC->fb = 0;
    *pA = pC;
}

void RL(TArvBin *pA)
{
    TArvBin pB = (*pA)->Dir;
    TArvBin pC = pB->Esq;
    pB->Esq = pC->Dir;
    pC->Dir = pB;
    (*pA)->Dir = pC->Esq;
    pC->Esq = *pA;
    if (pC->fb == -1)
        (*pA)->fb = +1;
    else
        (*pA)->fb = 0;
    if (pC->fb == +1)
        pB->fb = -1;
    else
        pB->fb = 0;
    pC->fb = 0;
    *pA = pC;
}

int BalancaEsquerda(TArvBin *pNo)
{
    int fbe = FB((*pNo)->Esq);
    if (fbe > 0)
    {
        LL(pNo);
        return 1;
    }
    else if (fbe < 0)
    {
        LR(pNo);
        return 1;
    }
    else
    {
        LL(pNo);
        return 0;
    }
}

int BalancaDireita(TArvBin *pNo)
{
    int fbd = FB((*pNo)->Dir);
    if (fbd < 0)
    {
        RR(pNo);
        return 1;
    }
    else if (fbd > 0)
    {
        RL(pNo);
        return 1;
    }
    else
    {
        RR(pNo);
        return 0;
    }
}

int BalancaNo(TArvBin *pNo)
{
    int fb = FB(*pNo);
    if (fb > 1)
        return BalancaEsquerda(pNo);
    else if (fb < -1)
        return BalancaDireita(pNo);
    return 0;
}

int Insere(TArvBin *pNo, TItem x)
{
    counter_comparacao++; // Incrementa comparação
    if (*pNo == NULL)
    {
        *pNo = (TArvBin)malloc(sizeof(TNo));
        (*pNo)->Item = x;
        (*pNo)->Esq = NULL;
        (*pNo)->Dir = NULL;
        (*pNo)->fb = 0;
        return 1;
    }
    else if (x.Chave < (*pNo)->Item.Chave)
    {
        if (Insere(&(*pNo)->Esq, x))
            switch ((*pNo)->fb)
            {
            case -1:
                (*pNo)->fb = 0;
                return 0;
            case 0:
                (*pNo)->fb = +1;
                return 1;
            case +1:
                return !BalancaEsquerda(pNo);
            }
        return 0;
    }
    else if (x.Chave > (*pNo)->Item.Chave)
    {
        if (Insere(&(*pNo)->Dir, x))
            switch ((*pNo)->fb)
            {
            case +1:
                (*pNo)->fb = 0;
                return 0;
            case 0:
                (*pNo)->fb = -1;
                return 1;
            case -1:
                return !BalancaDireita(pNo);
            }
        return 0;
    }
    else
        return 0; // retorna 0 caso o item já estiver na árvore
}

int Retira(TArvBin *p, TChave c)
{
    counter_comparacao++; // Incrementa comparação
    TArvBin q;
    int ret;
    if (*p == NULL)
        return 0; // retorna 0 caso o item não esteja na árvore
    else if (c < (*p)->Item.Chave)
    {
        if (Retira(&(*p)->Esq, c))
            switch ((*p)->fb)
            {
            case +1:
                (*p)->fb = 0;
                return 1;
            case 0:
                (*p)->fb = -1;
                return 0;
            case -1:
                return BalancaDireita(p);
            }
        return 0;
    }
    else if (c > (*p)->Item.Chave)
    {
        if (Retira(&(*p)->Dir, c))
            switch ((*p)->fb)
            {
            case -1:
                (*p)->fb = 0;
                return 1;
            case 0:
                (*p)->fb = +1;
                return 0;
            case +1:
                return BalancaEsquerda(p);
            }
        return 0;
    }
    else
    {
        q = *p;
        if (q->Esq == NULL)
        {
            *p = q->Dir;
            ret = 1;
        }
        else if (q->Dir == NULL)
        {
            *p = q->Esq;
            ret = 1;
        }
        else
        {
            ret = Sucessor(&q, &q->Esq);
            if (ret)
                switch ((*p)->fb)
                {
                case +1:
                    (*p)->fb = 0;
                    return 1;
                case 0:
                    (*p)->fb = -1;
                    return 0;
                case -1:
                    return BalancaDireita(p);
                }
        }
        free(q);
        return ret;
    }
}

int Sucessor(TArvBin *q, TArvBin *r)
{
    int ret;
    if ((*r)->Dir != NULL)
    {
        if (Sucessor(q, &(*r)->Dir))
            switch ((*r)->fb)
            {
            case -1:
                (*r)->fb = 0;
                return 1;
            case 0:
                (*r)->fb = +1;
                return 0;
            case +1:
                return BalancaEsquerda(r);
            }
        return 0;
    }
    else
    {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Esq;
        return 1;
    }
}

int Busca(TArvBin No, TChave c)
{
    counter_comparacao++; // Incrementa comparação
    if (No == NULL)
        return 0;
    else if (c < No->Item.Chave)
        return Busca(No->Esq, c);
    else if (c > No->Item.Chave)
        return Busca(No->Dir, c);
    else
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

    // Inicializar árvore AVL
    TArvBin arvoreAVL = Inicializa();

    // Rodar algoritmo de inserção na árvore AVL
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TItem item;
        item.Chave = point[i];
        Insere(&arvoreAVL, item);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de inserção
    printf("TEMPO_INSERCAO=%f; COMP_INSERCAO=%u\n", cpu_time_used, counter_comparacao);

    // Imprimir estado da árvore AVL após inserção
    // printf("Arvore AVL apos insercao: ");
    // printAVL(arvoreAVL);
    // printf("\n");

    // Reset counters for search
    counter_comparacao = 0;

    // Rodar algoritmo de busca na árvore AVL
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TChave chave = point[i];
        Busca(arvoreAVL, chave);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de busca
    printf("TEMPO_BUSCA=%f; COMP_BUSCA=%u\n", cpu_time_used, counter_comparacao);

    // Reset counters for delete
    counter_comparacao = 0;

    // Rodar algoritmo de remoção na árvore AVL
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TChave chave = point[i];
        Retira(&arvoreAVL, chave);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de remoção
    printf("TEMPO_REMOCAO=%f; COMP_REMOCAO=%u\n", cpu_time_used, counter_comparacao);

    // Imprimir estado da árvore AVL após remoção
    // printf("Arvore AVL apos remocao: ");
    // printAVL(arvoreAVL);
    // printf("\n");

    // Liberar memória
    free(arvoreAVL);

    return 0;
}
