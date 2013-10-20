package plateau;

/**
 * File: Plateau.java
 * 
 * @author Charbel Boutros
 * 
 *         Contains method to create and edit a plateau
 */
public class Plateau implements PlateauIntf {
	private int upperXCord;
	private int upperYCord;

	/**
	 * Set upper x coordinate of plateau
	 * 
	 * @param upperX x coordinate to apply to plateau
	 */
	public void setUpperX(int upperX) {
		upperXCord = upperX;
	}

	/**
	 * Set upper y coordinate of plateau
	 * 
	 * @param upperY y coordinate to apply to plateau
	 */
	public void setUpperY(int upperY) {
		upperYCord = upperY;
	}

	/**
	 * Get upper x coordinate of plateau
	 * 
	 * @return upper X coordinate of plateau
	 */
	public int getUpperX() {
		return upperXCord;
	}

	/**
	 * Get upper y coordinate of plateau
	 * 
	 * @return upper Y coordinate of plateau
	 */
	public int getUpperY() {
		return upperYCord;
	}
}
