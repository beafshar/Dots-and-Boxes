#include"Client.h"

void signal_handler(int signal){
    write(1,"You missed your turn.\n",25);

}
void get_input(char* string, int coordination[3]){
    if (string[0] == '9')
    return;
    char* z_char = strtok(string," ");
    char* x_char = strtok(NULL, " ");
    char* y_char = strtok(NULL, " \n");
    coordination[0] = atoi(z_char);
    coordination[1] = atoi(x_char);
    coordination[2] = atoi(y_char);

}
void game(int turn){
    
    int** mapV;
    int** mapH;
    int** scores;
    mapV = malloc((BOARD_WIDTH+1)* sizeof(int*));
    mapH = malloc((BOARD_WIDTH)* sizeof(int*));
    scores = malloc((BOARD_WIDTH)* sizeof(int*));
    for(int i=0; i < BOARD_WIDTH + 1; i++){
        mapV[i] = malloc(BOARD_WIDTH* sizeof(int));
        mapH[i] = malloc((BOARD_WIDTH+1)* sizeof(int));
        scores[i] = malloc(BOARD_WIDTH* sizeof(int));
        if (i == BOARD_WIDTH){
            mapV[BOARD_WIDTH+1] = malloc(BOARD_WIDTH* sizeof(int));
        }
    }
    initMapAndScores(mapV, mapH, scores, BOARD_WIDTH);
    while(!doesSomeOneWin(scores,BOARD_WIDTH))
    {
        int  z, x, y;
        int coordination[3] = {0};
        write(1,"\n--------------------------------------------\n",47);
        showMap(mapV, mapH, scores,BOARD_WIDTH);
        printf("turn: %d\n", turn);
        printf("id: %d\n", id);


        if (turn == id){
            char input[1024];
            char send[1024];
            memset(input,0,sizeof(input));
            memset(send,0,sizeof(send));
            strcpy(input,"9");
            write(1,"\nPlease enter coordinates :   \n", 32);
            signal(SIGALRM,signal_handler);
            alarm(TIMEOUT);
            read(0,input,1024);
            alarm(0);
            strcpy(send,input);
            get_input(input,coordination);
            
            write(1,send,1024);

            if (sendto(game_socket,send, 1024, 0 ,(struct sockaddr *)&gameAddr,  sizeof(gameAddr)) < 0){
                write(1,"\nsending coordination failed! \n",33);
                exit(EXIT_FAILURE);
            }
            memset(send,0,sizeof(send));
            recv(game_socket,send,1024, 0);
            write(1,"\nSuccessfuly sent! waiting for other player to move\n", 53);
            if(send[0] == '9'){
                turn = calcTurn(turn,BOARD_WIDTH);
                continue;
            }
                
        }
        else{
            char received[1024];
            memset(received,0,sizeof(received));
            write(1,"\nNot your turn. waiting for others to play...\n",47);
            if (recv(game_socket,received,1024, 0) < 0){
                write(1,"\nreceiving coordination failed! \n",35);
                exit(EXIT_FAILURE);
            }
            if(received[0] == '9'){
                turn = calcTurn(turn,BOARD_WIDTH);
                continue;
            }
            write(1,"\nnew line received! \n", 22);
            get_input(received,coordination);
        }
        turn = addNewLine(coordination[0], coordination[1], coordination[2], mapV, mapH, scores, turn,BOARD_WIDTH);

    }
    showMap(mapV, mapH, scores, BOARD_WIDTH);
    printScores(scores, BOARD_WIDTH,BOARD_WIDTH);
}


int ConnecttoPort(int broadcastPort){
    int sock;
    int Permission = 1;
    int opt = 1;

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        write(1,"socket() failed\n",17);
        exit(EXIT_FAILURE);
    }

    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &Permission, sizeof(Permission));
    setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (void *) &opt, sizeof(opt));

    gameAddr.sin_family = AF_INET; 
    gameAddr.sin_addr.s_addr = inet_addr("255.255.255.255");
    gameAddr.sin_port = htons(broadcastPort);

   
    if (bind(sock, (struct sockaddr *) &gameAddr, sizeof(gameAddr)) < 0){
        write(1,"\nbind to new failed\n",21);
        exit(EXIT_FAILURE);
    }
    write(1,"\nsuccesfully bind to new port\n",31);
    return sock;
}
int FindServer(char* msg){
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
        write(1,"\n Socket creation error \n", 26); 
        exit(EXIT_FAILURE); 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       

   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){ 
        write(1,"\nConnection Failed \n",21); 
        exit(EXIT_FAILURE); 
    }
    write(1,"succesfully bind to server\n",28);
    send(sock , msg , strlen(msg) , 0 ); 

    char string[1024]= {0};
    recv(sock, string, 1024,0);
    write(1,"port recieved\n",15);


    char* port_string = strtok(string,"#");
    write(1,"\n",1);
    write(1,port_string,strlen(port_string));
    char* id_string = strtok(NULL,"#");
    write(1,"\n",1);
    write(1,id_string,strlen(id_string));
    char* turn_string = strtok(NULL,"#");
    int port = atoi(port_string);
    id = atoi(id_string);
    turn = atoi(turn_string);
    close(sock);
    return port;
}

int main(int argc, char const *argv[]) 
{   
    char msg[128];
    int sock;
    write(1,"choose players numbers: 2, 3, 4.\n",34);
    read(0,msg, sizeof(msg));
    BOARD_WIDTH = atoi(msg);
    siginterrupt(SIGALRM, 1);
    int port = FindServer(msg);
    game_socket = ConnecttoPort(port);
    game(turn);
    
    return 0; 
} 