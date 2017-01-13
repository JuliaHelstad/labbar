#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
//#include <crtdbg.h>
#include "utils.h"
#include "tree2.h"
#include "list2.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

///////////////////////////is_shelf
bool is_shelf(char *str)
{
  if (!isalpha(str[0]) || strlen(str) < 2)
    {
      return false;
    }

 
  for(int i = 1; i < strlen(str); i++)
    {
      if (!isdigit(str[i]))
	{
	  return false;
	}
    }

  return true;
} 

///////////////////////////ask_question_shelf
char *ask_question_shelf(char *question)
{
  return ask_question(question, is_shelf, (convert_func) strdup).s;
}

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

///////////////////////////copy_goods
goods_t *copy_goods(goods_t *original)
{
  goods_t *new_goods = make_goods(original->name, original->description, original->price);
  new_goods->goods_list = copy_list(original->goods_list);
  new_goods->free_function = original->free_function;
  return new_goods;
}

///////////////////////////edit_goods
goods_t *edit_goods(tree_t *root, goods_t *original)
{
	char c;
	goods_t *edited_goods = copy_goods(original);
	while (true)
	{
		print_goods((void*)original);
		c = ask_question_char("\nVad vill du redigera?\n[N]amn\n[B]eskrivning\n[P]ris\n[L]agerhyllor\n[S]para\n[A]vbryt\n");
		if ((c == 'N') || (c == 'n'))
		{
			char * new_name = ask_question_string("Skriv in ett nytt namn:");
			free(edited_goods->name);
			edited_goods->name = new_name;
		}
		else if ((c == 'B') || (c == 'b'))
		{
			char * new_descr = ask_question_string("Skriv in en ny beskrivning:");
			free(edited_goods->description);
			edited_goods->description = new_descr;
		}
		else if ((c == 'P') || (c == 'p'))
		{
			edited_goods->price = ask_question_int("Skriv in ett nytt pris:");
		}
		else if ((c == 'L') || (c == 'l'))
		{
			char s = 'a';
			while (!(s == 'l' || s == 'L' || s == 'b' || s == 'B'))
			{
				s = ask_question_char("Vill du [l]ägga till eller ta [b]ort ett existerande hyllplan?");
			}
			if (s == 'l' || s == 'L')
			{
				bool a = true;
				char *shelf_name = NULL;
				while (a == true)
				{
				
					if (shelf_name != NULL) free(shelf_name);

					shelf_name = ask_question_shelf("Skriv nya lagerhyllans namn XXX (t.ex. A25)");

					if (shelf_name != NULL && strlen(shelf_name) > 0)
					{
						goods_t *found_goods = find_shelf_in_tree(root, shelf_name);
						if (found_goods != NULL)
						{
							if (strcmp(edited_goods->name, found_goods->name) == 0)
							{
								printf("Antal kommer att adderas till existerande hyllplan!");
								a = false;
							}
							else
							{
								printf("FEL! Hylla %s är redan upptagen av varan %s! Kommer att ignoreras!\n", shelf_name, found_goods->name);
							}
						}
						else
						{
							a = false;
						}
					}
				}

				int amount = ask_question_int("Skriv in ett nytt antal (0 innebär att hyllan tas bort):");
				shelf_t *new_shelf = make_shelf(shelf_name, amount);
				list_t *new_list_node = make_list_node(new_shelf, compare_shelf, free_shelf, add_shelf, print_shelf, copy_shelf);

				list_node_insert(edited_goods, new_list_node);
			}
			else if (s == 'b' || s == 'B')
			{
				char *shelf_name = ask_question_shelf("Skriv namnet på lagerhyllan du vill ta bort");

				if (shelf_name != NULL && strlen(shelf_name) > 0)
				{
					list_t *found_list = find_shelf_in_list(edited_goods->goods_list, shelf_name);
					if (found_list != NULL)
					{
						edited_goods->goods_list = remove_list_node(edited_goods->goods_list, found_list);
					}
					else
					{
						printf("FEL! Hylla %s finns ej!\n", shelf_name);
					}
		      
					free(shelf_name);
				}
			}
		}
		else if ((c == 'a') || (c == 'A'))
		{
			free_goods(edited_goods);
			return NULL;
		}
		else if ((c == 's') || (c == 'S'))
		{
			return edited_goods;
		}
	}
	return NULL;
}

