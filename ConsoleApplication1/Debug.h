#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include "TimeUtil.h"
#include <algorithm>
using namespace std;

enum class LogLevel
{
	eNoraml,
	eWarning,
	eError,
};


class Debug
{
private:
	vector<string> writeList;
	ofstream outFile;
	time_t lastOpenTime = 0;
	thread* runThread;
	mutex runMutex;
	bool exitRun = false;
public:

	static Debug* GetPtr();

	void Start();
	void Close();

	void Log(string str);
	void LogWarning(string str);
	void LogError(string str);

	string GetFileName(string str);

private:
	void DoWrite(LogLevel lv, string str);
	void PushWriteList(string str);
	void WriteToFile(string str);

	void Run();
};

