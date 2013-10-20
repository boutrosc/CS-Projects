package marsrover;

/**
 * File: RoverIntf.java
 * 
 * @author Charbel Boutros
 * 
 * Interface for the Rover class
 */
public interface RoverIntf {
	public void setXPos(int x);

	public void setYPos(int y);

	public void setDirection(int dir);

	public int getXPos();

	public int getYPos();

	public int getDirection();
}
