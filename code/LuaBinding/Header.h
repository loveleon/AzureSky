#pragma once 

#include <map>
#include <vector>
#include <string>
#include <iostream>

extern "C"
{ // 这是个C++程序, 所以要extern "C",  因为lua的头文件都是C格式的  
#include "lua.h"  
#include "lualib.h"  
#include "lauxlib.h"  
}