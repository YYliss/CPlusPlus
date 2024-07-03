#include "CommonUtil.h"

vector<string> CommonUtil::Spilt(string src, string ssplitter)
{
	vector<string> result;
	int findOffset = 0;
	while (true)
	{
		int findindex = src.find(ssplitter, findOffset);
		if (findindex != string::npos)
		{
			string tempStr = src.substr(findOffset, findindex - findOffset);
			result.push_back(tempStr);

			findOffset = findindex + ssplitter.size();
		}
		else
		{
			break;
		}
	}
	if (findOffset < src.size())
	{
		string tempStr = src.substr(findOffset, src.size() - findOffset);
		result.push_back(tempStr);
	}
	return result;
}