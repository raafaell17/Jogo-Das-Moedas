#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


EstadoDoJogo* iniciarJogo() {
    EstadoDoJogo *estado = malloc(sizeof(EstadoDoJogo));
    if (estado == NULL) {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }

    do {
        printf("Quantas filas deseja no seu jogo?\n");
        int input = scanf("%d", &estado->numFilas);
        if (input != 1 || estado->numFilas <= 0) {
            printf("Número de filas inválido.\n");
            while (getchar() != '\n');
            estado->numFilas = -1;
        }
    } while (estado->numFilas <= 0);

    estado->moedas = malloc(estado->numFilas * sizeof(int));
    if (estado->moedas == NULL) {
        printf("Erro ao alocar memória para as moedas.\n");
        free(estado);
        return NULL;
    }
    
    for (int i = 0; i < estado->numFilas; i++) {
        int moedas;
        do {
            printf("Quantas moedas tem a fila %d?\n", i + 1);
            int input = scanf("%d", &moedas);
            if (input != 1 || moedas <= 0) {
                printf("Número de moedas inválido.\n");
                while (getchar() != '\n');
                moedas = -1;
            }
        } while (moedas <= 0);

        estado->moedas[i] = moedas;
    }

    return estado;
}

void estadoDoJogo(EstadoDoJogo *estado){

    printf("\nEstado do jogo:\n");
    for(int i = 0; i < estado->numFilas; i++){
        printf("Fila %d: %d moedas\n", i + 1, estado->moedas[i]);
    }
    printf("\n"); // Nova linha após cada fila
}

int validarJogada(EstadoDoJogo *estado, int moedas, int filas){

    if(filas < 1 || filas > estado->numFilas || moedas < 1 || moedas > estado->moedas[filas - 1]){
        printf("Digite valores possíveis para este jogo!\n");
        return 0;
    }
    return 1;
}

int jogada(EstadoDoJogo *estado, int moedas, int filas){

    if(!validarJogada(estado, moedas, filas)){
        return 0;
    }
    estado->moedas[filas - 1] -= moedas;
    return 1;
}

int jogoAcabou(EstadoDoJogo *estado){
    
    for(int i = 0; i < estado->numFilas; i++){
        if(estado->moedas[i] > 0){
            return 0;
        }
    }
    return 1;
}

void guardarJogo(EstadoDoJogo *estado) {
    FILE *arquivo = fopen("jogo_guardado.bin", "wb");
    if (!arquivo) {
        printf("Erro ao guardar o jogo.\n");
        return;
    }
    fwrite(&estado->numFilas, sizeof(int), 1, arquivo);
    fwrite(estado->moedas, sizeof(int), estado->numFilas, arquivo);
    fwrite(&estado->modo, sizeof(int), 1, arquivo);
    fwrite(&estado->dificuldade, sizeof(int), 1, arquivo);
    fwrite(&estado->jogadorAtual, sizeof(int), 1, arquivo);
    fclose(arquivo);
    printf("O jogo foi guardado.\n");
}

EstadoDoJogo* carregarJogo() {
    FILE *arquivo = fopen("jogo_guardado.bin", "rb");
    if (!arquivo) {
        printf("Não existe um jogo guardado.\n");
        return NULL;
    }
    EstadoDoJogo *estado = malloc(sizeof(EstadoDoJogo));
    fread(&estado->numFilas, sizeof(int), 1, arquivo);
    estado->moedas = malloc(estado->numFilas * sizeof(int));
    fread(estado->moedas, sizeof(int), estado->numFilas, arquivo);
    fread(&estado->modo, sizeof(int), 1, arquivo);
    fread(&estado->dificuldade, sizeof(int), 1, arquivo);
    fread(&estado->jogadorAtual, sizeof(int), 1, arquivo);
    fclose(arquivo);

    printf("Continuar Jogo!\n");
    return estado;
}

void apagarJogoGuardado(){
    if(remove("jogo_guardado.bin") == 0){
        printf("Jogo guardado apagado com sucesso!\n");
    }
}

void jogadaMaquina(EstadoDoJogo *estado){
    int fila, moedas;
    do {
        fila = rand() % estado->numFilas;
    } while (estado->moedas[fila] == 0);

    moedas = (rand() % estado->moedas[fila]) + 1;
    printf("A máquina escolheu a fila %d e retirou %d moedas.\n", fila + 1, moedas);
    estado->moedas[fila] -= moedas;
}

