
#define  _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <process.h>

void diamond(int n, char c)
{
	if (n % 2 == 0)
	{
		printf("不能是偶数");
		return;
	}
	int i, j;

	int helf = n / 2 + 1;
	for (i = 1; i <= n; i++)
	{
		int df = abs(helf - i) * 2;
		for (j = 0; j < df / 2; j++)
		{
			printf("\t");
		}
		for ( j = 0; j < n - df; j++)
		{
			printf("%c\t", c);
		}
		for (j = 0; j < df / 2; j++)
		{
			printf("\t");
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	diamond(5, '*');
	
}