#pragma once

#include "Header.h"

//地点
class Spot
{	
	//编号
	CREATE_MEMBER(long, ID);
	//名字
	CREATE_MEMBER(string, Name);
	//纬度
	CREATE_MEMBER(float, Latitude);
	//经度
	CREATE_MEMBER(float, Longitude);
};