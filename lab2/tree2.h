#ifndef __TREE2_H_
#define __TREE2_H_

///////////////////////////structar
typedef int(*cmp_t)(void *, void *);
typedef void(*free_t)(void *);
typedef void(*print_t)(void *);
typedef void*(*copy_t)(void*);
typedef void(*add_t)(void *, void *);

struct shelf
{  
  char *shelf_name;
  int amount;
};

typedef struct shelf shelf_t;

struct list
{  
  void *data;
  cmp_t compare;
  free_t free_function;
  print_t print;
  copy_t copy;
  struct list *next;
  add_t add;
};

typedef struct list list_t;

struct goods
{
  char *name;
  char *description;
  int price;
  list_t *goods_list;
  free_t free_function;
};

typedef struct goods goods_t;

typedef int(*cmp_t)(void *, void *);

struct tree
{       
  void *data;
  cmp_t compare;
  free_t free_function;
  print_t print;
  struct tree *left;
  struct tree *right;
  struct tree *parent;
};
typedef struct tree tree_t;

struct action
{
	int type; // NOTHING = 0, ADD = 1, REMOVE = 2, EDIT = 3
	goods_t *merch;
	goods_t *copy;
};
typedef struct action action_t;

///////////////////////////funktioner
/**Compare goods
*\param a first data of goods
*\param b second data of goods
*\return the number that tells which one is bigger or if they are the same.
*/
int compare_goods(void *a, void *b);

/**Free goods
*\param a the goods you want to remove
*/
void free_goods(void* a);

/**Prints out goods
*\param a the data of the goods you want printed out.
*/
void print_goods(void* a);

/**Prints out name of the goods
*\param a the goods of the name you want it to print out.
*/
void print_name(void *a);

/**Creates new tree
*\param data is the data of the goods you want the node to have.
*\param compare is the compare function.
*\param free_function is the free function.
*\param print is the print function.
*\return the new node.
*/
tree_t *tree_new(goods_t *data, cmp_t compare, free_t free_function, print_t print);

/**Insert new tree node
*\param tree is the tree you want to add it to.
*\param new_item is the data of the goods you want the node to have.
*\param compare is the compare function.
*\param free_function is the free function.
*\param print is the print function.
*\return the tree with the new node.
*/
tree_t  *tree_insert(tree_t *tree, goods_t *new_item, cmp_t compare, free_t free_function, print_t print);

/**Insert a new tree node in a tree.
*\param tree is the tree you want to add it to.
*\param new_item is the node you want to add to the tree.
*\return the tree with thenew node.
*/
void tree_insertnode(tree_t *tree, tree_t *new_item);

/**Prints out the tree
*\param tree is the tree you want to print out.
*\param type 1 stands for printing without details and 2 stands for printing it with details.
*/
void print_tree(tree_t *tree, int type);

/**Finds out the size of the tree
*\param tree is the tree you want to know how big it is.
*\return the number of nodes it have.
*/
int tree_size(tree_t *tree);

/**Insert new tree node
*\param tree is the tree you want to find the node in.
*\param name is the name of the node you want to find.
*\return the found node or NULL.
*/
tree_t *find_treenode_by_name(tree_t *tree, char *name);

/**Finds the node by the number it holds.
*\param tree is the tree you want to lfind the node in.
*\param varonummer is the number the node holds depending on which position it haas in the tree.
*\return the found node or NULL.
*/
tree_t *find_treenode(tree_t *tree, int varonummer);

/**Removes a tree node
*\param root is the tree you want to remove a node from.
*\param tree is the node you want to remove.
*\return the tree without the node or NULL.
*/
tree_t *remove_node(tree_t *root, tree_t *tree);

/**Removes the whole tree.
*\param tree is the tree you want to remove.
*/
void free_tree(tree_t **tree);

/**Prints a balanced tree.
*\param tree is the tree you want to print out.
*/
void print_tree_balanced(tree_t *tree);

/**Balances a tree.
*\param tree is the tree you want to balance.
*/
tree_t * balance_tree(tree_t *tree);

#endif
