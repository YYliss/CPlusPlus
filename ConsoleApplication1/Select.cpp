
#include <iostream>
#include <fstream>
#include <string>
#include <WinSock2.h>
#include <vector>
#include <mstcpip.h>
using namespace std;

#define BUF_SIZE 1024

void ErrorHanding(const char* message) {
	printf("Error %s \n", message);
	exit(-1);
}

int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHanding("WSAStartup");
	}

	SOCKADDR_IN sockAddr;
	int sockAddrSize = sizeof(sockAddr);

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(9527);

	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sockServer == INVALID_SOCKET)
	{
		ErrorHanding("Socket");
	}

	if (bind(sockServer, (SOCKADDR*)&sockAddr, sockAddrSize) == SOCKET_ERROR)
	{
		ErrorHanding("bind error");
	}
	if (listen(sockServer, 5) == SOCKET_ERROR)
	{
		ErrorHanding("listen error");
	}

	int maxFd;
	fd_set readfds, cpy_reads;
	FD_ZERO(&readfds);
	FD_SET(sockServer, &readfds);
	maxFd = sockServer;
	timeval timeout;
	int fd_num = 0;

	SOCKADDR_IN clntAddr;
	int clntAddrSize = sizeof(clntAddr);

	while (1)
	{
		cpy_reads = readfds;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;
	 	fd_num = select(maxFd + 1, &cpy_reads, 0, 0, &timeout);

		if (fd_num == -1)
		{
			ErrorHanding("select error");
		}
		else if (fd_num == 0)
		{
			printf("Time Out \n");
		}
		else
		{
			for (size_t i = 0; i <= maxFd; i++)
			{
				if (FD_ISSET(i, & cpy_reads))
				{
					if (i == sockServer)
					{
						SOCKET sockTemp = accept(sockServer, (SOCKADDR*)&clntAddr, &clntAddrSize);
						if (sockTemp == SOCKET_ERROR)
						{
							ErrorHanding("accept error");
						}
						FD_SET(sockTemp, &readfds);
						maxFd = sockTemp;
						cout << "几首 " << maxFd << endl;
					}
					else
					{
						char buf[BUF_SIZE] = {0};
						int read_len = recv(i, buf, BUF_SIZE, 0);
						if (read_len < 0)
						{
							FD_CLR(i, &readfds);
							closesocket(i);
						}
						else
						{
							printf("接收消息：%s\n", buf);
						}
					}
				}
			}
		}
	}

	closesocket(sockServer);

	WSACleanup();
}

