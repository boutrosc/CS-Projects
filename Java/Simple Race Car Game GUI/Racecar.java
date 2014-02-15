import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;

/**
 * File: Racecar.java
 * 
 * @author Charbel Boutros
 * 
 * 
 *         Racecar Class that includes specifications of a race car
 */

public class Racecar {
	// instance fields
	int xLeft, yTop, racesRun, racesWon, carNumber, slowest;
	private Color colorCode;

	/**
	 * Intializes a race car with specified parameters
	 * 
	 * @param x
	 *            top left X position of race car
	 * @param y
	 *            top left Y position of race car
	 * @param rR
	 *            numbers of races run
	 * @param rW
	 *            number of races won
	 * @param cN
	 *            car number identifier
	 * @param code
	 *            color code for race car
	 */
	public Racecar(int x, int y, int rR, int rW, int cN, Color code) {
		xLeft = x;
		yTop = y;
		racesRun = rR;
		racesWon = rW;
		carNumber = cN;
		colorCode = code;
	}

	/**
	 * Draw component to draw one race car
	 * 
	 * @param g2
	 */
	public void drawCar(Graphics2D g2) {
		Rectangle body = new Rectangle(xLeft, yTop + 10, 60, 10);
		Ellipse2D.Double frontTire = new Ellipse2D.Double(xLeft + 10,
				yTop + 20, 10, 10);
		Ellipse2D.Double rearTire = new Ellipse2D.Double(xLeft + 40, yTop + 20,
				10, 10);
		// The bottom of the rear windshield
		Point2D.Double r1 = new Point2D.Double(xLeft + 20, yTop + 10);
		// The rear of the roof
		Point2D.Double r2 = new Point2D.Double(xLeft + 20, yTop);
		// The front of the roof
		Point2D.Double r3 = new Point2D.Double(xLeft + 40, yTop);
		// The bottom of the front windshield
		Point2D.Double r4 = new Point2D.Double(xLeft + 50, yTop + 10);
		Line2D.Double frontWindshield = new Line2D.Double(r1, r2);
		Line2D.Double roofTop = new Line2D.Double(r2, r3);
		Line2D.Double rearWindshield = new Line2D.Double(r3, r4);
		g2.setColor(colorCode);
		g2.draw(body);
		g2.draw(frontTire);
		g2.draw(rearTire);
		g2.draw(frontWindshield);
		g2.draw(roofTop);
		g2.draw(rearWindshield);
		g2.fill(body);
		g2.setColor(Color.black);
		g2.draw(frontTire);
		g2.draw(rearTire);
		g2.fill(frontTire);
		g2.fill(rearTire);
		g2.setColor(Color.white);
		g2.drawString("#" + carNumber, xLeft + 18, yTop + 20);
	}

	/**
	 * Repositions car on race track
	 * 
	 * @param int x number of pixels to move car
	 */
	public void move(int x) {
		xLeft += x;
	}

	/**
	 * Moves race car back to start line after race ends
	 */
	public void reset() {
		xLeft = 0;
	}
}
