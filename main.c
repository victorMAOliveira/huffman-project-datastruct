#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Nó para a Árvore do Algorítimo de Huffman:
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
} huff_no_t;

/*
    Árvore que contém ponteiro para sua raíz e será montada e remontada
    para a compressão e extração de arquivos respectivamente
*/
typedef struct huff_arvore {
    huff_no_t *raiz;
} huff_arvore_t;

/*
    Soma as frequências dos dois nós passados (INVÁLIDO SE UM DELES FOR NULL)

    ATENÇÃO: nós 1 e 2 passam a apontar para null em 'prox'

    Retorna ponteiro para o novo nó com identificador '*', soma da frequência dos dois nós e 
    que posiciona o menor nó dos dois à esquerda e o maior à direita (vem com 'prox' apontando para NULL)
*/
huff_no_t *fundir_nos(huff_no_t *no1, huff_no_t *no2) {
    if(!no1 || !no2) {
        fprintf(stderr, "ERRO[fundir_nos()]: PARAMETRO NULL\n");
        return NULL;
    }

    no1->prox = NULL;
    no2->prox = NULL;
    
    huff_no_t *novo_no = malloc(sizeof(huff_no_t));
    if(!novo_no) {
        fprintf(stderr, "ERRO[fundir_nos()]: ALOCACAO DE MEMORIA DO NO FUNDIDO INVALIDA\n");
        return NULL;
    }

    novo_no->c = '*';
    novo_no->freq = no1->freq + no2->freq;
    novo_no->prox = NULL;

    if(no1->freq < no2->freq) {
        novo_no->esq = no1;
        novo_no->dir = no2;
    } else {
        novo_no->esq = no2;
        novo_no->dir = no1;
    }

    return novo_no;
}

int main() {
    

    return 0;
}