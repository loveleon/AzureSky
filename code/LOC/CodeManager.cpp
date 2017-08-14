//File:CodeManager
//Data:20150627
//Author:Jacky

#include "CodeC.h"
#include "CodeC__.h"
#include "CodeXML.h"
#include "CodeManager.h"

mutex m;
void Foo(Code* code, Count& count)
{
	m.lock();
	code->Execute();
	code->Gather(count);
	m.unlock();
}

CodeManager* CodeManager::manager = nullptr;
CodeManager* CodeManager::Instance()
{
	if (!manager)
	{
		manager = new CodeManager;
	}
	return manager;
}

void CodeManager::Init(const string& dir)
{
	m_strDir = dir;
	vector<string> vec;
	getFile(dir, vec);
	for (auto item : vec)
	{
		Code* code = nullptr;
		int pos = item.find_last_of(".");
		if (string::npos != pos)
		{
			string ext = item.substr(pos + 1, item.size() - pos - 1);
			if (!strcmp(ext.c_str(), "h") || !strcmp(ext.c_str(), "c"))
			{
				code = new CodeC(item);
			}
			else if (!strcmp(ext.c_str(), "hpp") || !strcmp(ext.c_str(), "cpp"))
			{
				code = new CodeC__(item);
			}
			else if (!strcmp(ext.c_str(), "xml"))
			{
				code = new CodeXML(item);
			}
			//if success
			if (code)
			{
				m_mapData[item] = code;
			}
		}
	}
}

void CodeManager::Destroy()
{
	for (auto item : m_mapData)
	{
		delete item.second;
		item.second = nullptr;
	}
	m_mapData.clear();
}

void CodeManager::Execute(bool MT)
{
	clock_t start = clock();

	for (auto item : m_mapData)
	{
		Code* code = item.second;
		if (code)
		{
			if (MT)
			{
				thread t(Foo, code, m_sCount);
				t.join();
			}
			else
			{
				code->Execute();
				code->Gather(m_sCount);
			}
		}
	}

	clock_t end = clock();
	cout << "Total Cost Time : " << 0.001f * (end - start) <<"s"<< endl << endl;
}

void CodeManager::Print()
{
	cout << m_strDir << endl;
	m_sCount.Print(cout);
	for (auto item : m_mapData)
	{
		cout << item.first << endl;
		Count& count = const_cast<Count&>(item.second->getCount());
		count.Print(cout);
	}
}

void CodeManager::Save(const string& str)
{
	ofstream of(str);
	if (of.is_open())
	{
		of << m_strDir << endl;
		m_sCount.Print(of);
		for (auto item : m_mapData)
		{
			of << item.first << endl;
			Count& count = const_cast<Count&>(item.second->getCount());
			count.Print(of);
		}
		of.close();
	}
}

void CodeManager::getFile(string dir, vector<string>& vec)
{
	if (dir.empty())
	{
		return;
	}
	int size = dir.size();
	if ('\\' != dir[size - 1])
	{
		dir += "\\";
	}
	string path = dir + "*.*";

	WIN32_FIND_DATA FindData;
	HANDLE handle = ::FindFirstFileA(path.c_str(), &FindData);
	if (INVALID_HANDLE_VALUE == handle)
	{
		return;
	}
	while (::FindNextFileA(handle, &FindData))
	{
		if (strcmp(FindData.cFileName, ".") && strcmp(FindData.cFileName, ".."))
		{
			string name = string(FindData.cFileName);
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				getFile(dir + name, vec);
			}
			else
			{
				vec.push_back(dir + name);
			}
		}
	}
}