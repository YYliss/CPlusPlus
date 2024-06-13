#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>

using namespace std;
#define BUFF_SIZE 1024
void ErrorHanding(const char* message) {
	printf("ErrorHanding: %s\n", message);
	//exit(1);
}


void IntToCharArr(int i, char* arr);
int CharArrToInt(char* arr);


int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHanding("WSAStartup error");
	}

	SOCKADDR_IN sockServAddr;
	int sockServAddrLen = sizeof(sockServAddr);
	memset(&sockServAddr, 0, sockServAddrLen);
	sockServAddr.sin_family = AF_INET;
	sockServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockServAddr.sin_port = htons(9527);

	SOCKET hServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hServerSock == INVALID_SOCKET)
	{
		ErrorHanding("socket error");
	}
	if (bind(hServerSock, (SOCKADDR*)&sockServAddr, sockServAddrLen) == SOCKET_ERROR)
	{
		ErrorHanding("bind error");
	}

	if (listen(hServerSock, 5) == SOCKET_ERROR)
	{
		ErrorHanding("listen error");
	}

	SOCKADDR_IN clntAddr;
	int clntAddrLen = sizeof(clntAddr);

	printf("开始Accept\n");

	SOCKET clntSocket = accept(hServerSock, (SOCKADDR*)&clntAddr, &clntAddrLen);
	if (clntSocket == INVALID_SOCKET)
	{
		ErrorHanding("accept error");
	}
	printf("有连接进来\n");

	int dataMaxLen = 0;
	char dataLenBuf[4];

	int readLen = 0;
	char readData[BUFF_SIZE * 100] = { 0 };

	while (true)
	{
	
		if (dataMaxLen == 0)
		{
			int len = recv(clntSocket, dataLenBuf, 4, 0);
			cout << "dataLenBuf：" << dataLenBuf << endl;
			if (len <= 0)
			{
				break;
			}
			dataMaxLen = CharArrToInt(dataLenBuf);
			readLen = 0;
			printf("读取数据长度：%d\n", dataMaxLen);
		}
		else
		{
			char dateTemp[BUFF_SIZE];
			int len = recv(clntSocket, dateTemp, dataMaxLen - readLen, 0);

			if (len <= 0)
			{
				printf("recv error");
				break;
			}
			else
			{
				memcpy(readData + readLen, dateTemp, len);
				readLen += len;
				if (readLen >= dataMaxLen)
				{
					dataMaxLen = 0;
					printf("读取完毕：%s", readData);
					memset(readData, 0, BUFF_SIZE * 100);
				}
			}
		}
	}

	printf("客户端断开\n");
	closesocket(clntSocket);
	closesocket(hServerSock);
	WSACleanup();
}


void IntToCharArr(int i, char* arr) {
	arr[0] = (i & 0xff);
	arr[1] = ((i >> 8) & 0xff);
	arr[2] = ((i >> 16) & 0xff);
	arr[3] = ((i >> 24) & 0xff);
}

int CharArrToInt(char* arr) {
	int n0 = arr[0];
	int n1 = arr[1];
	int n2 = arr[2];
	int n3 = arr[3];
	return (n0)
		+(n1 << 8)
		+ (n2 << 16)
		+ (n3 << 24);
}