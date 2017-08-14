//File:CodeXML
//Data:20150628
//Author:Jacky

#pragma once

#include "Code.h"

class CodeXML : public Code
{
public:
	CodeXML(const string& name);
	virtual void Execute();
};