#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista {
    char info[100]; 
    struct lista* prox;
} Lista;

Lista* criarLista();
Lista* inserirNoInicio(Lista* lista, const char* info);
Lista* inserirOrdem(Lista* lista, const char* info);
void exibirLista(Lista* lista);
Lista* buscarElemento(Lista* lista, const char* info);
Lista* excluirElemento(Lista* lista, const char* info);
void liberarLista(Lista* lista);
int verificarVazia(Lista* lista);

Lista* criarLista() {
    return NULL;
}

Lista* inserirNoInicio(Lista* lista, const char* info) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    if (novo == NULL) {
        printf("Erro de alocação\n");
        return lista;
    }
    strcpy(novo->info, info);
    novo->prox = lista;
    return novo;
}

Lista* inserirOrdem(Lista* lista, const char* info) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    if (novo == NULL) {
        printf("Erro de alocação\n");
        return lista;
    }
    strcpy(novo->info, info);

    if (lista == NULL || strcmp(lista->info, info) > 0) {
        novo->prox = lista;
        return novo;
    }

    Lista* atual = lista;
    while (atual->prox != NULL && strcmp(atual->prox->info, info) < 0) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
    return lista;
}

void exibirLista(Lista* lista) {
    if (lista == NULL) {
        printf("Lista vazia\n");
    } else {
        for (Lista* p = lista; p != NULL; p = p->prox) {
            printf("%s\n", p->info);
        }
    }
}

Lista* buscarElemento(Lista* lista, const char* info) {
    for (Lista* p = lista; p != NULL; p = p->prox) {
        if (strcmp(p->info, info) == 0) {
            return p; 
        }
    }
    printf("Informação não encontrada\n");
    return NULL; 
}

Lista* excluirElemento(Lista* lista, const char* info) {
    Lista* ant = NULL;
    Lista* p = lista;
    while (p != NULL && strcmp(p->info, info) != 0) {
        ant = p;
        p = p->prox;
    }
    if (p == NULL) {
        return lista; 
    }
    if (ant == NULL) {
        lista = p->prox; 
    } else {
        ant->prox = p->prox; 
    }
    free(p);
    return lista;
}

void liberarLista(Lista* lista) {
    Lista* p;
    while (lista != NULL) {
        p = lista;
        lista = lista->prox;
        free(p);
    }
}

int verificarVazia(Lista* lista) {
    return lista == NULL; 
}
