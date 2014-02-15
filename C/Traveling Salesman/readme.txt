***********PURPOSE***********
Traveling salesman problem. Takes X numbers of
cities, performs a brute force algorithm to calculate
optimal route. Then performs smart algorithm using
permuations and genetic mutations to find optimal route
with X number of generations calculated

**********
HOW TO RUN
**********

1. Place .c and .dat file in same directory
2. Open a terminal

3. Change directory to file .c and .dat location
4. Enter "make" into the terminal
5. Next type "./traveling cityweights.dat" to run



**********
HOW TO USE
**********


Upon startup, you will be prompted to enter five numbers
as follows:
Number of cities in current run
Starting City
Number of generations to run
Number of individuals in each generation
Percentage of each generation to be made with mutations

After entering all inputs, a simulation will run
and the results will print on your screen.


********Brute Force Method*******
Performs n! recursive permutations of the last
permuated tour for every permutation

******Genetic Algorithm**********
Intial population is created with permutations.
Thereafter, for X number of mutations per 
generation, the worst offspring is replaced 
by a mutation of the best offspring (elite).