///////////////////////////input_goods
void *input_goods(tree_t *root)
{
	printf("Skapar en ny vara: \n");
	char *name = ask_question_string("Skriv produktens namn: XXXXX");
	char *description = ask_question_string("Skriv produktbeskrivning XXXXX");
	int price = ask_question_int("Skriv produktens pris XX.XX");
	bool a = true;
	char *shelf_name = NULL;
	while (a == true)
	{
		if (shelf_name != NULL) free(shelf_name);

		shelf_name = ask_question_shelf("Skriv lagerhyllans namn XXX (t.ex. A25)");

		if (shelf_name != NULL && strlen(shelf_name) > 0)
		{
			goods_t *found_goods = find_shelf_in_tree(root, shelf_name);
			if (found_goods != NULL)
			{
				printf("FEL! Hylla %s är redan upptagen av varan %s! Kommer att ignoreras!\n", shelf_name, found_goods->name);
			}
			else
			{
				a = false;
			}
		}
	}

	int amount = ask_question_int("Skriv antalet varor");

	goods_t *new_goods = make_goods(name, description, price);

	shelf_t *shelf = make_shelf(shelf_name, amount);
	list_t *node = make_list_node(shelf, compare_shelf, free_shelf, add_shelf, print_shelf, copy_shelf);
	new_goods->goods_list = node;

	free(name);
	free(description);
	free(shelf_name);

	char s = 'b';

	while (!((s == 'E') || (s == 'e') || (s == 'N') || (s == 'n') || (s == 'Y') || (s == 'y')))
	{
		s = ask_question_char("Vill du lägga till varan i databasen?(Y/N)\nEller vill du redigera varan?(E)");
	}
	if ((s == 'E') || (s == 'e'))
	{
		return edit_goods(root, new_goods);
	}
	else if ((s == 'N') || (s == 'n'))
	{
		return NULL;
	}
	else if ((s == 'Y') || (s == 'y'))
	{
		return new_goods;
	}

	return NULL;
}

///////////////////////////prepare_undo
void prepare_undo(action_t *current_undo, int type, goods_t *copy, goods_t *merch)
{
  if (current_undo->copy != NULL)
    {
      free_goods((void *)current_undo->copy);
	  current_undo->copy = NULL;
    }
  if (type == 1)    // ADD
    {
	  current_undo->merch = merch;
      current_undo->type = type;
      return;
    }
  if (type == 2)    // REMOVE
    {	  
      current_undo->merch = NULL;
	  current_undo->copy = copy_goods(merch);
      current_undo->type = type;
      return;
    }
  if (type == 3)   // EDIT
    {
	  current_undo->copy = copy;
      current_undo->merch = merch;
	  current_undo->type = type;
      return;
    }
  return;
}

///////////////////////////compare
int compare (void *a, void *b)
{
  return strcmp(((goods_t *)a)->name, (char *)b);
}

///////////////////////////convert_to_goods
goods_t * convert_to_goods (void *a)
{
  return (goods_t*)a;
}

