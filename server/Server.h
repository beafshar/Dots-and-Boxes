#ifndef SERVER_H
#define SERVER_H

#include <unistd.h> 
#include <stdio.h> 
#include <sys/types.h>  
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <errno.h> 
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8080 
#define TRUE 1
#define FALSE 0
#define EXIT_FAILURE 1
#define ADDR "239.255.255.250"
#define CLIENT_ADDR "127.0.0.1"

int MaxNumOfClients = 10;
struct sockaddr_in address; 
int addrlen = sizeof(address);

char* itoa(int input, char* str);
char* create_port_string(int port,int base);
int initServer();
int acceptClient(int server_socket);
void checkClientMsg(char* buffer, int socket,  int* group_2, int* group_3, int* group_4);
void handleConnection(int client_socket, char* buffer);
int sendPort(int* group, int broadcastPort, int size);
void addtoGroup(int* group,int size, int member);
#endif