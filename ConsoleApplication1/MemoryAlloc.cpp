#include "MemoryAlloc.h"

MemoryBuff::MemoryBuff(int size)
{
	data = new unsigned char[size];
	this->size = size;
}
MemoryBuff::~MemoryBuff() {
	delete[] data;
	size = 0;
}

unsigned char* MemoryBuff::GetData() {
	return data;
}

int MemoryBuff::Size() {
	return size;
}

unsigned char& MemoryBuff:: operator[](int index)
{
	return data[index];
}
unsigned char* MemoryBuff::operator+(int value)
{
	return (data + value);
}

template<int SIZE>
MemoryPool<SIZE>::MemoryPool()
{
	for (size_t i = 0; i < INIT_MEMORY_COUNT; i++)
	{
		MemoryBuff* buff = new MemoryBuff(SIZE);
		memList.push(buff);
	}
}

template<int SIZE>
MemoryBuff* MemoryPool<SIZE>::Take() {

	if (memList.size() > 0)
	{
		return memList.back();
	}
	else
	{
		MemoryBuff* buff = new MemoryBuff(SIZE);
		return buff;
	}
	
}
template<int SIZE>
void MemoryPool<SIZE>::Put(MemoryBuff* buf)
{
	memList.push(buf);
}

MemoryAlloc* MemoryAlloc::InsPtr()
{
	static MemoryAlloc _ins;
	return &_ins;
}

MemoryBuff* MemoryAlloc::Malloc(int size)
{
	if (size <= 2)
		return pool_2Bytes.Take();
	else if (size <= 4)
		return pool_4Bytes.Take();
	else if (size <= 8)
		return pool_8Bytes.Take();
	else if (size <= 16)
		return pool_16Bytes.Take();
	else if (size <= 32)
		return pool_32Bytes.Take();
	else if (size <= 64)
		return pool_64Bytes.Take();
	else if (size <= 128)
		return pool_128Bytes.Take();
	else if (size <= 256)
		return pool_256Bytes.Take();
	else if (size <= 512)
		return pool_512Bytes.Take();
	else if (size <= 1024)
		return pool_1024Bytes.Take();
	else if (size <= 2048)
		return pool_2048Bytes.Take();
	else
	{
		printf("需要分配的内存太多");
	}
	return pool_2048Bytes.Take();
}

void MemoryAlloc::Free(MemoryBuff* buf)
{
	int size = 0;
	if (size <= 2)
		pool_2Bytes.Put(buf);
	else if (size <= 4)
		pool_4Bytes.Put(buf);
	else if (size <= 8)
		pool_8Bytes.Put(buf);
	else if (size <= 16)
		pool_16Bytes.Put(buf);
	else if (size <= 32)
		pool_32Bytes.Put(buf);
	else if (size <= 64)
		pool_64Bytes.Put(buf);
	else if (size <= 128)
		pool_128Bytes.Put(buf);
	else if (size <= 256)
		pool_256Bytes.Put(buf);
	else if (size <= 512)
		pool_512Bytes.Put(buf);
	else if (size <= 1024)
		pool_1024Bytes.Put(buf);
	else if (size <= 2048)
		pool_2048Bytes.Put(buf);
	else
	{
		printf("需要分配的内存太多");
	}
}