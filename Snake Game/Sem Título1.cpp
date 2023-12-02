//Trabalho Final Da Materia "ESTRUTURA DE DADOS"
//GRUPO 8
//Integrantes: João Victor Santos Neri e Efraim Trovão Lustosa Moraes
//Professor: Joao Robson Santos Martins

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

#define COR_COBRA 2   
#define COR_COMIDA 4  



//Lógica do jogo

//O código implementa a lógica clássica do jogo Snake.
//A matriz G representa o tabuleiro, onde a cobra (representada
//por X e Y) move-se, come comida e evita colisões. A função
//configurar() inicializa o jogo, fimDeJogo() trata o término,
//e o loop principal controla o movimento da cobra. A cada iteração,
//a função imprimir() exibe o estado atual na tela, e as entradas
//do jogador definem a direção. O objetivo é aumentar o comprimento
//da cobra, evitando colisões. Uma abordagem clara e eficiente
//para a mecânica clássica do Snake.



//Variaveis

int G[26][76], X[1771], Y[1771], l = 5, s = 0, x, y, f = 0, d = 1;
int recorde = 0;



//Função imprimir 

//Essa função é responsável por imprimir o estado atual do jogo na tela.
//Ela utiliza loops para percorrer a matriz G e imprime caracteres visuais
//correspondentes aos elementos do jogo, como a cobra, a comida e a direção
//da cabeça da cobra. Além disso, utiliza códigos ANSI para colorir a cobra
//e a comida. No final, imprime a pontuação atual do jogador.

