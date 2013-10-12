CFLAGS = -g -Wall
CC = gcc 

objects = mt-prime.o

prime: $(objects)
	$(CC) -o prime $(objects) -lpthread -lrt -lm

mt-prime.o: mt-prime.c

.PHONY : clean
clean: 
	rm prime $(objects)
