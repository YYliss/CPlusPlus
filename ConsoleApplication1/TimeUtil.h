#pragma once
#include <string>
#include <ctime>
#include <stdio.h>
using namespace std;

namespace TimeUtil {
	string FormatCurTime(int type = 1);
	string FormatTime(time_t t);
	string FormatTime2(time_t t);

	time_t GetZone();

	bool IsSameDay(time_t time1, time_t time2);
}
