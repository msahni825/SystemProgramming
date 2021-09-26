#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h> 

#define PORT 5555
#define MAXSIZE 80

int main(int argc, char *argv[])
{
    int sock = 0;
    char sendbuff[MAXSIZE], recvbuff[MAXSIZE];
    int valread;
    
    struct sockaddr_in serv_addr; 
    

    if(argc != 2)
    {
        printf("\n Usage: %s <Server IP address>\n",argv[0]);
        return -1;
    } 
//SOCKET ESTABLISHMENT
    
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0) //convert IPv4 and IPv6 addresses from text to binary form
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    } 

//CONNECTION ESTABLISHMENT
    if( connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\nConnection Failed \n");
       return -1;
    } 

    int readbytes = 0;
    char recvBuff[500];
    char recvBuff1[100];
    int readdata=0;
    memset(recvBuff, '0',sizeof(recvBuff));

printf("Connection established,enter the string: \n");

    while(fgets(sendbuff,MAXSIZE,stdin)!=NULL)
	{
          send(sock,sendbuff,sizeof(sendbuff),0);


       bzero(recvbuff,MAXSIZE);
     
      //read the string sent by the server
      printf("HELLO");
      valread=read(sock,recvbuff,strlen(recvbuff));
      while((readdata=read(sock,recvBuff1,sizeof(recvBuff1)))>0)
       {
        recvBuff1[readdata]=0;
       printf("%s \n",recvBuff1);
       }

       }

       close(sock);
  
    return 0;
}

