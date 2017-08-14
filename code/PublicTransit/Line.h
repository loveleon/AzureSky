//ÏßÂ·
#pragma once

#include "Header.h"

class Station;
class Line
{
	CREATE_MEMBER(long, ID);
	CREATE_MEMBER(string, Name);
public:
	list<int>& getStations(){ return m_listStations; }
protected:
	list<int> m_listStations;
};