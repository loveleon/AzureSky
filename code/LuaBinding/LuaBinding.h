#pragma once

#include "Header.h"

class LuaBinding
{
public: 
	LuaBinding();
	~LuaBinding();

public:
	lua_State* L; 

	//C++��ȡLua�е�ȫ�ֱ���
	float global(const std::string& name);
	
	//C++����Lua�еķ���
	float fun_4_1(const std::string& fun, float a, float b, float c, float d);

	//Lua����C++�еķ���
	static int average(lua_State *L) ;
};