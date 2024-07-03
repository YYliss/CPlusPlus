#include "TimerMgr.h"
#include <algorithm>

bool TimerSlot::Update()
{
	if (TimerMgr::GetPtr()->GetGameTime() >= triggerTime)
	{
		func();
		curTimes++;
		if (curTimes >= maxTimes)
		{
			return true;
		}
		triggerTime += microSecond;
	}
	return false;
}

TimerMgr* TimerMgr::GetPtr()
{
	static TimerMgr _ins;
	return &_ins;
}

void TimerMgr::Start()
{
	auto t = std::chrono::high_resolution_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(t);
	startTime = now_ms.time_since_epoch().count();
}

unsigned int TimerMgr::GetGameTime()
{
	auto t = std::chrono::high_resolution_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(t);
	unsigned int time = now_ms.time_since_epoch().count() - startTime;
	return time;
}

unsigned int TimerMgr::AddTimer(TimerCallBack f, unsigned int mircoSec, unsigned int nTimes /* = 1 */)
{
	unsigned int trigger = mircoSec + GetGameTime();
	TimerSlot* ts = new TimerSlot(f, mircoSec, nTimes, trigger);
	timerMap.insert(make_pair(++id, ts));
	return id;
}

void TimerMgr::CancelTimer(unsigned int id)
{
	if (timerMap.find(id) != timerMap.end())
	{
		TimerSlot* ts = timerMap.at(id);
		delete ts;
		timerMap.erase(id);
	}
}

void TimerMgr::OnUpdate()
{
	vector<int> deleteList;
	for_each(timerMap.begin(), timerMap.end(), [&deleteList](pair<int, TimerSlot*> item) {
		bool bDelete = item.second->Update();
		if (bDelete)
		{
			deleteList.push_back(item.first);
		}
	});

	for (size_t i = 0; i < deleteList.size(); i++)
	{
		unsigned int nid = deleteList.back();
		TimerSlot* ts = timerMap.at(nid);
		delete ts;
		timerMap.erase(nid);
	}
	deleteList.clear();
}