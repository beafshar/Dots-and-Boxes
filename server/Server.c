#include "Server.h"


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

int sendPort(int* group, int broadcastPort, int size){
    char buffer[128];
    char* port_string = itoa(broadcastPort,buffer);
    write(1,port_string,strlen(port_string));
    for (int i = 0; i < size;i++){
        char temp[1024] = {0};
        strcpy(temp,port_string);
        strcat(temp,"#");
        char buffer[128] = {0};
        char* id = itoa(i+1,buffer);
        strcat(temp,id);
        strcat(temp,"#");
        strcat(temp,"1");
        strcat(temp,"#");
        
        if (send(group[i] ,temp , 1024 , 0) == 1024){
            write(1,"\nport sucesfully sent!\n",24);
        }
        else
        {
            write(1,"port sending faild\n",23);
        }
    }
}
int initServer(){
    int server_socket;
    int opt = 0;

    if((server_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0){   
        write(1,"socket failed\n",15);   
        exit(EXIT_FAILURE);   
    }   
     
    if(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,sizeof(opt)) < 0 ){   
        write(1,"setsockopt\n",12);   
        exit(EXIT_FAILURE);   
    }   
 
    address.sin_family = AF_INET;   
    address.sin_addr.s_addr = INADDR_ANY;   
    address.sin_port = htons( PORT );   
         
    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address))<0){   
        write(1,"bind failed\n",13);   
        exit(EXIT_FAILURE);   
    }

    printf("Listener on port %d \n", PORT);   

    if (listen(server_socket, 3) < 0){   
        write(1,"listen failed\n",15);   
        exit(EXIT_FAILURE);   
    }

    return server_socket;
}

int acceptClient(int server_socket){
    int new_socket;
    if ((new_socket = accept(server_socket,(struct sockaddr *)&address, (socklen_t*)&addrlen))<0){   
                write(1,"accept failed\n", 15);   
                exit(EXIT_FAILURE);   
            } 
    return new_socket;
}
void addtoGroup(int* group,int size, int member){
    for(int i = 0; i < size; i++){
        if(group[i] == 0){
            group[i] = member;
            break;
        }
    }
    int port = rand()%7000 + 1000;
    if(group[size-1] != 0){
        sendPort(group,port,size);
        for(int i = 0; i < size; i++){
            group[i] = 0;
        }
    }
    return;
}
void checkClientMsg(char* buffer, int socket, int* group_2, int* group_3, int* group_4){

    if (buffer[0] == '2'){
            addtoGroup(group_2,2,socket);
    }
    else if (buffer[0] == '3'){
        addtoGroup(group_3,3,socket);
    }
    else if (buffer[0] == '4'){
        addtoGroup(group_4,4,socket);

        }
}

void handleConnection(int client_socket, char* buffer){
    int valread;
    char* msg = "you sucessfully added to port! waiting for others to join...\n";
    valread = read(client_socket , buffer, 1024); 
    write(1,"request:",9);
    write(1,buffer, strlen(buffer));

}
int main(int argc, char const *argv[]) { 
    int server_socket,client_socket;
    int new_socket; 
    char* msg = '\0';
    int group_2[2] = {0};
    int group_3[3] = {0};
    int group_4[4] = {0};
    char buffer[1024] = {0};

    server_socket = initServer();

    fd_set current_sockets, ready_sockets; 
    FD_ZERO(&current_sockets);
    FD_SET(server_socket,&current_sockets);

    while (TRUE){
        ready_sockets = current_sockets;
        if (select(FD_SETSIZE,&ready_sockets, NULL, NULL, NULL) < 0){
            write(1,"select error\n", 14);   
            exit(EXIT_FAILURE); 
        }

        for (int i = 0; i < FD_SETSIZE; i++){
            if (FD_ISSET(i, &ready_sockets)){
                if (i == server_socket){
                    client_socket = acceptClient(server_socket);
                    FD_SET(client_socket, &current_sockets);
                }
                else{
                    handleConnection(i,buffer);
                    checkClientMsg(buffer,i, group_2, group_3, group_4);
                    FD_CLR(i, &current_sockets);
                }

            }
        }

    }
    return 0; 
} 