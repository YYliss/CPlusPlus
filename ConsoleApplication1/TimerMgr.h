#pragma once
#include <time.h>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <chrono>
using namespace std;
typedef void(*TimerCallBack)();

class TimerSlot {
private:
	TimerCallBack func;
	unsigned int microSecond;//间隔多少毫秒调用
	unsigned int maxTimes;//最大调用次数
	unsigned int curTimes;//当前调用次数
	unsigned int triggerTime;//下次触发时间点;

public:
	TimerSlot(TimerCallBack f, unsigned int microSecond, unsigned int maxTimes, unsigned int triggerTime)
	{
		curTimes = 0;
		func = f;
		this->maxTimes = maxTimes;
		this->microSecond = microSecond;
		this->triggerTime = triggerTime;
	}
	bool Update();

};

class TimerMgr
{
private:
	map<int, TimerSlot*> timerMap;
	unsigned int id;
	unsigned long long startTime;
public:

	void Start();
	unsigned int GetGameTime();

	unsigned int AddTimer(TimerCallBack f, unsigned int mircoSec, unsigned int nTimes = 1);

	void CancelTimer(unsigned int id);

	void OnUpdate();

	static TimerMgr* GetPtr();
};

