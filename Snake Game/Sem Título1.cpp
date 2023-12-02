//Trabalho Final Da Materia "ESTRUTURA DE DADOS"
//GRUPO 8
//Integrantes: Jo�o Victor Santos Neri e Efraim Trov�o Lustosa Moraes
//Professor: Joao Robson Santos Martins

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

#define COR_COBRA 2   
#define COR_COMIDA 4  



//L�gica do jogo

//O c�digo implementa a l�gica cl�ssica do jogo Snake.
//A matriz G representa o tabuleiro, onde a cobra (representada
//por X e Y) move-se, come comida e evita colis�es. A fun��o
//configurar() inicializa o jogo, fimDeJogo() trata o t�rmino,
//e o loop principal controla o movimento da cobra. A cada itera��o,
//a fun��o imprimir() exibe o estado atual na tela, e as entradas
//do jogador definem a dire��o. O objetivo � aumentar o comprimento
//da cobra, evitando colis�es. Uma abordagem clara e eficiente
//para a mec�nica cl�ssica do Snake.



//Variaveis

int G[26][76], X[1771], Y[1771], l = 5, s = 0, x, y, f = 0, d = 1;
int recorde = 0;



//Fun��o imprimir 

//Essa fun��o � respons�vel por imprimir o estado atual do jogo na tela.
//Ela utiliza loops para percorrer a matriz G e imprime caracteres visuais
//correspondentes aos elementos do jogo, como a cobra, a comida e a dire��o
//da cabe�a da cobra. Al�m disso, utiliza c�digos ANSI para colorir a cobra
//e a comida. No final, imprime a pontua��o atual do jogador.

