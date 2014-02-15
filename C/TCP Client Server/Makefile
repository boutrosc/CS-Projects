all: TCPclient TCPserver

TCPclient:
	gcc -Wall -Wextra -o TCPclient TCPmain.c TCPclient.c TCPclient.h

TCPserver:
	gcc -Wall -Wextra -o TCPserver TCPserver.c -pthread


.PHONY : clean
clean: 
	rm TCPclient TCPserver

