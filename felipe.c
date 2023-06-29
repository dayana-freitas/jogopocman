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
void moveper (int mapa[10][10], char mover){
    int  xAtu/*linha atual*/, yAtu/*coluna atual*/, xDes/*linha desejada*/ , yDes/*coluna desejada*/;
    /*função para achar o personagem*/
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (mapa[i][j] == 1) {
                xAtu = i; 
                yAtu = j; 
                break;
            }
        }
    }
 
  
  switch (mover)
  {

    case 's':
	    xDes = xAtu++;
	    yDes = yAtu;
	    mapa[xDes][yDes]=0;
	    mapa[xAtu][yAtu]=1;
	  break;
	  
case 'w':
        xDes = xAtu--;
	    yDes = yAtu;
	    mapa[xDes][yDes]=0;
	    mapa[xAtu][yAtu]=1;
	break;
	
      
case 'a':
        xDes = xAtu;
	    yDes = yAtu--;
	    mapa[xDes][yDes]=0;
	    mapa[xAtu][yAtu]=1;
	break;
	
      
case 'd':
        xDes = xAtu;
	    yDes = yAtu++;
	    mapa[xDes][yDes]=0;
	    mapa[xAtu][yAtu]=1;
	break;
	
      
       default:
            printf("Direção inválida!\n");
            return;}
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
    char mover;
    // TODA VEZ QUE VOCE DESEJAR GERAR UM NOVO MAPA, BASTA CHAMAR A FUNCAO geraMapa, conforme o exemplo a seguir
    // O primeiro par�metro � a sua matriz 10x10, o segundo � o n�vel de dificuldade do jogo: 1-F�cil, 2-Intermedi�rio, 3-Dif�cil
    geraMapa(mapa, 3); //AQUI ESTOU USANDO O N�VEL DE DIFICULDADE 3 - DIF�CIL
    imprimeMapa(mapa);
   
    

    do{
        printf("escolha uma direção para ir: ");
        scanf("%c",&mover);
        setbuf(stdin,NULL);
         
        // TODA VEZ QUE VOCE DESEJAR ATUALIZAR UM MAPA, BASTA CHAMAR A FUNCAO atualizaMapa, conforme o exemplo a seguir
         
             
      moveper(mapa,mover);
    atualizaMapa(mapa);
    system("clear");
             
         imprimeMapa(mapa);   
         
    
    } while (mover);
    return 0;}






