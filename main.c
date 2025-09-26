#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    Struct para guardar o endereço dos 2 menores nós da atual lista encadeada
*/
typedef struct menores_nos {
    huff_no_t *menor;
    huff_no_t *segundo_menor;
} menores_nos_t;

/*
    Remove o nó passado da lista encadeada

    Retorna cabeça atualizada
*/
huff_no_t *remover_no(huff_no_t *cabeca, huff_no_t *no); 

/*
    Soma as frequências dos dois nós passados (INVÁLIDO SE UM DELES FOR NULL)

    Remove os 2 nós da lista encadeada

    ATENÇÃO: nós 1 e 2 passam a apontar para null em 'prox'

    Retorna ponteiro para o novo nó com identificador '*', soma da frequência dos dois nós e 
    que posiciona o menor nó dos dois à esquerda e o maior à direita (vem com 'prox' apontando para NULL)
*/
huff_no_t *fundir_nos(huff_no_t *no1, huff_no_t *no2, huff_no_t **cabeca); 

/*
    Recebe cabeça da lista encadeada e acha os 2 menores nós

    Retorna o struct com o ponteiro dos 2 menores nós
*/
menores_nos_t achar_menores(huff_no_t *cabeca); 

/*
    Empurra o novo nó como cabeça da lista encadeada

    Retorna cabeça da lista atualizada
*/
huff_no_t *push_no(huff_no_t *cabeca, huff_no_t *novo_no); 
/*
    Esta função vai receber o nó não vazio que começa a lista encadeada
    com os nós a serem inseridos

    Retorna a raíz da árvore binária que servirá para comprimir o arquivo
*/
huff_arvore_t *organizar_arvore(huff_no_t *cabeca); 

int main() {
    

    return 0;
}


huff_no_t *remover_no(huff_no_t *cabeca, huff_no_t *no) {
    if(cabeca == no) {
        cabeca = cabeca->prox;
        return cabeca;
    }

    huff_no_t *atual = cabeca;
    while(atual->prox != no && atual->prox) {
        atual = atual->prox;
    }

    if(atual->prox == no) {
        atual->prox = no->prox;
    }

    return cabeca;
}

huff_no_t *remover_no(huff_no_t *cabeca, huff_no_t *no) {
    if(cabeca == no) {
        cabeca = cabeca->prox;
        return cabeca;
    }

    huff_no_t *atual = cabeca;
    while(atual->prox != no && atual->prox) {
        atual = atual->prox;
    }

    if(atual->prox == no) {
        atual->prox = no->prox;
    }

    return cabeca;
}

/*
    Soma as frequências dos dois nós passados (INVÁLIDO SE UM DELES FOR NULL)

    Remove os 2 nós da lista encadeada

    ATENÇÃO: nós 1 e 2 passam a apontar para null em 'prox'

    Retorna ponteiro para o novo nó com identificador '*', soma da frequência dos dois nós e 
    que posiciona o menor nó dos dois à esquerda e o maior à direita (vem com 'prox' apontando para NULL)
*/
huff_no_t *fundir_nos(huff_no_t *no1, huff_no_t *no2, huff_no_t **cabeca) {
    if(!no1 || !no2 || !cabeca) {
        fprintf(stderr, "ERRO[fundir_nos()]: PARAMETRO NULL\n");
        return NULL;
    }

    (*cabeca) = remover_no(*cabeca, no1);
    (*cabeca) = remover_no(*cabeca, no2);

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
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    if(no1->freq < no2->freq) {
        novo_no->esq = no1;
        novo_no->dir = no2;
    } else {
        novo_no->esq = no2;
        novo_no->dir = no1;
    }

    return novo_no;
}

menores_nos_t achar_menores(huff_no_t *cabeca) {
    if(!cabeca) {
        fprintf(stderr, "ERRO[achar_menores()]: CABECA DA LISTA VAZIA\n");
        menores_nos_t menores = {NULL, NULL};
        return menores;
    }
    
    menores_nos_t menores = {NULL, NULL};

    huff_no_t *atual = cabeca;
    while(atual) {
        if(!menores.menor || atual->freq < menores.menor->freq) {
            menores.segundo_menor = menores.menor;
            menores.menor = atual;
        } else if(!menores.segundo_menor || atual->freq < menores.segundo_menor->freq) {
            menores.segundo_menor = atual;
        }

        atual = atual->prox;
    }

    return menores;
}

huff_no_t *push_no(huff_no_t *cabeca, huff_no_t *novo_no) {
    if(!novo_no) {
        fprintf(stderr, "ERRO[push_no()]: PARAMETRO NULO\n");
        return NULL;
    }
    
    novo_no->prox = cabeca;
    cabeca = novo_no;

    return cabeca;
}

huff_arvore_t *organizar_arvore(huff_no_t *cabeca) {
    if(!cabeca) {
        fprintf(stderr, "ERRO[organizar_arvore()]: PARAMETRO NULO\n");
        return NULL;
    }

    while(cabeca->prox != NULL) {
        menores_nos_t menores = achar_menores(cabeca);

        huff_no_t *no_fundido = fundir_nos(menores.menor, menores.segundo_menor, &cabeca);

        cabeca = push_no(cabeca, no_fundido);
    }

    huff_arvore_t *nova_arvore = malloc(sizeof(huff_arvore_t));

    if(!nova_arvore) {
        fprintf(stderr, "ERRO[organizar_arvore()]: ALOCACAO DE MEMORIA PARA ARVORE\n");
        return NULL;
    }

    nova_arvore->raiz = cabeca;

    return nova_arvore;
}