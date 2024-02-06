#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

RBTree* alocarArvore() {
    RBTree* novaArvore = (RBTree*)malloc(sizeof(RBTree));
    if (novaArvore != NULL) {
        novaArvore->raiz = NULL;
    }
    return novaArvore;
}

void desalocarArvoreRecursivo(RBTreeNode* no) {
    if (no != NULL) {
        desalocarArvoreRecursivo(no->esquerda);
        desalocarArvoreRecursivo(no->direita);
        free(no);
    }
}

void desalocarArvore(RBTree* arvore) {
    if (arvore != NULL) {
        desalocarArvoreRecursivo(arvore->raiz);
        free(arvore);
    }
}

void leArvoreRecursivo(RBTree* arvore, RBTreeNode* no) {
    if (no != NULL) {
        leArvoreRecursivo(arvore, no->esquerda);

        printf("Nome: %s, Data de Nascimento: %s, Idade: %d\n", no->dado.nome, no->dado.dataNascimento, no->dado.idade);

        leArvoreRecursivo(arvore, no->direita);
    }
}

// Função auxiliar para obter o tio de um nó
RBTreeNode* obterTio(RBTreeNode* no) {
    if (no == NULL || no->pai == NULL || no->pai->pai == NULL) {
        return NULL; // Não há tio se o nó, o pai ou o avô forem nulos
    }

    if (no->pai == no->pai->pai->esquerda) {
        return no->pai->pai->direita; // Tio à direita
    } else {
        return no->pai->pai->esquerda; // Tio à esquerda
    }
}

// Função auxiliar para realizar a troca de cor
void trocarCor(RBTreeNode* no) {
    if (no != NULL) {
        if (no->cor == VERMELHO) {
            no->cor = PRETO;
        } else {
            no->cor = VERMELHO;
        }
    }
}

RBTreeNode* criarNo(Pessoa dado) {
    RBTreeNode* novoNo = (RBTreeNode*)malloc(sizeof(RBTreeNode));
    if (novoNo != NULL) {
        novoNo->dado = dado;
        novoNo->cor = VERMELHO; // Por padrão, um novo nó é sempre vermelho
        novoNo->pai = NULL;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
    }
    return novoNo;
}

void leArvore(RBTree* arvore, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        Pessoa pessoa;
        scanf("%s", pessoa.nome);
        // scanf("%s", pessoa.dataNascimento);
        scanf("%d", &pessoa.idade);
        insertRBTree(arvore, pessoa);
    }
}

void rotacaoDireita(RBTree* arvore, RBTreeNode* y) {
    if (y != NULL && y->esquerda != NULL) {
        RBTreeNode* x = y->esquerda;
        y->esquerda = x->direita;

        if (x->direita != NULL) {
            x->direita->pai = y;
        }

        x->pai = y->pai;

        if (y->pai == NULL) {
            arvore->raiz = x;
            printf("Rotação Direita - Nova Raiz: %s\n", x->dado.nome);
        } else if (y == y->pai->esquerda) {
            y->pai->esquerda = x;
            printf("Rotação Direita - Novo Filho Esquerdo de %s: %s\n", y->pai->dado.nome, x->dado.nome);
        } else {
            y->pai->direita = x;
            printf("Rotação Direita - Novo Filho Direito de %s: %s\n", y->pai->dado.nome, x->dado.nome);
        }

        x->direita = y;
        y->pai = x;
    }
}

void rotacaoEsquerda(RBTree* arvore, RBTreeNode* x) {
    if (x != NULL && x->direita != NULL) {
        RBTreeNode* y = x->direita;
        x->direita = y->esquerda;

        if (y->esquerda != NULL) {
            y->esquerda->pai = x;
        }

        y->pai = x->pai;

        if (x->pai == NULL) {
            arvore->raiz = y;
            printf("Rotação Esquerda - Nova Raiz: %s\n", y->dado.nome);
        } else if (x == x->pai->esquerda) {
            x->pai->esquerda = y;
            printf("Rotação Esquerda - Novo Filho Esquerdo de %s: %s\n", x->pai->dado.nome, y->dado.nome);
        } else {
            x->pai->direita = y;
            printf("Rotação Esquerda - Novo Filho Direito de %s: %s\n", x->pai->dado.nome, y->dado.nome);
        }

        y->esquerda = x;
        x->pai = y;
    }
}

