#pragma once

#include <queue>
using namespace std;

#define INIT_MEMORY_COUNT 2

class MemoryBuff
{
private:
	unsigned char* data;
	int size;

public:
	MemoryBuff(int size);
	~MemoryBuff();
	unsigned char* GetData();
	int Size();

	unsigned char& operator[] (int index);
	unsigned char* operator+ (int index);
};

template<int SIZE>
class MemoryPool {
private:
	queue<MemoryBuff*> memList;
public:
	MemoryPool();
	MemoryBuff* Take();
	void Put(MemoryBuff* buf);
};

class MemoryAlloc
{

private:
	MemoryPool<2> pool_2Bytes;
	MemoryPool<4> pool_4Bytes;
	MemoryPool<8> pool_8Bytes;
	MemoryPool<16> pool_16Bytes;
	MemoryPool<32> pool_32Bytes;
	MemoryPool<64> pool_64Bytes;
	MemoryPool<128> pool_128Bytes;
	MemoryPool<256> pool_256Bytes;
	MemoryPool<512> pool_512Bytes;
	MemoryPool<1024> pool_1024Bytes;
	MemoryPool<2048> pool_2048Bytes;

public:
	static MemoryAlloc* InsPtr();

	MemoryBuff* Malloc(int size);
	void Free(MemoryBuff* buf);
};

