#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <termios.h>

//👻 🍒 😶 🍅 🍎 🍇 🫠
// Função para identificar o sistema operacional e incluir a biblioteca
#ifdef __linux__
	#include <unistd.h>
#elif _WIN32
	#include <windows.h>
#endif

// Função clean conforme o sistema operacional
void clear() {
	#ifdef __linux__
		system("clear");
	#elif _WIN32
		system("cls");
	#else
	#endif
}

// Cores
#define RED "\x1B[31m"
#define GRN "\x1B[32m"  
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

/* Funções Básicas Disponibilizadas */

// Gerador de números aleatórios
int randomInteger (int low, int high) {
    int k;
    double d;

    d = (double) rand () / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);

    return low + k;
}

// Função para gerar o mapa
void geraMapa(int mapa[10][10], int nivel) {
    int i, j, qtdO, qtdA, lin, col, infO=5, supO=15, personagem=1;

    switch (nivel) {
        case 2: infO=5; supO=25; break;
        case 3: infO=15; supO=35; break;
    }

    srand((unsigned int)time(NULL));

    for (i=0; i<10; i++)
        for (j=0; j<10; j++)
            mapa[i][j] = 0;

    mapa[randomInteger(0,9)][0]= personagem;
    mapa[randomInteger(0,9)][9]= 2;
    qtdA = randomInteger(3,10);
    qtdO = randomInteger(infO, supO);

    while (qtdO>0) {
        lin = randomInteger(0,9);
        col = randomInteger(1,8);
        if (mapa[lin][col] == 0) {
            mapa[lin][col] = 3;
            qtdO--;
        }
    }

    while (qtdA>0) {
        lin = randomInteger(0,9);
        col = randomInteger(1,8);
        if (mapa[lin][col] == 0) {
            mapa[lin][col] = 4;
            qtdA--;
        }
    }
}

//atualizar mapa 
void atualizaMapa(int mapa[10][10]) {
    int i, j, upd, atualizado[10][10];
    for (i=0; i<10; i++) for (j=0; j<10; j++) atualizado[i][j]=0;

    for (i=0; i<10; i++)
        for (j=0; j<10; j++) {
            if ((mapa[i][j] == 2 || mapa[i][j] == 3 || mapa[i][j] == 4) && atualizado[i][j] == 0) {
                upd = randomInteger(1,4);
                switch (upd) {
                    case 1:
                        if ((mapa[i-1][j] == 0 || (mapa[i-1][j] == 1 && mapa[i][j] == 3)) && i>0) {
                            mapa[i-1][j] = mapa[i][j];
                            mapa[i][j] = 0;
                            atualizado[i-1][j]=1;
                        }
                        break;
                    case 2:
                        if ((mapa[i+1][j] == 0 || (mapa[i+1][j] == 1 && mapa[i][j] == 3)) && i<9) {
                            mapa[i+1][j] = mapa[i][j];
                            mapa[i][j] = 0;
                            atualizado[i+1][j]=1;
                        }
                        break;
                    case 3:
                        if ((mapa[i][j+1] == 0 || (mapa[i][j+1] == 1 && mapa[i][j] == 3)) && j<9) {
                            mapa[i][j+1] = mapa[i][j];
                            mapa[i][j] = 0;
                            atualizado[i][j+1]=1;
                        }
                        break;
                    case 4:
                        if ((mapa[i][j-1] == 0 || (mapa[i][j-1] == 1 && mapa[i][j] == 3)) && j>0) {
                            mapa[i][j-1] = mapa[i][j];
                            mapa[i][j] = 0;
                            atualizado[i][j-1]=1;
                        }
                }
            }
       }
}

// Função para imprimir o mapa
void imprimeMapa(int mapa[10][10]) {
    int i, j;
    printf("\n  -----------------------------------------------------------------------  ");
    for (i=0; i<10; i++) {
        printf("\n  -----------------------------------------------------------------------  \n  ");
        for (j=0; j<10; j++) {
            if (mapa[i][j]==0) {
                printf("|  ");
                printf("\xF0\x9F\x8C\xBF   ");
            }
            else if (mapa[i][j]==1) {
                printf("|  ");
                printf("\xF0\x9F\x98\x80   ");
            }
            else if (mapa[i][j]==2) {
                printf("|  ");
                printf("\xF0\x9F\x8F\x86   ");
            }
            else if (mapa[i][j]==3) {
                printf("|  ");
                printf("\xF0\x9F\x91\xBB   ");
            }
            else {
                printf("|  ");
                printf("\xF0\x9F\x8D\x8E   ");
            }       
        }
        printf("|");
    }
    printf("\n  -----------------------------------------------------------------------  ");
    printf("\n  -----------------------------------------------------------------------  \n  ");
}


