//File:CodeXML
//Data:20150628
//Author:Jacky

#include "CodeXML.h"

CodeXML::CodeXML(const string& name)
:Code(name)
{
	m_nType = CT_XML;
}

void CodeXML::Execute()
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
			if (0 == s.find("<!--"))
			{
				++m_sCount.Comment;
				bFlag = string::npos != s.find("-->") ? false : true;
			}
			else if (s.size() > 2 && s.size() - 3 == s.find("-->"))
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