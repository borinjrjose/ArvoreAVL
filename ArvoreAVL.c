//ÁRVORE AVL.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s
{
    int info;
    int alt;
    struct s* esq;
    struct s* dir;
}NO;

int alt_no(NO* no)
{
    if(no == NULL) return -1;
    else return no->alt;
}

int fatorBalanceamento(NO* no)
{
    return labs(alt_no(no->esq) - alt_no(no->dir));
}

int maior(int x, int y)
{
    if(x > y) return x;
    else return y;
}

void rotacaoLL(NO** raiz)
{
    NO* no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->esq), alt_no(no->dir)) + 1;
    *raiz = no;
}

void rotacaoRR(NO** raiz)
{
    NO* no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = *raiz;
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->esq), alt_no(no->dir)) + 1;
    *raiz = no;
}

void rotacaoLR(NO** raiz)
{
    rotacaoRR(&(*raiz)->esq);
    rotacaoLL(raiz);
}

void rotacaoRL(NO** raiz)
{
    rotacaoLL(&(*raiz)->dir);
    rotacaoRR(raiz);
}

NO* acharMenor(NO* no)
{
    NO* prox = no->esq;
    while(prox)
    {
        no = prox;
        prox = prox->esq;
    }
    return no;
}

int inserir(NO** raiz, int valor)
{
    int resp;
    if(*raiz == NULL)
    {

        NO* novo = (NO*) malloc(sizeof(NO));
        if(novo == NULL) return 0;

        novo->info = valor;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    NO* atual = *raiz;
    if(valor < (*raiz)->info)
    {
        if((resp = inserir(&((*raiz)->esq), valor)) == 1)
        {
            if(fatorBalanceamento(*raiz) >= 2)
            {
                if(valor < (*raiz)->esq->info)
                {
                    rotacaoLL(raiz);
                }
                else
                {
                    rotacaoLR(raiz);
                }
            }
        }
    }
    else if(valor > (*raiz)->info)
    {
        if((resp = inserir(&((*raiz)->dir), valor)) == 1)
        {
            if(fatorBalanceamento(*raiz) >= 2)
            {
                if(valor > (*raiz)->dir->info)
                {
                    rotacaoRR(raiz);
                }
                else
                {
                    rotacaoRL(raiz);
                }
            }
        }
    }
    else
    {
        printf("VALOR DUPLICADO!!!");
        return 0;
    }

    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    return resp;
}

int remover(NO** raiz, int valor)
{
    int resp;
    if(*raiz == NULL)
    {
        printf("ELEMENTO INEXISTENTE!!!\n");
        return 0;
    }

    if(valor < (*raiz)->info)
    {
        if((resp = remover(&(*raiz)->esq, valor)) == 1)
        {
            if(fatorBalanceamento(*raiz) >= 2)
            {
                if(alt_no((*raiz)->dir->esq) <= alt_no((*raiz)->dir->dir))
                {
                    rotacaoRR(raiz);
                }
                else
                {
                    rotacaoRL(raiz);
                }
            }
        }
    }
    else if(valor > (*raiz)->info)
    {
        if((resp = remover(&(*raiz)->dir, valor)) == 1)
        {
            if(fatorBalanceamento(*raiz) >= 2)
            {
                if(alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq))
                {
                    rotacaoLL(raiz);
                }
                else
                {
                    rotacaoLR(raiz);
                }
            }
        }
    }
    else if(valor == (*raiz)->info)
    {
        if(!(*raiz)->esq || !(*raiz)->dir)
        {
            NO* atual = *raiz;
            if((*raiz)->esq)
            {
                *raiz = (*raiz)->esq;
            }
            else
            {
                *raiz = (*raiz)->dir;
            }
            free(atual);
        }
        else
        {
            NO* atual = acharMenor((*raiz)->dir);
            (*raiz)->info = atual->info;
            remover(&(*raiz)->dir, atual->info);
            if(fatorBalanceamento(*raiz) >= 2)
            {
                if(alt_no((*raiz)->esq->dir) >= alt_no((*raiz)->esq->esq))
                {
                    rotacaoLL(raiz);
                }
                else
                {
                    rotacaoLR(raiz);
                }

            }
            (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
        }
        return 1;
    }
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    return resp;
}

int main()
{
    NO* raiz = NULL;
    inserir(&raiz, 1);
    inserir(&raiz, 2);
    inserir(&raiz, 3);
    inserir(&raiz, 4);
    inserir(&raiz, 5);
    inserir(&raiz, 6);
    inserir(&raiz, 7);
    remover(&raiz, 1);
    remover(&raiz, 2);
    remover(&raiz, 3);
    printf("%i", raiz->info);
    return 0;
}
