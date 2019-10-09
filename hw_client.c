#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>

#define IPADDR "127.0.0.1"
#define PORT 9000

char input[100];

int main()
{
	int c_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;
	int n;
	char rcv[100];

	c_socket = socket(PF_INET,SOCK_STREAM,0);
	
	memset(&c_addr,0,sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR);
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);
	
	if(connect(c_socket,(struct sockaddr *)&c_addr,sizeof(c_addr)) == -1)
	{
		printf("Cannot Connect\n");
		close(c_socket);
		return -1;
	}
	while(1)
	{
		fgets(input,sizeof(input),stdin);
		write(c_socket,input,sizeof(input));
	
		if((n=read(c_socket,rcv,sizeof(rcv)))<0)	
		{	
			return -1;
		}
		rcv[n]='\0';
		printf("%s\n",rcv);
	}
		close(c_socket);
		return 0;
}
