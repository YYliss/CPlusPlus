
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <WinSock2.h>
#include <windows.h>
#include <iostream>
#include <event.h>
#include <map>
#include <vector>
#include <chrono>
#include <pthread.h>

#include "NetMgr.h"
#include "TimerMgr.h"
#include "TimeUtil.h"
#include "Debug.h"
#include "CommonUtil.h"
#include "ConfigMgr.h"
void Update() {
	TimerMgr::GetPtr()->OnUpdate();
}

void OnSecond() {
	cout << "秒：：" << endl;
}

void* OnFunc(void* args) {
	cout << "AA";
	return 0;
}

template<class TKey1, class TKey2, class TKey3, class TValue >
class DicKey3
{
private:
	map<TKey1,map<TKey2, map<TKey3, TValue>>> mmmp;
};


int main() {
	/*TimerMgr::GetPtr()->Start();
	TimerMgr::GetPtr()->AddTimer(OnSecond, 1000, 10);
	NetMgr::GetPtr()->Start(9527, Update);*/
	//Debug::GetPtr()->Start();
	//Debug::GetPtr()->Log("A");
	//Debug::GetPtr()->LogWarning("A");
	//Debug::GetPtr()->LogError("A");
	//
	//Debug::GetPtr()->Close();


	//map<int, map<int, map<int, int>>> mmmp;
	//mmmp[1][2][3] = 3;
	//cout << mmmp[1][2][3];

	ConfigMgr::GetPtr()->Start();
	ConfigObject* obj = ConfigMgr::GetPtr()->Get("TestConfig");
	printf("row %d\n", obj->Data.size());
	for (size_t i = 0; i < obj->Data.size(); i++)
	{
		printf("nid 第%d 个元素的值：%d\n", i, obj->Data[i]->GetUInt32("nId"));
	}
}

