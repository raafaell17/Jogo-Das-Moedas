#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

int main(){

    int opcao, dificuldade;
    EstadoDoJogo *estado = NULL;
    srand(time(NULL));

    do{
        printf("Bem-vindo ao Jogo da Moeda!\n");
        printf("Por favor digite a opção que pretendo:\n");
        printf("    1 - Iniciar Novo Jogo\n");
        printf("    2 - Continuar Jogo Guardado\n");
        printf("    3 - Sair\n");
        
        while(1){
        
            int input = scanf("%d", &opcao);
            if(input != 1 || opcao < 1 || opcao > 3){
                printf("Numero não encontrado no menu!\n");
                while(getchar() != '\n'); // Limpa o buffer
            } else {
                while(getchar() != '\n');
                break;
            }
        }
        
        if(opcao == 1){
            int modo;
            do{
                printf("Iniciar um Novo Jogo\n");
                printf("Por favor digite o modo que pretende:\n");
                printf("    1 - Humano X Humano\n");
                printf("    2 - Humano X Máquina\n");
                printf("    3 - Voltar ao Menu anterior\n");

                while(1){
                    int input = scanf("%d", &modo);
                    if(input != 1 || modo < 1 || modo > 3){
                        printf("Numero não encontrado no menu!\n");
                        while(getchar() != '\n'); // Limpa o buffer
                    } else {
                        while(getchar() != '\n');
                        break;
                    }
                }
            } while(modo < 1 || modo > 3);

            if(modo == 3){
                continue;
            }
              
            estado = iniciarJogo();

            if(modo == 1){
                estado->modo = 1;
                estado->dificuldade = 0;
                estado->jogadorAtual = 1;
                
                printf("Jogo Iniciou!\n");
                printf("Para guardar o jogo, no estado atual, inserir 0 0.\n");
                
                humanoXhumano(estado);

                limparEstado(estado);
                estado = NULL;
            }

            if(modo == 2){
                estado->modo = 2;

                do{
                    printf("Por favor digite o que pretende:\n");
                    printf("    1 - Modo Fácil\n");
                    printf("    2 - Modo Difícil\n");
                    printf("    3 - Voltar ao Menu anterior\n");

                    while(1){
                        int input = scanf("%d", &dificuldade);
                        if(input != 1 || dificuldade < 1 || dificuldade > 3){
                            printf("Número não encontrado no menu!\n");
                            while(getchar() != '\n');
                        } else {
                            while(getchar() != '\n');
                            break;
                        }
                    }
                } while (dificuldade < 1 || dificuldade > 3);

                if(dificuldade == 3){
                    limparEstado(estado);
                    estado = NULL;
                    continue;
                }
                
                if(dificuldade == 1){
                    estado->dificuldade = 1;
                    estado->jogadorAtual = 1;
                    
                    printf("Jogo Iniciou!\n");
                    printf("Para guardar o jogo, no estado atual, inserir 0 0.\n");
                    
                    humanoXmaquinaFacil(estado);

                    limparEstado(estado);
                    estado = NULL;
                }

                if(dificuldade == 2){
                    estado->dificuldade = 2;
                    estado->jogadorAtual = 1;
                    
                    printf("Jogo Iniciou!\n");
                    printf("Para guardar o jogo, no estado atual, inserir 0 0.\n");
                    
                    humanoXmaquinaDificil(estado);

                    limparEstado(estado);
                    estado = NULL;
                }
            }
        }

        if(opcao == 2) {
            estado = carregarJogo();
            if(estado == NULL){
                while(getchar() != '\n');
                continue;
            } else {
                printf("Continuar Jogo!\n");
            }

            if (estado->modo == 1) {
                humanoXhumano(estado);
            }
            else if (estado->modo == 2) {
                if (estado->dificuldade == 1) {
                    humanoXmaquinaFacil(estado);
                } 
                else if (estado->dificuldade == 2) {
                    humanoXmaquinaDificil(estado);
                }
            }

            limparEstado(estado);
            estado = NULL;
        }

        if(opcao == 3){
            printf("A sair do Jogo!\n");
        }
    } while(opcao != 3);


    return 0;
}
