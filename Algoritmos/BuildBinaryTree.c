// Código base para o BinaryTree (Estrutura)

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

/* procedimentos e funcoes do TAD */
TArvBin TArvBin_Inicia();
TArvBin TArvBin_CriaNo(TItem x, TArvBin Esq, TArvBin Dir);
int TArvBin_EhExterno(TArvBin No);
TArvBin TArvBin_SubarvoreEsquerda(TArvBin No);
TArvBin TArvBin_SubarvoreDireita(TArvBin No);
void TArvBin_Libera(TArvBin No);

TArvBin TArvBin_Inicia()
{
    return NULL;
}
TArvBin TArvBin_CriaNo(TItem x, TArvBin Esq, TArvBin Dir)
{
    TArvBin No;
    No = (TArvBin)malloc(sizeof(TNo));
    No->Item = x;
    No->Esq = Esq;
    No->Dir = Dir;
    return No;
}
int TArvBin_EhExterno(TArvBin No)
{
    return ((No == NULL) || ((No->Esq == NULL) && (No->Dir == NULL)));
}

TArvBin TArvBin_SubarvoreEsquerda(TArvBin No)
{
    return No->Esq;
}
TArvBin TArvBin_SubarvoreDireita(TArvBin No)
{
    return No->Dir;
}

void TArvBin_Libera(TArvBin No)
{
    if (No != NULL)
    {
        TArvBin_Libera(No->Esq);
        TArvBin_Libera(No->Dir);
        free(No);
    }
}

void PreOrdem(TArvBin No)
{
    while (No != NULL)
    {
        processa(No->Item);
        PreOrdem(No->Esq);
        No = No->Dir;
    }
}

void EmOrdem(TArvBin No)
{
    while (No != NULL)
    {
        EmOrdem(No->Esq);
        processa(No->Item);
        No = No->Dir;
    }
}

void PosOrdem(TArvBin No)
{
    if (No != NULL)
    {
        PosOrdem(No->Esq);
        PosOrdem(No->Dir);
        processa(No->Item);
    }
}

int Pesquisa(TItem *Em, int Esq, int Dir, TChave x)
{
    int Raiz;

    for (Raiz = Esq; Raiz <= Dir; Raiz++)
        if (Em[Raiz].Chave == x)
            return Raiz;

    return 0;
}
TArvBin Constroi(TItem *Pre, TItem *Em, int n)
{
    int No;
    No = 0;
    return ConstroiRecursivo(Pre, &No, Em, 0, n - 1);
}

TArvBin ConstroiRecursivo(TItem *Pre, int *pNo,

                          TItem *Em, int Esq, int Dir)

{
    TArvBin pEsq, pDir;
    TItem Item;
    int Raiz;

    if (Esq <= Dir)
    {
        Item = Pre[(*pNo)++];
        Raiz = Pesquisa(Em, Esq, Dir, Item.Chave);
        pEsq = ConstroiRecursivo(Pre, pNo, Em, Esq, Raiz - 1);
        pDir = ConstroiRecursivo(Pre, pNo, Em, Raiz + 1, Dir);
        return TArvBin_CriaNo(Item, pEsq, pDir);
    }

    return TArvBin_Inicia();
}