import javax.swing.JFrame;

/**
 * File: Controller.java
 * 
 * @author Charbel Boutros
 * 
 *         Class: COP 4331
 * 
 *         Project 2
 * 
 *         Main class - creates JFrame
 */

@SuppressWarnings("serial")
public class Controller extends JFrame {
	public Controller() {
		setSize(650, 400);
		setTitle("Stocks");
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		new View(this);
		setJMenuBar(new View(this));
		setVisible(true);
	}

	public static void main(String[] args) {
		new Controller();
	}
}
