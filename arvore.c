#include "arvore.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "impressao.h"

void alocarArvore(No **ppRaiz)
{
    *ppRaiz = NULL;
}

void desalocarArvore(No **ppRaiz)
{
    liberaArvore(ppRaiz);
    *ppRaiz = NULL;
}

void liberaArvore(No **ppRaiz)
{
    if (*ppRaiz != NULL)
    {
        liberaArvore(&(*ppRaiz)->pEsq); // Desaloca subarvore esquerda
        liberaArvore(&(*ppRaiz)->pDir); // Desaloca subarvore direita
        free(*ppRaiz);                  // Desaloca o no atual
        *ppRaiz = NULL;
    }
}

No *NoCria(No x)
{

    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo != NULL)
    {
        novoNo->pessoa = x.pessoa;
        novoNo->cor = RED; // Por padrao, um novo no e sempre RED
        novoNo->pPai = NULL;
        novoNo->pEsq = NULL;
        novoNo->pDir = NULL;
    }
    return novoNo;
}

void leArvore(Arvore *pRaiz, int n)
{
    No temp;
    for (int i = 0; i < n; i++)
    {
        scanf("%s%d", temp.pessoa.nome, &temp.pessoa.idade);
        insercao(pRaiz, &temp);
    }
}

void rotacaoAEsquerda(No** arvore, No* x) {
    if (x != NULL && x->pDir != NULL) {
        No* y = x->pDir;
        x->pDir = y->pEsq;

        if(x->pEsq != NULL)          // Caso a direita de X nao seja um no folha (NULL) corrige o parentesco
            x->pEsq->pPai = x;

        y->pPai = x->pPai;

        if (x->pPai == NULL) {
            *arvore = y;
        } else if (x == x->pPai->pEsq) {
            x->pPai->pEsq = y;
        } else {
            x->pPai->pDir = y;
        }

        y->pEsq = x;
        x->pPai = y;
    }
    //printRBTreeRecursive(*arvore, 0, "");
}

void rotacaoADireita(No** arvore, No* y) {
    if (y != NULL && y->pEsq != NULL) {
        No* x = y->pEsq;
        y->pEsq = x->pDir;

        if (y->pDir != NULL) {
            y->pDir->pPai = y;
        }

        x->pPai = y->pPai;

        if (y->pPai == NULL) {
            *arvore = x;
        } else if (y == y->pPai->pDir) {
            y->pPai->pDir = x;
        } else {
            y->pPai->pEsq = x;
        }

        x->pDir = y;
        y->pPai = x;
    }
    //printRBTreeRecursive(*arvore, 0, "");
}

void insercao(No **raiz, No *umValor)
{
    No *novoNoh = NoCria(*umValor);

    if (*raiz == NULL)
    {
        *raiz = novoNoh;
    }
    else
    {
        No *atual = *raiz;
        No *anterior = NULL;

        while (atual != NULL)
        {
            anterior = atual;

            if (atual->pessoa.idade > umValor->pessoa.idade)
            {
                atual = atual->pEsq;
            }
            else
            {
                atual = atual->pDir;
            }
        }

        novoNoh->pPai = anterior;

        if (anterior->pessoa.idade > novoNoh->pessoa.idade)
        {
            anterior->pEsq = novoNoh;
        }
        else
        {
            anterior->pDir = novoNoh;
        }

        // Corrigir as propriedades da arvore red-black apos a insercao
        balanceamento(raiz, novoNoh);
    }
}

void balanceamento(No **raiz, No *novo)
{
    //printRBTreeRecursive(*raiz, 0, "");
    No* pai;

    while (novo != *raiz && novo->pPai->cor == RED && novo->cor == RED)
    {
        int rot_dupla2 = 0;
        int rot_dupla1 = 0;
        pai = novo->pPai;
        if(pai->pPai == NULL){
            break;
        }
        
        if (novo->pPai == novo->pPai->pPai->pEsq)
        {
            No *tio = novo->pPai->pPai->pDir;
            if (tio != NULL && tio->cor == RED)
            {
                pai->cor = BLACK;
                tio->cor = BLACK;          // Caso 1
                novo->pPai->pPai->cor = RED; // Caso 1
                novo = novo->pPai->pPai;     // Caso 1
            }
            else
            {
                if (novo == pai->pDir)
                {
                    novo = pai;             // Caso 2
                    rotacaoAEsquerda(raiz, pai); // Caso 2
                    pai->cor = RED;
                    rot_dupla1++;

                }
                if(!rot_dupla1)
                    pai->cor = BLACK;
                novo->pPai->pPai->cor = RED;         // Caso 3
                rotacaoADireita(raiz, novo->pPai->pPai); // Caso 3

            }
        } else {
            No *tio = novo->pPai->pPai->pEsq;
            if (tio != NULL && tio->cor == RED)
            {
                pai->cor = BLACK;
                tio->cor = BLACK;          // Caso 1
                novo->pPai->pPai->cor = RED; // Caso 1
                novo = novo->pPai->pPai;     // Caso 1
            }
            else
            {
                if (novo == novo->pPai->pEsq)
                {
                    novo = pai;
                    rotacaoADireita(raiz, pai); // Caso 2
                    pai->cor = RED;
                    rot_dupla2++;
                }
                if(!rot_dupla2)
                    pai->cor = BLACK;
                novo->pPai->pPai->cor = RED;         // Caso 3
                rotacaoAEsquerda(raiz, novo->pPai->pPai); // Caso 3
            }
        }
    }
    (*raiz)->cor = BLACK; // Conserta possivel quebra regra 2
}

void printInOrder(No *p)
{
    if (p == NULL)
        return;
    if (p != NULL && p->pEsq != NULL)
    {
        printInOrder(p->pEsq);
    }

    printf("Nome: %s\nIdade: %d\n", p->pessoa.nome, p->pessoa.idade);

    if (p != NULL && p->pDir != NULL)
    {
        printInOrder(p->pDir);
    }
}
