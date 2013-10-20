package marsrover;

/**
 * File: Rover.java
 * 
 * @author Charbel Boutros
 * 
 * Contains method to create and move a rover
 */
public class Rover implements RoverIntf {
	private int xPos;
	private int yPos;
	private int direction;

	/**
	 * Creates a new rover
	 * @param x starting x coordinate
	 * @param y starting y coordinate
	 * @param dir starting direction
	 */
	public Rover(int x, int y, int dir) {
		xPos = x;
		yPos = y;
		direction = dir;
	}

	/**
	 * Changes x position of rover
	 * @param x value to replace rover's x coordinate with
	 */
	public void setXPos(int x) {
		xPos = x;
	}

	/**
	 * Changes y position of rover
	 * @param y value to replace rover's y coordinate with
	 */
	public void setYPos(int y) {
		yPos = y;
	}

	/**
	 * Changes direction of rover
	 * @param dir changes direction of rover to this value
	 */
	public void setDirection(int dir) {
		direction = dir;
	}

	/**
	 * Returns x coordinate of rover
	 * @return xPos x coordinate of rover
	 */
	public int getXPos() {
		return xPos;
	}

	/**
	 * Returns y coordinate of rover
	 * @return yPos y coordinate of rover
	 */
	public int getYPos() {
		return yPos;
	}

	/**
	 * Returns direction of rover
	 * @return direction direction of rover
	 */
	public int getDirection() {
		return direction;
	}
}
