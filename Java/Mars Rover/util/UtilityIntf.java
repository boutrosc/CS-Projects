package util;

import java.util.ArrayList;

/**
 * File: UtilityIntf.java
 * 
 * @author Charbel Boutros
 * 
 *         Interface for the Utility class
 */
public interface UtilityIntf {
	public ArrayList<String> parseInput(String args[]);

	public String getPlateau(ArrayList<String> input);

	public void handleInput(String args[]);

}
