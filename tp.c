#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "arvore.h"
#include "impressao.h"

int main()
{
    int op = 1, n;
    Arvore raiz;
    raiz = malloc(sizeof(Arvore));

    alocarArvore(&raiz);

    while (op != 0)
    {
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            scanf("%d", &n);
            leArvore(&raiz, n);
            break;
        case 2:
            printf("Dados inOrder:\n");
            printInOrder(raiz);
            break;
        case 0:
            printf("Dados inOrder:\n");
            printInOrder(raiz);
            break;
        default:
            printf("Operacao invalida. Digite novamente. \n");
            scanf("%d", &op);
            break;
        }
    }

    //printRBTreeRecursive(raiz, 0, "");

    desalocarArvore(&raiz);
}
