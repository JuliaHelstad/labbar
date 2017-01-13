#ifndef __UTILS_H_
#define __UTILS_H_
#include <stdbool.h>

typedef union{
  int i;
  float f;
  char *s;
}answer_t;


///typer
//typedef union answer_t *answer_t;
typedef bool(*check_func)(char *check);
typedef answer_t(*convert_func)(char *conv);

///deklarationer

extern char *strdup(const char *);

///funktioner

int read_string(char *buf, int buf_siz);
bool is_number(char *str);
bool not_empty(char *str);
answer_t ask_question(char *question, check_func check, convert_func convert);
char *ask_question_string(char *question);
int ask_question_int(char *question);
char ask_question_char(char *question);



#endif
