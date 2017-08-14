//File:CodeManager
//Data:20150627
//Author:Jacky

#pragma once

#include "Code.h"

class CodeManager
{
public:
	static CodeManager* Instance();
	void Init(const string& dir);
	void Execute(bool MT = false);
	void Destroy();
	void Print();
	void Save(const string& str = "Result.txt");
	
protected:
	void getFile(string dir, vector<string>& vec);

private:
	static CodeManager* manager;
	map<string, Code*> m_mapData;
	Count m_sCount;
	string m_strDir;
};