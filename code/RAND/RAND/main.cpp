//伪随机数生成器

#include <time.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <windows.h> 

using namespace std;

//RAND.exe 100 10
void main(int argc, char *argv[])
{
	int size = (1 < argc ? atoi(argv[1]) : 100);
	int group = (2 < argc ? atoi(argv[2]) : 10);
	
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	char c[MAX_PATH];
	sprintf_s(c, MAX_PATH, "%4d%02d%02d%02d%02d%02d.txt", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
	std::ofstream ofs(c);
	if (!ofs.is_open())
	{
		return;
	}

	srand((int)time(0));
	for (int j = 0; j < group; j++)
	{
		vector<int> vec;
		vec.resize(size);
		for (int i = 0; i < size; i++)
		{
			vec[i] = i;
		}

		for (int i = size - 1; i > 0; i--)
		{
			int index = rand() % i;
			int temp = vec[i];
			vec[i] = vec[index];
			vec[index] = temp;
		}

		for (int i = 0; i < size; i++)
		{
			ofs << vec[i] << ",";
		}

		ofs << std::endl;
	}

	ofs.close();
}