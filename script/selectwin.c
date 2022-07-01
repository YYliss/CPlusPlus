#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#define BUF_SZIE 1024
void Errorling(char* msg);
#define PORT 9527

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	TIMEVAL timeout;
	fd_set reads, cpyReads;

	int adrSz;
	int strLen, fdNum, i;
	char buf[BUF_SZIE];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		Errorling("WSAStartup() error!");
	}

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = PF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(PORT);

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		Errorling("bind() error");
	}
	printf("Bind 成功....");
	if (listen(hServSock, 5) == SOCKET_ERROR)
	{
		Errorling("listen() error");
	}
	printf("listen 成功....");
	FD_ZERO(&reads);
	FD_SET(hServSock, &reads);

	while (1)
	{
		cpyReads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		if ((fdNum = select(0, &cpyReads, 0, 0, &timeout)) == SOCKET_ERROR)
		{
			break;
		}
		if (fdNum == 0)
		{
			//没任何变化
			continue;
		}
		for (i = 0; i < reads.fd_count; i++)
		{
			if (FD_ISSET(reads.fd_array[i], &cpyReads))
			{
				if (reads.fd_array[i] == hServSock)
				{
					adrSz = sizeof(clntAdr);
					hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &adrSz);
					FD_SET(hServSock, &reads);
					printf("connect client:%d \n", hClntSock);
				}
				else
				{
					strLen = recv(reads.fd_array[i], buf, BUF_SZIE - 1, 0);
					if (strLen == 0)
					{
						FD_CLR(reads.fd_array[i], &reads);
						closesocket(cpyReads.fd_array[i]);
						printf("closed client:%d \n", cpyReads.fd_array[i]);
					}
					else 
					{
						send(reads.fd_array[i], buf, strLen, 0);
					}
				}
			}
		}
	}
	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void Errorling(char* msg) 
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}