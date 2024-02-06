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
    if (*ppRaiz != NULL)
    {
        desalocarArvore(&(*ppRaiz)->pEsq); // Desaloca subarvore esquerda
        desalocarArvore(&(*ppRaiz)->pDir); // Desaloca subarvore direita
        free(*ppRaiz);                  // Desaloca o no atual
        *ppRaiz = NULL;
    }
}

No *NoCria(No x)
{
    // Aloca memoria para um novo no
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo != NULL)
    {
        // Inicializa o novo no com os valores fornecidos
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
    No temp; // Variavel temporaria para armazenar os dados lidos temporariamente
    for (int i = 0; i < n; i++)
    {
        // Le o nome e a idade da pessoa da entrada padrao
        scanf("%s%d", temp.pessoa.nome, &temp.pessoa.idade);
        // Insere o no contendo as informacoes lidas na arvore
        insercao(pRaiz, &temp);
    }
}

void rotacaoEsquerda(No** arvore, No* x) {
    // Verifica se o no fornecido e seu filho a direita nao sao nulos
    if (x != NULL && x->pDir != NULL) {
        // Define o no y como o filho a direita de x
        No* y = x->pDir;
        // Atualiza o filho a direitra de x para ser o filho a esquerda de y
        x->pDir = y->pEsq;

        // Se o filho a esquerda de y nao for nulo, corrige o pai dele para apontar para x
        if(x->pEsq != NULL) 
            x->pEsq->pPai = x;
        
        // Atualiza o pai de y para ser o pai de x
        y->pPai = x->pPai;

        if (x->pPai == NULL) {
            *arvore = y; // Se x era a raiz, atualiza a raiz da arvore para ser y
        } else if (x == x->pPai->pEsq) {
            x->pPai->pEsq = y; // Se x era filho a esquerda de seu pai, atualiza o ponteiro a esquerda do pai para y
        } else {
            x->pPai->pDir = y; // Se for filho a direita, atualiza o ponteiro a direita do pai para y
        }

        // Atualiza o filho a esquerda de y para apontar para x
        y->pEsq = x;
        // Atualiza o pai de x para apontar para y
        x->pPai = y;
    }
    //printRBTreeRecursive(*arvore, 0, "");
}

void rotacaoDireita(No** arvore, No* y) {
    // Verifica se y e seu filho a esquerda nao sao nulos
    if (y != NULL && y->pEsq != NULL) {
        // Define o no x como filho a esquerda de y
        No* x = y->pEsq; 
        // Atualiza o filho esquerdo de y para receber o filho direito de x
        y->pEsq = x->pDir;

        // Se o filho direito de y nao for nulo, atribue y ao pai dele
        if (y->pDir != NULL) {
            y->pDir->pPai = y;
        }

        // Atualiza o pai de x para ser o pai de y
        x->pPai = y->pPai;
        
        // Verifica se y eh a raiz
        if (y->pPai == NULL) {
            *arvore = x; // Se sim, atualiza a raiz da arvore para x
        } else if (y == y->pPai->pDir) {
            y->pPai->pDir = x; // Se y era filho a direita de seu pai, atualiza o ponteiro a direita do pai para x
        } else {
            y->pPai->pEsq = x; // Se for filho a esquerda, atualiza o ponteiro a esquerda do pai para x
        }

        // Atualiza o filho direito de x para receber y
        x->pDir = y;
        // Atualiza o o pai de y para receber x
        y->pPai = x;
    }
    //printRBTreeRecursive(*arvore, 0, "");
}

void insercao(No **raiz, No *valor)
{
    // Cria um novo com o valor fornecido
    No *novoNoh = NoCria(*valor);

    // Se a arvore estiver vazia, novo no se torna a raiz
    if (*raiz == NULL)
    {
        *raiz = novoNoh;
    }
    else
    {
        No *atual = *raiz;
        No *anterior = NULL;
        
        // Procura o local adequado na arvore para inserir o novo no
        while (atual != NULL)
        {
            anterior = atual;

            if (atual->pessoa.idade > valor->pessoa.idade)
            {
                atual = atual->pEsq;
            }
            else
            {
                atual = atual->pDir;
            }
        }

        // Define o pai do novo no como sendo o no onde a insercao sera realizada
        novoNoh->pPai = anterior;

        // Insere o novo no como filho a esquerda ou a direita do no anterior, dependendo do valor
        if (anterior->pessoa.idade > novoNoh->pessoa.idade)
        {
            anterior->pEsq = novoNoh;
        }
        else
        {
            anterior->pDir = novoNoh;
        }

        // Corrigir as propriedades da arvore rubro-negra apos a insercao
        balanceamento(raiz, novoNoh);
    }
}

