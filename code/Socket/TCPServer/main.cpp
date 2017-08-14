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

	SOCKET sockSvr = socket(AF_INET, SOCK_STREAM, 0);	
	SOCKADDR_IN addrSvr;								
	addrSvr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);   
	addrSvr.sin_family = AF_INET;
	addrSvr.sin_port = htons(LISTEN_PORT);

	bind(sockSvr, (SOCKADDR*)&addrSvr, sizeof(SOCKADDR));
	listen(sockSvr, 5);

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET sockConn = accept(sockSvr, (SOCKADDR*)&addrClient, &len);
		printf("%s is logining this server!\n", inet_ntoa(addrClient.sin_addr));

		char sendBuf[MAX_PATH] = "login success!\n";
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);

		char recvBuf[MAX_PATH];
		recv(sockConn, recvBuf, MAX_PATH, 0);
		printf("%s\n", recvBuf);

		closesocket(sockConn);
	}

	WSACleanup();

#else
	
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(LISTEN_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(sockSvr, 5);

	
	struct sockaddr_in cliaddr;
	int cliaddr_len = sizeof(cliaddr);
	while (1)
	{
		int connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);

		char buf[255];
		int n = read(connfd, buf, 255);

		write(connfd, buf, n);

		close(connfd);
	}

#endif
}