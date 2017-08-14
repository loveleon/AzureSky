#include "Header.h"

#define N  7
#define NN  6
#define NNN  5

#define PrintToFile

class STLTest
{
public:
	STLTest();
	~STLTest();

	//add
	void test_add_vector();
	void test_add_vector_reserve();
	void test_add_vector_resize();
	void test_add_list();
	void test_add_map();

	//traverse 
	void test_traverse_vector_index();
	void test_traverse_vector_iter_after();
	void test_traverse_vector_iter_pre();
	void test_traverse_list_iter_after();
	void test_traverse_list_iter_pre();
	void test_traverse_map_iter_after();
	void test_traverse_map_iter_pre();

	//find
	void test_find_vector();
	void test_find_list();
	void test_find_map();
	
	//end
	void end();

	void show(string str, int len, float time);

private:
	ofstream of;
	vector<int> vecData[N];
	list<int> listData[NN];
	map<int, int> mapData[NNN];
};