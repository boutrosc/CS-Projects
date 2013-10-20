import java.util.ArrayList;
import util.Utility;
import control.Driver;
import plateau.Plateau;
import marsrover.Rover;

/**
 * File: Main.java
 * 
 * @author Charbel Boutros
 * 
 *         Initiates the mars rover program
 */
public class Main {
	@SuppressWarnings("unused")
	public static void main(String[] args) {
		Utility utility = new Utility();
		Driver driver = new Driver();
		Plateau plateau = new Plateau();
		utility.handleInput(args);
		ArrayList<String> input = utility.parseInput(args);
		String plateauCords = utility.getPlateau(input);
		// while loop to create rover, move rover, print output
		while (input.size() > 0) {
			plateau = driver.createPlateau(plateauCords);
			Rover rover = driver.createRover(input);
			driver.moveRover(rover, input);
			utility.printOutput(rover);
		}
	}
}
