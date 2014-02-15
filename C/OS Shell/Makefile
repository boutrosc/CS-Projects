all: shell

shell: myshell.c parse.c
	$(CC) -o $@ $^

.PHONY : clean
clean: 
	rm shell
