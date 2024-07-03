#include "Debug.h"

Debug* Debug::GetPtr()
{
	static Debug _ins;
	return &_ins;
}

void Debug::Start()
{
	runThread = new thread([this]() {
		Run();
	});
}

void Debug::Close() {
	if (outFile.is_open())
	{
		outFile.close();
	}
	runMutex.lock();
	exitRun = true;
	runMutex.unlock();
	runThread->join();

}

void Debug::Log(string str)
{
	DoWrite(LogLevel::eNoraml, str);
}

void Debug::LogWarning(string str)
{
	DoWrite(LogLevel::eWarning, str);
}

void Debug::LogError(string str)
{
	DoWrite(LogLevel::eError, str);
}

void Debug::DoWrite(LogLevel lv, string str)
{
	string result = TimeUtil::FormatCurTime() + " " + str + "\n";
	switch (lv)
	{
	case LogLevel::eNoraml:
		printf("\033[0m %s", result.c_str());
		break;
	case LogLevel::eWarning:
		printf("\033[1;33;40m %s \033[0m", result.c_str());
		break;
	case LogLevel::eError:
		printf("\033[1;31;40m %s \033[0m", result.c_str());
		break;
	default:
		break;
	}
}

void Debug::PushWriteList(string str)
{
	runMutex.lock();
	writeList.push_back(str);
	runMutex.unlock();
}

string Debug::GetFileName(string str)
{
	int indx = str.find_last_of('\\');
	return str.substr(indx + 1, str.size() - indx - 1);
}

void Debug::WriteToFile(string str)
{
	if (lastOpenTime == 0 || !TimeUtil::IsSameDay(lastOpenTime, time(NULL)))
	{
		if (outFile.is_open())
		{
			outFile.close();
		}
		string timeStr = TimeUtil::FormatCurTime(2);
		outFile.open(timeStr, ios::app);
	}

	outFile.write(str.c_str(), str.size());
	outFile.flush();
}

void Debug::Run() {
	while (true)
	{
		this_thread::sleep_for(std::chrono::milliseconds(10));
		if (writeList.size() > 0)
		{
			runMutex.lock();
			vector<string>temp;
			temp.swap(writeList);
			runMutex.unlock();
			
			for_each(temp.begin(), temp.end(), [this](string str) {
				WriteToFile(str);
			});
			temp.clear();
		}
		if (exitRun)
		{
			cout << "Debug Exit";
			return;
		}
	}
}