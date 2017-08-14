//File:Code
//Data:20150628
//Author:Jacky

#include "Code.h"

Code::Code(const string& name)
: m_nType(CT_NULL),
  m_strFile(name)
{
	
}

void Code::Execute()
{

}

void Code::Trim(string& str)
{
	if (str.empty())
	{
		return;
	}
	while ('\t' == str[0] || ' ' == str[0])
	{
		str.erase(str.begin());
	}
}

void Code::Gather(Count& count)
{
	count.Total += m_sCount.Total;
	count.Code += m_sCount.Code;
	count.Comment += m_sCount.Comment;
	count.Space += m_sCount.Space;
}