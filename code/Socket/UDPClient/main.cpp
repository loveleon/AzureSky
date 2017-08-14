#include "../Header.h"

#define LISTEN_PORT 4023

void main()
{
	WSADATA wsaData;
	int Ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Ret != 0)
	{
		printf("无法初始化winsock.\n");
		WSACleanup();
	}

	SOCKET socketc = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	sockaddr_in addr;
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.4.53");
	addr.sin_family = AF_INET;
	addr.sin_port = ntohs(LISTEN_PORT);

	int len = sizeof(sockaddr);
	while (1)
	{
		char buf[200] = "you are a pig!\n";
		char rbuf[300];

		sendto(socketc, buf, strlen(buf) + 1, 0, (SOCKADDR*)&addr, len);
		recvfrom(socketc, rbuf, sizeof(rbuf), 0, (SOCKADDR*)&addr, &len);
		printf("%s", rbuf);
	}

	closesocket(socketc);
	WSACleanup();
}