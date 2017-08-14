#include "Test.h"

void main()
{
	STLTest t;
	t.test_add_vector();
	t.test_add_vector_reserve();
	t.test_add_vector_resize();
	t.test_add_list();
	t.test_add_map();
	t.test_traverse_vector_index();
	t.test_traverse_vector_iter_after();
	t.test_traverse_vector_iter_pre();
	t.test_traverse_list_iter_after();
	t.test_traverse_list_iter_pre();
	t.test_traverse_map_iter_after();
	t.test_traverse_map_iter_pre();
	t.test_find_vector();
	t.test_find_list();
	t.test_find_map();
	t.end();

	char c;
	cin >> c;
}