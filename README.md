# Jogo-Das-Moedas
# Descrição

O Jogo das Moedas é uma implementação do famoso jogo matemático Nim. O objetivo do jogo é evitar ser o jogador que remove a última moeda do tabuleiro. O jogo oferece dois modos: Humano vs Humano e Humano vs Máquina, com diferentes níveis de dificuldade para a IA adversária.

O código do jogo está organizado em dois ficheiros principais: 
- main.c: Contém a lógica principal do jogo, incluindo o menu e a gestão da interação com o jogador;
- utils.c: Implementação das funções auxiliares para gerir o estado do jogo, execução das jogadas e lógica da IA;
- utils.h: Ficheiro de cabeçalho que declara as funções utilizadas no utils.c.
# Requisitos
- Compilador C (GCC ou equivalente)
- Sistema Operativo: Windows, Linux ou macOS
- Bibliotecas Padrão: stdio.h, stdlib.h, string.h
# Características
- Interface baseada em linha de comandos;
- Possibilidade de iniciar um novo jogo ou continuar um jogo guardado;
- Suporte para guardar e carregar o estado do jogo;
- IA com duas dificuldades: Fácil (aleatória) e Difícil (estratégica com XOR).
# Funcões Principais
- EstadoDoJogo* iniciarJogo(); - Inicializa um novo jogo, solicitando ao jogador o número de filas e moedas.
- void exibirEstadoDoJogo(EstadoDoJogo *estado); - Exibe o estado atual do jogo.
- int validarJogada(EstadoDoJogo *estado, int moedas, int fila); - Verifica se a jogada é válida.
- void realizarJogada(EstadoDoJogo *estado, int moedas, int fila); - Atualiza o estado do jogo após uma jogada.
- int jogoAcabou(EstadoDoJogo *estado); - Verifica se o jogo terminou.
- void guardarJogo(EstadoDoJogo *estado); - Guarda o estado do jogo num ficheiro binário.
- EstadoDoJogo* carregarJogo(); - Carrega um jogo previamente guardado.
- void apagarJogoGuardado(); - Apaga o ficheiro de jogo guardado.
- void jogadaMaquina(EstadoDoJogo *estado); - IA faz uma jogada aleatória.
- void jogadaMaquinaXOR(EstadoDoJogo *estado); - IA faz uma jogada otimizada baseada em XOR.
# Como Compilar e Executar
Para compilar o jogo, utilize o compilador gcc: gcc main.c utils.c -o jogo

Para executar o jogo: ./jogo

# Melhorias Futuras
- Implementar uma interface gráfica.
- Melhorar a IA para tornar o jogo mais desafiador.
- Adicionar suporte para diferentes variantes do jogo.
# Licença
Este projeto é distribuído sob a licença MIT. Consulte o ficheiro [Licença](LICENSE) para mais detalhes.
