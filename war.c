#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio *mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\nTerritorio %d\n", i + 1);

        printf("Nome do territorio: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf(" %9s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os territórios
void exibirTerritorios(Territorio *mapa, int total) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < total; i++) {
        printf("\n[%d] %s", i, mapa[i].nome);
        printf("\nCor: %s", mapa[i].cor);
        printf("\nTropas: %d\n", mapa[i].tropas);
    }
}

// Função de ataque entre territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nRolagem de dados:");
    printf("\nAtacante (%s): %d", atacante->nome, dadoAtacante);
    printf("\nDefensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor && atacante->tropas > 1) {
        printf("\n>>> Ataque bem-sucedido! <<<\n");

        // Troca de cor
        strcpy(defensor->cor, atacante->cor);

        // Transferência de tropas
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

    } else {
        printf("\n>>> Ataque falhou! Atacante perde 1 tropa <<<\n");
        atacante->tropas--;
    }
}

// Função para liberar memória
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {
    int totalTerritorios;
    int atacanteIndex, defensorIndex;
    char continuar;

    srand(time(NULL));

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &totalTerritorios);

    // Alocação dinâmica dos territórios
    Territorio *mapa = (Territorio *)calloc(totalTerritorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, totalTerritorios);

    do {
        exibirTerritorios(mapa, totalTerritorios);

        printf("\nEscolha o territorio ATACANTE (indice): ");
        scanf("%d", &atacanteIndex);

        printf("Escolha o territorio DEFENSOR (indice): ");
        scanf("%d", &defensorIndex);

        // Validações
        if (atacanteIndex < 0 || atacanteIndex >= totalTerritorios ||
            defensorIndex < 0 || defensorIndex >= totalTerritorios) {
            printf("\nIndices invalidos.\n");
        }
        else if (strcmp(mapa[atacanteIndex].cor, mapa[defensorIndex].cor) == 0) {
            printf("\nNao é permitido atacar territorio da mesma cor.\n");
        }
        else if (mapa[atacanteIndex].tropas <= 1) {
            printf("\nTerritorio atacante nao possui tropas suficientes.\n");
        }
        else {
            atacar(&mapa[atacanteIndex], &mapa[defensorIndex]);
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    // Liberação da memória
    liberarMemoria(mapa);

    printf("\nMemoria liberada. Programa encerrado.\n");

    return 0;
}
