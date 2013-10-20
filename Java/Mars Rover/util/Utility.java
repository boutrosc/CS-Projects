package util;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

import marsrover.Rover;

/**
 * File: Utility.java
 * 
 * @author Charbel Boutros
 * 
 *         Contains useful utility methods
 */
public class Utility implements UtilityIntf {

	/**
	 * Parses input text file submitted by user
	 * 
	 * @param args
	 *            array of input tokens
	 * @return input contents of user input file
	 */
	public ArrayList<String> parseInput(String args[]) {
		ArrayList<String> input = new ArrayList<String>();
		try {
			// opens input file
			FileInputStream fstream = new FileInputStream(args[1] + "/"
					+ args[0]);
			BufferedReader br = new BufferedReader(new InputStreamReader(
					fstream));
			String strLine;
			// read file line by line and stores in Arraylist
			while ((strLine = br.readLine()) != null) {
				input.add(strLine);
			}
			// close input stream
			fstream.close();
		} catch (Exception e) {// Catch exception if any
			System.err.println("Error: " + e.getMessage());
		}
		return input;
	}

	/**
	 * Finds plateau coordinates in Arraylist
	 * 
	 * @param input
	 *            contents of user input file
	 * @return contains the X Y plateau coordinates stored in string
	 */
	public String getPlateau(ArrayList<String> input) {
		String plateau = input.get(0);
		input.remove(0);
		return plateau;
	}

	/**
	 * Handles input error
	 * 
	 * @param args
	 *            array of input tokens
	 */
	public void handleInput(String args[]) {
		if (args.length != 2) {
			System.err
					.println("Invalid command line, input file and file path (placed in paranthesis) must be included!");
			System.exit(1);
		}
	}

	/**
	 * Prints output summary
	 * 
	 * @param rover
	 *            reference to the rover object
	 */
	public void printOutput(Rover rover) {
		char direction = 0;
		// converts integral direction to character
		switch (rover.getDirection()) {
		case 0:
			direction = 'E';
			break;
		case 90:
			direction = 'N';
			break;
		case 180:
			direction = 'W';
			break;
		case 270:
			direction = 'S';
			break;
		}
		System.out.println(rover.getXPos() + " " + rover.getYPos() + " "
				+ direction);
	}
}
