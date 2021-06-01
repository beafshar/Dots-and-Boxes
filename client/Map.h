#ifndef MAP_H
#define MAP_H
#include<stdio.h>
#include <stdbool.h>
#define TRUE 1
#define False 0

//tools
char* itoa(int input, char* str);
void initMapAndScores(int** mapV, int** mapH,int** score, int BOARD_WIDTH);

//map
void showMap(int** mapV, int** mapH, int** score, int BOARD_WIDTH);
void showVerticalLines(int** mapV, int numLine, int BOARD_WIDTH);
void showHorizonalLines(int** mapH, int** score, int lineNum, int BOARD_WIDTH);
int calcTurn(int turn, int BOARD_WIDTH);
int addNewLine(int z, int x, int y, int** mapV,int** mapH, int** score, int turn, int BOARD_WIDTH);
void printScores(int** score,int BOARD_WIDTH, int size);
bool doesSomeOneWin(int** scores,int BOARD_WIDTH);
#endif