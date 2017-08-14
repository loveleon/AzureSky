#include "LuaBinding.h"

LuaBinding::LuaBinding()
{ 
	L = lua_open();    
	//lua_baselibopen(L); 
	luaL_openlibs(L);  
	lua_register(L, "average", LuaBinding::average);
	luaL_dofile(L, "Calulator.lua");  
}

LuaBinding::~LuaBinding()
{ 
	lua_close(L); 
}

float LuaBinding::global(const std::string& name)
{
	lua_getglobal(L, name.c_str());
	float ret = (float)lua_tonumber(L, 1);
	lua_pop(L, 1);
	return ret;
}

float LuaBinding::fun_4_1(const std::string& fun, float a, float b, float c, float d)
{  
    lua_getglobal(L, fun.c_str());           
    lua_pushnumber(L, a);          
    lua_pushnumber(L, b); 
	lua_pushnumber(L, c);
	lua_pushnumber(L, d);
    lua_call(L, 4, 1);               
    float ret = (float)lua_tonumber(L, -1); 
    lua_pop(L, 1);                    
    return ret;  
} 

int LuaBinding::average(lua_State* L)
{
	int n = lua_gettop(L);  
	double sum = 0;   
	for (int i = 1; i <= n; i++)  
	{  
		if (!lua_isnumber(L, i))   
		{  
			lua_pushstring(L, "Incorrect argument to 'average'");  
			lua_error(L);  
		}  
		sum += lua_tonumber(L, i);  
	}  
	lua_pushnumber(L, sum / n);  
	lua_pushnumber(L, sum);   
	return 2;  
}