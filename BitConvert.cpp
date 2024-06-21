#include "BitConvert.h"
#include "BitConvert.h"


void BitConvert::GetBytes(unsigned char* dest, bool value)
{
	dest[0] = value;
}

void BitConvert::GetBytesByShort(unsigned char* dest, short value)
{
	dest[0] = value;
	dest[1] = (value >> 8) & 255;
}

void BitConvert::GetBytesByUShort(unsigned char* dest, unsigned short value)
{
	dest[0] = value;
	dest[1] = value & 255;
}

void BitConvert::GetBytes(unsigned char* dest, int value)
{
	dest[0] = value;
	dest[1] = (value >> 8) & 255;
	dest[2] = (value >> 16) & 255;
	dest[3] = (value >> 24) & 255;
}

void BitConvert::GetBytes(unsigned char* dest, unsigned int value)
{
	dest[0] = value;
	dest[1] = (value >> 8) & 255;
	dest[2] = (value >> 16) & 255;
	dest[3] = (value >> 24) & 255;
}

void BitConvert::GetBytes(unsigned char* dest, long long value)
{
	dest[0] = value;
	dest[1] = (value >> 8) & 255;
	dest[2] = (value >> 16) & 255;
	dest[3] = (value >> 24) & 255;
	dest[4] = (value >> 32) & 255;
	dest[5] = (value >> 40) & 255;
	dest[6] = (value >> 48) & 255;
	dest[7] = (value >> 56) & 255;
}

void BitConvert::GetBytes(unsigned char* dest, unsigned long long value)
{
	dest[0] = value;
	dest[1] = (value >> 8) & 255;
	dest[2] = (value >> 16) & 255;
	dest[3] = (value >> 24) & 255;
	dest[4] = (value >> 32) & 255;
	dest[5] = (value >> 40) & 255;
	dest[6] = (value >> 48) & 255;
	dest[7] = (value >> 56) & 255;
}

bool BitConvert::ToBool(unsigned char* data)
{
	return data[0];
}

short BitConvert::ToShort(unsigned char* data)
{
	short c1 = data[0];
	short c2 = data[1] << 8;
	return c1 + c2;
}

unsigned short BitConvert::ToUShort(unsigned char* data)
{
	short c1 = data[0];
	short c2 = data[1] << 8;
	return c1 + c2;
}

int BitConvert::ToInt(unsigned char* data)
{
	int c1 = data[0];
	int c2 = data[1] << 8;
	int c3 = data[2] << 16;
	int c4 = data[3] << 24;
	return c1 + c2 + c3 + c4;
}

unsigned int BitConvert::ToUInt(unsigned char* data)
{
	unsigned int c1 = (unsigned int)data[0];
	unsigned int c2 = (unsigned int)data[1] << 8;
	unsigned int c3 = (unsigned int)data[2] << 16;
	unsigned int c4 = (unsigned int)data[3] << 24;
	return c1 + c2 + c3 + c4;
}

long long BitConvert::ToLLong(unsigned char* data)
{
	long long c1 = (long long)data[0];
	long long c2 = (long long)data[1] << 8;
	long long c3 = (long long)data[2] << 16;
	long long c4 = (long long)data[3] << 24;
	long long c5 = (long long)data[4] << 32;
	long long c6 = (long long)data[5] << 40;
	long long c7 = (long long)data[6] << 48;
	long long c8 = (long long)data[7] << 56;
	return c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8;
}

unsigned long long BitConvert::ToULLong(unsigned char* data)
{
	unsigned long long c1 = (unsigned long long)data[0];
	unsigned long long c2 = (unsigned long long)data[1] << 8;
	unsigned long long c3 = (unsigned long long)data[2] << 16;
	unsigned long long c4 = (unsigned long long)data[3] << 24;
	unsigned long long c5 = (unsigned long long)data[4] << 32;
	unsigned long long c6 = (unsigned long long)data[5] << 40;
	unsigned long long c7 = (unsigned long long)data[6] << 48;
	unsigned long long c8 = (unsigned long long)data[7] << 56;
	return c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8;
}

void BitConvert::Test()
{
	cout << "Bool 类型测试：：：：：：：：：：：：：：：：：：：：：：：：：：" << endl;
	unsigned char boolData[1];
	GetBytes(boolData, true);
	cout << "打印 TRUE 的转换结果 :" << ToBool(boolData) << endl;
	GetBytes(boolData, false);
	cout << "打印 False 的转换结果 :" << ToBool(boolData) << endl;


	cout << "Short 类型测试：：：：：：：：：：：：：：：：：：：：：：：：：：" << endl;
	unsigned char shortData[2];
	GetBytesByShort(shortData, INT16_MAX);
	cout << "打印 INT8_MAX 的转换结果 :" << ToShort(shortData) << endl;
	GetBytesByShort(shortData, INT16_MIN);
	cout << "打印 INT8_MIN 的转换结果 :" << ToShort(shortData) << endl;


	cout << "unsigned Short 类型测试：：：：：：：：：：：：：：：：：：：：：：：：：：" << endl;
	unsigned char uShortData[2];
	GetBytesByUShort(uShortData, UINT16_MAX);
	cout << "打印 UINT8_MAX 的转换结果 :" << ToUShort(uShortData) << endl;


	cout << " Int 类型测试：：：：：：：：：：：：：：：：：：：：：：：：：：" << endl;
	unsigned char intData[4];
	GetBytes(intData, INT32_MAX);
	cout << "打印 INT32_MAX 的转换结果 :" << ToInt(intData) << endl;
	GetBytes(intData, INT32_MIN);
	cout << "打印 INT32_MIN 的转换结果 :" << ToInt(intData) << endl;


	cout << "unsigned Int 类型测试：：：：：：：：：：：：：：：：：：：：：：：：：：" << endl;
	unsigned char uIntData[4];
	GetBytes(uIntData, UINT32_MAX);
	cout << "打印 INT8_MAX 的转换结果 :" << ToUInt(uIntData) << endl;

	cout << " long long 类型测试：：：：：：：：：：：：：：：：：：：：：：：：：：" << endl;
	unsigned char longlongData[8];
	GetBytes(longlongData, INT64_MAX);
	cout << "打印 INT64_MAX 的转换结果 :" << ToLLong(longlongData) << endl;
	GetBytes(longlongData, INT64_MIN);
	cout << "打印 INT64_MIN 的转换结果 :" << ToLLong(longlongData) << endl;


	cout << "unsigned Long Long 类型测试：：：：：：：：：：：：：：：：：：：：：：：：：：" << endl;
	unsigned char uLongLongData[8];
	GetBytes(uLongLongData, UINT64_MAX);
	cout << "打印 UINT64_MAX 的转换结果 :" << ToULLong(uLongLongData) << endl;
}