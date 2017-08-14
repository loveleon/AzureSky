#pragma once

#include "Header.h"

class LuaBinding
{
public: 
	LuaBinding();
	~LuaBinding();

public:
	lua_State* L; 

	//C++获取Lua中的全局变量
	float global(const std::string& name);
	
	//C++调用Lua中的方法
	float fun_4_1(const std::string& fun, float a, float b, float c, float d);

	//Lua调用C++中的方法
	static int average(lua_State *L) ;
};