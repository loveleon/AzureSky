//File:CodeC__
//Data:20150628
//Author:Jacky

#include "CodeC__.h"

CodeC__::CodeC__(const string& name)
:Code(name)
{
	m_nType = CT_C__;
}

void CodeC__::Execute()
{
	ifstream in(m_strFile);
	bool bFlag = false;
	string s;
	while (getline(in, s))
	{
		Trim(s);
		if (s.empty())
		{
			++(m_sCount.Space);
		}
		else
		{
			if (0 == s.find("//"))
			{
				++m_sCount.Comment;
			}
			else if (0 == s.find("/*"))
			{
				++m_sCount.Comment;
				bFlag = string::npos != s.find("*/") ? false : true;
			}
			else if (s.size() > 1 && s.size() - 2 == s.find("*/"))
			{
				++m_sCount.Comment;
				bFlag = false;
			}
			else
			{
				bFlag ? ++m_sCount.Comment : ++m_sCount.Code;
			}
		}
	}
	m_sCount.Total = m_sCount.Code + m_sCount.Comment + m_sCount.Space;
	in.close();
}