///////////////////////////welcome_menu
void welcome_menu(tree_t *root)
{
	// detta använder vi för undoångra/undo!
	action_t *lastAction = malloc(sizeof(action_t));
	lastAction->copy = NULL;
	lastAction->merch = NULL;
	lastAction->type = 0;

	while (true)
	{
		puts("\nVälkommen till Lagerhantering 1.0\n");
		puts("=================================\n");
		char c = ask_question_char("[L]ägg till en vara\n[T]a bort en vara\n[R]edigera en vara\nÅn[g]ra senaste ändringen\nLista [h]ela varukatalogen\nLista [v]arukatalogen med detaljer\n[p]Visa träd\n[1]Balansera träd\n[A]vsluta");
		if (c == ('l') || c == ('L'))
		{
			goods_t *new_item = input_goods(root);
			if (new_item == NULL)
			{

			}
			else
			{
				if (root == NULL)
				{
					root = tree_new(new_item, compare_goods, free_goods, print_goods);
				}
				else
				{
					tree_insert(root, new_item, compare_goods, free_goods, print_goods);

				}
				prepare_undo(lastAction, 1, NULL, new_item);	// ADD action			
			}
		}
		else if (c == ('h') || c == ('H'))
		{
			print_tree(root, 1);
			char s = 't';
			while (!(s == 'y' || s == 'Y' || s == 'n' || s == 'N'))
			{
				s = ask_question_char("Vill du se en detaljerad beskrivning av en vara?(Y/N)");
			}
			if (s == 'y' || s == 'Y')
			{
				int i = ask_question_int("Skriv in numret på varan du vill se detaljerad information om.");
				//root->print;
				tree_t *found_node = find_treenode(root, i);
				
				if (found_node == NULL)
				{
				  printf("Varan hittades inte\n");
				}
				else
				{
				  found_node = NULL;
				  found_node->print(found_node->data);
				}
			}
		}
		else if (c == ('v') || c == ('V'))
		{

			print_tree(root, 2);

		}
		
		else if (c == ('r') || c == ('R'))
		{
			print_tree(root, 1);
			int varonummer = ask_question_int("Välj nummer på varan du vill redigera");
			tree_t *found_node = find_treenode(root, varonummer);
			if (found_node == NULL)
			{
				printf("Varan hittades inte\n");
			}
			else
			{
				goods_t *copy = copy_goods(convert_to_goods(found_node->data));
				goods_t *edited = edit_goods(root, copy);
				if (edited != NULL)
				{
					if (strcmp((convert_to_goods(found_node->data))->name, edited->name) == 0)
					{
						found_node->data = (void *)edited;
						prepare_undo(lastAction, 3, copy, edited);	// EDIT action
					}
					else
					{
						root = remove_node(root, found_node);
						root = tree_insert(root, edited, compare_goods, free_goods, print_goods);
						prepare_undo(lastAction, 3, copy, convert_to_goods(found_node->data));	// EDIT action*/
					}
				}
				else
				{
					free_goods((void *)copy);
				}
			}
		}
		else if (c == ('a') || c == ('A'))
		{
			char s = 'a';
			while (!(s == 'y' || s == 'Y' || s == 'N' || s == 'n'))
			{
				s = ask_question_char("Är du säker på att du vill avsluta? Allt kommer att bli förlorat. (y/n)");
			}
			if (s == 'Y' || s == 'y')
			{
				if (lastAction->copy != NULL)
				{
					free_goods(lastAction->copy);
				}
				free(lastAction);
				free_tree(&root);

				//_CrtDumpMemoryLeaks();

				exit(0);
			}
			if (s == 'N' || s == 'n')
			{
			}
		}
		else if (c == ('t') || c == ('T'))
		{
			print_tree(root, 1);
			int s = ask_question_int("Skriv numret på varan du vill ta bort?");
			tree_t *found_node = find_treenode(root, s);
			if (found_node != NULL)
			{
				prepare_undo(lastAction, 2, NULL, convert_to_goods(found_node->data));	// REMOVE action
				root = remove_node(root, found_node);
				printf("Varan har tagits bort\n");
			}
			else
			{
				printf("Vara nummer %d kunde ej hittas\n", s);
			}
		}
		else if (c == ('x'))
		{
			goods_t *a = make_goods("8", "", 1); 
			goods_t *b = make_goods("4", "", 1); 
			goods_t *c1 = make_goods("9", "", 1); 
			goods_t *d = make_goods("2", "", 1); 
			goods_t *e = make_goods("1", "", 1); 
			goods_t *f = make_goods("3", "", 1); 
			goods_t *g = make_goods("6", "", 1); 
			goods_t *h = make_goods("5", "", 1); 
			goods_t *i = make_goods("7", "", 1); 
			goods_t *j = make_goods("9", "", 1); 
			tree_t *newNode = tree_insert(root, a, compare_goods, free_goods, print_goods);
			if (root == NULL) root = newNode;
			tree_insert(root, b, compare_goods, free_goods, print_goods);
			tree_insert(root, c1, compare_goods, free_goods, print_goods);
			tree_insert(root, d, compare_goods, free_goods, print_goods);
			tree_insert(root, e, compare_goods, free_goods, print_goods);
			tree_insert(root, f, compare_goods, free_goods, print_goods);
			tree_insert(root, g, compare_goods, free_goods, print_goods);
			tree_insert(root, h, compare_goods, free_goods, print_goods);
			tree_insert(root, i, compare_goods, free_goods, print_goods);
			tree_insert(root, j, compare_goods, free_goods, print_goods);
		}
		else if (c == ('p') || c == ('P'))
		{
			print_tree_balanced(root);
		}
		else if (c == ('1'))
		{
			root = balance_tree(root);
		}
		else if (c == ('b'))
		{
			// Skapa ett balanserat träd
			goods_t *a = make_goods("Fredrik", "", 1); 
			goods_t *b = make_goods("Ceasar", "", 1); 
			goods_t *c1 = make_goods("Bertil", "", 1); 
			goods_t *d = make_goods("David", "", 1); 
			goods_t *e = make_goods("Herman", "", 1); 
			goods_t *f = make_goods("Gustaf", "", 1); 
			goods_t *g = make_goods("Ivar", "", 1); 

			tree_t *newNode = tree_insert(root, a, compare_goods, free_goods, print_goods);
			if (root == NULL) root = newNode;
			tree_insert(root, b, compare_goods, free_goods, print_goods);
			tree_insert(root, c1, compare_goods, free_goods, print_goods);
			tree_insert(root, d, compare_goods, free_goods, print_goods);
			tree_insert(root, e, compare_goods, free_goods, print_goods);
			tree_insert(root, f, compare_goods, free_goods, print_goods);
			tree_insert(root, g, compare_goods, free_goods, print_goods);
		}
		else if (c == ('n'))
		{
			// Skapa ett icke-balanserat träd
			goods_t *a = make_goods("Adam", "", 1);
			goods_t *b = make_goods("Bertil", "", 1);
			goods_t *c1 = make_goods("David", "", 1);
			goods_t *d = make_goods("Ceasar", "", 1);
			goods_t *e = make_goods("Erik", "", 1);
			goods_t *f = make_goods("Gustaf", "", 1);
			goods_t *g = make_goods("Fredrik", "", 1);
			goods_t *h = make_goods("Ivar", "", 1);
			goods_t *i = make_goods("Henrik", "", 1);

			tree_t *newNode = tree_insert(root, a, compare_goods, free_goods, print_goods);
			if (root == NULL) root = newNode;
			tree_insert(root, b, compare_goods, free_goods, print_goods);
			tree_insert(root, c1, compare_goods, free_goods, print_goods);
			tree_insert(root, d, compare_goods, free_goods, print_goods);
			tree_insert(root, e, compare_goods, free_goods, print_goods);
			tree_insert(root, f, compare_goods, free_goods, print_goods);
			tree_insert(root, g, compare_goods, free_goods, print_goods);
			tree_insert(root, h, compare_goods, free_goods, print_goods);
			tree_insert(root, i, compare_goods, free_goods, print_goods);
		}
		else if (c == ('g') || c == ('G'))
		{
			if (lastAction->type == 0)
			{
				printf("\nHär ska vi inte vara!\n");
			}
			else
			{
				printf("\nFörsöker ångra lägga till!\n");
				char response;
				if (lastAction->type == 1)
				{
					response = ask_question_char("Är du säker? (Y/N)\nÅngra kommer att TA BORT senast tillagda varan \n");
				}
				else if (lastAction->type == 2)
				{
					response = ask_question_char("Är du säker? (Y/N)\nÅngra kommer att ÅTERSTÄLLA senast borttagna varan\n");
				}
				else if (lastAction->type == 3)
				{
					response = ask_question_char("Är du säker? (Y/N)\nÅngra kommer att ÅTERSTÄLLA senast redigerade varan\n");
				}

				if (response == 'y' || response == 'Y')
				{
					if (lastAction->type == 1)// ångra ADD
					{
						tree_t *to_be_removed = find_treenode_by_name(root, lastAction->merch->name);
						if (to_be_removed != NULL)
						{
							root = remove_node(root, to_be_removed);
							if (root == NULL)
							{
								printf("Nu är trädet tomt!\n");
							}
							else 
							{
								printf("Senaste varan togs bort.");
							}
						}
						else
						{
							printf("Fanns ingen vara att ta bort.");
						}
					}
					else if (lastAction->type == 2) // Ångra REMOVE
					{
						root = tree_insert(root, lastAction->copy, compare_goods, free_goods, print_goods);
					}
					else if (lastAction->type == 3)// Ångra EDIT
					{
						tree_t *to_be_restored = find_treenode_by_name(root, lastAction->merch->name);
						if (to_be_restored != NULL)
						{
							free_goods(to_be_restored->data);
							to_be_restored->data = (void *)(lastAction->copy);
							lastAction->copy = NULL;
						}
						else printf("\nnågot gick fel!\n");
					}
					lastAction->type = 0;// nollställer Ångra!
					lastAction->merch = NULL;
				}
			}
		}
	}
  return;
}

///////////////////////////main
int main(int argc, char *argv[])
{
  tree_t *tree = NULL;
  welcome_menu(tree);
  return 0;
}