int XOR(EstadoDoJogo *estado){
    int xor = 0;
    for(int i = 0; i < estado->numFilas; i++){
        xor ^= estado->moedas[i];
    }
    return xor;
}

void jogadaMaquinaXOR(EstadoDoJogo *estado){
    int xor = XOR(estado);
    int fila, estadoMoedas;

    if(xor == 0){
        do{
            fila = rand() % estado->numFilas;
        } while(estado->moedas[fila] == 0);

        int jogada = (rand() % estado->moedas[fila]) + 1;
        estado->moedas[fila] -= jogada;
        printf("A máquina escolheu a fila %d e retirou %d moedas.\n", fila + 1, jogada);
    }

    if(xor != 0){
        for(int i = 0; i < estado->numFilas; i++){
            estadoMoedas = estado->moedas[i];
            int aposXOR = estadoMoedas ^ xor;
            if(aposXOR < estadoMoedas){
                int jogada = estadoMoedas - aposXOR;
                estado->moedas[i] -= jogada;
                printf("A máquina escolheu a fila %d e retirou %d moedas.\n", i + 1, jogada);
                return;
            }
        }
    }
}

void humanoXhumano(EstadoDoJogo *estado) {
    int jogadorAtual = estado->jogadorAtual;
    do{
        estadoDoJogo(estado);
        printf("Jogador %d - Escolha a fila de moedas e o número de moedas a retirar?\n", jogadorAtual);
                    
        int fila, moedas;
        int input = scanf("%d %d", &fila, &moedas);
                    
        if(input !=2){
            printf("Digite valores possíveis para este jogo!\n");
            while(getchar() != '\n');
            continue;
        }

        if(fila == 0 && moedas == 0){
            guardarJogo(estado);
            break;
        }
                    
        if(!validarJogada(estado, moedas, fila)){
            continue;
        }
        jogada(estado, moedas, fila);

        if(jogoAcabou(estado)){
            estadoDoJogo(estado);
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
            printf("Jogador %d Venceu!\n", jogadorAtual);
            apagarJogoGuardado();
            break;
        }

        jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        estado->jogadorAtual = jogadorAtual;

    } while(1);
}

void humanoXmaquinaFacil(EstadoDoJogo *estado){
    int jogadorAtual = estado->jogadorAtual;
    do{
        estadoDoJogo(estado);

        if(jogadorAtual == 1){ 
            printf("Jogador %d - Escolha a fila de moedas e o número de moedas a retirar?\n", jogadorAtual);
            int fila, moedas;
            int input = scanf("%d %d", &fila, &moedas);
                        
            if(input != 2){
                printf("Digite valores possíveis para este jogo!\n");
                while(getchar() != '\n');
                continue;
            }

            if(fila == 0 && moedas == 0){
                guardarJogo(estado);
                break;
            }

            if(!validarJogada(estado, moedas, fila)){
                continue;
            }

            jogada(estado, moedas, fila);
        }
                    
        else {
            jogadaMaquina(estado);
        }

        if(jogoAcabou(estado)){
            estadoDoJogo(estado);
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
            printf("Jogador %d Venceu!\n", jogadorAtual);
            apagarJogoGuardado();
            break;
        }

        jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        estado->jogadorAtual = jogadorAtual;

    } while(1);
}

void humanoXmaquinaDificil(EstadoDoJogo *estado){
    int jogadorAtual = estado->jogadorAtual;
    do{
        estadoDoJogo(estado);

        if(jogadorAtual == 1){
            printf("Jogador %d - Escolha a fila de moedas e o número de moedas a retirar?\n", jogadorAtual);
            int fila, moedas;
            int input = scanf("%d %d", &fila, &moedas);

            if(input != 2){
                printf("Digite valores possíveis para este jogo!\n");
                while(getchar() != '\n');
                continue;
            }

            if(fila == 0 && moedas == 0){
                guardarJogo(estado);
                break;
            }

            if(!validarJogada(estado, moedas, fila)){
                continue;
            }

            jogada(estado, moedas, fila);
        }

        else {
            jogadaMaquinaXOR(estado);
        }

        if(jogoAcabou(estado)){
            estadoDoJogo(estado);
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
            printf("Jogador %d Venceu!\n", jogadorAtual);
            apagarJogoGuardado();
            break;
        }

        jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        estado->jogadorAtual = jogadorAtual;

    } while(1);
}

void limparEstado(EstadoDoJogo *estado) {
    free(estado->moedas);
    free(estado);
}
