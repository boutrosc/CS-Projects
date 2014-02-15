all: TCPclient TCPserver

TCPclient: TCPmain.c TCPclient.c
	$(CC) -o $@ $^

TCPserver: TCPserver.c
	$(CC) -o $@ $^ -pthread


.PHONY : clean
clean: 
	rm TCPclient TCPserver

