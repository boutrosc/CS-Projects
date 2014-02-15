Name: Multi-threaded Prime Number Generator

Installation: 
Open command prompt
Navigate to folder containing program files (make, .c)
Enter 'make' to compile the program
To run program you must pass two integeral parameters which are the maximum numbers to check for primality and number of threads to use, respectively.
Enter './prime maxNumbers numberOfThreads' replacing maxNumbers and numberOfThreads with the desired values to run the program.
After usage enter 'make clean' to remove program


Purpose: The purpose of the multi-threaded prime number generator is to take a maximum number of values and search through them for any prime numbers using a specfied number of threads to perform the search operation.

Usage: After executing the program, a list of prime numbers up to the maximum number the user specified will be displayed. Below the list of prime numbers there will be a summary displaying the numbers checked, number of threads used, and elapsed time to search for prime numbers.
