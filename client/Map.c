#include "Map.h"

void showMap(int** mapV, int** mapH, int** score, int BOARD_WIDTH)
{   
    
    printf("\n");
    int i, j;
    for(int i = 0 ; i < BOARD_WIDTH + 1 ; i++)
    {    
        showVerticalLines(mapV, i, BOARD_WIDTH);
        if(i != BOARD_WIDTH)
            showHorizonalLines(mapH, score, i, BOARD_WIDTH);
    }
}
void showVerticalLines(int** mapV, int lineNum, int BOARD_WIDTH)
{
    int i;
    for(i = 0 ; i < BOARD_WIDTH ; i++)
    {
        if(mapV[lineNum][i] == 1)
        {
            if(i == 0)
                printf("*--*");
            else 
                printf("--*");
        }
        else
        {
            if(i == 0)
                printf("*  *");
            else 
                printf("  *");
        }
    }
    printf("\n");
}
void showHorizonalLines(int** mapH, int** score, int lineNum,int BOARD_WIDTH)
{
    int i;
    for(i = 0 ; i < BOARD_WIDTH + 1 ; i++)
    {
        if(mapH[lineNum][i] == 1)
            printf("|");
        else 
            printf(" ");
        if(i != BOARD_WIDTH )
        {
            if(score[lineNum][i] != 0)
                printf("%d ", score[lineNum][i]);

            else    
                printf("  ");
        }   
    }
    printf("\n");
}   

int calcTurn(int turn, int BOARD_WIDTH){
    int newTurn;
    if (BOARD_WIDTH == 2)
        newTurn = (turn % 2)+1;
    else if(BOARD_WIDTH == 3)
        newTurn = (turn % 3)+1;
    else if(BOARD_WIDTH == 4)
        newTurn = (turn % 4)+1;

    return newTurn;
}
int addNewLine(int z, int x, int y, int** mapV,
             int** mapH, int** score, int turn, int BOARD_WIDTH)
{
    int s;

    int newTurn =calcTurn(turn,BOARD_WIDTH);
    if(z == 0)
    {   
        mapV[x - 1][y - 1] = 1;
        if(x != 1)
            if(mapH[x - 2][y - 1] && mapH[x - 2][y] && mapV[x - 2][y - 1]) // Check upper square
            {
                score[x-2][y-1] = turn;
                newTurn = turn;
            } 
        if(x != BOARD_WIDTH + 1)
            if(mapH[x - 1][y - 1] && mapH[x - 1][y] && mapV[x][y - 1]) // Check lower
            {
                score[x-1][y-1] = turn;
                newTurn = turn;
            }    
    }
    if( z == 1)
    {
       
        mapH[x - 1][y - 1] = 1;
        if(y != 1)
            if(mapV[x - 1][y - 2] && mapV[x][y - 2] && mapH[x - 1][y - 2]) // left square
            {
                score[x-1][y-2] = turn;
                newTurn = turn;
            } 
        if( y != BOARD_WIDTH + 2)
            if(mapV[x - 1][y - 1] && mapV[x][y - 2] && mapH[x-1 ][y]) // right square
            {
                score[x-1][y-1] = turn;
                newTurn = turn;
            } 
    }
    return newTurn;
}

bool doesSomeOneWin(int** scores, int BOARD_WIDTH)
{
    int i, j;
    for( i = 0 ; i < BOARD_WIDTH ; i++)
    {
        for( j = 0 ; j < BOARD_WIDTH ; j++)
        {
            if(scores[i][j] == 0)
                return false;
        }
    }
    return true;
}
void printScores(int** scores, int BOARD_WIDTH, int size)
{
    int i, j;

    int score[4] = {0};
    for(i = 0 ; i < BOARD_WIDTH ; i++)
    {
        for(j = 0 ; j < BOARD_WIDTH ; j++)
        {
            if(scores[i][j] == 1)
                score[0]++;
            else if(scores[i][j] == 2)
                score[1]++;
            else if(scores[i][j] == 3)  
                score[2]++;
            else if(scores[i][j] == 4)
                score[3]++; 
        }
    }
    int max = 0;
    int winner = 0;
    for(int i = 0; i < size; i++){
        printf("Player %d : %d\n", i+1 ,score[i]);
        if (score[i] > max){
            max = score[i];
            winner = i;
        }


    }

    printf("Player %d won the game!\n", winner+1);
}