// Código base para o BinarySearch

#define NIL -1

typedef int TChave;

typedef struct
{
    TChave Chave;
    /* outros compomentes */
} TItem;

typedef int TApontador;

typedef struct
{
    TItem *Item;
    int n, max;
} TDicionario;

/* Inicia um dicionario vazio */
TDicionario *TDicionario_Inicia()
{
    TDicionario *D;
    D = (TDicionario *)malloc(sizeof(TDicionario));
    D->n = 0;
    D->max = 10;
    D->Item = (TItem *)malloc(D->max * sizeof(TItem));
    return D;
}

/* Retorna um apontador para o item com chave c no dicionario */
TApontador TDicionario_Pesquisa(TDicionario *D, TChave c)
{
    TApontador meio, esq, dir;
    esq = 0;
    dir = D->n - 1;
    while (esq <= dir)
    {
        meio = (esq + dir) / 2;
        if (c > D->Item[meio].Chave)
            esq = meio + 1;
        else if (c < D->Item[meio].Chave)
            dir = meio - 1;
        else
            return meio;
    }
    return NIL; // retorna -1 caso a chave nao seja encontrada
}

/* Insere um item no dicionario */
int TDicionario_Insere(TDicionario *D, TItem x)
{
    TApontador i;
    if (TDicionario_Pesquisa(D, x.Chave) != NIL)
        return 0; // retorna 0 caso o item ja estiver no dicionario
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
    }
    D->Item[i + 1] = x;
    D->n++;
    return 1;
}

/* Insere um item no dicionario */
int TDicionario_Insere(TDicionario *D, TItem x)
{
    TApontador i;
    if (TDicionario_Pesquisa(D, x.Chave) != NIL)
        return 0; // retorna 0 caso o item ja estiver no dicionario
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
    }
    D->Item[i + 1] = x;
    D->n++;
    return 1;
}

/* Retira o item com chave c do dicionario */
int TDicionario_Retira(TDicionario *D, TChave c)
{
    TApontador i;
    i = TDicionario_Pesquisa(D, c);
    if (i == NIL)
        return 0; // retorna 0 caso o item nao esteja no dicionario
    while (i < D->n - 1)
    {
        D->Item[i] = D->Item[i + 1];
        i++;
    }
    D->n--;
    if (4 * D->n == D->max)
    {
        D->max /= 2;
        D->Item = (TItem *)realloc(D->Item, D->max * sizeof(TItem));
    }
    return 1;
}