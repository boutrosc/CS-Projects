all: prime

prime: mt-prime.c
	$(CC) -o $@ $^ -lpthread -lrt -lm

.PHONY : clean
clean: 
	rm prime