void imprimir() {
    int i, j;
    for (i = 1; i <= 25; i++) {
        for (j = 1; j <= 75; j++) {
        	
        	//1 a 6 s�o usados para representar diferentes partes da cobra
        	
            if ((i == 1 || i == 25) && (j < 35 || j > 39))
                printf("|");
            else if ((j == 1 || j == 75) && (i < 10 || i > 14))
                printf("-");
            else if (G[i][j] == 1)
                printf("\033[1;%dm*\033[0m", COR_COBRA); //Cor da cobra
            else if (G[i][j] == 2)
                printf("\033[1;%dm*\033[0m", COR_COMIDA); //Cor da comida
            else if (G[i][j] == 3)
                printf(">"); //Dire��o da cabe�a para a direita
            else if (G[i][j] == 4)
                printf("^"); //Dire��o da cabe�a para cima
            else if (G[i][j] == 5)
                printf("<"); //Dire��o da cabe�a para a esquerda
            else if (G[i][j] == 6)
                printf("v"); //Dire��o da cabe�a para baixo
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("\nPontua��o: %d", s); //Imprimir pontua��o
}



//Fun��o Configurar

//Essa Fun��o oonfigura o estado inicial do jogo. Inicializa a matriz G
//representando o campo de jogo, define a posi��o inicial da cobra, limita
//as bordas do campo e posiciona a comida, caso seja necess�rio.

void configurar() {
    int i, j;
    
    //Inicializa a matriz G representando o campo de jogo
    for (i = 1; i <= 25; i++) {
        for (j = 1; j <= 75; j++) {
            if (i == 1 || i == 25 || j == 1 || j == 75)
                G[i][j] = 1; //Paredes do campo
            else
                G[i][j] = 0; //Espa�os internos do campo
        }
    }
	
	//Remove partes desnecess�rias nas bordas para criar aberturas
    for (i = 10; i <= 14; i++) {
        G[i][1] = 0;
        G[i][75] = 0;
    }

    for (i = 35; i <= 39; i++) {
        G[1][i] = 0;
        G[25][i] = 0;
    }
	
	//Define a posi��o da cabe�a da cobra e a dire��o na matriz G
    G[X[0]][Y[0]] = 1;
    
    if (d == 1)
        G[X[1]][Y[1]] = 3; //Dire��o da cabe�a para a direita
    else if (d == 2)
        G[X[1]][Y[1]] = 4; //Dire��o da cabe�a para cima
    else if (d == 3)
        G[X[1]][Y[1]] = 5; //Dire��o da cabe�a para a esquerda
    else if (d == 4)
        G[X[1]][Y[1]] = 6; //Dire��o da cabe�a para baixo

	//Marca as posi��es ocupadas pelo corpo da cobra na matriz G
    for (i = 2; i <= l; i++) {
        G[X[i]][Y[i]] = 1;
    }
	
	//Coloca a comida na matriz G se necess�rio
    if (f > 0) {
        G[x][y] = 2;
        f = f - 1;
    }
}



//Fun��o ImprimirMenu

//Essa fun��o � respondavel por imprimir o menu inicial na tela
//e apresenta op��es para iniciar o jogo ou sair.

void imprimirMenu() {
    system("CLS"); //Limpa a tela
    printf("=== Jogo da Cobra ===\n");
    printf("      Bem vindo!\n\n");

    printf("1. Iniciar Jogo\n"); //Iniciar
    printf("2. Sair\n\n"); //Sair
}



//Fun��o ObterEscolhaMenu

//Essa fun��o � responsavel por solitar o usuario a escolha
//das op��es do meunu

int obterEscolhaMenu() {
    int escolha;
    printf("Digite sua escolha: "); 
    scanf("%d", &escolha); //leitura da escolha
    return escolha;
}



//Fun��o MostrarInstru��es

//Essa fun��o � responsavel por exibir as instru��es do jogo
//na tela. Informa ao jogador como controlar a cobra, crescer
//ao comer a comida e evitar colis�es.

void mostrarInstrucoes() {
    system("CLS"); //Limpa a tela
    printf("=== Instru��es ===\n\n");
    printf("Use as setas para controlar a cobra.\n");
    printf("Coma a comida (*) para crescer a cobra e ganhar pontos.\n");
    printf("Evite colis�es com as paredes e o corpo da cobra.\n\n");
    printf("Pressione qualquer tecla para continuar...\n\n");
    getch();
}



//Fun��o MenuGameOver

//Essa Fun��o � responsavel por apresentar o menu de game over
//quando o jogo termina. Mostra a pontua��o alcan�ada e o recorde
//atual, al�m de oferecer op��es para jogar novamente ou sair do jogo.

void menuGameOver() {
    system("CLS"); //Limpa a tela
    printf("=== Fim de Jogo ===\n\n");
    printf("Pontua��o: %d\n", s); //Pontua��o da rodada
    printf("Recorde: %d\n\n", recorde); //Recorde
    printf("1. Jogar Novamente\n"); //Jogar Novamente
    printf("2. Sair do Jogo\n\n"); //Sair
}



//Fun��o ObterEscolhaMenuGameOver

//Essa fun��o � responsavel por obter a escolha do usu�rio a partir 
//do menu de fim de jogo. Similar � fun��o obterEscolhaMenu(), solicita
//uma entrada e retorna o valor inserido.

int obterEscolhaMenuGameOver() {
    int escolha;
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);//Leitura da escolha
    return escolha;
}



//Fun��o FimDeJogo

//Essa fun��o � chamada quando o jogo termina. Ela atualiza o recorde
//se necess�rio, exibe o menu de fim de jogo e reinicia o jogo ou encerra
//o programa conforme a escolha do jogador.

void fimDeJogo() {
	
	//Verifica se a pontua��o atual � maior que o recorde e, se for, atualiza o recorde
    if (s > recorde) {
        recorde = s;
    }
	
    menuGameOver();//Chama o menu de fim de jogo
    int escolha = obterEscolhaMenuGameOver();//Obt�m a escolha do usu�rio no menu de fim de jogo

    switch (escolha) {
        case 1:
        	
        	//Reinicia o jogo com valores iniciais
            l = 5;
            s = 0;
            x = 0;
            y = 0;
            f = 0;
            d = 1;

			//Define a posi��o inicial da cobra
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

			//Gera uma nova posi��o para a comida que n�o est� ocupada pela cobra
            while (G[X[0]][Y[0]] >= 1) {
                X[0] = rand() % 23 + 2;
                Y[0] = rand() % 73 + 2;
            }
            break;
        case 2:
        	//Encerra o programa
            exit(0);
        default:
        	//Em caso de escolha inv�lida, exibe uma mensagem de erro e encerra o programa
            printf("Escolha inv�lida. Saindo...\n");
            exit(1);
    }
}



//Fun��o Creditos

//Essa fun��o exibe os cr�ditos por 5 segundos.

void exibirCreditos() {
    system("CLS"); // Limpa a tela
    printf("=== Cr�ditos ===\n\n");
    printf("Desenvolvido por:\n");
    printf("Jo�o Victor Santos Neri\n");
    printf("Efraim Trov�o Lustosa Moraes\n\n");
    printf("Obrigado por jogar!\n");
    Sleep(5000); // Espera por 5 segundos
}



//Fun��o Main

//Essa � a fun��o principal do programa. Configura a localiza��o
//para imprimir caracteres especiais, inicializa vari�veis, apresenta
//o menu inicial e executa o jogo ou sai do programa de acordo com a
//escolha do jogador.

int main() {
    setlocale(LC_ALL, "Portuguese"); //Define o idioma para Portugu�s

    int escolha;

    imprimirMenu(); //Chama o Menu Inicial
    escolha = obterEscolhaMenu(); //Obt�m a escolha do menu
	
	//Executa a a��o com base na escolha do usu�rio
    switch (escolha) {
        case 1:
        	//Mostra as instru��es do jogo
            mostrarInstrucoes();
            break;
        case 2:
        	//Exibe os cr�ditos ao sair do jogo
        	exibirCreditos();
            return 0;
        default:
        	//Encerra o programa em caso de escolha inv�lida
            printf("Escolha inv�lida. Saindo...\n");
            return 1;
    }
	
	//Inicializa o gerador de n�meros aleat�rios com o tempo atual
    srand(time(NULL));
    
    //Configura��o inicial das posi��es da cobra, comida e outras vari�veis
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
	
	//Configura��o inicial do campo de jogo
    configurar();
	
	//Posiciona a comida em uma posi��o n�o ocupada pela cobra
    while (G[X[0]][Y[0]] >= 1) {
        X[0] = rand() % 23 + 2;
        Y[0] = rand() % 73 + 2;
    }
	
	//Configura��o inicial do campo de jogo novamente e exibe o campo
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
        		//Move a cobra para a direita e gera uma nova posi��o para a comida
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
                fimDeJogo();//Fim de jogo, caso haja colis�o com a parede ou com a pr�pria cobra
                
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
        		//Move a cobra para cima e gera uma nova posi��o para a comida
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
                fimDeJogo();//Fim de jogo, caso haja colis�o com a parede ou com a pr�pria cobra
                
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
        		//Move a cobra para a esquerda e gera uma nova posi��o para a comida
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
                fimDeJogo();//Fim de jogo, caso haja colis�o com a parede ou com a pr�pria cobra
                
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
        		//Move a cobra para baixo e gera uma nova posi��o para a comida
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
                fimDeJogo();//Fim de jogo, caso haja colis�o com a parede ou com a pr�pria cobra
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



