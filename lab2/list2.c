#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "list2.h"

///////////////////////////print_shelf
void print_shelf (void *a)
{
  shelf_t *shelf = (shelf_t *)a;

  printf("Hyllplan: %s, Antal: %d \n", shelf->shelf_name, shelf->amount);
}

///////////////////////////free_shelf
void free_shelf (void *a)
{
  shelf_t *shelf = (shelf_t *)a;
 
  free(shelf->shelf_name);
  free(shelf);
  shelf = NULL;
}

///////////////////////////compare_shelf
int compare_shelf (void *a, void *b)
{
  if(a == NULL && b == NULL) return 0;

  if(a == NULL) return -1;

  if(b == NULL) return 1;
  
  shelf_t *shelf_a = (shelf_t *)a;
  shelf_t *shelf_b = (shelf_t *)b;

  return strcmp(shelf_a->shelf_name, shelf_b->shelf_name);
}

///////////////////////////add_shelf
void add_shelf (void *a, void *b)
{
  if(a == NULL || b == NULL) return;
  
  shelf_t *shelf_a = (shelf_t *)a;
  shelf_t *shelf_b = (shelf_t *)b;

  shelf_a->amount = shelf_a->amount + shelf_b->amount;
}

///////////////////////////list_print
void list_print(list_t* list)
{
  list_t* cursor = list;
  while(cursor)
    {
      cursor->print(cursor->data);
      cursor = cursor->next;
    }
}

///////////////////////////copy_shelf
void *copy_shelf(void *data)
{
  shelf_t *shelf = (shelf_t*)data;

  return make_shelf(shelf->shelf_name, shelf->amount);
}

///////////////////////////find_shelf_in_list
list_t *find_shelf_in_list(list_t *list, char *name)
{
  if (list == NULL)
    {
      return NULL;
    }

  list_t * cursor = list;
  while (cursor != NULL)
    {
      shelf_t * shelf = (shelf_t *)cursor->data;
      if (strcmp(shelf->shelf_name, name) == 0) return cursor;
      cursor = cursor->next;
    }
  return NULL;
}
///////////////////////////find_shelf_in_tree
goods_t *find_shelf_in_tree(tree_t *root, char *shelf_name)
{
  if (root == NULL || shelf_name == NULL)
    {
      return NULL;
    }

  goods_t * goods = (goods_t *)root->data;
  list_t *list = find_shelf_in_list(goods->goods_list, shelf_name);
  if (list != NULL) return goods;

  goods = find_shelf_in_tree(root->left, shelf_name);
  if (goods != NULL) return goods;

  return find_shelf_in_tree(root->right, shelf_name);
}

///////////////////////////list_node_insert
goods_t *list_node_insert(goods_t *goods, list_t *new_node)
{
  if (goods == NULL || new_node == NULL)
    {
      return NULL;
    }
  
  list_t * next_node = goods->goods_list;
  list_t * previous_node = NULL;	
  while (next_node != NULL)
    {
      if (next_node->compare(next_node->data, new_node->data) == 0)
	{
	  new_node->add(next_node->data, new_node->data); 
	  return goods;
	}
      previous_node = next_node;
      next_node = next_node->next;

    }
  if(previous_node == NULL)
    {
      goods->goods_list = new_node;
      return goods;
    }
  else
    {
      previous_node->next = new_node;
      return goods;
    }
}

///////////////////////////make_shelf
shelf_t *make_shelf (char *shelf_name, int amount)
{
  shelf_t *shelf = malloc(sizeof(shelf_t));

  char* p_shelf_name = malloc(255);
  strcpy(p_shelf_name, shelf_name);
  
  shelf->shelf_name = p_shelf_name;
  shelf->amount = amount;

  return shelf;
}

///////////////////////////make_list_node
list_t *make_list_node(shelf_t *data, cmp_t compare, free_t free_function, add_t add, print_t print, copy_t copy)
{
  list_t* list = malloc(sizeof(list_t));
  
  if (!data)
    {
      printf("\nSUPERFEL på list!\n");
      return NULL;
    }

  list->data = data; 
  list->add = add;
  list->print = print;
  list->compare = compare;
  list->free_function = free_function;
  list->copy = copy;	
  
  list->next = NULL;
  
  return list;
}

///////////////////////////copy_list
list_t *copy_list(list_t *list)
{
  if (!list) 
    {
      return list;
    }
  
  list_t* cursor = list;
  list_t *first = NULL;
  list_t *last = NULL;

  while (cursor != NULL) 
    {
      void *data = cursor->copy(cursor->data);
      list_t * new_node = make_list_node(data, cursor->compare, cursor->free_function, cursor->add, cursor->print, cursor->copy);
      if(first == NULL)
	{
	  first = new_node;
	}
      else
	{
	  last->next = new_node;	  
	}
      last = new_node;
      cursor = cursor->next;
    }
  return first; 
}

///////////////////////////remove_list_node
list_t *remove_list_node (list_t *list, list_t *node_to_remove)
{ 
  if(list == NULL || node_to_remove == NULL)
    {
      return list;
    }
 
  list_t *cursor = list;
  list_t *previous = NULL;

  while (cursor)
    {
      if (cursor->compare(cursor->data, node_to_remove->data) == 0)
	{
	  if(previous == NULL)
	    {
	      list = cursor->next;
	    }
	  else
	    {
	      previous->next = cursor->next;
	    }
	  cursor->free_function(cursor->data);
	  free(cursor);	    
	  return list;	  
	}
	  previous = cursor;
       cursor = cursor->next;
    }
  return list;
}

///////////////////////////remove_whole_list
void remove_whole_list(list_t *list)
{
  list_t *cursor = list;
  while (cursor != NULL)
    {
      list_t *temp = cursor;
      cursor = cursor->next;
      list = remove_list_node(list, temp);
    }
  free(list);
}
