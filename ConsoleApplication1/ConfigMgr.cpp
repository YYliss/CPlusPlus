#include "ConfigMgr.h"

ConfigRow::ConfigRow(int row)
{
	this->row = row;
}

void ConfigObject::ParseChar(vector<string> content)
{
	for (size_t i = 0; i < content.size(); i++)
	{
		char value = stoi(content[i]);
		char_array.push_back(value);
	}
}

void ConfigObject::ParseUChar(vector<string> content)
{
	for (size_t i = 0; i < content.size(); i++)
	{
		unsigned char value = stoi(content[i]);
		uchar_array.push_back(value);
	}
}
void ConfigObject::ParseShort(vector<string> content)
{
	for (size_t i = 0; i < content.size(); i++)
	{
		short value = stoi(content[i]);
		short_array.push_back(value);
	}
}

void ConfigObject::ParseUShort(vector<string> content)
{
	for (size_t i = 0; i < content.size(); i++)
	{
		unsigned short value = stoi(content[i]);
		ushort_array.push_back(value);
	}
}

void ConfigObject::ParseInt(vector<string> content)
{
	for (size_t i = 0; i < content.size(); i++)
	{
		int value = stoi(content[i]);
		int_array.push_back(value);
	}
}

void ConfigObject::ParseUInt(vector<string> content)
{
	for (size_t i = 0; i < content.size(); i++)
	{
		unsigned int value = stoi(content[i]);
		uint_array.push_back(value);
	}
}

void ConfigObject::ParseFloat(vector<string> content)
{
	for (size_t i = 0; i < content.size(); i++)
	{
		float value = stod(content[i]);
		float_array.push_back(value);
	}
}

void ConfigObject::ParseDouble(vector<string> content)
{
	for (size_t i = 0; i < content.size(); i++)
	{
		double value = stod(content[i]);
		double_array.push_back(value);
	}
}

void ConfigObject::ParseString(vector<string> content)
{
	for (size_t i = 0; i < content.size(); i++)
	{
		string_array.push_back(content[i]);
	}
}

void ConfigObject::ParseInt2Array(vector<string>content)
{
	for (size_t i = 0; i < content.size(); i++)
	{
		ConfigIntArray* arr;
		
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

		int2Array.push_back(arr);
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
			ParseUInt(alldata[i]);
		}else if (fieldType[i] == "string")
		{
			ParseString(alldata[i]);
		}
		else if (fieldType[i] == "uchar")
		{
			ParseUChar(alldata[i]);
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

		ConfigObject* obj{};
		obj->Load(temp[0]);
		allConfig.insert(make_pair(temp[1], obj));
	}
}