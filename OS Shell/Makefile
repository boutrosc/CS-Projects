CFLAGS = -g -Wall 
CC = gcc

objects = myshell.o parse.o

shell: $(objects)
	$(CC) -o shell $(objects)

myshell.o: myshell.c parse.h
parse.o: parse.c parse.h

.PHONY : clean
clean: 
	rm shell $(objects)
