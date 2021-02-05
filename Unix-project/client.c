#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "mainAES.h"
#include "md5.h"

void * doRecieving(void * sockID){

  int clientSocket = *((int *) sockID);

  while(1){
    char input[1024]; int read = recv(clientSocket,input,1024,0); input[read]='\0';

    if(strcmp(input,"LIST")==0){
     
    printf("Listing All Clients \n");
    char dat[1024];
     read = recv(clientSocket,dat,1024,0);
    dat[read] = '\0';
    printf("%s\n",dat);

    }else if(strcmp(input,"SEND")==0){

    uint8_t data[1024]; char size[1024]; uint8_t hash[1024];

    //read hash value
     read = recv(clientSocket,hash,1024,0);

    //receive sizeof cipher
     read = recv(clientSocket,size,1024,0);
     size[read]='\0';
     int ciphersize = atoi(size) ;

    //read cipher
     read = recv(clientSocket,data,1024,0);

    //Decrypting data
    Decrypt(data,ciphersize,hash);//,h0,h1,h2,h3);

    printf("-------------------------------------------------------------------------------------\n");
      }

  memset(input,0,1024);
  }

}

int main(){

  int clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8080);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) return 0;

  printf("Connection established ............\n");

  pthread_t thread;
  pthread_create(&thread, NULL, doRecieving, (void *) &clientSocket );

  //Instruction to operate client
  printf("Instruction To send Message to other client\n");
  printf("Type :  < LIST > press enter to list all client in network \n");
  printf("Type : < SEND 'space' 'client number' 'space' 'message' > press enter to send message\n");

  printf("-------------------------------------------------------------------------------------\n");

  while(1){

    char input[1024];
    scanf("%s",input);

    if(strcmp(input,"LIST") == 0){

      send(clientSocket,input,1024,0);

    }
    if(strcmp(input,"SEND") == 0){

      send(clientSocket,input,1024,0);
      
      scanf("%s",input);
      send(clientSocket,input,1024,0);
      
      scanf("%[^\n]s",input);

      //send hash value 
      send(clientSocket,HashingMD5(input),1024,0);
      
      //send sizeof cipher
      int size=strlen(input);
      char sz[1024];  sprintf(sz,"%d",size);
      send(clientSocket,sz,1024,0);

      // send encrypting data
      send(clientSocket,Encrypt(input),1024,0);
      
      memset(input,0,1024);
    
    printf("-------------------------------------------------------------------------------------\n");
      

    }

  }


}
