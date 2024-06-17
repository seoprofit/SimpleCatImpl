CC=gcc 
CFLAGS=-Wextra -Wall -Werror -std=c11

build: s21_cat

main.o: cat.c
	$(CC) $(CFLAGS) -c cat.c

s21_cat: cat.o
	$(CC) $(CFLAGS) cat.o -o s21_cat

clean: 
	rm cat.o s21_cat

test:
	./test_cat.sh

rebuild: clean build
	
