all: UDPclient UDPserver

UDPclient:
	gcc -Wall -Wextra -o UDPclient UDPmain.c UDPclient.c UDPclient.h

UDPserver:
	gcc -Wall -Wextra -o UDPserver UDPserver.c -pthread


.PHONY : clean
clean: 
	rm UDPclient UDPserver

