#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===================== STRUCT =====================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ===================== FUNÇÕES EXISTENTES =====================
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

void exibirTerritorios(Territorio *mapa, int total) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < total; i++) {
        printf("\n[%d] %s", i, mapa[i].nome);
        printf("\nCor: %s", mapa[i].cor);
        printf("\nTropas: %d\n", mapa[i].tropas);
    }
}

void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nDados:");
    printf("\nAtacante (%s): %d", atacante->nome, dadoAtacante);
    printf("\nDefensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor && atacante->tropas > 1) {
        printf("\n>>> Ataque venceu! <<<\n");

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
    } else {
        printf("\n>>> Ataque perdeu! Atacante perde 1 tropa <<<\n");
        atacante->tropas--;
    }
}

// ===================== NOVAS FUNÇÕES (MISSÕES) =====================

// Sorteia e atribui missão ao jogador
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Exibe a missão apenas uma vez
void exibirMissao(char *missao) {
    printf("\n=== SUA MISSAO ===\n");
    printf("%s\n", missao);
}

// Verifica se a missão foi cumprida (lógica simples inicial)
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    int territoriosControlados = 0;

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, "Azul") == 0) {
            territoriosControlados++;
        }
    }

    if (strstr(missao, "Conquistar 3 territorios") && territoriosControlados >= 3) {
        return 1;
    }

    return 0;
}

// Liberação de memória
void liberarMemoria(Territorio *mapa, char *missaoJogador) {
    free(mapa);
    free(missaoJogador);
}

// ===================== MAIN =====================
int main() {
    int totalTerritorios;
    int atacanteIndex, defensorIndex;
    char continuar;

    srand(time(NULL));

    // Vetor de missões
    char *missoes[] = {
        "Conquistar 3 territorios",
        "Dominar todos os territorios inimigos",
        "Eliminar tropas de uma cor adversaria",
        "Manter 10 tropas em um territorio",
        "Conquistar territorios consecutivos"
    };

    int totalMissoes = 5;

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &totalTerritorios);

    // Alocação dinâmica do mapa
    Territorio *mapa = (Territorio *)calloc(totalTerritorios, sizeof(Territorio));

    // Alocação dinâmica da missão do jogador
    char *missaoJogador = (char *)malloc(100 * sizeof(char));

    if (mapa == NULL || missaoJogador == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, totalTerritorios);

    // Atribui e exibe missão apenas uma vez
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    do {
        exibirTerritorios(mapa, totalTerritorios);

        printf("\nEscolha o territorio ATACANTE (indice): ");
        scanf("%d", &atacanteIndex);

        printf("Escolha o territorio DEFENSOR (indice): ");
        scanf("%d", &defensorIndex);

        if (atacanteIndex < 0 || atacanteIndex >= totalTerritorios ||
            defensorIndex < 0 || defensorIndex >= totalTerritorios) {
            printf("\nIndices invalidos.\n");
        }
        else if (strcmp(mapa[atacanteIndex].cor, mapa[defensorIndex].cor) == 0) {
            printf("\nNao pode atacar territorio da mesma cor.\n");
        }
        else if (mapa[atacanteIndex].tropas <= 1) {
            printf("\nTropas insuficientes para atacar.\n");
        }
        else {
            atacar(&mapa[atacanteIndex], &mapa[defensorIndex]);
        }

        // Verificação silenciosa da missão
        if (verificarMissao(missaoJogador, mapa, totalTerritorios)) {
            printf("\n🏆 MISSAO CUMPRIDA! VOCE VENCEU O JOGO! 🏆\n");
            break;
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa, missaoJogador);

    printf("\nMemoria liberada. Programa encerrado.\n");

    return 0;
}
