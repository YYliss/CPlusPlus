#pragma once
#include "FileUtil.h"
#include "CommonUtil.h"

#include <string>
#include <iostream>
#include <map>

using namespace std ;

class ConfigMgr;

struct ConfigIntArray {
public :
	vector<vector<int>> Data;
};

class ConfigRow {
private:
	int row;
public:
	ConfigRow(int row);
};

class ConfigObject {

	friend class ConfigMgr;
private:
	void Load(string path);

private:

	vector<char> char_array;
	vector<unsigned char> uchar_array;

	vector<short> short_array;
	vector<unsigned short> ushort_array;

	vector<unsigned int> uint_array;
	vector<int> int_array;

	vector<string> string_array;
	
	vector<float> float_array;
	vector<double> double_array;

	vector<bool> bool_array;

	vector<ConfigIntArray*> int2Array;

	void ParseChar(vector<string> content);
	void ParseUChar(vector<string> content);

	void ParseShort(vector<string> content);
	void ParseUShort(vector<string> content);

	void ParseInt(vector<string> content);
	void ParseUInt(vector<string> content);

	void ParseFloat(vector<string> content);
	void ParseDouble(vector<string> content);

	void ParseeString(vector<string> content);

	void ParseInt2Array(vector<string>content);

public:
	vector<ConfigRow> Data;
};

class ConfigMgr
{
private:
	map<string, ConfigObject*> allConfig;

public:
	static ConfigMgr* GetPtr();
	void Start();
};

