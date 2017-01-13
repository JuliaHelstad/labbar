#ifndef __LIST2_H_
#define __LIST2_H_
#include "tree2.h"

///////////////////////////funktioner
/**Frees a shelf.
*\param a is the shelf you want to remove.
*/
void free_shelf (void *a);

/**Prints out shelf
*\param a is the shelf you want to print out.
*/
void print_shelf (void *a);

/**Compares shelfs
*\param a is the first shelf you want to compare.
*\param b is the second shelf you want to compare.
*\return the number as the function strcmp would.
*/
int compare_shelf (void *a, void *b);

/**Adds amount to one shelf
*\param a is the shelf you want to add amount to.
*\param b is the shelf you want to add it's amount to the first shelf.
*/
void add_shelf (void *a, void *b);

/**Prints out a list
*\param list is the list you want to print out.
*/
void list_print(list_t* list);

/**Makes a copy of a shelf
*\param data is the shelf you want to copy.
*/
void *copy_shelf(void *data);

/**Finds a shelf in the tree.
*\param root is the tree you want to seek in.
*\param shelf_name is the name of the shelf you want to find.
*\return the found goods or NULL.
*/
goods_t *find_shelf_in_tree(tree_t *root, char *shelf_name);

/**Finds a shelf in a list
*\param list is the list you want to seek in.
*\param name is the name of the shlef you want to find.
*\return the list node with the shelf or NULL.
*/
list_t *find_shelf_in_list(list_t *list, char *name);

/**Inserts a list node
*\param goods is the goods you want to add a new list node to.
*\param new_node is the list node you want to add.
*\return the goods with the added list node.
*/
goods_t *list_node_insert(goods_t *goods, list_t *new_node);

/**Creates a new shelf
*\param shelf_name is the name of the new shelf.
*\param amount is the amount of the thing you want to add.
*\return the new shelf.
*/
shelf_t *make_shelf (char *shelf_name, int amount);

/**Creates a new list node
*\param data is the shelf of the new list node.
*\param compare is the compare function.
*\param free_function is the free function.
*\param add is the add function.
*\param print is the print function.
*\param copy is the copy function.
*\return the new node.
*/
list_t *make_list_node(shelf_t* data, cmp_t compare, free_t free_function, add_t add, print_t print, copy_t copy);

/**Makes a copy of a list
*\param list is the list you want to make a copy of.
*\return the copied list.
*/
list_t *copy_list(list_t *list);

/**Removes a list node
*\param list is the list you want to remove a list node from.
*\param node_to_remove is the list node you want to remove.
*\return the list with the removed list node.
*/
list_t *remove_list_node (list_t *list, list_t *node_to_remove);

/**Removes a whole list
*\param list is the list you want to remove.
*/
void remove_whole_list(list_t *list);
  
#endif
