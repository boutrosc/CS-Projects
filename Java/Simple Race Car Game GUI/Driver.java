import javax.swing.JFrame;

/**
 * File: Driver.java
 * 
 * @author Charbel Boutros
 * 
 * 
 *         Driver Class that implements animated race cars
 */
@SuppressWarnings("serial")
public class Driver extends JFrame {

	/**
	 * Creates JFrame
	 */
	public Driver() {
		setSize(800, 370);
		setTitle("Race Car");
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Component race = new Component();
		// Adds drawn race track and cars to JFrame
		add(race);
		setVisible(true);

		try {
			Thread.sleep(2000);
		} catch (InterruptedException e) {
			System.err.println(e);
			System.exit(1);
		}
		// Calls start method in Component class
		race.start();
	}

	/**
	 * Creates new Driver to initialize program
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		new Driver();
	}
}