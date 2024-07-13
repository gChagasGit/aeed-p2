// Código para AVLTree

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
        { // possui dois filhos
            if (Sucessor(&q, &q->Dir))
                switch ((*p)->fb)
                {
                case -1:
                    (*p)->fb = 0;
                    ret = 1;
                    break;
                case 0:
                    (*p)->fb = +1;
                    ret = 0;
                    break;
                case +1:
                    ret = BalancaEsquerda(p);
                    break;
                }
            else
                ret = 0;
        }
        free(q);
        return ret;
    }
}

int Sucessor(TArvBin *q, TArvBin *r)
{
    if ((*r)->Esq != NULL)
    {
        if (Sucessor(q, &(*r)->Esq))
            switch ((*r)->fb)
            {
            case +1:
                (*r)->fb = 0;
                return 1;
            case 0:
                (*r)->fb = -1;
                return 0;
            case -1:
                return BalancaDireita(r);
            }
        return 0;
    }
    else
    {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Dir;
        return 1;
    }
}
