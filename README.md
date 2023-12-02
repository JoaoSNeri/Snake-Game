# Snake Game

## Descrição do Projeto

Este projeto implementa a lógica clássica do jogo Snake em linguagem C. A matriz G representa o tabuleiro, onde a cobra (representada por X e Y) move-se, come comida e evita colisões. O jogo possui uma abordagem clara e eficiente para a mecânica clássica do Snake.

## Funcionalidades

- **Imprimir o Estado Atual:**
  - Função `imprimir()` exibe o estado atual do jogo na tela, utilizando códigos ANSI para colorir a cobra e a comida.

- **Configuração Inicial do Jogo:**
  - Função `configurar()` inicializa o campo de jogo, define a posição inicial da cobra, limita as bordas do campo e posiciona a comida.

- **Menu Inicial:**
  - Função `imprimirMenu()` exibe opções iniciais para iniciar o jogo ou sair.

- **Instruções do Jogo:**
  - Função `mostrarInstrucoes()` exibe as instruções do jogo na tela, informando ao jogador como controlar a cobra, crescer ao comer a comida e evitar colisões.

- **Menu de Game Over:**
  - Função `menuGameOver()` mostra o menu de game over, exibindo a pontuação alcançada, o recorde atual e oferecendo opções para jogar novamente ou sair.

- **Créditos:**
  - Função `exibirCreditos()` exibe os créditos do jogo por 5 segundos.

## Como Jogar

1. Execute o programa.
2. Escolha a opção no menu inicial.
   - Opção 1: Iniciar Jogo
   - Opção 2: Sair do Jogo

## Controles

- Use as setas direcionais para controlar a direção da cobra:
  - Seta para cima: Mover para cima
  - Seta para baixo: Mover para baixo
  - Seta para a direita: Mover para a direita
  - Seta para a esquerda: Mover para a esquerda

- Coma a comida (*) para aumentar o comprimento da cobra e ganhar pontos.

- Evite colisões com as paredes e o próprio corpo da cobra.

## Recorde

- O recorde atual é mantido durante as sessões de jogo.

---

Desenvolvido por:
- João Victor Santos Neri
- Efraim Trovão Lustosa Moraes

Obrigado por jogar!
