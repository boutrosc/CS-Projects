all: UDPclient UDPserver

UDPclient: UDPmain.c UDPclient.c
	$(CC) -o $@ $^

UDPserver: UDPserver.c
	$(CC) -o $@ $^ -pthread


.PHONY : clean
clean: 
	rm UDPclient UDPserver

