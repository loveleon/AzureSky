#include "LuaBinding.h"

void main()
{
	LuaBinding lua;

	float sum = lua.global("sum");
	float avg = lua.global("avg");
	float ret = lua.fun_4_1("pre2after", 5000, 3500, 0.03, 0);

	char c = ' ';
	putchar(c);

}