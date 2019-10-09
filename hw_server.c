#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>

#define PORT 9000

char hello[100] = "안녕하세요. 만나서 반가워요.";
char c_hello[20] = "안녕하세요";
char rd_hello[100];
int main()
{
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;
	int n;

	s_socket = socket(PF_INET,SOCK_STREAM,0);
	
	memset(&s_addr,0,sizeof(s_addr));
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);
	
	if(bind(s_socket, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) 
	{
		printf("Can not Bind\n");
		return -1;
	}
	
	if(listen(s_socket, 5) == -1)
	{
			printf("listen Fail\n");
			return -1;
	}
	
	
	while(1) 
	{

	len = sizeof(c_addr);
	printf("접속을 기다리는 중...\n");
	c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);
	printf("클라이언트 접속 허용 \n");

	while(1)
	{
		read(c_socket,rd_hello,sizeof(rd_hello));
		
		printf("%s\n",rd_hello);
	
		if(strncmp(rd_hello,c_hello,10) == 0)
		{
			n = strlen(hello);
			write(c_socket, hello, n);
		}
	}
	close(c_socket);

	}

	close(s_socket);	
	return 0;
}
