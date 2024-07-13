// Código base para o Treap

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
    int Prioridade;
} TItem;

typedef struct NoTreap
{
    TItem item;
    struct NoTreap *esquerda;
    struct NoTreap *direita;
} NoTreap;

typedef struct
{
    NoTreap *raiz;
} Treap;

/* Procedimentos e funções do TAD */

Treap *TDicionario_Inicia();
NoTreap *novoNo(TItem item);
NoTreap *TDicionario_Pesquisa(Treap *T, TChave c);
void TDicionario_Divide(NoTreap *T, TChave c, NoTreap **L, NoTreap **R);
NoTreap *TDicionario_Junta(NoTreap *L, NoTreap *R);
int TDicionario_Insere(Treap *T, TItem item);
int TDicionario_Retira(Treap *T, TChave c);
void emOrdem(NoTreap *raiz);

/* Inicia um Treap vazio */
Treap *TDicionario_Inicia()
{
    Treap *T = (Treap *)malloc(sizeof(Treap));
    T->raiz = NULL;
    return T;
}

/* Cria um novo nó do Treap */
NoTreap *novoNo(TItem item)
{
    NoTreap *temp = (NoTreap *)malloc(sizeof(NoTreap));
    temp->item = item;
    temp->esquerda = temp->direita = NULL;
    return temp;
}

/* Função para buscar uma chave no Treap */
NoTreap *TDicionario_Pesquisa(Treap *T, TChave c)
{
    NoTreap *atual = T->raiz;
    while (atual != NULL && atual->item.Chave != c)
    {
        counter_comparacao++;
        if (c < atual->item.Chave)
            atual = atual->esquerda;
        else
            atual = atual->direita;
    }
    return atual;
}

/* Divide o Treap em L e R conforme a chave c */
void TDicionario_Divide(NoTreap *T, TChave c, NoTreap **L, NoTreap **R)
{
    if (T == NULL)
    {
        *L = *R = NULL;
    }
    else if (c < T->item.Chave)
    {
        counter_comparacao++;
        TDicionario_Divide(T->esquerda, c, L, &T->esquerda);
        *R = T;
    }
    else
    {
        TDicionario_Divide(T->direita, c, &T->direita, R);
        *L = T;
    }
}

/* Junta dois Treaps L e R */
NoTreap *TDicionario_Junta(NoTreap *L, NoTreap *R)
{
    if (L == NULL)
        return R;
    if (R == NULL)
        return L;
    if (L->item.Prioridade > R->item.Prioridade)
    {
        L->direita = TDicionario_Junta(L->direita, R);
        return L;
    }
    else
    {
        R->esquerda = TDicionario_Junta(L, R->esquerda);
        return R;
    }
}

/* Insere um item no Treap */
int TDicionario_Insere(Treap *T, TItem item)
{
    NoTreap *novo_no = novoNo(item);
    if (T->raiz == NULL)
    {
        T->raiz = novo_no;
        return 1;
    }

    NoTreap *L, *R;
    TDicionario_Divide(T->raiz, item.Chave, &L, &R);
    T->raiz = TDicionario_Junta(TDicionario_Junta(L, novo_no), R);
    return 1;
}

/* Remove um nó com uma chave específica do Treap */
int TDicionario_Retira(Treap *T, TChave c)
{
    NoTreap *L, *R;
    TDicionario_Divide(T->raiz, c, &L, &R);
    TDicionario_Divide(R, c + 1, &T->raiz, &R);
    return (R != NULL);
}

/* Percorre o Treap em ordem */
void emOrdem(NoTreap *raiz)
{
    if (raiz)
    {
        emOrdem(raiz->esquerda);
        printf("chave: %d | prioridade: %d\n", raiz->item.Chave, raiz->item.Prioridade);
        emOrdem(raiz->direita);
    }
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

    // Inicializar Treap
    Treap *treap = TDicionario_Inicia();

    // Rodar algoritmo de inserção no Treap
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TItem item;
        item.Chave = point[i];
        item.Prioridade = rand() % 100; // Prioridade aleatória para manter o Treap balanceado
        TDicionario_Insere(treap, item);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de inserção
    printf("TEMPO_INSERCAO=%f; COMP_INSERCAO=%u\n", cpu_time_used, counter_comparacao);

    // Imprimir estado do Treap após inserção
    // printf("Estado do Treap após inserção:\n");
    // emOrdem(treap->raiz);

    // Resetar contadores para busca
    counter_comparacao = 0;

    // Rodar algoritmo de busca no Treap
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TDicionario_Pesquisa(treap, point[i]);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de busca
    printf("TEMPO_BUSCA=%f; COMP_BUSCA=%u\n", cpu_time_used, counter_comparacao);

    // Resetar contadores para remoção
    counter_comparacao = 0;

    // Rodar algoritmo de remoção no Treap
    start = clock();
    for (int i = 0; i < N_array; i++)
    {
        TDicionario_Retira(treap, point[i]);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Plotar resultados de remoção
    printf("TEMPO_REMOCAO=%f; COMP_REMOCAO=%u\n", cpu_time_used, counter_comparacao);

    // Liberar memória
    free(treap);

    return 0;
}