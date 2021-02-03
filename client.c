/*
    argv[0]--->fileName
    argv[1]--->ipadress
    argv[2]--->portno
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd,portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int n;

    char buffer[255];
    if(argc<3)
    {
        fprintf(stderr,"usage %s hostname portno",argv[0]);
        exit(0);

    }

    portno=atoi(argv[2]);
     sockfd=socket(AF_INET,SOCK_STREAM,0);
     if(sockfd<0)
     {
         error("Error opening socket:\n");
        
     }

     server=gethostbyname(argv[1]);
     if(server==NULL)
     {
         fprintf(stderr,"Error,no such host");
     }
     bzero((char*)&serv_addr,sizeof(serv_addr));
     serv_addr.sin_family=AF_INET;

     bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);

    serv_addr.sin_port=htons(portno);

    if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
    {
        error("connection failed:\n");
    }

    
    int num1,num2,ans,choice;
    S: bzero(buffer,255);           //reading string from server

   n= read(sockfd,buffer,255);
   if(n<0)
   error("Error in reading");

   printf("server %s\n",buffer);
   scanf("%d",&num1);               //Enter num1
   write(sockfd,&num1,sizeof(int)); //sending num1 to server

  bzero(buffer,255); 
  n= read(sockfd,buffer,255);
   if(n<0)
   error("Error in reading");

   printf("server %s\n",buffer);
   scanf("%d",&num2);               //Enter num2
   write(sockfd,&num2,sizeof(int)); //sending num2 to server


   bzero(buffer,255); 
  n= read(sockfd,buffer,255);
   if(n<0)
   error("Error in reading");

   printf("server %s\n",buffer);
   scanf("%d",&choice);               //Enter choice
   write(sockfd,&choice,sizeof(int)); //sending choice to server

   if(choice==5)
   {
       goto Q;
   }

   read(sockfd,&ans,sizeof(int));
   printf("Server Answer is %d\n",ans);

   if(choice!=5)
   goto S;


   Q:
    printf("Exit successfully:\n");
    close(sockfd);

    return 0;
}