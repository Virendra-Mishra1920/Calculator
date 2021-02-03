#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    if(argc<2)
    {
        fprintf(stderr,"please enter the port number\n");
        exit(1);
    }

    int sockfd,newsockfd,portno;
    char buffer[1024];
    int n;

    struct sockaddr_in serv_addr,clint_addr;
    socklen_t clilen;

    //creating socket

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
    {
        error("Error to opening socket\n");
    }

    bzero((char*)&serv_addr,sizeof(serv_addr));
    portno=atoi(argv[1]);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(portno);

    if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
    {
        error("Binding failed\n");
    }

    //listen connection

    listen(sockfd,5);
    clilen=sizeof(clilen);

    //accept request

    newsockfd=accept(sockfd,(struct sockaddr*)&clint_addr,&clilen);

    if(newsockfd<0)
    {
        error("Not accepting\n");
    }

    //communication starting

    int num1,num2,ans,choice;

 S: n= write(newsockfd,"Enter number 1:",sizeof("Enter number 1")); //Ask for num1
   if(n<0)
   {
       error("Error in writing:\n");
   }
   read(newsockfd,&num1,sizeof(int)); //read number1
   printf("client number 1:%d\n",num1);


   n= write(newsockfd,"Enter number 2:",sizeof("Enter number 2")); //Ask for num2
   if(n<0)
   {
       error("Error in writing:\n");
   }
   read(newsockfd,&num2,sizeof(int)); //read number2
   printf("client number 2:%d\n",num2);

   n=write(newsockfd,"Enter your choice :\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exit\n",
   strlen("Enter your choice :\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exit\n"));

   if(n<0)
   {
       error("Error in writing");
   }

   read(newsockfd,&choice,sizeof(int));
   printf("Client: choice %d\n",choice);

   switch (choice)
   {
        case 1:
            ans=num1+num2;
            break;

            case 2:
            ans=num1-num2;
            break;

            case 3:
            ans=num1*num2;
            break;

            case 4:
            ans=num1/num2;
            break;

            case 5:
            goto Q;
            break;
   
            default:
            printf("Invalid choice:\n");
            
                break;
   }

   write(newsockfd,&ans,sizeof(int));
   if(choice!=5)
   {
       goto S;
   }

   Q: close(newsockfd);
    close(sockfd);
    


    return 0;
}
