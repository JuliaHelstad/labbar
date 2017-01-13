#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "tree2.h"
#include "list2.h"


///////////////////////////make_item
goods_t* make_goods(char *name, char *description, int price)
{
  goods_t* pointer = malloc(sizeof(goods_t));
  if (!name)
    {
      printf("\nSUPERFEL på namn!\n");
      return NULL;
    }

  if (!description)
    {
      printf("\nSUPERFEL på desc!\n");
      return NULL;
    }

  char* p_name = malloc(255);
  strcpy(p_name, name);

  char* p_description = malloc(255);
  strcpy(p_description, description);

  pointer->name = p_name;
  pointer->description = p_description;
  pointer->price = price;
  pointer->goods_list = NULL;

  return pointer;
}


int main ()
{
  goods_t *root_node = make_goods("root","mitten",1);
  tree_t *root = tree_new(root_node, compare_goods, free_goods, print_goods);

  for(int i = 0; i < 1000000; i++)
    {
      char test[2];
      test[0] = (char)i;
      test[1] = '\n';
      goods_t *node_a = make_goods(test,"någonstans", 1);
      tree_insert(root, node_a, compare_goods, free_goods, print_goods);
    }

  print_tree(root, 1);
  
  return 0;
}