// Função para ler o ranking
void leRanking(char nomes[3][30], int pontos[3]) {
    FILE *arq = NULL;
    int res;
    arq = fopen("rank.dat", "rb");
    if (arq != NULL) {
        
        res=fread(nomes, sizeof(char), 90, arq);
       
        res=fread(pontos, sizeof(int), 3, arq);
        
        fclose(arq);
    } else {
        printf("\n\nNa primeira vez não há nada a ser lido.");
    }
}

// Função para atualizar o ranking
void atualizaRanking(char nomes[3][30], int pontos[3]) {
    FILE *arq = NULL;
    int res;
    arq = fopen("rank.dat", "wb");
    if (arq != NULL) {
       
        res=fwrite(nomes, sizeof(char), 90, arq);
        
        res=fwrite(pontos, sizeof(int), 3, arq);
        
        fclose(arq);
    } else {
        printf("\nProblemas na gravação.");
    }
}

// Função para imprimir o ranking
void imprimeRanking(char nomes[3][30], int pontos[3]) {
    int i;
    printf("\nRanking atual:");
    for(i=0; i<3; i++) {
        printf("\n\t[%d] - %s - Pontos: %d", i+1, nomes[i], pontos[i]);
    }
}

/* Funções Desenvolvidas */
int Vit = 0, Vida = 3, bonus = 0;
//Função para calcular pontuação de acordo com o tempo
int calculaPontos(double tempoPassado) {
    int pontuacao;
    if (tempoPassado <= 60) {
        pontuacao = 1000 + (bonus * 500);
    } 
    else if (tempoPassado <= 120) {
        pontuacao = 800 + (bonus * 500);
    } 
    else if (tempoPassado <= 180) {
        pontuacao = 600 + (bonus * 500);
    } 
    else {
        pontuacao = 400 + (bonus * 500);
    }
    return pontuacao;
}

// Função para não precisar dar enter
int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

void moveper(int mapa[10][10], char mover) {
    int xAtu, yAtu, xDes, yDes;

    // Encontrar as coordenadas atuais do personagem
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (mapa[i][j] == 1) {
                xAtu = i;
                yAtu = j;
                break;
            }
        }
    }

    // Definir as coordenadas desejadas com base na direção de movimento
    switch (mover) {
        case 's':
            xDes = xAtu + 1;
            yDes = yAtu;
            break;
        case 'w':
            xDes = xAtu - 1;
            yDes = yAtu;
            break;
        case 'a':
            xDes = xAtu;
            yDes = yAtu - 1;
            break;
        case 'd':
            xDes = xAtu;
            yDes = yAtu + 1;
            break;
        default:
            printf("\n  Direção inválida!\n");
            return;
    }

    // Verificar se saiu do mapa
    if (xDes >= 0 && xDes < 10 && yDes >= 0 && yDes < 10) {
        // Verificar se há colisão na posição desejada
        if (mapa[xDes][yDes] == 3) {
            mapa[xDes][yDes] = 1;
             mapa[xAtu][yAtu] = 0;
            printf(RED "\n  Você atingiu um monstro e perdeu uma vida!" RESET);
            Vida--; 
            printf("%i", Vida);
           return;
        }
        else if (mapa[xDes][yDes] == 2) {
            printf(GRN "\n  Parabéns, você acabou de zerar pocman!" RESET);
            Vit++;
            printf("%i", Vit);
            return;
        }
        else if (mapa[xDes][yDes] == 4) {
            mapa[xDes][yDes] = 1;
            mapa[xAtu][yAtu] = 0;
            printf(GRN "\n  Parabéns, você acabou de ganhar um bônus!" RESET);
            bonus++;
            printf("%i", bonus);
           return;
        }
        // Mover o personagem para a posição desejada
        mapa[xDes][yDes] = mapa[xAtu][yAtu];
        mapa[xAtu][yAtu] = 0;
    } 
    else {
        printf(RED "\n  GAME OVER, você acabou de sair do mapa :(" RESET);
        Vida=0;
        bonus=0;
    }
    return;
}

