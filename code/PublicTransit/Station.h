//Õ¾µã
#pragma once

#include "Spot.h"

class Station : public Spot
{
public:
	set<int> getLines(){ return m_setLines; }
protected:
	set<int> m_setLines;
};