#ifndef CLIENT_H
#define CLIENT_H



#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/time.h>
#include<signal.h>

#define PORT 8080
#define TRUE 1
#define FALSE 0
#define EXIT_FAILURE 1
#define ADDR "255.255.255.250"
#define CLIENT_ADDR "127.0.0.1"
#define TIMEOUT 30

int BOARD_WIDTH;
int game_socket;
struct sockaddr_in gameAddr;
int id;
int turn;
void get_input(char* string, int coordination[3]);
void game(int turn);
int Broadcast(int broadcastPort);
int ConnecttoPort(int broadcastPort);
int FindServer();


#endif