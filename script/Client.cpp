// Client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
using namespace std;
void ErrorHanding(const char* message);

void IntToCharArr(int i, char* arr);
int CharArrToInt(char* arr);


void SendData(SOCKET sock, char*message);

#define BUFF_SIZE 1024
int main()
{

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHanding("WSAStartup");
	}

	SOCKADDR_IN servAddr;
	int servAddrLen = sizeof(servAddr);
	memset(&servAddr, 0, servAddrLen);
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(9527);
	
	INADDR_ANY;
	SOCKET hSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hSock == INVALID_SOCKET)
	{
		ErrorHanding("socket error");
	}

	if (connect(hSock,(SOCKADDR*)&servAddr, servAddrLen) == SOCKET_ERROR)
	{
		ErrorHanding("connect error");
	}

	while (true)
	{
		cout << "enter message to send  (Q to quit)";
		char sendBuf[BUFF_SIZE];
		cin.getline(sendBuf, BUFF_SIZE);


		if (!strcmp(sendBuf, "q\n")|| !strcmp(sendBuf, "Q\n"))
		{
			cout << "退出\n";
			break;
		}

		SendData(hSock, sendBuf);
	}

	closesocket(hSock);
	WSACleanup();
	printf("断开网络");
}

void ErrorHanding(const char* message) {
	printf("Error: %s  Reason: %d \n", message, WSAGetLastError());
	exit(-1);
}

void SendData(SOCKET sock, char* message) {
	int messageLen = strlen(message);
	char dataLen[4];
	IntToCharArr(messageLen, dataLen);

	printf("发送数据长度：%d\n", messageLen);

	send(sock, dataLen, 4, 0);
	send(sock, message, messageLen, 0);
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