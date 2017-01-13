#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//////////////read_string
int read_string(char *buf, int buf_siz)
{
  int i = 0;

do
  {
    buf[i] = getchar();
    i = i + 1;
  }
 while ((buf[i-1] != '\n') && (i < buf_siz - 1));
 buf[i-1]= '\0';
 return i-1;
}

//////////////is_number
bool is_number(char *str)
{
  if (isdigit(str[0]) || str[0]== '-') {}
  else 
    {return false;}

  int langd = strlen(str);

  for(int i = 1; i < langd; i++)
    {
      if (isdigit(str[i])){}
      else
        {return false;}
    }
  return true;
} 
//////////////not_empty
bool not_empty(char *str)
{
  return strlen(str) > 0;
}

/////////////ask_question
answer_t ask_question(char *question, check_func check, convert_func convert)
{
const int buf_siz = 100;
char buf[100];

do
  {
	if (buf[0] != '\0')
		puts(question);
    read_string(buf, buf_siz);
  }
 while (!check(buf));
return convert(buf);

}

///////////////////////////ask_question_char
char ask_question_char(char *question)
{
  puts(question);
  char c = getchar();
  while(getchar() != '\n');

  return c;
}

//////////////////////////ask_question_string
char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).s;
}

//////////////ask_question_int
int ask_question_int(char *question)
{
  int result = 0;
  int conversions = 0;
do
  {
    printf("%s\n", question);
    conversions = scanf("%d", &result);
    int c;
   
    do
      {
        c = getchar();
      }
    
    while(c != '\n' && c != EOF);
    putchar('\n');
  }
 
while(conversions < 1);

return result;

}
