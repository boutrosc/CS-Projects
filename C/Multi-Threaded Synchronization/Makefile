CFLAGS = -g -Wall
CC = gcc 

objects = lizard.o

lizard: $(objects)
	$(CC) -o lizard $(objects) -lpthread -lrt

lizard.o: lizard.c

.PHONY : clean
clean: 
	rm lizard $(objects)
