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

/////////////////////////compare_goods
int compare_goods(void *a, void *b)
{
  if(a == NULL && b == NULL) return 0;

  if(a == NULL) return -1;

  if(b == NULL) return 1;
  
  goods_t* name_a = (goods_t*)a;
  goods_t* name_b = (goods_t*)b;

  return strcmp(name_a->name, name_b->name);
}

/////////////////////////compare_name_and_goods
int compare_name_and_goods(void *a, char *name_b)
{
  if(a == NULL && name_b == NULL) return 0;

  if(a == NULL) return -1;

  if(name_b == NULL) return 1;
  
  goods_t* name_a = (goods_t*)a;

  return strcmp(name_a->name, name_b); 
}

/////////////////////////free_goods
void free_goods(void* a)
{
	if (a == NULL) return;
	goods_t* data = (goods_t*)a;
	if (data->name != NULL) free(data->name);
	if (data->description != NULL) free(data->description);
	remove_whole_list(data->goods_list);
	free(data);
}

/////////////////////////print_goods
void print_goods(void* a)
{
  if(a == NULL)
    {
      printf("does not exist.\n");
    }
  goods_t *data = (goods_t*)a;
  printf("Name: %s\n", data->name);
  printf("Description: %s\n", data->description);
  printf("Price: %d\n", data->price);
  list_print(data->goods_list);
}

/////////////////////////print_name
void print_name(void *a)
{
  goods_t *data = (goods_t*)a;
  printf("%s\n", data->name);
}

///////////////////////////tree_new
tree_t *tree_new(goods_t *data, cmp_t compare, free_t free_function, print_t print)
{ 
  tree_t *node = malloc(sizeof (tree_t));
  node -> print = print;
  node -> free_function = free_function;
  node -> compare = compare;
  node -> data = data;
  node -> left = NULL;
  node -> right = NULL;
  node -> parent = NULL;

  return node;
}

///////////////////////////tree_insert
tree_t  *tree_insert(tree_t *tree, goods_t *new_item, cmp_t compare, free_t free_function, print_t print)
{
  if (tree == NULL)
    {      
      return tree_new(new_item, compare, free_function, print);
    }
  tree_t *cursor = tree;   
  while(cursor != NULL)
    {
      int comp = tree->compare(new_item, cursor -> data); 
      if (comp < 0)
        {
          if (cursor -> left == NULL)
            {
              cursor -> left = tree_new(new_item, compare, free_function, print);
              cursor -> left -> parent = cursor;
              return cursor -> left;  
            }
          else
            {
              cursor = cursor -> left;
            }
        }
      if (comp > 0)
        {
          if(cursor -> right == NULL)
            {
              cursor -> right = tree_new(new_item, compare, free_function, print);
              cursor -> right -> parent = cursor;
              return cursor -> right;  
            }
          else
            {
              cursor = cursor -> right;
            }
        }
      else if(comp == 0)
        {
	  return cursor;
        }
    } 
  return tree;
}

///////////////////////////tree_insernode (som tree_insert fast tar in ett tree_t istället för goods_t.)
void tree_insertnode(tree_t *tree, tree_t *new_item)
{
  if (tree == NULL)
    {
      tree = new_item;
      return;
    }

  tree_t *cursor = tree;
  while (cursor != NULL)
    {
      int comp = tree->compare(new_item->data, cursor->data);
      if (comp < 0)
	{
	  if (cursor->left == NULL)
	    {
	      cursor->left = new_item;
	      cursor->left->parent = cursor;
	      return;
	    }
	  else
	    {
	      cursor = cursor->left;
	    }
	}
      if (comp > 0)
	{
	  if (cursor->right == NULL)
	    {
	      cursor->right = new_item;
	      cursor->right->parent = cursor;
	      return;
	    }
	  else
	    {
	      cursor = cursor->right;
	    }
	}
      else if (comp == 0)
	{
	  return;
	}
    }
}

///////////////////////////print_tree_AUX
void print_tree_AUX(tree_t *tree, int *index, int* max_index, int type)
{
  if (tree == NULL)
    {
      return;
    }
   
  if (*index == *max_index + 1)
    {
      char s;
      do
	{
	  s = ask_question_char("Vill du se nästa 20 varor?(Y/N)");
	} while (s != 'y' && s != 'Y'&& s != 'n' && s != 'N');

      if (s == 'y' || s == 'Y')
	{
	  *max_index = *max_index + 20;
	}
      else
	{
	  return;
	}
    }
  print_tree_AUX (tree->left, index, max_index, type);
  if(type == 1)
    {
      printf("%d. ", *index);
      print_name(tree -> data);
    }
  if(type == 2)
    {
      printf("%d. ", *index);
      print_goods(tree -> data);
    }
  *index = *index + 1;
  print_tree_AUX (tree->right, index, max_index, type);
}

///////////////////////////print_tree
void print_tree(tree_t *tree, int type)
{
  int count = 1;
  int max_index = 20;
  print_tree_AUX(tree, &count, &max_index, type);
}

///////////////////////////tree_size
int tree_size(tree_t *tree)
{
  if (tree == NULL)
    {
      return(0);
    }
  else
    {
      return(tree_size(tree -> left) + 1 + tree_size(tree -> right));
    }
}

///////////////////////////find_treenode_by_name_AUX
tree_t *find_treenode_by_name_AUX(tree_t *tree, char *name)
{
  if (tree == NULL)
    {
      return NULL;
    }

  if ((compare_name_and_goods(tree->data, name)) == 0)
    {
      return tree;
    }

  tree_t *found = find_treenode_by_name_AUX(tree->left, name);
  if (found != NULL) 
    {
      return found;
    }
  return find_treenode_by_name_AUX(tree->right, name);
}

