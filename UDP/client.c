


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT  2001
#define BUFFER_SIZE  256

char buffer[BUFFER_SIZE];


int main(int argc,char * argv[])
{
	int i,n,len;
	int client_sock;
	socklen_t server_len;
	struct sockaddr_in server;

	if(argc < 2)
	{
		printf("\n");
		printf("Sorry, your type si wrong.\n");
		printf("Usage:%s x.x.x.x(Server IP)\n",argv[0]);
		printf("\n");
		exit(EXIT_FAILURE);
	}


	if((client_sock = socket(AF_INET, SOCK_DGRAM,0)) < 0)
	{
		fprintf(stderr, "%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("create socket ok !\n");	
	}


	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = inet_addr(argv[1]);

	while(1)
	{
		i = write(STDOUT_FILENO,">",3);
		if((len = read(STDIN_FILENO,buffer,BUFFER_SIZE)) > 0)
		{
			server_len = sizeof(server);
			n = sendto(client_sock,buffer,len,0,(const struct sockaddr *)&server,server_len);
		}
		
		if(buffer[0] == '.') break;
		server_len = sizeof(server);
		n = recvfrom(client_sock,buffer,BUFFER_SIZE,0,(struct sockaddr *)&server,&server_len);
		if(n > 0)
		{
			i = write(STDOUT_FILENO,buffer,n);
		}
	}
	close(client_sock);
	exit(EXIT_SUCCESS);
	
}
