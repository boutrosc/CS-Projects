package control;

import marsrover.Rover;

/**
 * File: ControllerIntf.java
 * 
 * @author Charbel Boutros
 * 
 *         Interface for the Controller class
 */
public interface ControllerIntf {
	public void turnRight(Rover rover);

	public void turnLeft(Rover rover);

	public void moveForward(Rover rover);
}
