// Código modelo para RedBlackTree

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

int AlturaNegra(TArvBin No)
{
    int hEsq, hDir;

    if (No == NULL)
        return 0; // altura negra de arvore vazia e 0

    hEsq = AlturaNegra(No->Esq);
    hDir = AlturaNegra(No->Dir);
    if (hEsq > hDir)
        return hEsq + EhNegro(No);
    else
        return hDir + EhNegro(No);
}

int ArvoreARN(TArvBin No)
{
    if (No == NULL)
        return 1;
    if (!ArvoreARN(No->Esq))
        return 0;
    if (!ArvoreARN(No->Dir))
        return 0;
    if (EhRubro(No) && (!EhNegro(No->Esq) || !EhNegro(No->Dir)))
        return 0;
    if (AlturaNegra(No->Esq) != AlturaNegra(No->Dir))
        return 0;
    return 1;
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
    TArvBin pB;

    pB = (*pA)->Esq;
    (*pA)->Esq = pB->Dir;
    pB->Dir = *pA;
    *pA = pB;
}

void RotacaoEsquerda(TArvBin *pA)
{
    TArvBin pB;

    pB = (*pA)->Dir;
    (*pA)->Dir = pB->Esq;
    pB->Esq = *pA;
    *pA = pB;
}

int BalancaEsquerda(TArvBin *pC)
{
    TArvBin pD = (*pC)->Esq;
    if (EhRubro(pD))
    { // caso 4b
        RotacaoDireita(pC);
        pC = &(*pC)->Dir;
        pD = (*pC)->Esq;
    }
    if (pD != NULL)
    {
        if (EhNegro(pD->Esq) && EhNegro(pD->Dir))
        { // caso 1
            InverteCor(pD);
            if (EhRubro(*pC))
            {
                InverteCor(*pC);
                return 0;
            }
        }
        else
        {
            int cor = (*pC)->cor;
            (*pC)->cor = 0;
            if (EhNegro(pD->Esq)) // caso 2b
                RotacaoEsquerda(&(*pC)->Esq);
            else
                InverteCor(pD->Esq);
            RotacaoDireita(pC); // caso 3b
            (*pC)->cor = cor;
            return 0;
        }
    }
    return 1;
}

int BalancaDireita(TArvBin *pC)
{
    TArvBin pD = (*pC)->Dir;
    if (EhRubro(pD))
    { // caso 4a
        RotacaoEsquerda(pC);
        pC = &(*pC)->Esq;
        pD = (*pC)->Dir;
    }
    if (pD != NULL)
    {
        if (EhNegro(pD->Esq) && EhNegro(pD->Dir))
        { // caso 1
            InverteCor(pD);
            if (EhRubro(*pC))
            {
                InverteCor(*pC);
                return 0;
            }
        }
        else
        {
            int cor = (*pC)->cor;
            (*pC)->cor = 0;
            if (EhNegro(pD->Dir)) // caso 2a
                RotacaoDireita(&(*pC)->Dir);
            else
                InverteCor(pD->Dir);
            RotacaoEsquerda(pC); // caso 3a
            (*pC)->cor = cor;
            return 0;
        }
    }
    return 1;
}

void BalancaNo(TArvBin *pA, TArvBin *pB, TArvBin *pC)
{
    if ((pC != NULL) && EhRubro(*pA) && EhRubro(*pB))
    {
        if (*pA == (*pC)->Esq)
            BalancaEsquerda(pA, pB, pC);
        else
            BalancaDireita(pA, pB, pC);
    }
}

void TDicionario_InsereRecursivo(TArvBin *pA, TArvBin *pC, TItem x)
{
    if (*pA == NULL)
    {
        *pA = (TArvBin)malloc(sizeof(TNo));
        (*pA)->Item = x;
        (*pA)->Esq = NULL;
        (*pA)->Dir = NULL;
        (*pA)->cor = 1; // o novo no e rubro
    }
    else if (x.Chave < (*pA)->Item.Chave)
    {
        TDicionario_InsereRecursivo(&(*pA)->Esq, pA, x);
        BalancaNo(pA, &(*pA)->Esq, pC);
    }
    else if (x.Chave > (*pA)->Item.Chave)
    {
        TDicionario_InsereRecursivo(&(*pA)->Dir, pA, x);
        BalancaNo(pA, &(*pA)->Dir, pC);
    }
}
void TDicionario_Insere(TArvBin *pRaiz, TItem x)
{
    TDicionario_InsereRecursivo(pRaiz, NULL, x);
    (*pRaiz)->cor = 0; // a raiz e negra
}

int Retira(TArvBin *p, TChave x)
{
    TArvBin q;
    if (*p == NULL)
        return 0; // retorna 0 caso o item nao esteja na arvore
    else if (x < (*p)->Item.Chave)
        return Retira(&(*p)->Esq, x);
    else if (x > (*p)->Item.Chave)
        return Retira(&(*p)->Dir, x);
    else
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
}

int Sucessor(TArvBin *q, TArvBin *r)
{
    int bh;
    if ((*r)->Esq != NULL)
    {
        if (Sucessor(q, &(*r)->Esq))
            return BalancaDireita(r); // subarvore esquerda encolheu
        return 0;
    }
    else
    {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Dir;
        bh = EhNegro(*q) && EhNegro(*r);
        if (!bh && EhNegro(*q))
            (*r)->cor = 0;
        return bh;
    }
}