void imprimir() {
    int i, j;
    for (i = 1; i <= 25; i++) {
        for (j = 1; j <= 75; j++) {
        	
        	//1 a 6 são usados para representar diferentes partes da cobra
        	
            if ((i == 1 || i == 25) && (j < 35 || j > 39))
                printf("|");
            else if ((j == 1 || j == 75) && (i < 10 || i > 14))
                printf("-");
            else if (G[i][j] == 1)
                printf("\033[1;%dm*\033[0m", COR_COBRA); //Cor da cobra
            else if (G[i][j] == 2)
                printf("\033[1;%dm*\033[0m", COR_COMIDA); //Cor da comida
            else if (G[i][j] == 3)
                printf(">"); //Direção da cabeça para a direita
            else if (G[i][j] == 4)
                printf("^"); //Direção da cabeça para cima
            else if (G[i][j] == 5)
                printf("<"); //Direção da cabeça para a esquerda
            else if (G[i][j] == 6)
                printf("v"); //Direção da cabeça para baixo
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("\nPontuação: %d", s); //Imprimir pontuação
}



//Função Configurar

//Essa Função oonfigura o estado inicial do jogo. Inicializa a matriz G
//representando o campo de jogo, define a posição inicial da cobra, limita
//as bordas do campo e posiciona a comida, caso seja necessário.

void configurar() {
    int i, j;
    
    //Inicializa a matriz G representando o campo de jogo
    for (i = 1; i <= 25; i++) {
        for (j = 1; j <= 75; j++) {
            if (i == 1 || i == 25 || j == 1 || j == 75)
                G[i][j] = 1; //Paredes do campo
            else
                G[i][j] = 0; //Espaços internos do campo
        }
    }
	
	//Remove partes desnecessárias nas bordas para criar aberturas
    for (i = 10; i <= 14; i++) {
        G[i][1] = 0;
        G[i][75] = 0;
    }

    for (i = 35; i <= 39; i++) {
        G[1][i] = 0;
        G[25][i] = 0;
    }
	
	//Define a posição da cabeça da cobra e a direção na matriz G
    G[X[0]][Y[0]] = 1;
    
    if (d == 1)
        G[X[1]][Y[1]] = 3; //Direção da cabeça para a direita
    else if (d == 2)
        G[X[1]][Y[1]] = 4; //Direção da cabeça para cima
    else if (d == 3)
        G[X[1]][Y[1]] = 5; //Direção da cabeça para a esquerda
    else if (d == 4)
        G[X[1]][Y[1]] = 6; //Direção da cabeça para baixo

	//Marca as posições ocupadas pelo corpo da cobra na matriz G
    for (i = 2; i <= l; i++) {
        G[X[i]][Y[i]] = 1;
    }
	
	//Coloca a comida na matriz G se necessário
    if (f > 0) {
        G[x][y] = 2;
        f = f - 1;
    }
}



//Função ImprimirMenu

//Essa função é respondavel por imprimir o menu inicial na tela
//e apresenta opções para iniciar o jogo ou sair.

void imprimirMenu() {
    system("CLS"); //Limpa a tela
    printf("=== Jogo da Cobra ===\n");
    printf("      Bem vindo!\n\n");

    printf("1. Iniciar Jogo\n"); //Iniciar
    printf("2. Sair\n\n"); //Sair
}



//Função ObterEscolhaMenu

//Essa função é responsavel por solitar o usuario a escolha
//das opções do meunu

int obterEscolhaMenu() {
    int escolha;
    printf("Digite sua escolha: "); 
    scanf("%d", &escolha); //leitura da escolha
    return escolha;
}



//Função MostrarInstruções

//Essa função é responsavel por exibir as instruções do jogo
//na tela. Informa ao jogador como controlar a cobra, crescer
//ao comer a comida e evitar colisões.

void mostrarInstrucoes() {
    system("CLS"); //Limpa a tela
    printf("=== Instruções ===\n\n");
    printf("Use as setas para controlar a cobra.\n");
    printf("Coma a comida (*) para crescer a cobra e ganhar pontos.\n");
    printf("Evite colisões com as paredes e o corpo da cobra.\n\n");
    printf("Pressione qualquer tecla para continuar...\n\n");
    getch();
}



//Função MenuGameOver

//Essa Função é responsavel por apresentar o menu de game over
//quando o jogo termina. Mostra a pontuação alcançada e o recorde
//atual, além de oferecer opções para jogar novamente ou sair do jogo.

void menuGameOver() {
    system("CLS"); //Limpa a tela
    printf("=== Fim de Jogo ===\n\n");
    printf("Pontuação: %d\n", s); //Pontuação da rodada
    printf("Recorde: %d\n\n", recorde); //Recorde
    printf("1. Jogar Novamente\n"); //Jogar Novamente
    printf("2. Sair do Jogo\n\n"); //Sair
}



//Função ObterEscolhaMenuGameOver

//Essa função é responsavel por obter a escolha do usuário a partir 
//do menu de fim de jogo. Similar à função obterEscolhaMenu(), solicita
//uma entrada e retorna o valor inserido.

int obterEscolhaMenuGameOver() {
    int escolha;
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);//Leitura da escolha
    return escolha;
}



//Função FimDeJogo

//Essa função é chamada quando o jogo termina. Ela atualiza o recorde
//se necessário, exibe o menu de fim de jogo e reinicia o jogo ou encerra
//o programa conforme a escolha do jogador.

void fimDeJogo() {
	
	//Verifica se a pontuação atual é maior que o recorde e, se for, atualiza o recorde
    if (s > recorde) {
        recorde = s;
    }
	
    menuGameOver();//Chama o menu de fim de jogo
    int escolha = obterEscolhaMenuGameOver();//Obtém a escolha do usuário no menu de fim de jogo

    switch (escolha) {
        case 1:
        	
        	//Reinicia o jogo com valores iniciais
            l = 5;
            s = 0;
            x = 0;
            y = 0;
            f = 0;
            d = 1;

			//Define a posição inicial da cobra
            X[1] = 12;
            Y[1] = 12;
            X[2] = 12;
            Y[2] = 11;
            X[3] = 12;
            Y[3] = 10;
            X[4] = 12;
            Y[4] = 9;
            X[5] = 12;
            Y[5] = 8;

			//Gera uma nova posição para a comida que não está ocupada pela cobra
            while (G[X[0]][Y[0]] >= 1) {
                X[0] = rand() % 23 + 2;
                Y[0] = rand() % 73 + 2;
            }
            break;
        case 2:
        	//Encerra o programa
            exit(0);
        default:
        	//Em caso de escolha inválida, exibe uma mensagem de erro e encerra o programa
            printf("Escolha inválida. Saindo...\n");
            exit(1);
    }
}



//Função Creditos

//Essa função exibe os créditos por 5 segundos.

void exibirCreditos() {
    system("CLS"); // Limpa a tela
    printf("=== Créditos ===\n\n");
    printf("Desenvolvido por:\n");
    printf("João Victor Santos Neri\n");
    printf("Efraim Trovão Lustosa Moraes\n\n");
    printf("Obrigado por jogar!\n");
    Sleep(5000); // Espera por 5 segundos
}



//Função Main

//Essa é a função principal do programa. Configura a localização
//para imprimir caracteres especiais, inicializa variáveis, apresenta
//o menu inicial e executa o jogo ou sai do programa de acordo com a
//escolha do jogador.

int main() {
    setlocale(LC_ALL, "Portuguese"); //Define o idioma para Português

    int escolha;

    imprimirMenu(); //Chama o Menu Inicial
    escolha = obterEscolhaMenu(); //Obtém a escolha do menu
	
	//Executa a ação com base na escolha do usuário
    switch (escolha) {
        case 1:
        	//Mostra as instruções do jogo
            mostrarInstrucoes();
            break;
        case 2:
        	//Exibe os créditos ao sair do jogo
        	exibirCreditos();
            return 0;
        default:
        	//Encerra o programa em caso de escolha inválida
            printf("Escolha inválida. Saindo...\n");
            return 1;
    }
	
	//Inicializa o gerador de números aleatórios com o tempo atual
    srand(time(NULL));
    
    //Configuração inicial das posições da cobra, comida e outras variáveis
    X[0] = 0;
    Y[0] = 0;
    X[1] = 12;
    Y[1] = 12;
    X[2] = 12;
    Y[2] = 11;
    X[3] = 12;
    Y[3] = 10;
    X[4] = 12;
    Y[4] = 9;
    X[5] = 12;
    Y[5] = 8;
    int i = 12, j = 12;
	
	//Configuração inicial do campo de jogo
    configurar();
	
	//Posiciona a comida em uma posição não ocupada pela cobra
    while (G[X[0]][Y[0]] >= 1) {
        X[0] = rand() % 23 + 2;
        Y[0] = rand() % 73 + 2;
    }
	
	//Configuração inicial do campo de jogo novamente e exibe o campo
    configurar();
    imprimir();
    getch();
    system("CLS"); //Limpa a tela
	
	//Loop principal do jogo
    while (1) {
        configurar();//Atualiza o campo de jogo
        imprimir();//Exibe o campo de jogo
	
		//Movimento para a direita
        if (d == 1) {
            if (Y[1] == 75)
                Y[1] = 0;
            if (G[X[1]][Y[1] + 1] == 0) {
            	//Move a cobra para a direita
                for (int k = l; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                Y[1] = Y[1] + 1;
                i = X[1];
                j = Y[1];
            } else if ((X[1] == X[0]) && (Y[1] + 1 == Y[0])) {
                //Cobra comeu a comida
        		//Move a cobra para a direita e gera uma nova posição para a comida
				for (int k = l + 1; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                Y[1] = Y[1] + 1;
                i = X[1];
                j = Y[1];
                x = X[0];
                y = Y[0];
                f = l;
                while (G[X[0]][Y[0]] >= 1) {
                    X[0] = rand() % 23 + 2;
                    Y[0] = rand() % 73 + 2;
                }
                l = l + 1;
                s = s + 1;
            } else
                fimDeJogo();//Fim de jogo, caso haja colisão com a parede ou com a própria cobra
                
        //Movimento para cima       
        } else if (d == 2) {
            if (X[1] == 1)
                X[1] = 26;
            if (G[X[1] - 1][Y[1]] == 0) {
            	//Move a cobra para cima
                for (int k = l; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                X[1] = X[1] - 1;
                i = X[1];
                j = Y[1];
            } else if ((X[1] - 1 == X[0]) && (Y[1] == Y[0])) {
            	//Cobra comeu a comida
        		//Move a cobra para cima e gera uma nova posição para a comida
                for (int k = l + 1; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                X[1] = X[1] - 1;
                i = X[1];
                j = Y[1];
                x = X[0];
                y = Y[0];
                f = l;
                while (G[X[0]][Y[0]] >= 1) {
                    X[0] = rand() % 23 + 2;
                    Y[0] = rand() % 73 + 2;
                }
                l = l + 1;
                s = s + 1;
            } else
                fimDeJogo();//Fim de jogo, caso haja colisão com a parede ou com a própria cobra
                
        //Movimento para a esquerda
        } else if (d == 3) {
            if (Y[1] == 1)
                Y[1] = 76;
            if (G[X[1]][Y[1] - 1] == 0) {
            	//Move a cobra para a esquerda
                for (int k = l; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                Y[1] = Y[1] - 1;
                i = X[1];
                j = Y[1];
            } else if ((X[1] == X[0]) && (Y[1] - 1 == Y[0])) {
            	//Cobra comeu a comida
        		//Move a cobra para a esquerda e gera uma nova posição para a comida
                for (int k = l + 1; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                Y[1] = Y[1] - 1;
                i = X[1];
                j = Y[1];
                x = X[0];
                y = Y[0];
                f = l;
                while (G[X[0]][Y[0]] >= 1) {
                    X[0] = rand() % 23 + 2;
                    Y[0] = rand() % 73 + 2;
                }
                l = l + 1;
                s = s + 1;
            } else
                fimDeJogo();//Fim de jogo, caso haja colisão com a parede ou com a própria cobra
                
        //Movimento para baixo
        } else if (d == 4) {
            if (X[1] == 25)
                X[1] = 0;
            if (G[X[1] + 1][Y[1]] == 0) {
            	//Move a cobra para baixo
                for (int k = l; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                X[1] = X[1] + 1;
                i = X[1];
                j = Y[1];
            } else if ((X[1] + 1 == X[0]) && (Y[1] == Y[0])) {
            	//Cobra comeu a comida
        		//Move a cobra para baixo e gera uma nova posição para a comida
                for (int k = l + 1; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                X[1] = X[1] + 1;
                i = X[1];
                j = Y[1];
                x = X[0];
                y = Y[0];
                f = l;
                while (G[X[0]][Y[0]] >= 1) {
                    X[0] = rand() % 23 + 2;
                    Y[0] = rand() % 73 + 2;
                }
                l = l + 1;
                s = s + 1;
            } else
                fimDeJogo();//Fim de jogo, caso haja colisão com a parede ou com a própria cobra
        }

        if ((GetAsyncKeyState(VK_RIGHT)) && (d != 3))
            d = 1;
        else if ((GetAsyncKeyState(VK_UP)) && (d != 4))
            d = 2;
        else if ((GetAsyncKeyState(VK_LEFT)) && (d != 1))
            d = 3;
        else if ((GetAsyncKeyState(VK_DOWN)) && (d != 2))
            d = 4;

        Sleep(18);//Pequena pausa para controlar a velocidade do jogo
        system("CLS");//Limpa a tela 
    }

    return 0;
}



