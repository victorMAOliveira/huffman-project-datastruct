#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITERACOES 10000

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
    Struct para guardar o endereço dos 2 menores nós da atual lista encadeada
*/
typedef struct menores_nos {
    huff_no_t *menor;
    huff_no_t *segundo_menor;
} menores_nos_t;

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

/*
    Recebe cabeça da lista encadeada e acha os 2 menores nós

    Retorna o struct com o ponteiro dos 2 menores nós
*/
menores_nos_t achar_menores(huff_no_t *cabeca) {
    menores_nos_t menores = {NULL, NULL};
    int menor = 0, segundo_menor = 0;

    // TODO
}

/*
    Esta função vai receber o nó não vazio que começa a lista encadeada
    com os nós a serem inseridos

    Retorna a raíz da árvore binária que servirá para comprimir o arquivo
*/
huff_arvore_t *organizar_arvore(huff_no_t *cabeca) {
    int iteracoes = 0;
    while(cabeca->prox != NULL) {
        if(iteracoes > MAX_ITERACOES) {
            fprintf(stderr, "ERRO[organizar_arvore]: MAXIMO DE ITERACOES ATINGIDO\n");
            break;
        }
        
        menores_nos_t menores = achar_menores(cabeca);

        huff_no_t *no_fundido = fundir_nos(menores.menor, menores.segundo_menor);

        // TODO
    }

    // TODO
}

int main() {
    

    return 0;
}