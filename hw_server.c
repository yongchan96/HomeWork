#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>

#define PORT 9000

char hello[100] = "안녕하세요. 만나서 반가워요.";
char c_hello[20] = "안녕하세요";
char rd_str[100];
char age[20] = "나는 24살이야";
char name[50] = "내 이름은 서버야";
char compare[2][50];
char inputchar[2];
int main()
{
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;
	int n;
	int result;
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
		read(c_socket,rd_str,sizeof(rd_str));
		
		printf("%s\n",rd_str);
	
		if(strncmp(rd_str,c_hello,10) == 0)
		{
			n = strlen(hello);
			write(c_socket, hello, n);
		}

		else if(strncmp(rd_str,"이름이 뭐야?",12) == 0)
		{
			n = strlen(name);
			write(c_socket, name, n);
		}

		else if(strncmp(rd_str,"몇 살이야?",10) == 0)
		{
			n = strlen(age);
			write(c_socket, age, n);
		}
			
		else if(strncmp(rd_str,"strcmp",6) == 0 )
		{
			strtok(rd_str,"\n ");
			strcpy(compare[0],strtok(NULL,"\n "));
			strcpy(compare[1],strtok(NULL,"\n "));
			sprintf(inputchar,"%d",strcmp(compare[0],compare[1]));
			write(c_socket,inputchar,sizeof(inputchar));
		}

		else if(strncmp(rd_str,"strlen",6) == 0)
		{
			strtok(rd_str,"\n ");
			strcpy(compare[0],strtok(NULL,"\n "));
			sprintf(inputchar,"%d",strlen(compare[0]));
			write(c_socket,inputchar,sizeof(inputchar));
		}
		
		else
		{		
			write(c_socket,rd_str,sizeof(rd_str));
		}			
		
	}	
	close(c_socket);

	}

	close(s_socket);	
	return 0;
}
