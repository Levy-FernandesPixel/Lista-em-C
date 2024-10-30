#include <stdio.h>
#include <stdlib.h>
#include "lista_encadeada.h"

int main() {
    Lista* l = criarLista();
    l = inserirOrdem(l, "Guilherme, ADS");
    l = inserirOrdem(l, "Pedro, Engenharia de Software");
    l = inserirOrdem(l, "Kaue, Ciência da Computação");
    l = inserirOrdem(l, "Laura, Medicina");

    printf("Lista antes da remoção:\n");
    exibirLista(l);

    char* busca = "Kaue, Ciência da Computação";
    Lista* x = buscarElemento(l, busca);
    if (x != NULL) {
        printf("\nO elemento buscado é: %s\n", x->info);
    }

    l = excluirElemento(l, "Laura, Medicina");
    printf("\nLista após remoção:\n");
    exibirLista(l);

    liberarLista(l);
    return 0;
}
