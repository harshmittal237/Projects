#include <stdio.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT1 8080
#define PORT2 8088 
#define SA struct sockaddr 
int size;
void func(int sockfd1,int sockfd2) 
{ 
    char s[MAX]; 
    int temp,ack,c; 
    while(1)
    {
    	read(sockfd1, s, sizeof(s));
    	if(s[0]=='$')
    	{
    		printf("%s\n",s);
    		write(sockfd2, s, sizeof(s));
    		break;
    	}	
        size=strlen(s); 
        printf("Received Codeword from Sender is: %s\n",s);
        do
        {
        	c=rand()%2;
        	if(c==1)
        	{	
        		sleep(8);
				printf("Timeout from Sender!\n");
        	}
		}while(c==1);
		int r=(rand()%2) & (rand()%2);
		if(r)
		{
			int x=rand()%(size);
			s[x]=(s[x]=='0')? '1':'0';
		}
		printf("Codeword to Receiver is: %s\n",s);	
        write(sockfd2, s, sizeof(s)); 
  		read(sockfd2, &temp, sizeof(temp)); 
  		ack=ntohs(temp);
  		printf("Acknowlegment from Receiver: %d\n",ack);
  		do
        {
        	c=rand()%2;
        	if(c==1)
        	{	
        		sleep(8);
				printf("Timeout from Receiver!\n");
        	}
		}while(c==1);
  		write(sockfd1, &temp, sizeof(temp));    
    }    
} 
  
// Driver function 
int main() 
{ 
    int sockfd1, sockfd2, connfd1, connfd2, len; 
    struct sockaddr_in serv1, serv2, cli; 
    sockfd1 = socket(AF_INET, SOCK_STREAM, 0); 
    sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd1 == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket 1 successfully created..\n");
    printf("Socket 2 successfully created..\n");    	 
    bzero(&serv1, sizeof(serv1)); 
    bzero(&serv2, sizeof(serv2));
    serv1.sin_family = AF_INET; 
    serv1.sin_addr.s_addr = htonl(INADDR_ANY); 
    serv1.sin_port = htons(PORT1); 
    serv2.sin_family = AF_INET; 
    serv2.sin_addr.s_addr = htonl(INADDR_ANY); 
    serv2.sin_port = htons(PORT2);
    if ((bind(sockfd1, (SA*)&serv1, sizeof(serv1))) != 0) { 
        printf("socket bind failed1...\n"); 
        exit(0); 
    } 
    else
        printf("Socket 1 successfully binded..\n"); 
  	if ((bind(sockfd2, (SA*)&serv2, sizeof(serv2))) != 0) { 
        printf("socket bind failed2...\n"); 
        exit(0); 
    } 
    else
        printf("Socket 2 successfully binded..\n"); 
    if ((listen(sockfd1, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
     
    if ((listen(sockfd2, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
        
    len = sizeof(cli); 
    connfd1 = accept(sockfd1, (SA*)&serv1, &len); 
    connfd2 = accept(sockfd2, (SA*)&serv2, &len); 
    if (connfd1 < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 
  	
    func(connfd1,connfd2); 
  	 
    close(sockfd1); 
    close(sockfd2);
} 

