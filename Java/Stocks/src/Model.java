/**
 * File: Model.java
 * 
 * @author Charbel Boutros
 * 
 *         Class: COP 4331
 * 
 *         Project 2
 * 
 *         Contains design of a new stock
 */

public class Model {
	// instance fields
	private String stockName;
	private String stockSymbol;
	private String stockOpen;
	private String stockClose;
	private String stockHigh;
	private String stockLow;
	private String marketCap;
	private int active;

	public Model(String sName, String sSymbol, String sOpen, String sClose,
			String sHigh, String sLow, String sMCap) {
		stockName = new String(sName);
		stockSymbol = new String(sSymbol);
		stockOpen = new String(sOpen);
		stockClose = new String(sClose);
		stockHigh = new String(sHigh);
		stockLow = new String(sLow);
		marketCap = new String(sMCap);
		active = 0;
	}

	/**
	 * Set stock name
	 * 
	 * @param sName
	 *            user-defined name
	 */
	public void setName(String sName) {
		stockName = new String(sName);
	}

	/**
	 * Retrieves stock name
	 * 
	 * @return Name of stock
	 */
	public String getName() {
		return stockName;
	}

	/**
	 * Sets stock symbol
	 * 
	 * @param sSymbol
	 *            user-defined symbol
	 */
	public void setSymbol(String sSymbol) {
		stockSymbol = new String(sSymbol);
	}

	/**
	 * Retrieves symbol
	 * 
	 * @return Stock symbol
	 */
	public String getSymbol() {
		return stockSymbol;
	}

	/**
	 * Sets stock open price
	 * 
	 * @param sOpen
	 *            user-defined stock open price
	 */
	public void setOpen(String sOpen) {
		stockOpen = sOpen;
	}

	/**
	 * Retrieves stock open price
	 * 
	 * @return stock open price
	 */
	public String getOpen() {
		return stockOpen;
	}

	/**
	 * Set stock closing price
	 * 
	 * @param sClose
	 *            user-defined stock closing price
	 */
	public void setClose(String sClose) {
		stockClose = sClose;
	}

	/**
	 * Retrieves stock closing price
	 * 
	 * @return stock closing price
	 */
	public String getClose() {
		return stockClose;
	}

	/**
	 * Sets stock high price
	 * 
	 * @param sHigh
	 *            user-defined stock high price
	 */
	public void setHigh(String sHigh) {
		stockHigh = sHigh;
	}

	/**
	 * Retrieves stock high price
	 * 
	 * @return stock high price
	 */
	public String getHigh() {
		return stockHigh;
	}

	/**
	 * Sets stock low price
	 * 
	 * @param sLow
	 *            user-defined stock low price
	 */
	public void setLow(String sLow) {
		stockLow = sLow;
	}

	/**
	 * Retrieves stock low price
	 * 
	 * @return stock low price
	 */
	public String getLow() {
		return stockLow;
	}

	/**
	 * Sets stock market cap
	 * 
	 * @param sMCap
	 *            user-defined stock market cap
	 */
	public void setMCap(String sMCap) {
		marketCap = sMCap;
	}

	/**
	 * Retrieves stock market cap
	 * 
	 * @return stock market cap
	 */
	public String getMCap() {
		return marketCap;
	}

	/**
	 * Used for comparator purposes
	 * 
	 * @return
	 */
	public String test() {
		return new String(getName() + " (" + getSymbol() + ") - Open: "
				+ getOpen() + "  Close: " + getClose() + "  High: " + getHigh()
				+ "  Low: " + getLow() + "  Market Cap: " + getMCap());
	}
}
