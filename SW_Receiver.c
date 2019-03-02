
// Write CPP code here 
#include <stdio.h>
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 80 
#define PORT 8088
#define SA struct sockaddr
int size;
int parity(char* s,int n)
{
	int c1=0;
	for(int i=0;i<n;i++)
		if(s[i]=='1')
			c1++;
	c1=c1%2;		
	return c1;		
} 

int main() 
{ 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
    char s[MAX];	
    while(1)
    {
        read(sockfd, s, sizeof(s));
		printf("%Received Codeword is: %s\n",s);
        if(s[0]=='$')
        {
        	printf("%s\n",s);
        	break;
    	}
    	size=strlen(s);
    	
    	int ack,temp,c1=parity(s,size);
		if(c1==0)
		{
			printf("No Errors!\n");
			temp=1;
		}	
		else
		{
			printf("Error detected!\n");
			temp=0;
		}
		ack=htons(temp);
		write(sockfd,&ack,sizeof(ack));
		 
	}
	close(sockfd);	
} 

