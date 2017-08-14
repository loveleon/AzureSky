//ÇøÓò·¶Î§
#pragma once

#include "Header.h"

class Spot;
class Area
{
	CREATE_MEMBER(long, ID);
	CREATE_MEMBER(float, Top);
	CREATE_MEMBER(float, Bottom);
	CREATE_MEMBER(float, Left); 
	CREATE_MEMBER(float, Right);

public:
	set<int>& getSpots(){ return m_setSpots; }

protected:
	set<int> m_setSpots;
};