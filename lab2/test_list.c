#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "utils.h"
#include "list2.h"
#include "tree2.h"

void test_free_shelf()
{
  shelf_t *test_shelf = make_shelf("shelf", 1);  
  free_shelf ((void*)test_shelf);
  CU_ASSERT_TRUE(test_shelf->shelf_name == NULL);
}

void test_compare_shelf()
{
  shelf_t *test_shelf_a = make_shelf("shelf", 1);
  shelf_t *test_shelf_b = make_shelf("shelf", 1);

  int a = compare_shelf((void*)test_shelf_a, (void*)test_shelf_b);  
  CU_ASSERT_TRUE(a == 0);
  
  free_shelf(test_shelf_a);
  free_shelf(test_shelf_b);
}

void test_add_shelf()
{
  shelf_t *test_shelf_a = make_shelf("shelf", 1);
  shelf_t *test_shelf_b = make_shelf("shelf", 1);

  add_shelf((void*)test_shelf_a, (void*)test_shelf_b);
  CU_ASSERT_TRUE(test_shelf_a->amount == 2);
  
  free_shelf(test_shelf_a);
  free_shelf(test_shelf_b);
}

void test_find_shelf_in_list()
{
  shelf_t *test_shelf_a = make_shelf("shelf", 1);
  list_t * test_list = make_list_node(test_shelf_a, compare_shelf, free_shelf, add_shelf, print_shelf, copy_shelf);
  list_t * a = find_shelf_in_list(test_list, "shelf");

  CU_ASSERT_TRUE(a != NULL);

  remove_list_node(test_list, test_list);
}

void test_make_shelf()
{
  shelf_t *test_shelf_a = make_shelf("shelf", 1);
  
  CU_ASSERT_TRUE(test_shelf_a->shelf_name != NULL);

  free_shelf(test_shelf_a);
}

void test_make_list_node()
{
  shelf_t *test_shelf_a = make_shelf("shelf", 1);
  list_t * test_list = make_list_node(test_shelf_a, compare_shelf, free_shelf, add_shelf, print_shelf, copy_shelf);

  CU_ASSERT_TRUE(test_list != NULL);

  remove_list_node(test_list, test_list);
}

void test_remove_list_node()
{
  shelf_t *test_shelf_a = make_shelf("shelf", 1);
  list_t * test_list = make_list_node(test_shelf_a, compare_shelf, free_shelf, add_shelf, print_shelf, copy_shelf);
  
  list_t * removed_list = remove_list_node(test_list, test_list);

  CU_ASSERT_TRUE(removed_list == NULL); 
}

void test_remove_whole_list()
{
  shelf_t *test_shelf_a = make_shelf("shelf", 1);
  list_t * test_list = make_list_node(test_shelf_a, compare_shelf, free_shelf, add_shelf, print_shelf, copy_shelf);
  
  remove_whole_list(test_list);

  CU_ASSERT_TRUE(test_list->data == NULL); 
  
}


int main()
{
  CU_initialize_registry();
 
  CU_pSuite suite = CU_add_suite("testar", 0, 0);
 
  CU_add_test(suite,"free_shelf", test_free_shelf);
  CU_add_test(suite,"compare_shelf", test_compare_shelf);
  CU_add_test(suite,"add_shelf", test_add_shelf);
  CU_add_test(suite,"make_shelf", test_make_shelf);
  CU_add_test(suite,"make_list_node", test_make_list_node);
  CU_add_test(suite,"remove_list_node", test_remove_list_node);
  CU_add_test(suite,"remove_whole_list", test_remove_whole_list);
  
 
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
