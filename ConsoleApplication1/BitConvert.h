#pragma once
#include <iostream>
using namespace std;
namespace BitConvert {
	void GetBytes(unsigned char* dest, bool value);
	void GetBytesByShort(unsigned char* dest, short value);
	void GetBytesByUShort(unsigned char* dest, unsigned short value);
	void GetBytes(unsigned char* dest, int value);
	void GetBytes(unsigned char* dest, unsigned int value);
	void GetBytes(unsigned char* dest, long long value);
	void GetBytes(unsigned char* dest, unsigned long long value);
	void GetBytes(unsigned char* dest, float value);
	void GetBytes(unsigned char* dest, double value);

	bool ToBool(unsigned char* data);
	short ToShort(unsigned char* data);
	unsigned short ToUShort(unsigned char* data);
	int ToInt(unsigned char* data);
	unsigned int ToUInt(unsigned char* data);
	long long ToLLong(unsigned char* data);
	unsigned long long ToULLong(unsigned char* data);

	float ToFloat(unsigned char* data);
	double ToDouble(unsigned char* data);

	void Test();
}