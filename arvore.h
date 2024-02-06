#ifndef arvore_h
#define arvore_h
#include <stdbool.h>
#define TAMNOME 50  // Definicao do tamanho maximo do nome

#define RED 1
#define BLACK 0

// Definicao da estrutura de dados Pessoa
typedef struct {
    char nome[TAMNOME];
    int idade;
} Pessoa;

// Definicao da estrutura de dados No
typedef struct no
{
    Pessoa pessoa;
    struct no* pPai;
    struct no* pEsq;
    struct no* pDir;
    int cor;
} No;

typedef No* Arvore; // Definicao do tipo Arvore como um ponteiro para No

void alocarArvore(No **pRaiz); // Funcao para alocar uma nova arvore

void desalocarArvore(No **ppRaiz);  // Funcao para desalocar uma arvore

No* NoCria(No x); // Funcao para criar um novo no

void leArvore(Arvore *pRaiz, int n); // Funcao para ler os valores e construir a arvore

void balanceamento(No **raiz, No *novo); // Funcao para balancear a arvore apos a insercao

void printInOrder(No *p); // Funcao para imprimir os nos em ordem

void rotacaoDireita(No** arvore, No* y); // Funcao para realizar uma rotacao para a direita

void rotacaoEsquerda(No** arvore, No* x); // Funcao para realizar uma rotacao para a esquerda

void insercao(No **raiz, No *valor); // Funcao para inserir um novo no na arvore
#endif