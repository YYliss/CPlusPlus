#include "ConfigMgr.h"

ConfigRow::ConfigRow(int row, ConfigObject* parent)
{
	this->row = row;
	this->parent = parent;
}

unsigned int ConfigRow::GetUInt32(string name)
{
	if (parent->mAllData.find(name) != parent->mAllData.end())
	{
		ConfigData* data = parent->mAllData.at(name);
		return data->uint_array[row];
	}
	return 0;
}

string ConfigRow::GetString(string name)
{
	if (parent->mAllData.find(name) != parent->mAllData.end())
	{
		return parent->mAllData.at(name)->string_array[row];
	}
	return "";
}

unsigned char ConfigRow::GetUChar(string name)
{
	if (parent->mAllData.find(name) != parent->mAllData.end())
	{
		return parent->mAllData.at(name)->uchar_array[row];
	}
	return 0;
}

ConfigData* ConfigObject::CreateData(string name)
{
	ConfigData* data = new ConfigData();
	mAllData[name] = data;
	return data;
}
void ConfigObject::ParseChar(string name, vector<string> content)
{
	ConfigData* data = CreateData(name);
	for (size_t i = 0; i < content.size(); i++)
	{
		char value = stoi(content[i]);
		data->char_array.push_back(value);
	}
}

void ConfigObject::ParseUChar(string name, vector<string> content)
{
	ConfigData* data = CreateData(name);
	for (size_t i = 0; i < content.size(); i++)
	{
		unsigned char value = stoi(content[i]);
		data->int_array.push_back(value);
	}
}
void ConfigObject::ParseShort(string name, vector<string> content)
{
	ConfigData* data = CreateData(name);
	for (size_t i = 0; i < content.size(); i++)
	{
		short value = stoi(content[i]);
		data->short_array.push_back(value);
	}
}

void ConfigObject::ParseUShort(string name, vector<string> content)
{
	ConfigData* data = CreateData(name);
	for (size_t i = 0; i < content.size(); i++)
	{
		unsigned short value = stoi(content[i]);
		data->ushort_array.push_back(value);
	}
}

void ConfigObject::ParseInt(string name, vector<string> content)
{
	ConfigData* data = CreateData(name);
	for (size_t i = 0; i < content.size(); i++)
	{
		int value = stoi(content[i]);
		data->int_array.push_back(value);
	}
}

void ConfigObject::ParseUInt(string name, vector<string> content)
{
	printf("开始插入 名字:%s\ns", name);
	ConfigData* data = CreateData(name);
	for (size_t i = 0; i < content.size(); i++)
	{
		unsigned int value = stoi(content[i]);
		data->uint_array.push_back(value);
		printf("插入uint %d\n", value);
	}
}

void ConfigObject::ParseFloat(string name, vector<string> content)
{
	ConfigData* data = CreateData(name);
	for (size_t i = 0; i < content.size(); i++)
	{
		float value = stod(content[i]);
		data->float_array.push_back(value);
	}
}

void ConfigObject::ParseDouble(string name, vector<string> content)
{
	ConfigData* data = CreateData(name);
	for (size_t i = 0; i < content.size(); i++)
	{
		double value = stod(content[i]);
		data->double_array.push_back(value);
	}
}

void ConfigObject::ParseString(string name, vector<string> content)
{
	ConfigData* data = CreateData(name);
	for (size_t i = 0; i < content.size(); i++)
	{
		data->string_array.push_back(content[i]);
	}
}

void ConfigObject::ParseInt2Array(string name, vector<string>content)
{
	ConfigData* data = CreateData(name);
	for (size_t i = 0; i < content.size(); i++)
	{
		ConfigIntArray* arr = new ConfigIntArray();
		
		vector<string> temp1 = CommonUtil::Spilt(content[i], ";");

		for (size_t j = 0; j < temp1.size(); j++)
		{
			vector<string>temp2 = CommonUtil::Spilt(temp1[j], "_");

			vector<int> intarr;
			for (size_t j2 = 0; j2 < temp2.size(); j2++)
			{
				int value = stoi(temp2[j2]);
				intarr.push_back(value);
			}
			arr->Data.push_back(intarr);
		}
		data->int2Array.push_back(arr);
	}
}

void ConfigObject::Load(string path)
{
	
	vector<string> allLine = FileUtil::ReadAllText(path);

	vector<string> fieldName;
	vector<string> fieldType;

	map<int, bool> vaildCol;

	vector<vector<string>> alldata;

	for (size_t i = 0; i < allLine.size(); i++)
	{
		vector<string> lineCont = CommonUtil::Spilt(allLine[i], ",");
		if (lineCont[0].find("//") == lineCont[0].npos)
		{
			if (i == 0)
			{
				for (size_t j = 0; j < lineCont.size(); j++)
				{
					if (lineCont[j].find("//") == lineCont[j].npos)
					{
						fieldName.push_back(lineCont[j]);
						vaildCol.insert(make_pair(j, true));

						vector<string> temp;
						alldata.push_back(temp);
					}
				}
			}
			else if(i == 1)
			{
				for (size_t j = 0; j < lineCont.size(); j++)
				{
					if (vaildCol.find(j) != vaildCol.end())
					{
						fieldType.push_back(lineCont[j]);
					}
				}
			}
			else
			{
				ConfigRow* row = new ConfigRow(i- 2, this);
				Data.push_back(row);
				int count = 0;
				for (size_t j = 0; j < lineCont.size(); j++)
				{
					if (vaildCol.find(j) != vaildCol.end())
					{
						alldata[count++].push_back(lineCont[j]);
					}
				}
			}
		}
	}

	for (size_t i = 0; i < alldata.size(); i++)
	{
		
		if (fieldType[i] == "uint32")
		{
			cout << "UInt32;";
			ParseUInt(fieldName[i], alldata[i]);
		}else if (fieldType[i] == "string")
		{
			ParseString(fieldName[i], alldata[i]);
			cout << "string;";
		}
		else if (fieldType[i] == "uchar")
		{
			ParseUChar(fieldName[i], alldata[i]);
			cout << "uchar;";
		}
	}
}

ConfigMgr* ConfigMgr::GetPtr()
{
	static ConfigMgr _ins;
	return &_ins;
}

void ConfigMgr::Start()
{
	vector<string> define = FileUtil::ReadAllText("ConfigDefine.txt");
	for (size_t i = 0; i < define.size(); i++)
	{
		vector<string> temp = CommonUtil::Spilt(define[i], "|");
		cout << temp[0] << "|" << temp[1]<<endl;

		ConfigObject* obj = new ConfigObject();
		obj->Load(temp[0]);
		allConfig.insert(make_pair(temp[1], obj));
	}
}

ConfigObject* ConfigMgr::Get(string name)
{
	return allConfig.at(name);
}