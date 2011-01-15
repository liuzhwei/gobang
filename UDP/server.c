
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

int main(int argc, char *argv[])
{
	char c;
	int i,len;
	int server_sock;
	socklen_t client_len;
	struct sockaddr_in server,client;
	struct in_addr in;

	if((server_sock = socket(AF_INET, SOCK_DGRAM,0)) < 0)
	{
		fprintf(stderr,"%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("creat socket ok !\n");	
	}


	bzero(&server,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = htons(INADDR_ANY);

	if(bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("bind addr ok !\n\n");	
	}

	while(1)
	{
		client_len = sizeof(client);
		len = recvfrom(server_sock, buffer,BUFFER_SIZE, 0,(struct sockaddr *)&client, &client_len);
		if(len < 0)
		{
			close(server_sock);
			fprintf(stderr,"%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("recvfrom client ok!\n");
			in.s_addr = client.sin_addr.s_addr;
			printf("client ip : %s\n",inet_ntoa(in));
			printf("client port: %d\n",ntohs(client.sin_port));
		}

		if(buffer[0] == '.') break;
		for(i=0; i<len; i++)
		{
			c = buffer[i];
			buffer[i] = toupper(c);
		}
		sendto(server_sock,buffer,len,0,(struct sockaddr *)&client, client_len);
	}
	printf("Client close the socket\n");
	close(server_sock);
	exit(EXIT_SUCCESS);
}
