package control;

import marsrover.Rover;

/**
 * File: Controller.java
 * 
 * @author Charbel Boutros
 * 
 *         Contains method move a rover
 */
public class Controller implements ControllerIntf {

	/**
	 * Turn rover right by 90 degrees
	 * 
	 * @param rover contains rover to turn
	 */
	public void turnRight(Rover rover) {
		if (rover.getDirection() == 0)
			rover.setDirection(270);
		else
			rover.setDirection(rover.getDirection() - 90);
	}

	/**
	 * Turn rover left by 90 degrees
	 * 
	 * @param rover contains rover to turn
	 */
	public void turnLeft(Rover rover) {
		if (rover.getDirection() == 270)
			rover.setDirection(0);
		else
			rover.setDirection(rover.getDirection() + 90);
	}

	/**
	 * Move rover forward by one grid unit
	 * 
	 * @param rover contains rover to move forward
	 */
	public void moveForward(Rover rover) {
		switch (rover.getDirection()) {
		case 270:
			rover.setYPos(rover.getYPos() - 1);
			break;
		case 180:
			rover.setXPos(rover.getXPos() - 1);
			break;
		case 90:
			rover.setYPos(rover.getYPos() + 1);
			break;
		case 0:
			rover.setXPos(rover.getXPos() + 1);
			break;
		}
	}
}
