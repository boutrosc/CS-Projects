import java.awt.*;
import java.awt.geom.*;
import javax.swing.*;
import java.util.Random;

/**
 * File: Component.java
 * 
 * @author Charbel Boutros
 * 
 * 
 *         Driver Class draws components and animates race cars
 */

@SuppressWarnings("serial")
public class Component extends JComponent {
	// instance fields
	private int cars, races, curRace = 1, firstPlace = 0;
	private Racecar car1;
	private Racecar car2;
	private Racecar car3;
	private Racecar car4;
	private Racecar slowest;

	/**
	 * Asks user for number of races and cars Initializes number of requested
	 * cars
	 */
	public Component() {
		// Asks user for number of cars and races
		String input = JOptionPane.showInputDialog("Number of races: ");
		if (input.equals(""))
			races = 1;
		else {
			races = Integer.parseInt(input);
			if (races < 1)
				races = 1;
		}
		input = JOptionPane.showInputDialog("Number of cars: ");
		if (input.equals(""))
			cars = 2;
		else {
			cars = Integer.parseInt(input);
			if (cars > 4 || cars < 1 || cars == 0)
				cars = 2;
		}

		// Switch statement to initialize carsnull
		switch (cars) {
		case 4:
			car1 = new Racecar(0, 50, races, 0, 72, Color.orange);
			car2 = new Racecar(0, 120, races, 0, 16, Color.red);
			car3 = new Racecar(0, 190, races, 0, 45, Color.magenta);
			car4 = new Racecar(0, 260, races, 0, 69, Color.blue);
			break;
		case 3:
			car1 = new Racecar(0, 50, races, 0, 72, Color.orange);
			car2 = new Racecar(0, 120, races, 0, 16, Color.red);
			car3 = new Racecar(0, 190, races, 0, 45, Color.magenta);
			break;
		case 2:
			car1 = new Racecar(0, 50, races, 0, 72, Color.orange);
			car2 = new Racecar(0, 120, races, 0, 16, Color.red);
			break;
		case 1:
			car1 = new Racecar(0, 50, races, 0, 72, Color.orange);
			break;
		}
	}

	/**
	 * Draws race track and cars
	 * 
	 * @param Graphics
	 *            g
	 */
	public void paintComponent(Graphics g) {
		Graphics2D g2 = (Graphics2D) g;
		// sets background color
		g2.setColor(Color.lightGray);
		g2.fillRect(0, 0, getWidth(), getHeight());
		// draws race track
		drawTrack(g2);
		// switch statement to draw cars
		switch (cars) {
		case 4:
			car1.drawCar(g2);
			car2.drawCar(g2);
			car3.drawCar(g2);
			car4.drawCar(g2);
			break;
		case 3:
			car1.drawCar(g2);
			car2.drawCar(g2);
			car3.drawCar(g2);
			break;
		case 2:
			car1.drawCar(g2);
			car2.drawCar(g2);
			break;
		case 1:
			car1.drawCar(g2);
			break;
		}
	}

	/**
	 * Draw component for race track
	 * 
	 * @param g2
	 */
	public void drawTrack(Graphics2D g2) {
		Line2D.Double startLine = new Line2D.Double(61, 35, 61, 290);
		Line2D.Double finishLine = new Line2D.Double(getWidth() - 60, 35,
				getWidth() - 60, 290);
		Line2D.Double trackLane1 = new Line2D.Double(61, 80, getWidth() - 60,
				80);
		Line2D.Double trackLane2 = new Line2D.Double(61, 150, getWidth() - 60,
				150);
		Line2D.Double trackLane3 = new Line2D.Double(61, 220, getWidth() - 60,
				220);
		Rectangle grass = new Rectangle(0, 291, getWidth(), getHeight());
		g2.setColor(Color.green);
		g2.draw(grass);
		g2.fill(grass);
		g2.setColor(Color.black);
		g2.draw(startLine);
		g2.draw(finishLine);
		g2.draw(trackLane1);
		g2.draw(trackLane2);
		g2.draw(trackLane3);
		g2.drawString("Race #" + curRace, getWidth() / 2, 20);
		g2.drawString("Start", 20, 30);
		g2.drawString("Finish", getWidth() - 60, 30);
	}

	/**
	 * Start method to begin the animated race
	 */
	public void start() {
		// begins first race
		race();
		// loops through number of races to run
		for (int i = 0; i < races - 1; i++) {
			curRace++;
			firstPlace = 0;
			try {
				Thread.sleep(800);
			} catch (InterruptedException e) {
				System.err.println(e);
				System.exit(1);
			}
			// switch statement to reset cars back to start
			// line after finished race
			switch (cars) {
			case 4:
				car1.reset();
				car2.reset();
				car3.reset();
				car4.reset();
				break;
			case 3:
				car1.reset();
				car2.reset();
				car3.reset();
				break;
			case 2:
				car1.reset();
				car2.reset();
				break;
			case 1:
				car1.reset();
				break;
			}
			repaint();
			try {
				Thread.sleep(800);
			} catch (InterruptedException e) {
				System.err.println(e);
				System.exit(1);
			}
			race();
		}
		// prints race summary
		summary();
	}

