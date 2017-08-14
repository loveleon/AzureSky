//Ê±¼äÏûºÄ

#pragma once

#include "Header.h"

class Cost
{
	CREATE_MEMBER(long, ID);
	CREATE_MEMBER(long, StationID1);
	CREATE_MEMBER(long, StationID2);
	CREATE_MEMBER(long, Time);
};

class CostManager
{

public:
	long getTime(long l);
	map<long, long> getTimes(){ return m_mapTimes; }
protected:
	map<long, long> m_mapTimes;
};