void balanceamento(No **raiz, No *novo)
{
    //printRBTreeRecursive(*raiz, 0, "");

    // Variavel para armazenar o pai do novo no
    No* pai;

    while (novo != *raiz && novo->pPai->cor == RED && novo->cor == RED)
    {
        // Variaveis para controle da rotacao dupla
        int rot_dupla2 = 0;
        int rot_dupla1 = 0;

        pai = novo->pPai;

        // Se o avo do novo no for nulo, encerra o loop
        if(pai->pPai == NULL){
            break;
        }
        
        // Verifica se o pai do novo no eh o filho esquerdo do avo
        if (novo->pPai == novo->pPai->pPai->pEsq)
        {
            No *tio = novo->pPai->pPai->pDir; // Armazena o tio como sendo o filho a direita do avo

            // Verifica se o tio do novo no nao eh nulo e se ele eh vermelho
            if (tio != NULL && tio->cor == RED)
            {
                pai->cor = BLACK;           // Caso 1
                tio->cor = BLACK;          // Caso 1
                novo->pPai->pPai->cor = RED; // Caso 1
                novo = novo->pPai->pPai;     // Caso 1
            }
            else
            {   
                // Verifica se o novo no eh filho a direita do pai
                if (novo == pai->pDir) 
                {
                    novo = pai;             // Caso 2
                    rotacaoEsquerda(raiz, pai); // Caso 2
                    pai->cor = RED;             // Caso 2
                    rot_dupla1++;                  // Caso 2

                }
                // Se nao houve rotacao dupla
                if(!rot_dupla1)
                    pai->cor = BLACK;
                novo->pPai->pPai->cor = RED;         // Caso 3
                rotacaoDireita(raiz, novo->pPai->pPai); // Caso 3

            }
        } else { // Se o pai do novo no eh o filho a direita do avo

            No *tio = novo->pPai->pPai->pEsq; // Armazena o tio do novo no como sendo o filho a esquerda do avo

            // Verifica se o tio do novo no nao eh nulo e se ele eh vermelho
            if (tio != NULL && tio->cor == RED) 
            {
                pai->cor = BLACK;
                tio->cor = BLACK;          // Caso 1
                novo->pPai->pPai->cor = RED; // Caso 1
                novo = novo->pPai->pPai;     // Caso 1
            }
            else
            {
                // Verifica se o novo no eh filho a esquerda do pai
                if (novo == novo->pPai->pEsq)
                {
                    novo = pai;                // Caso 2
                    rotacaoDireita(raiz, pai); // Caso 2
                    pai->cor = RED;            // Caso 2
                    rot_dupla2++;               // Caso 2
                }
                // Se nao houve rotacao dupla
                if(!rot_dupla2)
                    pai->cor = BLACK;                  // Caso 3
                novo->pPai->pPai->cor = RED;         // Caso 3
                rotacaoEsquerda(raiz, novo->pPai->pPai); // Caso 3
            }
        }
    }
    (*raiz)->cor = BLACK; // A raiz deve ser preta
}

void printInOrder(No *p)
{
    // Caso base da recursao
    if (p == NULL)
        return;

    // Verifica se o no atual nao eh nulo e tem filho a esquerda
    if (p != NULL && p->pEsq != NULL)
    {
        printInOrder(p->pEsq); // Chama recursivamente a funcao para a esquerda
    }

    // Imprime as informacoes de acordo com o modelo pedido
    printf("Nome: %s\nIdade: %d\n", p->pessoa.nome, p->pessoa.idade);

    // Se o no atual nao eh nulo e tem filho a direita
    if (p != NULL && p->pDir != NULL)
    {
        printInOrder(p->pDir); // Chama recursivamente a funcao para a direita
    }
}