void insertRBTree(RBTree* arvore, Pessoa dado) {
    RBTreeNode* z = criarNo(dado);
    RBTreeNode* y = NULL;
    RBTreeNode* x = arvore->raiz;

    while (x != NULL) {
        y = x;
        if (z->dado.idade < x->dado.idade)
            x = x->esquerda;
        else
            x = x->direita;
    }

    z->pai = y;

    if (y == NULL) {
        arvore->raiz = z;
        printf("Inserido com sucesso na raiz: %s, %d anos\n", z->dado.nome, z->dado.idade);
    } else if (z->dado.idade < y->dado.idade) {
        y->esquerda = z;
        printf("Novo filho esquerdo de %s: %s, %d anos\n", y->dado.nome, z->dado.nome, z->dado.idade);
    } else {
        y->direita = z;
        printf("Novo filho direito de %s: %s, %d anos\n", y->dado.nome, z->dado.nome, z->dado.idade);
    }

    balanceamento(arvore, z);

}
// Função auxiliar para realizar a inserção recursiva
void insercaoRecursiva(RBTree* arvore, RBTreeNode* no, Pessoa pessoa) {
    if (no == NULL) {
        // Chegamos a um nó folha, criamos um novo nó
        RBTreeNode* novoNo = criarNo(pessoa);
        if (novoNo == NULL) {
            // Falha na alocação, encerrar
            return;
        }
        // Se o pai é nulo, estamos na raiz
        if (arvore->raiz == NULL) {
            arvore->raiz = novoNo;
            novoNo->cor = PRETO; // A raiz é sempre preta
            return;
        }
        else{
            // Ligamos o novo nó ao pai
            novoNo->pai = arvore->raiz;
        }
        

        // Atualizamos os ponteiros do pai para o novo nó
        if (arvore->raiz != NULL) {
            if (pessoa.idade < arvore->raiz->dado.idade) {
                arvore->raiz->esquerda = novoNo;
                printf("Inserido com sucesso - Novo Filho Esquerdo de %s: %s\n", arvore->raiz->dado.nome, novoNo->dado.nome);
            } else {
                arvore->raiz->direita = novoNo;
                printf("Inserido com sucesso - Novo Filho Direito de %s: %s\n", arvore->raiz->dado.nome, novoNo->dado.nome);
            }
        }
        // Realizamos o balanceamento após a inserção
        balanceamento(arvore, novoNo);
    } else {
        if (pessoa.idade < no->dado.idade) {
            insercaoRecursiva(arvore, no->esquerda, pessoa);
        } else {
            insercaoRecursiva(arvore, no->direita, pessoa);
        }
    }
}

void insercao(RBTree* arvore, Pessoa pessoa) {
    insercaoRecursiva(arvore, arvore->raiz, pessoa);
}

void balanceamento(RBTree* arvore, RBTreeNode* novoNo) {
    RBTreeNode* pai;
    RBTreeNode* avo;
    while (novoNo != arvore->raiz && novoNo->cor == VERMELHO && novoNo->pai->cor == VERMELHO) {
        printf("entrou");
        pai = novoNo->pai;
        avo = pai->pai;

        // Caso 1: O pai do novo nó é filho esquerdo do avô
        if (pai == avo->esquerda) {
            RBTreeNode* tio = avo->direita;

            // Caso 1a: O tio é vermelho, apenas trocar as cores
            if (tio != NULL && tio->cor == VERMELHO) {
                trocarCor(avo);
                trocarCor(pai);
                trocarCor(tio);
                novoNo = avo;
            } else {
                // Caso 1b: O tio é preto ou nulo, fazer rotações e trocar as cores
                if (novoNo == pai->direita) {
                    rotacaoEsquerda(arvore, pai);
                    novoNo = pai;
                    pai = novoNo->pai;
                }

                rotacaoDireita(arvore, avo);
                trocarCor(pai);
                trocarCor(avo);
            }
        } else {
            // Caso 2: O pai do novo nó é filho direito do avô
            RBTreeNode* tio = avo->esquerda;

            // Caso 2a: O tio é vermelho, apenas trocar as cores
            if (tio != NULL && tio->cor == VERMELHO) {
                trocarCor(avo);
                trocarCor(pai);
                trocarCor(tio);
                novoNo = avo;
            } else {
                // Caso 2b: O tio é preto ou nulo, fazer rotações e trocar as cores
                if (novoNo == pai->esquerda) {
                    rotacaoDireita(arvore, pai);
                    novoNo = pai;
                    pai = novoNo->pai;
                }

                rotacaoEsquerda(arvore, avo);
                trocarCor(pai);
                trocarCor(avo);
            }
        }
    }

    arvore->raiz->cor = PRETO; // Garantindo que a raiz seja preta após a inserção
}

void printInOrder(RBTreeNode* no) {
    // if(no == NULL){
    //     printf("deu");
    // }
    if (no != NULL) {
        // Percorre a subárvore esquerda
        printInOrder(no->esquerda);

        // Imprime os dados do nó atual
        printf("Nome: %s,  Idade: %d, cor: %d\n", no->dado.nome,  no->dado.idade, no->cor);

        // Percorre a subárvore direita
        printInOrder(no->direita);
    }
}
