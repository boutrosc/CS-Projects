package control;

import java.util.ArrayList;
import marsrover.Rover;
import plateau.Plateau;

/**
 * File: DriverIntf.java
 * 
 * @author Charbel Boutros
 * 
 *         Interface for the Driver class
 */
public interface DriverIntf {
	public Plateau createPlateau(String plateauCords);

	public Rover createRover(ArrayList<String> input);

	public void moveRover(Rover rover, ArrayList<String> input);
}
