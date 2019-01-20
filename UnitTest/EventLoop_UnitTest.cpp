//
// Created by kiwi on 19-1-10.
//

#include "../Reactor/EventLoop.h"
#include "../Reactor/Channel.h"
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <cstdio>

#define PORT 23333
#define BUFFER_SIZE 100

void echo_cli(int sockfd);

void fun(char buffer[],int sockfd)
{
	memset(buffer, 0, sizeof(buffer));
	read(sockfd, buffer, BUFFER_SIZE);
	printf("read msg:%s\n", buffer);
}
void fun1(char buffer[],int sockfd)
{
	printf("sent msg:%s\n", buffer);
	write(sockfd, buffer, strlen(buffer));
}

int main(int argc, char *argv[])
{
	char *ip_addr;
	int sockfd;
	sockaddr_in servaddr{};
	int opt;

	while ((opt = getopt(argc, argv, {"a:"})) != -1)
	{
		switch (opt)
		{
			case 'a':
				ip_addr = optarg;
				break;
			default:
				printf("Unexpected option : -%c\n", opt);
				return -1;
		}
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	inet_pton(AF_INET, ip_addr, &servaddr.sin_addr);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		printf("create socket error!\n");
		return -1;
	}
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1)
	{
		printf("connecting failed\n");
		return -1;
	}
	char buffer[BUFFER_SIZE];
	buffer[0] = 'a';
	buffer[1] = '\0';
	Kiwi::EventLoop loop;
	Kiwi::Channel channel(&loop, sockfd);
	channel.enable_writing();
	channel.enable_reading();

	channel.set_read_handler(std::bind(fun,buffer,sockfd));
	channel.set_write_handler(std::bind(fun1,buffer,sockfd));
	loop.add_channel(&channel);
	loop.loop();
	//echo_cli(sockfd);
	close(sockfd);

	return 0;
}

void echo_cli(int sockfd)
{
	char buffer[BUFFER_SIZE];
	while (scanf("%s", buffer) != EOF)
	{
		printf("sent msg:%s\n", buffer);
		write(sockfd, buffer, strlen(buffer));

		memset(buffer, 0, sizeof(buffer));

		read(sockfd, buffer, BUFFER_SIZE);
		printf("read msg:%s\n", buffer);
	}
}