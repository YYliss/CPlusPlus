#pragma once
#include "FileUtil.h"
#include "CommonUtil.h"

#include <string>
#include <iostream>
#include <map>

using namespace std ;

class ConfigMgr;
class ConfigObject;

struct ConfigIntArray {
public :
	vector<vector<int>> Data;
};

class ConfigRow {
private:
	int row;
	ConfigObject* parent;
public:
	ConfigRow(int row, ConfigObject* parent);
	unsigned int GetUInt32(string name);
	string GetString(string name);
	unsigned char GetUChar(string name);
};

class ConfigData {
public:
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
};

class ConfigObject {

	friend class ConfigMgr;
	friend class ConfigRow;
private:
	void Load(string path);

public:
	vector<ConfigRow*> Data;
private:

	map<string, ConfigData*> mAllData;

	ConfigData* CreateData(string name);

	void ParseChar(string name, vector<string> content);
	void ParseUChar(string name, vector<string> content);

	void ParseShort(string name, vector<string> content);
	void ParseUShort(string name, vector<string> content);

	void ParseInt(string name, vector<string> content);
	void ParseUInt(string name, vector<string> content);

	void ParseFloat(string nanme, vector<string> content);
	void ParseDouble(string name, vector<string> content);

	void ParseString(string name, vector<string> content);

	void ParseInt2Array(string name, vector<string>content);

};

class ConfigMgr
{
private:
	map<string, ConfigObject*> allConfig;

public:
	static ConfigMgr* GetPtr();
	void Start();
	ConfigObject* Get(string name);
};

