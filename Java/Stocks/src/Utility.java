import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * File: Utility.java
 * 
 * @author Charbel Boutros
 * 
 *         Class: COP 4331
 * 
 *         Project 2
 * 
 *         Read/Write utility functions
 */

public class Utility {
	/**
	 * Parses input text file submitted by user
	 * 
	 * @param args
	 *            array of input tokens
	 * @return input contents of user input file
	 */
	public List<Model> parseInput(String fileName) {
		ArrayList<String> input = new ArrayList<String>();
		List<Model> list = new LinkedList<Model>();
		try {
			// opens input file
			FileInputStream fstream = new FileInputStream(fileName+".txt");
			BufferedReader br = new BufferedReader(new InputStreamReader(
					fstream));
			String strLine;
			// read file line by line and stores in Arraylist
			while ((strLine = br.readLine()) != null)
				input.add(strLine);
			// close input stream
			fstream.close();
		} catch (Exception e) {
		}
		while (input.size() > 0) {
			Model i = new Model(input.get(0), input.get(1), input.get(2),
					input.get(3), input.get(4), input.get(5), input.get(6));
			for (int x = 0; x < 7; x++)
				input.remove(0);
			list.add(i);
		}
		return list;
	}
	
	/**
	 * Parses output file
	 * @param list Contains all stocks
	 * @param fileName Contains file name
	 */
	public void parseOutput(List<Model> list, String fileName) {
		ArrayList<String> input = new ArrayList<String>();
		for (Model i : list){
			input.add(i.getName());
			input.add(i.getSymbol());
			input.add(i.getOpen());
			input.add(i.getClose());
			input.add(i.getHigh());
			input.add(i.getLow());
			input.add(i.getMCap());
		}
		try {
			// opens output file
			FileOutputStream fstream = new FileOutputStream(fileName+".txt");
			BufferedWriter bw
			   = new BufferedWriter(new OutputStreamWriter(fstream));
			while (input.size() > 0){
				bw.write(input.get(0)+"\n");
				input.remove(0);
			}
				
			// close output stream
			bw.close();
		} catch (Exception e) {
		}
	}
}
