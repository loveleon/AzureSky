#include "../Header.h"

#define LISTEN_PORT 4022

void main()
{
#ifdef WIN32

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData))
	{
		return;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) 
	{
		WSACleanup();
		return;
	}

	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.4.53");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(LISTEN_PORT);

	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	char recvBuf[MAX_PATH];
	recv(sockClient, recvBuf, MAX_PATH, 0);
	printf("%s\n", recvBuf);

	char sendBuf[MAX_PATH] = "I want to marry with you\n";
	send(sockClient, sendBuf, MAX_PATH + 1, 0);

	closesocket(sockClient); 

	WSACleanup();

	char c;
	std::cin>>c;

#else

	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	int sockfd, n;
	char *str;

	if (argc != 2) {
		fputs("usage: ./client message\n", stderr);
		exit(1);
	}
	str = argv[1];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	write(sockfd, str, strlen(str));

	n = read(sockfd, buf, MAXLINE);
	printf("Response from server:\n");
	write(STDOUT_FILENO, buf, n);

	close(sockfd);
	return 0;

#endif
}