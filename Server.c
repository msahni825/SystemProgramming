#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h> 
#include <time.h> 

#define PORT 5555

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 
    int valueread,temp,i,j;

    char sendbuff[500];
    char senddata[50];
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    memset(sendbuff, '0', sizeof(sendbuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 5); 
    printf("\nServer listening for connections!\n");
    
    time_t t_seconds;

    while(1)
    { 
        //printf(" hello \n");
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
        printf("\nAccepted a connection\n");
        t_seconds = time(0);

        snprintf(senddata, sizeof(senddata), "%s\n", ctime(&t_seconds));
        write(connfd, senddata, strlen(senddata)); 
//reading string by client
        valueread=read(connfd,senddata,sizeof(senddata));
        printf("String from Client:%s \n", senddata);
//loop to reverse the string sent by client

        for(i=0,j=strlen(senddata)-1; i<j; i++,j--)
        {
          
          temp=senddata[i];
          senddata[i]=senddata[j];
          senddata[j]=temp;


	}
        send(connfd,senddata,strlen(senddata),0);
        printf("Reversed String sent to client !\n");		
        close(connfd);
        
     }
}

