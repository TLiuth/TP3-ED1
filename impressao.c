#include <stdio.h>
#include "arvore.h"

// Define colors for better visualization
#define RESET "\x1b[0m"
#define red "\x1b[31m"
#define black "\x1b[30m"

void printRBTree(No *root, int level)
{
    if (root == NULL)
        return;

    // Increase indentation for better visualization
    level += 5;

    // Print right child
    printRBTree(root->pDir, level);

    // Print current node
    printf("\n");
    for (int i = 5; i < level; i++)
    {
        printf(" ");
    }

    if (root->cor == RED)
    {
        printf(red);
    }
    else
    {
        printf(black);
    }

    printf("%s %d\n", root->pessoa.nome, root->pessoa.idade);
    printf(RESET);

    // Print left child
    printRBTree(root->pEsq, level);
}

// Usage
// Call this function with the root of your Red-Black Tree
// Example: printRBTree(root, 0);


void printRBTreeRecursive(No *node, int level, const char *edge) {
    if (node != NULL) {
        // Print right child with increased level
        printRBTreeRecursive(node->pDir, level + 1, "R");

        // Print current node at the current level with color and edge information
        printf("%*s", level * 6, "");  // Adjust the multiplier based on the desired indentation
        if (node->cor == BLACK) {
            printf("\x1b[30m"); // ANSI escape code for black text
        } else {
            printf("\x1b[31m"); // ANSI escape code for red text
        }
        printf("%c---%d %s\n", (node->cor == BLACK) ? 'B' : 'R', node->pessoa.idade, edge);
        printf("\x1b[0m"); // ANSI escape code to reset color

        // Print left child with increased level
        printRBTreeRecursive(node->pEsq, level + 1, "L");
    }
}