/* MAIN */
int main () {

    setlocale(LC_ALL, "Portuguese");
    int session;
    int n;
    int dif; 
    char nome[30];
    clock_t start, parar;
    double tempoPassado;
    int minutos, segundos, pontus;
    int mapa[10][10];
    char mover;
    int confirmacao;

    do {
        /* Tela Inicial*/
        // Abertura:  Deve conter, no mínimo, o nome do jogo e o nome da equipe desenvolvedora
        printf(RED "\n\n  8b,dPPYba,  ,adPPYYba,  ,adPPYba, 88,dPYba,,adPYba,  ,adPPYYba, 8b,dPPYba\n");
        printf(RED "  88P'    \"8a a8\"     \"\" a8\"     \"\" 88P'   \"88\"    \"8a \"\"     `Y8 88P'   `\"8a\n");
        printf(RED "  88       d8 8b      8b 8b         88      88      88 ,adPPPPP88 88       88\n");
        printf(RED "  88b,   ,a8\" \"8a,   ,aa \"8a,   ,aa 88      88      88 88,    ,88 88       88\n");
        printf(RED "  88`YbbdP\"'   `\"Ybbd8\"   `\"Ybbd8\"' 88      88      88 `\"8bbdP\"Y8 88       88\n");
        printf(RED "  88\n");
        printf(RED "  88\n" RESET);
        printf(YEL "\n  By Dayana Freitas, Cauã Azevedo e Felipe Ribeiro\n\n" RESET);
                            
        // Codinome - Entre 3 e 15 caracteres
        printf("\n  Bem vindo ao POCMAN, antes de embarcar nessa aventura, insira seu codinome: ");
        
        do {
            n = 0;
            setbuf(stdin, NULL);
            scanf("%[^\n]s", nome);

            if (strlen(nome) < 3 || strlen(nome) > 15) {
                n = 1;
                if (strlen(nome) < 3 ) {
                    printf("\n  Nome muito pequeno, insira um nome com 3 ou mais caracteres: ");
                }
                else {
                    printf("\n  Nome muito grande, insira um nome com 15 ou menos caracteres: ");
                }
            }
        } while (n == 1);

        printf("\n");

        clear();

        printf(RED "\n\n  8b,dPPYba,  ,adPPYYba,  ,adPPYba, 88,dPYba,,adPYba,  ,adPPYYba, 8b,dPPYba\n");
        printf(RED "  88P'    \"8a a8\"     \"\" a8\"     \"\" 88P'   \"88\"    \"8a \"\"     `Y8 88P'   `\"8a\n");
        printf(RED "  88       d8 8b      8b 8b         88      88      88 ,adPPPPP88 88       88\n");
        printf(RED "  88b,   ,a8\" \"8a,   ,aa \"8a,   ,aa 88      88      88 88,    ,88 88       88\n");
        printf(RED "  88`YbbdP\"'   `\"Ybbd8\"   `\"Ybbd8\"' 88      88      88 `\"8bbdP\"Y8 88       88\n");
        printf(RED "  88\n");
        printf(RED "  88\n" RESET);
        printf(YEL "\n  By Dayana Freitas, Cauã Azevedo e Felipe Ribeiro\n\n" RESET);

        printf("  Em fliperamas muito distantes, existia um ser chamado Pocman que estava cansado de ser apenas o primo distante e queria ganhar reconhecimento.\n\n");
        printf("  Para demonstrar seu valor, decidiu ir atrás da única coisa que seu primo nunca conseguiu alcançar verdadeiramente, o fim do jogo.\n\n");
        printf("  Sua missão é ajudar o POCMAN a alcançar o fim e mostrar de uma vez por todas que o verdadeiro\n  caminho não se abre para aqueles que comem comem, e sim para os que lutam.\n\n\n");
        
        printf("  Aqui vai algumas instruções para ajuda-lo nessa jornada:\n\n");
        printf("  - O objetivo do jogo é pegar o troféu voador\n");
        printf("  - Ao colidir com as moedas você ganha pontos extras\n");
        printf("  - Ao colidir com um fantasma você perde uma vida\n");
        printf("  - Se você sair do mapa, morre imediatamente\n\n");
        printf("  Para se mover no jogo use os seguintes comandos:\n\n");
        printf("  - W: Move para cima\n");
        printf("  - S: Move para baixo\n");
        printf("  - A: Move para a esquerda\n");
        printf("  - D: Move para a direita\n\n");

        printf("  Agora que você sabe o que deve fazer, já pode embarcar nessa jornada, mas tome cuidado \n  O caminho para a glória é cheio de recompensas e armadilhas para impedi-lo\n\n\n");
        printf("  Selecione o nivel de dificuldade:\n\n  1 - Fácil\n  2 - Moderado\n  3 - Difícil\n  ");
        scanf("%i", &dif);

        // Iniciar o cronômetro
        time(&start);
        
        // Impressão do mapa
        Vida=3;
        bonus=0;   
        Vit=0;

        geraMapa(mapa, dif);
        imprimeMapa(mapa);
        setbuf(stdin, NULL);

        do {
            setbuf(stdin, NULL);
            printf("\n  Para onde deseja se mover? ");
            mover=getch();
            // moveper(mapa,mover);
            atualizaMapa(mapa);
            moveper(mapa,mover);
            //clear();  
            imprimeMapa(mapa);
        } while (Vida>0 && Vit<1);

        // Parar o cronômetro
        time(&parar);

        // Calcular o tempo decorrido em segundos
        tempoPassado = difftime(parar, start);
        
        if (Vida==0) {
            pontus=0;
        }

        else {
            //Calcular pontuação
            pontus=calculaPontos(tempoPassado);
        }

        // Converter o tempo decorrido para minutos e segundos
        minutos = (int)tempoPassado / 60;
        segundos = (int)tempoPassado % 60;

        printf("  Tempo decorrido: %d minutos e %d segundos\n", minutos, segundos);
        printf("  Sua pontuação: %d\n", pontus);
        
        // Ranking
        char nomes[3][30];
        int pontos[3];
        
        leRanking(nomes, pontos);
        //imprimeRanking(nomes, pontos);
        
        if (pontus>pontos[0]) {
            printf("\n  Parabéns, você é o novo lider do ranking");
            strcpy(nomes[1], nomes[0]);
            strcpy(nomes[0], nome);
            pontos[1] = pontos [0];
            pontos[0] = pontus;
    
            atualizaRanking(nomes, pontos);
            
            leRanking(nomes, pontos);
            imprimeRanking(nomes, pontos);
        }

        else if (pontus>pontos[1]) {
            printf("\n  Parabéns, você é o segundo colocado do ranking");
            strcpy(nomes[2], nomes[1]);
            strcpy(nomes[1], nome);
            pontos[2] = pontos [1];
            pontos[1] = pontus;
    
            atualizaRanking(nomes, pontos);
            
            leRanking(nomes, pontos);
            imprimeRanking(nomes, pontos);
        }

        else if (pontus>pontos[2]) {
            printf("\n  Parabéns, você é o terceiro colocado do ranking");
            
            strcpy(nomes[2], nome);
            
            pontos[2] = pontus;
    
            atualizaRanking(nomes, pontos);
            
            leRanking(nomes, pontos);
            imprimeRanking(nomes, pontos);
        }

        else { 
            printf("\n\n  Sua pontação não foi o suficiente para entrar no ranking");
            imprimeRanking(nomes, pontos);
        }

        printf("\n\n  %s deseja iniciar uma nova partida? Digite 1 para jogar novamente ou qualquer outro número para sair do quiz: ", nome);
        scanf("%d", &session);

        if (session != 1) {
            printf("\n\n  %s tem certeza que deseja sair do jogo? Digite 1 para retornar ao jogo ou qualquer outro número para sair: ", nome);
            scanf("%d", &confirmacao);

            if (confirmacao != 1) {
                printf("\n\n  Espero que tenha gostado dessa aventura! Até uma próxima, bye\n\n");
            }

            else {
                session = 1; 
                clear();
            } 
        }

        else clear();        
    } while (session == 1);
 
    return 0;
}
