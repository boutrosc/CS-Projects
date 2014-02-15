all: lizard

lizard: lizard.c
	$(CC) -o $@ $^ -lpthread -lrt

.PHONY : clean
clean: 
	rm lizard
