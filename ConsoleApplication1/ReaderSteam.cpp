#include "ReaderSteam.h"

ReaderSteam::ReaderSteam(unsigned char* src) {
	size = sizeof(src);
	memcpy(data, src, size);
}

unsigned char ReaderSteam::ReadChar()
{
	return data[postion++];
}

unsigned char ReaderSteam::PeekChar()
{
	return data[postion];
}

short ReaderSteam::ReadShort() {
	short value = BitConvert::ToShort(data + postion);
	postion += 2;
	return value;
}

short ReaderSteam::PeekShort()
{
	short value = BitConvert::ToShort(data + postion);
	return value;
}

unsigned short ReaderSteam::ReadUShort()
{
	unsigned short value = BitConvert::ToUShort(data + postion);
	postion += 2;
	return value;
}

unsigned short ReaderSteam::PeekUShort()
{
	unsigned short value = BitConvert::ToUShort(data + postion);
	return value;
}

int ReaderSteam::ReadInt()
{
	int value = BitConvert::ToInt(data + postion);
	postion += 4;
	return value;
}

int ReaderSteam::PeekInt()
{
	int value = BitConvert::ToInt(data);
	return value;
}

unsigned int ReaderSteam::ReadUInt()
{
	unsigned int value = BitConvert::ToUInt(data + postion);
	postion += 4;
	return value;
}
unsigned int ReaderSteam::PeekUInt()
{
	unsigned int value = BitConvert::ToUInt(data + postion);
	return value;
}

long long ReaderSteam::ReadLLong()
{
	long long value = BitConvert::ToLLong(data + postion);
	postion += 8;
	return value;
}

long long ReaderSteam::PeekLLong()
{
	long long value = BitConvert::ToLLong(data + postion);
	return value;
}

unsigned long long ReaderSteam::ReadULLong() {

	unsigned long long value = BitConvert::ToULLong(data + postion);
	postion += 8;
	return value;
}

unsigned long long ReaderSteam::PeekULLong()
{
	unsigned long long value = BitConvert::ToULLong(data + postion);
	return value;
}

string ReaderSteam::ReadString(int len)
{
	string str(data + postion, data + postion + len);
	postion += len;
	return str;
}

string ReaderSteam::PeekString(int len)
{
	string str(data + postion, data + postion + len);
	return str;
}

float ReaderSteam::ReadFloat()
{
	float value = BitConvert::ToFloat(data + postion);
	postion += 4;
	return value;
}

float ReaderSteam::PeekFloat() {
	float value = BitConvert::ToFloat(data + postion);
	return value;
}

double ReaderSteam::ReadDouble()
{
	double value = BitConvert::ToDouble(data + postion);
	postion += 8;
	return value;
}

double ReaderSteam::PeekDouble()
{
	double value = BitConvert::ToDouble(data + postion);
	return value;
}

int ReaderSteam::Size() {
	return size;
}