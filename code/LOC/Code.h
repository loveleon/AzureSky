//File:Code
//Data:20150628
//Author:Jacky

#pragma once

#include "Header.h"

enum CodeType
{
	CT_NULL,
	CT_C,
	CT_C__,			//C++
	CT_XML,
	//CT_JAVA,
	//CT_JS,
	//CT_PHP,
	//CT_HTML,
	//CT_PYTHON,
};

enum LineType
{
	LT_NULL,
	LT_CODE,
	LT_SPACE,
	LT_COMMENT,
};

struct Count
{
	Count()
	{
		Total = 0;
		Code = 0;
		Space = 0;
		Comment = 0;
	}
	void Print(ostream& os)
	{
		os << "Total : " << Total << endl;
		os << "Code : " << Code << endl;
		os << "Space : " << Space << endl;
		os << "Comment : " << Comment << endl;
		os << endl;
	}
	int Total;
	int Code;
	int Space;
	int Comment;
};

class Code
{
public:
	Code(const string& name);
	virtual void Execute();

public:
	void Gather(Count& count);
	const Count& getCount(){ return m_sCount; }
	
protected:
	void Trim(string& str);

protected:
	int m_nType;
	Count m_sCount;
	string m_strFile;
};