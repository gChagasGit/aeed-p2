// Código base para o BinarySearchTree

typedef int TChave;

typedef struct
{
    TChave Chave;
    /* outros compomentes */
} TItem;

typedef struct SNo *TArvBin;

typedef struct SNo
{
    TItem Item;
    TArvBin Esq, Dir;
} TNo;

#define NIL NULL
typedef TArvBin TApontador;
typedef struct
{
    TArvBin Raiz;
    int n;
} TDicionario;
/* Inicia um dicionario vazio */
TDicionario *TDicionario_Inicia()
{
    TDicionario *D;
    D = (TDicionario *)malloc(sizeof(TDicionario));
    D->n = 0;
    D->Raiz = NULL;
    return D;
}

TArvBin Pesquisa(TArvBin Raiz, TChave c)
{
    TArvBin No;

    No = Raiz;
    while ((No != NULL) && (c != No->Item.Chave))
    {
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
    return 0; // retorna 0 caso o item ja estiver na arvore
}

int Retira(TArvBin *pRaiz, TChave c)
{
    TArvBin *p, q;
    p = pRaiz;
    while ((*p != NULL) && (c != (*p)->Item.Chave))
    {
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
        else                       // possui dois filhos
            Sucessor(&q, &q->Dir); // equivalente a Predecessor(&q, &q->Esq);
        free(q);
        return 1;
    }
    return 0; // retorna 0 caso o item nao esteja na arvore
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
    }
}

/* Retorna um apontador para o item com chave c no dicionario */
TApontador TDicionario_Pesquisa(TDicionario *D, TChave c)
{
    return Pesquisa(D->Raiz, c);
}
/* Insere um item no dicionario */
int TDicionario_Insere(TDicionario *D, TItem x)
{
    if (!Insere(&D->Raiz, x))
        return 0; // retorna 0 caso o item ja estiver no dicionario
    D->n++;       // n eh o tamanho
    return 1;
}
/* Retira o item com chave c do dicionario */
int TDicionario_Retira(TDicionario *D, TChave c)
{
    if (!Retira(&D->Raiz, c))
        return 0; // retorna 0 caso o item nao esteja no dicionario
    D->n--;
    return 1;
}