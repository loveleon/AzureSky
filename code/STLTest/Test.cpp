#include "Test.h"

STLTest::STLTest()
{
#ifdef PrintToFile
	of.open("STLTest.txt");
#endif
}

STLTest::~STLTest()
{
#ifdef PrintToFile
	of.close();
#endif
}

void STLTest::show(string str, int len, float time)
{
#ifdef PrintToFile
	of << str << " " << len << " : " << (time) << endl;
#endif

	cout << str << " " << len << " : " << (time) << endl;
}

void STLTest::test_add_vector()
{
	vecData->clear();
	for (int i = 1; i <= N; i++)
	{
		clock_t start = clock();
		int size = pow(10, i);
		for (int j = 0; j < size; j++)
		{
			vecData[i - 1].push_back(j);
		}
		clock_t end = clock();
		show("vector add", size, 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_add_vector_reserve()
{
	vecData->clear();
	for (int i = 1; i <= N; i++)
	{
		clock_t start = clock();
		int size = pow(10, i);
		vecData[i - 1].reserve(size);
		for (int j = 0; j < size; j++)
		{
			vecData[i - 1].push_back(j);
		}
		clock_t end = clock();
		show("vector add reserve", size, 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_add_vector_resize()
{
	vecData->clear();
	for (int i = 1; i <= N; i++)
	{
		clock_t start = clock();
		int size = pow(10, i);
		vecData[i - 1].resize(size);
		for (int j = 0; j < size; j++)
		{
			vecData[i - 1][j] = j;
		}
		clock_t end = clock();
		show("vector add resize", size, 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_add_list()
{
	for (int i = 1; i <= NN; i++)
	{
		clock_t start = clock();
		int size = pow(10, i);
		for (int j = 0; j < size; j++)
		{
			listData[i - 1].push_back(j);
		}
		clock_t end = clock();
		cout << "list add " << size << " : " << 0.001f * (end - start) << endl;
		show("list add", size, 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_add_map()
{
	for (int i = 1; i <= NNN; i++)
	{
		clock_t start = clock();
		int size = pow(10, i);
		for (int j = 0; j < size; j++)
		{
			mapData[i - 1][j] = j;
		}
		clock_t end = clock();
		show("map add", size, 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_traverse_vector_index()
{
	for (int i = 1; i <= N; i++)
	{
		clock_t start = clock();
		for (int j = 0; j < pow(10, i); j++)
		{
			
		}
		clock_t end = clock();
		show("vector traverse index", pow(10, i), 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_traverse_vector_iter_after()
{
	for (int i = 1; i <= N; i++)
	{
		clock_t start = clock();
		for (auto iter = vecData[i - 1].begin(); iter != vecData[i - 1].end(); iter++)
		{
			
		}
		clock_t end = clock();
		show("vector traverse iter after", pow(10, i), 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_traverse_vector_iter_pre()
{
	for (int i = 1; i <= N; i++)
	{
		clock_t start = clock();
		for (auto iter = vecData[i - 1].begin(); iter != vecData[i - 1].end(); ++iter)
		{
			
		}
		clock_t end = clock();
		show("vector traverse iter pre", pow(10, i), 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_traverse_list_iter_after()
{
	for (int i = 1; i <= NN; i++)
	{
		clock_t start = clock();
		for (auto iter = listData[i - 1].begin(); iter != listData[i - 1].end(); iter++)
		{
			
		}
		clock_t end = clock();
		show("list iter after", pow(10, i), 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_traverse_list_iter_pre()
{
	for (int i = 1; i <= NN; i++)
	{
		clock_t start = clock();
		for (auto iter = listData[i - 1].begin(); iter != listData[i - 1].end(); ++iter)
		{
			
		}
		clock_t end = clock();
		show("list iter pre", pow(10, i), 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_traverse_map_iter_after()
{
	for (int i = 1; i <= NNN; i++)
	{
		clock_t start = clock();
		for (auto iter = mapData[i - 1].begin(); iter != mapData[i - 1].end(); iter++)
		{
			
		}
		clock_t end = clock();
		show("map iter after", pow(10, i), 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_traverse_map_iter_pre()
{
	for (int i = 1; i <= NNN; i++)
	{
		clock_t start = clock();
		for (auto iter = mapData[i - 1].begin(); iter != mapData[i - 1].end(); ++iter)
		{
			
		}
		clock_t end = clock();
		show("map iter pre", pow(10, i), 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_find_vector()
{
	for (int i = 1; i <= N; i++)
	{
		clock_t start = clock();
		int find = pow(10, i) / 2;
		for (int j = 0; j < pow(10, i); j++)
		{
			if (vecData[i - 1][j] == find)
			{
				break;
			}
		}
		clock_t end = clock();
		show("vector find by index", pow(10, i), 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_find_list()
{
	for (int i = 1; i <= NN; i++)
	{
		clock_t start = clock();
		int find = pow(10, i) / 2;
		for (auto iter = listData[i - 1].begin(); iter != listData[i - 1].end(); ++iter)
		{
			if (*iter == find)
			{
				break;
			}
		}
		clock_t end = clock();
		show("list find by ++iter", pow(10, i), 0.001f * (end - start));
	}
	cout << endl;
}

void STLTest::test_find_map()
{
	for (int i = 1; i <= NNN; i++)
	{
		clock_t start = clock();
		int find = pow(10, i) / 2;
		if (auto iter = mapData[i - 1].find(find) != mapData[i - 1].end())
		{
			clock_t end = clock();
			show("map find by find", pow(10, i), 0.001f * (end - start));
		}
	}
	cout << endl;
}

void STLTest::end()
{
	cout << "总结以上测试，得出以下几条结论：" << endl;
	cout << "1、10000以下小数据量，增删改查性能vector、list、map差别不大" << endl;
	cout << "2、10000以上大数量，vector由于采用连续内存结构，构造数据是最快的，push_pack之前reserve更佳, resize更好" << endl;
	cout << "3、10000以上大数量，迭代器++iter通常时间是iter++的一半" << endl;
	cout << "4、10000以上大数量，list由于采用链表内存设计，增加和删除是最快的" << endl;
	cout << "4、10000以上大数量，map由于采用红黑二叉树设计，查找是最快的" << endl;
}


