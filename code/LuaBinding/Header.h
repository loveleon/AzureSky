#pragma once 

#include <map>
#include <vector>
#include <string>
#include <iostream>

extern "C"
{ // ���Ǹ�C++����, ����Ҫextern "C",  ��Ϊlua��ͷ�ļ�����C��ʽ��  
#include "lua.h"  
#include "lualib.h"  
#include "lauxlib.h"  
}