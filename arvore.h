#ifndef arvore_h
#define arvore_h
#include <stdbool.h>
#define TAMNOME 50

#define RED 1
#define BLACK 0

typedef struct {
    char nome[TAMNOME];
    char nascimento[11];
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

void desalocarArvore();

No* NoCria(No x);

void leArvore(Arvore *pRaiz, int n);

void rotacaoEsquerda(No** pRaiz, No* x);

void rotacaoDireita(No **pRaiz, No* x);

void balanceamento(No **T, No *umNoh);

void printInOrder(No *p);

bool ArvoreRetira(No **p, Pessoa x);

void liberaArvore(No **ppRaiz);

void rotacaoADireita(No** arvore, No* y);

void rotacaoAEsquerda(No** arvore, No* x);

void insercao(No **raiz, No *umValor);
#endif