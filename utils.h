#ifndef UTILS_H
#define UTILS_H

// Struct que representa o estado do jogo
typedef struct {

    int *moedas;
    int numFilas;

    int modo;
    int dificuldade;
    int jogadorAtual;
} EstadoDoJogo;

// Função para iniciar o jogo
EstadoDoJogo* iniciarJogo();

//  Função para mostrar o estado do jogo atual
void estadoDoJogo(EstadoDoJogo *estado);

// Funções para validar e realizar jogadas
int validarJogada(EstadoDoJogo *estado, int moedas, int filas);
int jogada(EstadoDoJogo *estado, int moedas, int filas);
int jogoAcabou(EstadoDoJogo *estado);

// Funções para guardar, carregar e apagar o jogo
void guardarJogo(EstadoDoJogo *estado);
EstadoDoJogo* carregarJogo();
void apagarJogoGuardado();

// Jogadas da maquina no modo fácil, e a lógica XOR para a jogada ideal da maquina caso o modo seja difícil
void jogadaMaquina(EstadoDoJogo *estado);
int XOR(EstadoDoJogo *estado);
void jogadaMaquinaXOR(EstadoDoJogo *estado);

// Funções dos modos de jogo
void humanoXhumano(EstadoDoJogo *estado);
void humanoXmaquinaFacil(EstadoDoJogo *estado);
void humanoXmaquinaDificil(EstadoDoJogo *estado);

// Libertar memória
void limparEstado(EstadoDoJogo *estado);

#endif
