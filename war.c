#include <stdio.h>
#include <string.h>

#define TOTAL_TERRITORIOS 5

// Definição da struct 
// Armazena nome do território, cor do exército e quantidade de tropas
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Vetor para armazenar os 5 territórios
    struct Territorio territorios[TOTAL_TERRITORIOS];

    printf("=== Cadastro de Territorios ===\n\n");

    // Entrada de dados
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Territorio %d\n", i + 1);

        // Leitura do nome do território
        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", territorios[i].nome);

        // Leitura da cor do exército
        printf("Digite a cor do exercito: ");
        scanf(" %9s", territorios[i].cor);

        // Leitura da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("=== Territorios Cadastrados ===\n\n");

    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
