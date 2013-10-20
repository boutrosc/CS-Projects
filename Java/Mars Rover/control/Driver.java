package control;

import java.util.ArrayList;
import plateau.Plateau;
import marsrover.Rover;

/**
 * File: Driver.java
 * 
 * @author Charbel Boutros
 * 
 *         Contains method drive a rover
 */
public class Driver implements DriverIntf{

	/**
	 * Creates a new plateau
	 * 
	 * @param plateauCords creates plateau using specified coordinates
	 * @return returns initiated plateau object
	 */
	public Plateau createPlateau(String plateauCords) {
		Plateau plateau = new Plateau();
		plateau.setUpperX(plateauCords.charAt(0));
		plateau.setUpperY(plateauCords.charAt(2));
		return plateau;
	}

	/**
	 * Creates a new rover
	 * 
	 * @param input contains starting position and direction of rover
	 * @return returns initiated rover object
	 */
	public Rover createRover(ArrayList<String> input) {
		String newRover = input.get(0);
		input.remove(0);
		int direction = 0;
		int x = Character.getNumericValue(newRover.charAt(0));
		int y = Character.getNumericValue(newRover.charAt(2));
		switch (newRover.charAt(4)) {
		case 'E':
			direction = 0;
			break;
		case 'N':
			direction = 90;
			break;
		case 'W':
			direction = 180;
			break;
		case 'S':
			direction = 270;
			break;
		}
		Rover rover = new Rover(x, y, direction);
		return rover;
	}

	/**
	 * Moves the rover
	 * 
	 * @param rover specified rover to move
	 * @param input contains directions to move rover
	 */
	public void moveRover(Rover rover, ArrayList<String> input) {
		Controller controller = new Controller();
		String move = input.get(0);
		input.remove(0);
		for (int i = 0; i < move.length(); i++) {
			switch (move.charAt(i)) {
			case 'L':
				controller.turnLeft(rover);
				break;
			case 'R':
				controller.turnRight(rover);
				break;
			case 'M':
				controller.moveForward(rover);
				break;
			}
		}

	}
}
