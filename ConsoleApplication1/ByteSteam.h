#pragma once
#include <iostream>
using namespace std;
class ByteSteam
{

private:
	char* data;
	int readIndex;
	int writeIndex;
	int capacity;
public:
	ByteSteam(int capacity);
	ByteSteam();

	void Zero();

	int ReadInt();
	void WriteInt(int value);
	void WriteChar(char value);
	void WriteChar(char* src, int lenght);
	int GetSize();
	int GetCapacity();
	int GetWritePosition();
	int GetReadPosition();

	char* GetData();
};

