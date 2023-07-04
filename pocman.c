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


// Função para atualizar o mapa
void atualizaMapa(int mapa[10][10]) {
    int i, j, upd, atualizado[10][10];
    for (i=0; i<10; i++) for (j=0; j<10; j++) atualizado[i][j]=3;

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
    printf("\n  ---------------------------------------------------------------  ");
    for (i=0; i<10; i++) {
        printf("\n  ---------------------------------------------------------------  \n  ");
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
    printf("\n  ---------------------------------------------------------------  ");
    printf("\n  ---------------------------------------------------------------  \n  ");
}

// Funcionando
// void imprimeMapa(int mapa[10][10]) {
//     int i, j;
//     for (i=0; i<10; i++) {
//         for (j=0; j<10; j++) {
//             if (mapa[i][j]==0)
//                 printf("[ ] ", mapa[i][j]);
//             else
//                 printf("[%d] ", mapa[i][j]);
//         }
//         printf("\n");
//     }
// }

// Função para ler o ranking
void leRanking(char nomes[3][30], int pontos[3]) {
    FILE *arq = NULL;
    int res;
    arq = fopen("rank.dat", "rb");
    if (arq != NULL) {
        printf("\nLendo os dados ...");
        res=fread(nomes, sizeof(char), 90, arq);
        if(res == 90) {
            printf("\nNomes lidos corretamente");
        }
        res=fread(pontos, sizeof(int), 3, arq);
        if(res == 3) {
            printf("\nPontos lidos corretamente");
        }
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
        printf("\nComeçando a gravação ...");
        res=fwrite(nomes, sizeof(char), 90, arq);
        if(res == 90) {
            printf("\nNomes gravados corretamente");
        }
        res=fwrite(pontos, sizeof(int), 3, arq);
        if(res == 3) {
            printf("\nPontos gravados corretamente");
        }
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

//Função para calcular pontuação de acordo com o tempo
int calculaPontos(double tempoPassado) {
    int pontuação;
    if (tempoPassado <= 60) {
        pontuação = 100;
    } else if (tempoPassado <= 120) {
        pontuação = 80;
    } else if (tempoPassado <= 180) {
        pontuação = 60;
    } else {
        pontuação = 40;
    }
    return pontuação;
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

// Função cronômetro
void cronometro (void) {
    int segundo = 0;
    int minuto = 0;
    int hora = 0;
    
    for (int i = 0; i < 5; --i) {
        printf("\n\n\t\t%dh : %dmin : %dseg", hora, minuto, segundo);
        sleep(1000);
        system("CLS"); 
        segundo++;
        
        if (segundo == 60) {
            segundo = 0;  
            minuto++;
        }   
        
        if (minuto == 60) {
            minuto = 0;  
            hora++;
        }  
    }
}

//Função para mover personagem
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
            printf(RED "\n  Você atingiu um monstro e perdeu uma vida!" RESET);

        }
        if(mapa[xDes][yDes] ==4 ) {
            printf(GRN "\n  Parabéns, você acabou de ganhar um bônus!" RESET);
        }
        // Mover o personagem para a posição desejada
        mapa[xDes][yDes] = mapa[xAtu][yAtu];
        mapa[xAtu][yAtu] = 0;
    }

    else {
        printf(RED "\n  GAME OVER, você acabou de sair do mapa :(" RESET);
    }
}

/* MAIN */
int main () {
    setlocale(LC_ALL, "Portuguese");
    int session;

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
        int n;
        char nome[30];
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

        /* Tela de Instruções (J1)

            Cada grupo deve formular um conjunto de instruções de como jogar. Apresente-as na tela de
            maneira lúdica (considerando a história/narrativa) e clara.
            Logo após as instruções, o sistema deve dar duas opções:
            1. Nova partida
            2. Sair do jogo

        */
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
        printf("  Sua missão é ajudar o POCMAN a alcançar o fim e mostrar de uma vez por todas que o verdadeiro\n caminho não se abre para aqueles que comem comem, e sim para os que lutam.\n\n\n");
        
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
        printf("  Selecione o nivel de dificuldade:\n  1 - Fácil\n  2 - Moderado\n  3 - Difícil\n");
          
        int dif;    
        scanf("%i", &dif);

        /* Nova partida (J2)

            Agora a partida do seu jogo iniciará. A primeira ação é mostrar na tela o mapa, que deve ser
            uma matriz 10x10.
            O mapa inicial deve conter:
                1. Posição atual do avatar;
                2. Posição do destino (ou objetivo);
                3. Indicação de áreas com obstáculos a serem evitados;
                4. Indicação de áreas 0com bônus.
            Use a função geraMapa(int mapa[10][10], int nivel), disponível no arquivo
            mapa.c no Moodle. Esta função gera todos os elementos que devem estar no mapa inicial.
            Cada vez que a função é chamada ela gera um mapa diferente. O segundo parâmetro (int nivel)
            é usado para definir o nível de dificuldade da partida. Os valores possíveis são 1, 2 ou 3, sendo
            fácil, intermediário e difícil, respectivamente. Você pode escolher se vai perguntar à jogadora
            qual o nível de dificuldade ela deseja ou se usará sempre um nível fixo em seu jogo. A função
            preenche a matriz mapa da seguinte maneira:
            • Valor 0: posição por onde o avatar pode passar;
            • Valor 1: posição atual do avatar;
            • Valor 2: posição do destino (objetivo que deve ser alcançado para concluir a missão);
            • Valor 3: posição que contem um obstáculo (evitar);
            • Valor 4: posição de um bônus (coletar).
            Sejam criativos na apresentação do mapa de modo que fique simples de entendê-lo.
            Logo abaixo do mapa você deve exibir o menu do jogo (J3).

        */

        //cronometro();

        // Impressão do mapa
        int mapa[10][10];
        char mover;

        geraMapa(mapa, dif);
        imprimeMapa(mapa);
        setbuf(stdin, NULL);
        do {
         
            setbuf(stdin, NULL);
            printf("\n  Para onde deseja se mover? ");
            mover=getch();
            moveper(mapa,mover);
            atualizaMapa(mapa);
            clear();  
            imprimeMapa(mapa);}
            while (mover != 'k');

    /* Menu do Jogo (J3)

        O menu do jogo deve trazer, pelo menos, as seguintes opções de operação:
        1. Movimentar o avatar
        2. Nova partida
        3. Sair do jogo

    */

    /* Movimentar o avatar (J4)

        Quando esta opção for selecionada o jogo deve orientar a jogadora a usar as setas direcionais ou
        WSAD ([W] - cima, [S] - baixo, [A] - esquerda e [D] – direita) para movimentar o avatar.
        A cada tecla direcional pressionada você deve alterar a posição do avatar no mapa,
        considerando:
        1. [REQ_BONUS];
        2. [REQ_OBSTACULO];
        3. [REQ_VITORIA];
        4. [REQ_LIMITE];
        5. Atualizar a apresentar a pontuação atual da partida, conforme [REQ_PONTUACAO].
        Se qualquer outra tecla for pressionada, ela deve ser ignorada pelo jogo. Mas não precisa
        mostrar nenhuma mensagem de erro.
        Depois de movimentar o avatar e verificar o que ocorreu, você deve atualizar o mapa. Para isso:
        1. Atualize a posição do avatar na matriz mapa;
        2. Imprima novamente o mapa na tela;
        3. Aguarde 1 segundo (ver função sleep da biblioteca time.h);
        4. Chame a função atualizaMapa(int mapa[10][10]), disponível no arquivo
        mapa.c. Ela realiza a atualização do mapa, trazendo as novas posições dos obstáculos,
        bônus e do destino (objetivo);
        5. Reaizar [REQ_ATUALIZACAO];
        6. Imprima novamente o mapa atualizado na tela.
        Ao concluir a partida:
        1. Se alcançou o destino (objetivo), então apresentar:
        a. Uma mensagem de finalização da partida (não se esqueça de usar o codinome
        da jogadora);
        b. A quantidade de pontos obtidos;
        c. Voltar para (J1).
        2. Se a missão fracassou, então apresentar:
        a. Informar o motivo: obstáculo [REQ_OBSTACULO] ou saiu do mapa
        [REQ_LIMITE];
        b. Voltar para (J1).
        3. Em qualquer dos casos, se a pontuação for maior que 0 (zero) deve verificar se a
        pontuação vai para o ranking [REQ_RANKING]:
        a. Abrir o arquivo binário rank.dat e obter os dados das três maiores
        pontuações contidas lá. Esse arquivo deve armazenar as três maiores
        pontuações e os respectivos codinomes de quem as obteve;
        b. Se a pontuação da partida atual for maior que alguma das pontuações
        anteriores, então atualizar devidamente o ranking;
        c. Imprimir na tela o ranking atualizado.

    */

        // Ranking
        // char nomes[3][30];
        // int pontos[3];
        
        // leRanking(nomes, pontos);
        // imprimeRanking(nomes, pontos);
        
        // if (pontos[0] == 0) {
        //     printf("\nSe nada foi lido, podemos inserir algo e mandar atualizar.");
        //     strcpy(nomes[0], "Olaf");
        //     pontos[0] = 1000;
        //     strcpy(nomes[1], "Olafinho");
        //     pontos[1] = 500;
        //     atualizaRanking(nomes, pontos);
        //     printf("\n\nAgora que gravamos dados, vamos ler e imprimir novamente.\n");
        //     leRanking(nomes, pontos);
        //     imprimeRanking(nomes, pontos);
        // }

        /* Nova partida (J5)

            Quando esta opção for selecionada, você deve pedir a confirmação da jogadora e então deve
            voltar para o (J2).

        */

        printf("\n\n  %s deseja iniciar uma nova partida? Digite 1 para jogar novamente ou qualquer outro número para sair do quiz: ", nome);
		scanf("%d", &session);
		if (session != 1) {

            /* Sair do jogo (J6)

            Ao selecionar esta opção, o jogo deve pedir uma confirmação da jogadora antes de encerrar a
            execução do programa. Se confirmar, exibir uma mensagem de despedida e encerra o jogo.

            */

            int confirmacao;
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