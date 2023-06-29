//SEU PROGRAMA DEVE INCLUIR ESSAS BIBLIOTECAS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// INCLUA EM SEU CODIGO AS FUNCOES randomInteger, geraMapa E atualizaMapa
// ATENCAO: NAO ALTERE NENHUMA DESSAS TRES FUNCOES

int randomInteger (int low, int high) {
    int k;
    double d;

    d = (double) rand () / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);

    return low + k;
}

void geraMapa(int mapa[10][10], int nivel) {
    int i, j, qtdO, qtdA, lin, col, infO=5, supO=15;

    switch (nivel) {
        case 2: infO=5; supO=25; break;
        case 3: infO=15; supO=35; break;
    }

    srand((unsigned int)time(NULL));

    for (i=0; i<10; i++)
        for (j=0; j<10; j++)
            mapa[i][j] = 0;

    mapa[randomInteger(0,9)][0]= 1;
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

//A FUN��O IMRIMEMAPA � SOMENTE PARA CONFER�NCIA DO FUNCIONAMENTO DO C�DIGO
//VOC�S PRECISAM FAZER UMA APRESENTA��O BEM MAIS INTERESSANTE DO QUE ESSA
void imprimeMapa(int mapa[10][10]) {
    int i, j;
    for (i=0; i<10; i++) {
        for (j=0; j<10; j++) {
            if (mapa[i][j]==0)
                printf("[ ] ", mapa[i][j]);
            else
                printf("[%d] ", mapa[i][j]);
        }
        printf("\n");
    }
}

int main () {
    setlocale(LC_ALL, "Portuguese");
    int mapa[10][10], at;

    // TODA VEZ QUE VOCE DESEJAR GERAR UM NOVO MAPA, BASTA CHAMAR A FUNCAO geraMapa, conforme o exemplo a seguir
    // O primeiro par�metro � a sua matriz 10x10, o segundo � o n�vel de dificuldade do jogo: 1-F�cil, 2-Intermedi�rio, 3-Dif�cil
    geraMapa(mapa, 3); //AQUI ESTOU USANDO O N�VEL DE DIFICULDADE 3 - DIF�CIL
    imprimeMapa(mapa);

    do {
        printf("\nAtualizar mapa? Resposta (1-Sim, 0-N�o): ");
        scanf("%d", &at);

        // TODA VEZ QUE VOCE DESEJAR ATUALIZAR UM MAPA, BASTA CHAMAR A FUNCAO atualizaMapa, conforme o exemplo a seguir
        if (at) { atualizaMapa(mapa); imprimeMapa(mapa); }

    } while (at);
    return 0;
}


/*POSS�VEIS FUN��ES
1 - MOVIMENTAR AVATAR
2 - ONDE EST� O AVATAR?
3 - VERIFICAR COLIS�O DO AVATAR
4 - VERIFICAR COLIS�O DA ATUALIZA��O
5 - ATUALIZAR A TELA
6 - CALCULAR A PONTUACAO
7 - VERIFICAR VIT�RIA
8 - VERIFICAR SE SAIU DO MAPA
*/








#include <stdio.h>

#include <stdlib.h>

#include <time.h>
#include <locale.h>
#include <string.h>

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

// void sleep() {
//     #ifdef __linux__
//         system("sleep");
//     #elif _WIN32
//         system("usleep");
//     #else
//     #endif
// }


// cores
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
    int i, j, qtdO, qtdA, lin, col, infO=5, supO=15;

    switch (nivel) {
    case 2:
        infO=5;
        supO=25;
        break;
    case 3:
        infO=15;
        supO=35;
        break;
    }

    srand((unsigned int)time(NULL));

    for (i=0; i<10; i++)
        for (j=0; j<10; j++)
            mapa[i][j] = 0;

    mapa[randomInteger(0,9)][0]= 1;
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
    for (i=0; i<10; i++) {
        for (j=0; j<10; j++) {
            if (mapa[i][j]==0)
                printf("[%d] ", mapa[i][j]); // verificar
            else
                printf("[%d] ", mapa[i][j]);
        }
        printf("\n");
    }
}

/* Funções Desenvolvidas */

// Função cronometro
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
        printf("Direção inválida!\n");
        return;
    }

    // Verificar se saiu do mapa
    if (xDes >= 0 && xDes < 10 && yDes >= 0 && yDes < 10) {
        // Verificar se há colisão na posição desejada
        if (mapa[xDes][yDes] == 3) {
            printf("um monstro te atacou e você perdeu uma vida");

        }
        if(mapa[xDes][yDes] ==4 ) {
            printf("você ganho um bônus");
        }
        // Mover o personagem para a posição desejada
        mapa[xDes][yDes] = mapa[xAtu][yAtu];
        mapa[xAtu][yAtu] = 0;
    } else {
        printf("parace que você saiu do mapa :(");
    }
}

/* MAIN */
int main () {
    setlocale(LC_ALL, "Portuguese");

    /* Tela Inicial*/

    // Abertura:  Deve conter, no mínimo, o nome do jogo e o nome da equipe desenvolvedora

    // Codinome - Entre 3 e 15 caracteres

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    int n;
    char nome[30];
    printf("\n  Antes de começar, insira seu codinome: ");
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
    //cronometro();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    /* Tela de Instruções (J1)

        Cada grupo deve formular um conjunto de instruções de como jogar. Apresente-as na tela de
        maneira lúdica (considerando a história/narrativa) e clara.
        Logo após as instruções, o sistema deve dar duas opções:
        1. Nova partida
        2. Sair do jogo

    */

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

    // Impressão do mapa
    int mapa[10][10];
    char mover;

    geraMapa(mapa, 3);
    imprimeMapa(mapa);

    do {
        printf("escolha uma direção para ir: ");
        scanf("%c",&mover);
        setbuf(stdin, NULL);
        moveper(mapa,mover);
        atualizaMapa(mapa);
        //system("clear");
        imprimeMapa(mapa);
    } while (mover);

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

    /* Nova partida (J5)

        Quando esta opção for selecionada, você deve pedir a confirmação da jogadora e então deve
        voltar para o (J2).

    */

    /* Sair do jogo (J6)

    Ao selecionar esta opção, o jogo deve pedir uma confirmação da jogadora antes de encerrar a
    execução do programa. Se confirmar, exibir uma mensagem de despedida e encerra o jogo.

    */

    // Função para imprimir mapa
    /////////////////////////////////////////////////////////////////////////////////////
    // int mapa[10][10], at;
    // geraMapa(mapa, 3);
    // imprimeMapa(mapa);

    // // Atualização do mapa
    // do {
    //     printf("\nAtualizar mapa? Resposta (1-Sim, 0-Não) 👻: 🍒 😶 🍅 🍎 🍇  🫠");
    //     scanf("%d", &at);

    //     if (at) { atualizaMapa(mapa); imprimeMapa(mapa); }

    // } while (at);
    return 0;
}

