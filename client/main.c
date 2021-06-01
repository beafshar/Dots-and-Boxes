
#include "Map.h"
#include <stdio.h>
#include <stdbool.h>


int main()
{   
    int mapV[BOARD_WIDTH  + 1][BOARD_WIDTH];
    int mapH[BOARD_WIDTH][BOARD_WIDTH +1];
    int scores[BOARD_WIDTH][BOARD_WIDTH];
    bool turn = PLAYER1;
    initMapAndScores(mapV, mapH, scores);
    while(!doesSomeOneWin(scores))
    {
        showMap(mapV, mapH, scores);
        printf("turn : %s. Please enter coordinates :   \n", turn ? "Player A" : "Player B");
        int z, x, y;
        scanf("%d %d %d",&z, &x, &y);
        turn = addNewLine(z, x, y, mapV, mapH, scores, turn);
    }
    showMap(mapV, mapH, scores);
    printScores(scores);
    return 0;
}




