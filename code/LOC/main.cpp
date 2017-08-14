//File:Main
//Data:20150628
//Author:Jacky

/*TODO:
1¡¢add threadpool*/

#include "CodeManager.h"

int main(int argc, char* argv[])
{
	//No1 is exe  No2 is param dir
	assert(2 == argc);

	std::string dir = argv[1];
	CodeManager::Instance()->Init(dir);
	CodeManager::Instance()->Execute();
	CodeManager::Instance()->Print();
	CodeManager::Instance()->Save();
	CodeManager::Instance()->Destroy();

	getchar();
	return 1;
}