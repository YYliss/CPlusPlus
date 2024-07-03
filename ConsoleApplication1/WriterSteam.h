#pragma once
#include "BitConvert.h"
#include "MemoryAlloc.h"
class WriterSteam
{
private: 
	int position;
	int capacity;
	MemoryBuff* data;

	void CheckCapacity(int len);

public:
	WriterSteam(int preCapactiy = 10);

	void WriteChar(unsigned char value);
	void WriteShort(short value);
	void WriteUShort(unsigned short value);
	void WriteInt(int value);
	void WriteUInt(unsigned int value);
	void WriteLLong(long long value);
	void WriteULLong(unsigned long long value);
	void WriteFloat(float value);
	void WriteDouble(double value);
	void WriteString(string str);
	void WriteString(unsigned* str, int len);

	int Size();
};

