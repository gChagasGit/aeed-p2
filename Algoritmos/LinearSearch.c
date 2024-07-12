// Código base para o LinearSearch

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

/* procedimentos e funcoes do TAD */

TDicionario *TDicionario_Inicia();
TApontador TDicionario_Pesquisa(TDicionario *D, TChave c);
int TDicionario_Insere(TDicionario *D, TItem x);
int TDicionario_Retira(TDicionario *D, TChave c);

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
    TApontador i;

    for (i = 0; i < D->n; i++)
        if (D->Item[i].Chave == c)
            return i;

    return NIL; // retorna -1 caso a chave não seja encontrada
}

/* Insere um item no dicionario */
int TDicionario_Insere(TDicionario *D, TItem x)
{
    if (TDicionario_Pesquisa(D, x.Chave) != NIL)
        return 0; // retorna 0 caso o item ja estiver no dicionario

    if (D->n == D->max)
    {
        D->max *= 2;
        D->Item = (TItem *)realloc(D->Item, D->max * sizeof(TItem));
    }

    D->Item[D->n++] = x; // n eh o tamanho
    return 1;
}

/* Retira o item com chave c do dicionario */
int TDicionario_Retira(TDicionario *D, TChave c)
{
    TApontador i;
    i = TDicionario_Pesquisa(D, c);
    if (i == NIL)
        return 0;                 // retorna 0 caso o item nao esteja no dicionario
    D->Item[i] = D->Item[--D->n]; // n eh o tamanho
    if (4 * D->n == D->max)
    {
        D->max /= 2;
        D->Item = (TItem *)realloc(D->Item, D->max * sizeof(TItem));
    }
    return 1;
}