	/**
	 * Calls animator method to animate each race car
	 */
	public void race() {
		// while loop to check if race car reached finish line
		while (firstPlace < (getWidth() - 60)) {
			// switch statement to animate cars
			switch (cars) {
			case 4:
				moveCar(car1);
				if (firstPlace > (getWidth() - 60)) break;
				moveCar(car2);
				if (firstPlace > (getWidth() - 60)) break;
				moveCar(car3);
				if (firstPlace > (getWidth() - 60)) break;
				moveCar(car4);
				break;
			case 3:
				moveCar(car1);
				if (firstPlace > (getWidth() - 60)) break;
				moveCar(car2);
				if (firstPlace > (getWidth() - 60)) break;
				moveCar(car3);
				break;
			case 2:
				moveCar(car1);
				if (firstPlace > (getWidth() - 60)) break;
				moveCar(car2);
				break;
			case 1:
				moveCar(car1);
				break;
			}
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				System.err.println(e);
				System.exit(1);
			}
		}
		// records the slowest car of each race
		slowestCar();
	}

	/**
	 * Records the slowest car in the race
	 */
	public void slowestCar() {
		slowest = car1;
		switch (cars) {
		case 4:
			if (car2.xLeft < slowest.xLeft)
				slowest = car2;
			if (car3.xLeft < slowest.xLeft)
				slowest = car3;
			if (car4.xLeft < slowest.xLeft)
				slowest = car4;
			break;
		case 3:
			if (car2.xLeft < slowest.xLeft)
				slowest = car2;
			if (car3.xLeft < slowest.xLeft)
				slowest = car3;
			break;
		case 2:
			if (car2.xLeft < slowest.xLeft)
				slowest = car2;
			break;
		case 1:
			break;
		}
		// Increments slowest counter for
		// car that was slowest
		if (slowest.carNumber == 72)
			car1.slowest++;
		else if (slowest.carNumber == 16)
			car2.slowest++;
		else if (slowest.carNumber == 45)
			car3.slowest++;
		else if (slowest.carNumber == 69)
			car4.slowest++;

	}

	/**
	 * Animates race car by X amount of pixels
	 * 
	 * @param car
	 *            Car to be animated
	 */
	public void moveCar(Racecar car) {
		Random random = new Random();
		int x = random.nextInt(20);
		if (x <= 5)
			x = 5;
		else if (x <= 10)
			x = 10;
		else if (x <= 15)
			x = 15;
		else
			x = 20;
		// repositions the race car by X pixels
		car.move(x);
		// redraws the panel
		repaint();
		// Records X position of car closest to finish line to
		// eventually break out of while loop in Race method
		if (car.xLeft + 60 >= firstPlace)
			firstPlace = car.xLeft + 60;
		// Increments race car's racesWon counter
		// if car crossed finish line first
		if (car.xLeft + 60 >= (getWidth() - 60)) {
			car.racesWon++;
		}
	}

	/**
	 * Prints out race summary to console
	 */
	public void summary() {
		System.out
				.println("--------------------RACE RESULTS--------------------");
		switch (cars) {
		case 4:
			System.out.println("Orange Mustang #72:\t " + car1.racesRun
					+ " races run \t " + car1.racesWon + " races won");
			System.out.println("Red Challenger #16:\t " + car2.racesRun
					+ " races run \t " + car2.racesWon + " races won");
			System.out.println("Magenta  Camaro #45:\t " + car3.racesRun
					+ " races run \t " + car3.racesWon + " races won");
			System.out.println("Blue Firebird #69:\t " + car4.racesRun
					+ " races run \t " + car4.racesWon + " races won");
			slowest = car1;
			if (car2.slowest > slowest.slowest)
				slowest = car2;
			if (car3.slowest > slowest.slowest)
				slowest = car3;
			if (car4.slowest > slowest.slowest)
				slowest = car4;
			if (slowest.carNumber == 72)
				System.out.print("\n\nSlowest car: Orange Mustang #72");
			else if (slowest.carNumber == 16)
				System.out.print("\n\nSlowest car: Red Challenger #16");
			else if (slowest.carNumber == 45)
				System.out.print("\n\nSlowest car: Magenta  Camaro #45");
			else
				System.out.print("\n\nSlowest car: Blue Firebird #69");
			break;
		case 3:
			System.out.println("Orange Mustang #72:\t " + car1.racesRun
					+ " races run \t " + car1.racesWon + " races won");
			System.out.println("Red Challenger #16:\t " + car2.racesRun
					+ " races run \t " + car2.racesWon + " races won");
			System.out.println("Magenta  Camaro #45:\t " + car3.racesRun
					+ " races run \t " + car3.racesWon + " races won");
			slowest = car1;
			if (car2.slowest > slowest.slowest)
				slowest = car2;
			if (car3.slowest > slowest.slowest)
				slowest = car3;
			if (slowest.carNumber == 72)
				System.out.print("\n\nSlowest car: Orange Mustang #72");
			else if (slowest.carNumber == 16)
				System.out.print("\n\nSlowest car: Red Challenger #16");
			else if (slowest.carNumber == 45)
				System.out.print("\n\nSlowest car: Magenta  Camaro #45");
			break;
		case 2:
			System.out.println("Orange Mustang #72:\t " + car1.racesRun
					+ " races run \t " + car1.racesWon + " races won");
			System.out.println("Red Challenger #16:\t " + car2.racesRun
					+ " races run \t " + car2.racesWon + " races won");
			slowest = car1;
			if (car2.slowest > slowest.slowest)
				slowest = car2;
			if (slowest.carNumber == 72)
				System.out.print("\n\nSlowest car: Orange Mustang #72");
			else if (slowest.carNumber == 16)
				System.out.print("\n\nSlowest car: Red Challenger #16");
			break;
		case 1:
			System.out.println("Orange Mustang #72:\t " + car1.racesRun
					+ " races run \t " + car1.racesWon + " races won");
			System.out
					.print("\n\nSlowest car (and only car): Orange Mustang #72");

			break;
		}

	}

}
