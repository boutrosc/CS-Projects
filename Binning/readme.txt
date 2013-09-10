***********PURPOSE************
Demonstrates three different binning algoriths:
first fit, best fit, next fit
Prints out summary of each bin and item assortion

**********
HOW TO RUN
**********

1. Place both .c files in same directory
2. Open a terminal

3. Change directory .c file location
4. Enter "gcc auxillary.c -o aux.out" into the terminal
5. Enter "gcc binning.c -o bin.out" into the terminal
6. Next type "./aux.out" to run


7. Read "HOW TO USE AUX" below
8. Next type "./bin.out fileOne fileTwo fileThree" (change filexxx to the name of the output files you created in the aux.out program)
9. Read "HOW TO USE BIN" below

**********
HOW TO USE AUX
**********


Upon startup, you will be prompted to enter multiple
values for each type of output file
Read each prompt, type your response and press enter

After entering all inputs, there will be three output
files that will be stored in the same location as your
aux.out file

**********
HOW TO USE BIN**********


Upon startup, you will see a printed table detailing
how many bins were used for each heuristic in all
three files

A summary.txt file has been created in the same location as
your bin.c file with a very detailed summary of the
algorithmic processing


*****NOTES*****
Compiler Used: GCC
Environment Used: Linux (Ubuntu distro)