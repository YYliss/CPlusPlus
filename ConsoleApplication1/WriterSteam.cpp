#include "WriterSteam.h"


WriterSteam::WriterSteam(int preCapactiy /* = 10 */)
{
	data = MemoryAlloc::InsPtr()->Malloc(capacity);
	capacity = preCapactiy;
	position = 0;
}

void WriterSteam::CheckCapacity(int len)
{
	if (capacity < (Size() + len))
	{
		MemoryAlloc::InsPtr()->Free(data);
		int newSize = std::max(capacity + len, capacity * 2);
		data = MemoryAlloc::InsPtr()->Malloc(newSize);
		capacity = newSize;
	}
}

void WriterSteam::WriteChar(unsigned char value)
{
	CheckCapacity(1);
	data[position++] = value;
}

void WriterSteam::WriteShort(short value)
{
	CheckCapacity(2);
	BitConvert::GetBytesByShort(data->GetData() + position, value);
	position += 2;
}

void WriterSteam::WriteUShort(unsigned short value)
{
	CheckCapacity(2);
	BitConvert::GetBytesByUShort(data->GetData() + position, value);
	position += 2;
}

void WriterSteam::WriteInt(int value)
{
	CheckCapacity(4);
	BitConvert::GetBytes(data->GetData() + position, value);
	position += 4;
}

void WriterSteam::WriteUInt(unsigned int value)
{
	CheckCapacity(4);
	BitConvert::GetBytes(data->GetData() + position, value);
	position += 4;
}

void WriterSteam::WriteLLong(long long value)
{
	CheckCapacity(8);
	BitConvert::GetBytes(data->GetData() + position, value);
	position += 8;
}

void WriterSteam::WriteULLong(unsigned long long value)
{
	CheckCapacity(8);
	BitConvert::GetBytes((*data + position), value);
	position += 8;
}

void WriterSteam::WriteFloat(float value)
{
	CheckCapacity(4);
	BitConvert::GetBytes(*data + position, value);
	position += 4;
}

void WriterSteam::WriteDouble(double value)
{
	CheckCapacity(8);
	BitConvert::GetBytes(*data + position, value);
	position += 8;
}

void WriterSteam::WriteString(string str)
{
	CheckCapacity(str.size());
	for (size_t i = 0; i < str.size(); i++)
	{
		WriteChar(str[i]);
	}
	position += str.size();
}

void WriterSteam::WriteString(unsigned* str, int len)
{
	CheckCapacity(len);
	for (size_t i = 0; i < len; i++)
	{
		WriteChar(str[i]);
	}
	position += len;
}

int WriterSteam::Size()
{
	return position + 1;
	
}