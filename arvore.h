#ifndef arvore_h
#define arvore_h
#include <stdbool.h>
#define TAMNOME 50

#define RED 1
#define BLACK 0

typedef struct {
    char nome[TAMNOME];
    int idade;
} Pessoa;


typedef struct no
{
    Pessoa pessoa;
    struct no* pPai;
    struct no* pEsq;
    struct no* pDir;
    int cor;
} No;

typedef No* Arvore;

void alocarArvore(No **pRaiz);

void desalocarArvore(No **ppRaiz);

No* NoCria(No x);

void leArvore(Arvore *pRaiz, int n);

void balanceamento(No **T, No *umNoh);

void printInOrder(No *p);

void liberaArvore(No **ppRaiz);

void rotacaoDireita(No** arvore, No* y);

void rotacaoEsquerda(No** arvore, No* x);

void insercao(No **raiz, No *umValor);
#endif