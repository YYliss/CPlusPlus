#pragma 
#include <iostream>
#include "BitConvert.h"

using namespace std;

class ReaderSteam
{
private: 
	unsigned char* data;
	int postion;
	int size;

public:
	ReaderSteam(unsigned char* src);
	
	unsigned char ReadChar();
	unsigned char PeekChar();

	short ReadShort();
	short PeekShort();

	unsigned short ReadUShort();
	unsigned short PeekUShort();


	int ReadInt();
	int PeekInt();

	unsigned int ReadUInt();
	unsigned int PeekUInt();

	long long ReadLLong();
	long long PeekLLong();
	unsigned long long ReadULLong();
	unsigned long long PeekULLong();

	string ReadString(int len);
	string PeekString(int len);

	float ReadFloat();
	float PeekFloat();
	double ReadDouble();
	double PeekDouble();

	int Size();
	
};

