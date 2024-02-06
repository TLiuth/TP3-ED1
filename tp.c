#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "arvore.h"
#include "impressao.h"

int main()
{
    int op = 1, n;
    Arvore raiz; // Declaracao da raiz da arvore

    alocarArvore(&raiz); // Inicializa a raiz da arvore

    // Loop principal do programa
    while (op != 0)
    {
        scanf("%d", &op); // Le a operacao escolhida pelo usuario
        switch (op)
        {
        case 1: // Inserir elementos
            scanf("%d", &n); 
            leArvore(&raiz, n);
            break;
        case 2: // Imprime os dados da arvore
            printf("Dados inOrder:\n");
            printInOrder(raiz);
            break;
        case 0: // Encerra o programa e imprime os dados da arvore
            printf("Dados inOrder:\n");
            printInOrder(raiz);
            break;
        default:
            printf("Operacao invalida. Digite novamente. \n");
            scanf("%d", &op);
            break;
        }
    }

    printf("\n\n\n");
    printRBTreeRecursive(raiz, 0, "");
    printf("\n\n\n");

    desalocarArvore(&raiz); // Libera a memoria alocada para a arvore
}
