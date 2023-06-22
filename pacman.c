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

// cores
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

// Funções Básicas Disponibilizadas
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

// Funções Desenvolvidas

// MAIN
int main () {
    setlocale(LC_ALL, "Portuguese");
    int mapa[10][10], at;

    // Abertura



    // Codinome - Entre 3 e 15 acaracteres
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

    // Função para imprimir mapa
    imprimeMapa(mapa);

    // Atualização do mapa
    do {
        printf("\nAtualizar mapa? Resposta (1-Sim, 0-Não) 👻: 🍒 😶 🍅 🍎 🍇  🫠");
        scanf("%d", &at);

        if (at) { atualizaMapa(mapa); imprimeMapa(mapa); }

    } while (at);
    return 0;
}