///////////////////////////find_treenode_by_name
tree_t *find_treenode_by_name(tree_t *tree, char *name)
{
  tree_t *node = NULL;

  node = find_treenode_by_name_AUX(tree, name);

  if(node == NULL)
    {
      printf("Kunde inte hitta varan.");
    }
  
  return node;
}

///////////////////////////find_treenode_AUX
tree_t *find_treenode_AUX(tree_t *tree, int varonummer, int *index)
{
  if (tree == NULL)
    {
      return NULL;
    }
  if(tree_size(tree) == 1 && *index == varonummer)
    {
      return tree;
    }
  tree_t * findleft = find_treenode_AUX (tree->left, varonummer, index);
  if (findleft != NULL) return findleft;	

  print_name(tree -> data);
  if(*index == varonummer)
    {
      return tree;
    }
  *index = *index + 1;

  return find_treenode_AUX (tree->right, varonummer, index);
}
  
///////////////////////////find_treenode
tree_t *find_treenode(tree_t *tree, int varonummer)
{
  int count = 1;
  return find_treenode_AUX(tree, varonummer, &count);
}

///////////////////////////remove_node
tree_t *remove_node(tree_t *root, tree_t *tree)
{
  if (tree == NULL || root == NULL)
    {
      return root;
    }
	
  if (tree->parent != NULL)
  {
	  if (tree->parent->left == tree)
	  {
		  tree->parent->left = NULL;
	  }
	  else if (tree->parent->right == tree)
	  {
		  tree->parent->right = NULL;
	  }

	  if (tree->left != NULL)
	  {
		  tree_insertnode(root, tree->left);
	  }
	  if (tree->right != NULL)
	  {
		  tree_insertnode(root, tree->right);
	  }
  }
  else
  {
	  if (tree->left == NULL && tree->right == NULL)
	  {
		  printf("Tar bort enda noden i trädet!\n");
		  root = NULL;
	  }
	  else if (tree->left == NULL)
	  {
		  root = tree->right;
	  }
	  else if (tree->right == NULL)
	  {
		  root = tree->left;
	  }
	  else
	  {
		  if (tree_size(tree->left) < tree_size(tree->right))
		  {
			  root = tree->right;
			  tree_insertnode(root, tree->left);
		  }
		  else
		  {
			  root = tree->left;
			  tree_insertnode(root, tree->right);
		  }
	  }
  }
  tree->left = NULL;
  tree->right = NULL;
  tree->free_function(tree->data);
  free(tree);
  return root;
}

/////////////////////////free_tree
void free_tree(tree_t **tree)
{
  tree_t* root = *tree;
  if(root == NULL)
    {
      return;
    }
  root->free_function(root->data);
  free_tree(&(root->left));
  free_tree(&(root->right));
  free(root);
  *tree = NULL; 
}

/////////////////////////balance_tree_AUX
tree_t * balance_tree_AUX(tree_t **nodes, int first, int last)
{
	// Check validity...
	if (last < first) return NULL;

	// Middle node is root
	// This also works when there is a single node (first = last)
	int middle = first + (last - first) / 2;

	nodes[middle]->left = balance_tree_AUX(nodes, first, middle - 1);
	nodes[middle]->right = balance_tree_AUX(nodes, middle + 1, last);

	return nodes[middle];

}

/////////////////////////balance_tree
tree_t* balance_tree(tree_t *tree)
{
	// Create an oerdered list of pointers to nodes
	int size = tree_size(tree);
	tree_t **nodes = malloc(sizeof(tree_t*) * size);
	for (int i = 1; i <= size; i++)
	{
		nodes[i-1] = find_treenode(tree, i);
	}

	for (int i = 1; i <= size; i++)
	{
		printf("%d - %s\n", i, ((goods_t *)nodes[i-1]->data)->name);
	}

	tree_t * new_root = balance_tree_AUX(nodes, 0, size - 1);
	free(nodes);
	return new_root;
}

/////////////////////////string_of_spaces
char * string_of_spaces(int length)
{
	if (length < 0) return "";

	char *str = malloc(sizeof(char) * (length + 1));
	memset(str, ' ', length);
	str[length] = '\0';
	return str;
}

/////////////////////////print_tree_balanced_AUX
void print_tree_balanced_AUX(tree_t *tree, goods_t * parentkey, char * leftRight, int spaces, int diff)
{
	if (tree == NULL) return;
	char* space = string_of_spaces(spaces);
	char firstletter = parentkey->name[0];
	printf("%s%s%s%c\n", space, ((goods_t*)tree->data)->name, leftRight, firstletter);
	
	free(space);

	int newDiff = diff - 6;
	if (newDiff < 4) newDiff = 4;

	print_tree_balanced_AUX(tree->left, (goods_t*)tree->data, "<", spaces - diff, newDiff);
	print_tree_balanced_AUX(tree->right, (goods_t*)tree->data, ">", spaces + diff, newDiff);
}

void print_tree_balanced(tree_t *tree)
{
	int spaces = 50;

	printf("..........Printing tree..........\n");
	if (tree == NULL)
	{
		printf("*** Tree is empty!\n");
		return;
	}

	char* space = string_of_spaces(spaces);
	printf("%sRoot: %s\n", space, ((goods_t*)tree->data)->name);
	printf("%sSize: %d\n\n", space, tree_size(tree));
	printf("%s %s\n", space, ((goods_t*)tree->data)->name);
       
	free(space);
	print_tree_balanced_AUX(tree->left, tree->data, "<", spaces - 20, 14);
	print_tree_balanced_AUX(tree->right, tree->data, ">", spaces + 20, 14);
}
