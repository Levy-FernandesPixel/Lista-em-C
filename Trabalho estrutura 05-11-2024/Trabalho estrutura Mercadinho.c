#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fruta {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Fruta;

typedef struct lista {
    Fruta fruta;
    struct lista* prox;
} Lista;

Lista* criarLista() {
    return NULL;
}

void exibirMensagem(const char* msg) {
    printf("%s\n", msg);
}

Lista* cadastrarFruta(Lista* lista, int codigo, const char* nome, int quantidade, float preco) {
    for (Lista* temp = lista; temp; temp = temp->prox) {
        if (temp->fruta.codigo == codigo) {
            exibirMensagem("Erro existe uma fruta com este código!");
            return lista;
        }
    }

    Lista* novaFruta = malloc(sizeof(Lista));
    if (!novaFruta) {
        exibirMensagem("Erro de alocação de memória!");
        return lista;
    }

    novaFruta->fruta = (Fruta){codigo, "", quantidade, preco};
    strcpy(novaFruta->fruta.nome, nome);
    novaFruta->prox = lista;
    return novaFruta;
}

void listarFrutas(Lista* lista) {
    if (!lista) {
        exibirMensagem("Nenhuma fruta cadastrada");
        return;
    }
    for (Lista* temp = lista; temp; temp = temp->prox) {
        printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
               temp->fruta.codigo, temp->fruta.nome, temp->fruta.quantidade, temp->fruta.preco);
    }
}

Lista* buscarFruta(Lista* lista, int codigo) {
    for (; lista; lista = lista->prox)
        if (lista->fruta.codigo == codigo)
            return lista;
    return NULL;
}

Lista* alterarFruta(Lista* lista, int codigo, const char* nome, int quantidade, float preco) {
    Lista* fruta = buscarFruta(lista, codigo);
    if (fruta) {
        fruta->fruta = (Fruta){codigo, "", quantidade, preco};
        strcpy(fruta->fruta.nome, nome);
        exibirMensagem("Fruta alterada");
    } else {
        exibirMensagem("Fruta não encontrada");
    }
    return lista;
}

Lista* excluirFruta(Lista* lista, int codigo) {
    Lista *temp = lista, *anterior = NULL;

    while (temp && temp->fruta.codigo != codigo) {
        anterior = temp;
        temp = temp->prox;
    }

    if (!temp) {
        exibirMensagem("Fruta não encontrada");
        return lista;
    }

    if (temp->fruta.quantidade > 0) {
        return lista;
    }

    if (anterior) anterior->prox = temp->prox;
    else lista = temp->prox;

    free(temp);
    exibirMensagem("Fruta excluída com sucesso!");
    return lista;
}

void venderFruta(Lista* lista, int codigo, int quantidade) {
    Lista* fruta = buscarFruta(lista, codigo);
    if (!fruta) {
        exibirMensagem("Fruta não encontrada!");
        return;
    }
    
    if (fruta->fruta.quantidade < quantidade) {
        exibirMensagem("Estoque insuficiente!");
        return;
    }

    fruta->fruta.quantidade -= quantidade;
    FILE* arquivo = fopen("vendas.txt", "a");
    if (!arquivo) {
        exibirMensagem("Erro ao abrir o arquivo de vendas!");
        return;
    }

    fprintf(arquivo, "Venda - Código: %d, Nome: %s, Quantidade: %d, Preço Unitário: %.2f, Total: %.2f\n",
            fruta->fruta.codigo, fruta->fruta.nome, quantidade, fruta->fruta.preco, fruta->fruta.preco * quantidade);
    fclose(arquivo);
    exibirMensagem("Venda realizada com sucesso!");
}

int main() {
    Lista* lista = criarLista();

    lista = cadastrarFruta(lista, 1, "Maçã", 50, 1.99);
    lista = cadastrarFruta(lista, 2, "Banana", 100, 0.99);
    lista = cadastrarFruta(lista, 3, "Laranja", 75, 1.29);

    listarFrutas(lista);

    lista = alterarFruta(lista, 2, "Banana", 120, 1.05);
    listarFrutas(lista);

    lista = excluirFruta(lista, 1);
    listarFrutas(lista);

    venderFruta(lista, 3, 10);

    return 0;
}
