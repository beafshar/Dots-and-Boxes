#include "Map.h"
void initMapAndScores(int** mapV, int** mapH,int** score, int BOARD_WIDTH)
{
    int i, j;
    for( i = 0 ; i < BOARD_WIDTH + 1 ; i++)
    {

        for( j = 0 ; j < BOARD_WIDTH + 1; j++)
        {

            if(j < BOARD_WIDTH){
                        mapV[i][j] = 0;
            }
                
            if(i < BOARD_WIDTH){
                mapH[i][j] = 0;
            }
                
            if(j < BOARD_WIDTH && j < BOARD_WIDTH){
                score[i][j] = 0;
            }
                
        }
    }
}
char* itoa(int input, char* str) {
	int temp2 = input;
    int num = 0;
    while (temp2)
    {
      temp2 = temp2 / 10;
      num++;
    }
    int temp3 = input;
    for(int i = 0; i < num; i++)
    {
      str[num - i - 1] = '0' + (temp3 % 10);
      temp3 = temp3 / 10;
    }
	str[num] = '\0';
	return str;
}