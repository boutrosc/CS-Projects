Installation: 
Open command prompt
Navigate to folder containing program files
Enter 'make' to compile the program
Enter './UDPserver <port>' to run server program. You must chose a port number to run the server on.
Enter './UDPclient <server IP> <port>' to run client program

After usage enter 'make clean' to remove program

Usage: After executing the server program, an IP address and port number will be printed in the console. Use this information to run the client program. Below you will find the available commands to communicate with the server. If invalid input is sent to the server, an error response will be sent by the server to the client.

Commands:
<loadavg/> - Retrieves server load average for past 1, 5, and 15 minutes

<echo>'Enter text here'<echo> - Relay message to server with text inserted between the opening and closing echo

<shutdown/> - Terminates server

