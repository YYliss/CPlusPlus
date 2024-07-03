#include "FileUtil.h"

vector<string> FileUtil::ReadAllText(string path)
{
	vector<string> result;

	ifstream f(path);

	if (f.is_open())
	{
		while (!f.eof())
		{
			char buf[1204] = { 0 };
			f.getline(buf, 1024);
			if (strlen(buf) > 0)
			{
				result.push_back(buf);
			}
		}
	}
	return result;
}