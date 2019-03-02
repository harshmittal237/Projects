
// Write CPP code here 
#include <stdio.h>
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 80 
#define PORT 8080 
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
    scanf("%d",&size);
    FILE* f;
	f=fopen("Data.txt","r");
	char s[size+2];
	int c1,ack,temp; 
    while(!feof(f))
	{
		fgets(s,size+1,f);
		if(s[0]=='$')
		{
			//printf("%sa\n",s);
			write(sockfd, s, sizeof(s));
			break;
		}	
		
		c1=parity(s,size);
		if(c1==0)
			s[size]='0';
		else
			s[size]='1';
		s[size+1]='\0';
		do
		{
			printf("The codeword send is: %s\n",s);
			write(sockfd, s, sizeof(s));
			read(sockfd, &temp, sizeof(temp));
			ack=ntohs(temp);
			printf("Acknowledgment received is: %d\n",ack);
		}while(ack==0);				
	}
	fclose(f);
	close(sockfd); 
} 

