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

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return ;
	}

	SOCKET sockSvr = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	sockaddr_in addr;
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = ntohs(LISTEN_PORT);

	int rs = bind(sockSvr, (sockaddr*)&addr, sizeof(addr));

	char buf[MAX_PATH];
	char temp[MAX_PATH];
	sockaddr_in addrcl;
	int len = sizeof(sockaddr);
	while (1)
	{
		recvfrom(sockSvr, buf, sizeof(buf), 0, (sockaddr*)&addrcl, &len);
		printf("%s", buf);

		sprintf_s(temp, MAX_PATH, "%s:%s", inet_ntoa(addrcl.sin_addr), buf);
		sendto(sockSvr, temp, strlen(temp) + 1, 0, (sockaddr*)&addrcl, sizeof(addr));
	}

	closesocket(sockSvr);
	WSACleanup();
}