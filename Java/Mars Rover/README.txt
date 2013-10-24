MARS ROVERS: A squad of robotic rovers are to be landed by NASA on a plateau on Mars. This plateau, which is curiously rectangular, must be navigated by the rovers so that their on-board cameras can get a complete view of the surrounding terrain to send back to Earth.
 
A rover's position and location is represented by a combination of x and y co-ordinates and a letter representing one of the four cardinal compass points. The plateau is divided up into a grid to simplify navigation. An example position might be 0, 0, N, which means the rover is in the bottom left corner and facing North.
 
In order to control a rover, NASA sends a simple string of letters. The possible letters are 'L', 'R' and 'M'. 'L' and 'R' makes the rover spin 90 degrees left or right respectively, without moving from its current spot. 'M' means move forward one grid point, and maintain the same heading.


DESIGN: The program was broken into 6 classes: 
A 'Rover' class which includes  method implementations related to adjusting the position of the rover. 
A 'Plateau' class with method implementations for creating and adjusting a plateau. 
A 'Controller' class which includes method implemenations to turn a rover left, right, and move a rover forward by accessing 'Rover' class methods
A 'Driver' class which creates a plateau and rover and adjusts the rover's position according to the user input provided by accessing 'Controller' class methods
A 'Utility' class which includes method to parse user input, handle input error, and print the output summary
A 'Main' class to initiate the program

The plateau was designed in a grid layout and the rover moved around in a coordinate scheme. The directions (N,S,W,E) were converted to degree integerals (0, 90, 180, 270) during processing portion of the code to dicate compass position. A grid is created using the specified user coordinates and then a while loop is initiated to create new rovers, move them, and print the summary.

INPUT:
The first line of input is the upper-right coordinates of the plateau, the lower-left coordinates are assumed to be 0,0.
 
The rest of the input is information pertaining to the rovers that have been deployed. Each rover has two lines of input. The first line gives the rover's position, and the second line is a series of instructions telling the rover how to explore the plateau.
 
The position is made up of two integers and a letter separated by spaces, corresponding to the x and y co-ordinates and the rover's orientation.
 
Each rover will be finished sequentially, which means that the second rover won't start to move until the first one has finished moving.

Test Input:
5 5	  //Upper-right coordinates of plateau
1 2 N	  //Rover 1's starting coordinate position and heading
LMLMLMLMM //Rover 1's series of exploration instructions
3 3 E	  
MMRMMRMRRM
 
 
OUTPUT
The output for each rover should be its final co-ordinates and heading.
 
INPUT AND OUTPUT
 


ASSUMPTIONS:
Input is correct
Input is placed in a file and properly passed as command line arguement
Input file path is properly passed as command line arguement
Rover is kept within grid boundaries

HOW TO RUN:
Extract contents of zip file
Navigate to the 'Mars Rover' folder that was extracted via terminal window
Input 'javac Main.java' without parens to compile program
Command line arguements must be passed in to program as follows:
	first arguement contains name of input file (i.e input.txt)
	second arguement contains path to input file placed in paranthesis (i.e. "/home/user/documents")
To start program, input (java Main inputFile "input file path in parens") into the terminal window without the outside brackets 
A sample input to start the program would be as follows:
	java Main input.txt "/home/user/documents"


AUTHOR: Charbel Boutros


