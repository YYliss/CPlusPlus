#include "TimeUtil.h"


string TimeUtil::FormatCurTime(int type)
{
	if (type == 1)
	{
		return FormatTime(time(NULL));
	}else if (type == 2)
	{
		return FormatTime2(time(NULL));
	}
}
string TimeUtil::FormatTime(time_t t)
{
	char buf[100];
	tm* t_m = localtime(&t);
	
	sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d", t_m->tm_year + 1900, t_m->tm_mon + 1, t_m->tm_mday, t_m->tm_hour, t_m->tm_min, t_m->tm_sec);
	return buf;
}

string TimeUtil::FormatTime2(time_t t)
{
	char buf[100];
	tm* t_m = localtime(&t);

	sprintf(buf, "%d-%02d-%02d", t_m->tm_year + 1900, t_m->tm_mon + 1, t_m->tm_mday);
	return buf;
}

time_t TimeUtil::GetZone()
{
	time_t t = 0;
	tm* st = localtime(&t);
	return st->tm_hour;
}

bool TimeUtil::IsSameDay(time_t time1, time_t time2)
{
	time_t zoneSec = GetZone() * 3600;
	int day1 = (time1 + zoneSec) / 86400;
	int day2 = (time2 + zoneSec) / 86400;
	return day1 == day2;
}