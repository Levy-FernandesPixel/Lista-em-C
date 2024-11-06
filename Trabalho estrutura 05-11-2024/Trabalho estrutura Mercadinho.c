#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Hélio Wesley da Silva Martins
//Antonio Wagner Levy Lima Fernandes
#define MAX_FRUTAS 100

typedef struct {
    int codigo;
    char nome[30];
    int quantidade;
    float preco;
} Fruta;

Fruta* frutas[MAX_FRUTAS];
int numFrutas = 0;

void cadastrarFruta();
void listarFrutas();
void buscarFruta();
void alterarFruta();
void excluirFruta();
void venderFruta();
void registrarVenda(int codigo, int quantidade);

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar fruta\n");
        printf("2. Listar frutas\n");
        printf("3. Buscar fruta\n");
        printf("4. Alterar fruta\n");
        printf("5. Excluir fruta\n");
        printf("6. Vender fruta\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarFruta(); break;
            case 2: listarFrutas(); break;
            case 3: buscarFruta(); break;
            case 4: alterarFruta(); break;
            case 5: excluirFruta(); break;
            case 6: venderFruta(); break;
            case 7: printf("Saindo...\n"); break;
            default: printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}

void cadastrarFruta() {
    if (numFrutas >= MAX_FRUTAS) {
        printf("Limite de frutas atingido.\n");
        return;
    }

    Fruta* novaFruta = (Fruta*) malloc(sizeof(Fruta));
    printf("Digite o codigo da fruta: ");
    scanf("%d", &novaFruta->codigo);
    
    for (int i = 0; i < numFrutas; i++) {
        if (frutas[i]->codigo == novaFruta->codigo) {
            printf("Codigo de fruta ja cadastrado.\n");
            free(novaFruta);
            return;
        }
    }

    printf("Digite o nome da fruta: ");
    scanf("%s", novaFruta->nome);
    printf("Digite a quantidade: ");
    scanf("%d", &novaFruta->quantidade);
    printf("Digite o preco: ");
    scanf("%f", &novaFruta->preco);

    frutas[numFrutas++] = novaFruta;
    printf("Fruta cadastrada com sucesso!\n");
}

void listarFrutas() {
    printf("\nLista de frutas:\n");
    for (int i = 0; i < numFrutas; i++) {
        printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n",
               frutas[i]->codigo, frutas[i]->nome, frutas[i]->quantidade, frutas[i]->preco);
    }
}

void buscarFruta() {
    int codigo;
    printf("Digite o codigo da fruta a buscar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < numFrutas; i++) {
        if (frutas[i]->codigo == codigo) {
            printf("Fruta encontrada: Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n",
                   frutas[i]->codigo, frutas[i]->nome, frutas[i]->quantidade, frutas[i]->preco);
            return;
        }
    }
    printf("Fruta nao encontrada.\n");
}

void alterarFruta() {
    int codigo;
    printf("Digite o codigo da fruta a alterar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < numFrutas; i++) {
        if (frutas[i]->codigo == codigo) {
            printf("Digite o novo nome da fruta: ");
            scanf("%s", frutas[i]->nome);
            printf("Digite a nova quantidade: ");
            scanf("%d", &frutas[i]->quantidade);
            printf("Digite o novo preco: ");
            scanf("%f", &frutas[i]->preco);
            printf("Fruta alterada com sucesso!\n");
            return;
        }
    }
    printf("Fruta nao encontrada.\n");
}

void excluirFruta() {
    int codigo;
    printf("Digite o codigo da fruta a excluir: ");
    scanf("%d", &codigo);

    for (int i = 0; i < numFrutas; i++) {
        if (frutas[i]->codigo == codigo) {
            if (frutas[i]->quantidade > 0) {
                printf("A fruta nao pode ser excluida pois ainda ha estoque.\n");
                return;
            }
            free(frutas[i]);
            frutas[i] = frutas[numFrutas - 1]; // substitui pela última
            numFrutas--;
            printf("Fruta excluida com sucesso!\n");
            return;
        }
    }
    printf("Fruta nao encontrada.\n");
}

void venderFruta() {
    int codigo, quantidade;
    printf("Digite o codigo da fruta a vender: ");
    scanf("%d", &codigo);
    printf("Digite a quantidade a vender: ");
    scanf("%d", &quantidade);

    for (int i = 0; i < numFrutas; i++) {
        if (frutas[i]->codigo == codigo) {
            if (frutas[i]->quantidade < quantidade) {
                printf("Quantidade indisponivel em estoque.\n");
                return;
            }
            frutas[i]->quantidade -= quantidade;
            registrarVenda(codigo, quantidade);
            printf("Venda realizada com sucesso!\n");
            return;
        }
    }
    printf("Fruta nao encontrada.\n");
}

void registrarVenda(int codigo, int quantidade) {
    FILE* arquivo = fopen("vendas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de vendas.\n");
        return;
    }
    fprintf(arquivo, "Codigo: %d, Quantidade: %d\n", codigo, quantidade);
    fclose(arquivo);
}