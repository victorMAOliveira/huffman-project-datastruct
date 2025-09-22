#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Nó para a Árvore do Algorítimo de Huffman
    -> Char correspondente
    -> Sua frequência
    -> Ponteiro para o próximo nó (formato de lista encadeada)
    -> Ponteiro para o galho à esquerda
    -> Ponteiro para o galho à direita
*/
typedef struct huff_no {
    char c;
    int freq;
    struct huff_no *prox;
    struct huff_no *esq;
    struct huff_no *dir;
}huff_no_t;

int main() {


    return 0;
}