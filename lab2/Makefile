CC = gcc
FLAGS = -std=c11 -Wall -g -o


all: inlupp2.c inlupp2.o tree2.o list2.o utils.o
	$(CC) $(FLAGS) inlupp2 inlupp2.c tree2.c list2.c utils.c  $@.out

tree2.o: tree2.c tree2.o
	$(CC) $(FLAGS) -c tree2 tree2.c tree2.h $@.out

list2.o: list2.c list2.o
	$(CC) $(FLAGS) -c list2 list2.c list2.h $@.out

utils.o: utils.c utils.o
	$(CC) $(FLAGS) -c utils utils.c utils.h $@.ou

test: test_list.c test_list.o tree2.o list2.o utils.o
	$(CC) $(FLAGS)  test test_list.o utils.o list2.o tree2.o -lcunit $@.out



clean:
	rm -f main
	rm -f inlupp2
	rm -f tree2
	rm -f list2
	rm -f utils
	rm -f *.o
	rm -f *.out
	rm -rf *.dSYM
	rm -f *~

%.o: %.c
	$(CC) $(FLAGS) $< -c -o $@

