#include "ByteSteam.h"


ByteSteam::ByteSteam(int capacity) {
	data = new char[capacity];
	this->capacity = capacity;
	readIndex = 0;
	writeIndex = 0;
}

ByteSteam::ByteSteam() {
	capacity = 8;
	data = new char[capacity];
	readIndex = 0;
	writeIndex = 0;
}

void ByteSteam::Zero() {
	memset(data, 0, capacity);
	readIndex = 0;
	writeIndex = 0;
}

int ByteSteam::ReadInt() {
	int n0 = data[0];
	int n1 = data[1];
	int n2 = data[2];
	int n3 = data[3];
	return (n0)
		+(n1 << 8)
		+ (n2 << 16)
		+ (n3 << 24);
}

void ByteSteam::WriteInt(int value)
{
	WriteChar((value & 0xff));
	WriteChar((value >> 8) & 0xff);
	WriteChar((value >> 16) & 0xff);
	WriteChar((value >> 24) & 0xff);
}

void ByteSteam::WriteChar(char value)
{
	data[writeIndex++] = value;
}

void ByteSteam::WriteChar(char* value, int lenght)
{
	for (size_t i = 0; i < lenght; i++)
	{
		WriteChar(value[i]);
	}
}

int ByteSteam::GetSize() 
{
	return writeIndex;
}

int ByteSteam::GetCapacity() {
	return capacity;
}

int ByteSteam::GetWritePosition() {
	return writeIndex;
}

int ByteSteam::GetReadPosition() {
	return readIndex;
}

char* ByteSteam::GetData() {
	return data;
}