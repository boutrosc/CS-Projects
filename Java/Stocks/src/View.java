import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.awt.*;

import javax.swing.*;

/**
 * File: View.java
 * 
 * @author Charbel Boutros
 * 
 *         Class: COP 4331
 * 
 *         Project 2
 * 
 *         Creates and handles GUI components
 */

public class View extends JMenuBar {
	// instance fields
	private Controller gui;
	private JMenu fileMenu;
	private JMenu stockMenu;
	private JMenu viewMenu;
	private List<Model> list = new LinkedList<Model>();
	private JPanel basePanel = new JPanel();
	private JPanel viewPanel = new JPanel();
	private JPanel searchPanel = new JPanel();
	private Utility utility = new Utility();
	private String inputFile = new String("");

	public View(Controller controller) {
		gui = controller;
		basePanel.removeAll();
		JButton searchButton = new JButton("Search Stocks");
		JButton viewButton = new JButton("View/Edit Stocks");
		JButton addButton = new JButton("Add Stock");
		JLabel space1 = new JLabel();
		space1.setPreferredSize(new Dimension(600, 40));
		searchButton.addActionListener(new searchItemListener());
		JLabel space2 = new JLabel();
		space2.setPreferredSize(new Dimension(600, 40));
		searchButton.addActionListener(new searchItemListener());
		JLabel space3 = new JLabel();
		space3.setPreferredSize(new Dimension(600, 40));
		searchButton.addActionListener(new searchItemListener());
		viewButton.addActionListener(new viewItemListener());
		addButton.addActionListener(new addItemListener());
		basePanel.add(space1);
		basePanel.add(searchButton);
		basePanel.add(space2);
		basePanel.add(viewButton);
		basePanel.add(space3);
		basePanel.add(addButton);
		fileMenu = new JMenu("File");
		stockMenu = new JMenu("Manage Stocks");
		viewMenu = new JMenu("View");
		JMenuItem newMenuItem = new JMenuItem("New");
		JMenuItem openMenuItem = new JMenuItem("Open");
		JMenuItem saveMenuItem = new JMenuItem("Save");
		JMenuItem saveAsMenuItem = new JMenuItem("Save As");
		JMenuItem exitMenuItem = new JMenuItem("Exit");
		JMenuItem addStockMenuItem = new JMenuItem("Add");
		JMenuItem openStockMenuItem = new JMenuItem("View");
		JMenuItem editStockMenuItem = new JMenuItem("Edit");
		JMenu nameMenuItem = new JMenu("Stock Name");
		JMenu symbolMenuItem = new JMenu("Stock Symbol");
		JMenu sopenMenuItem = new JMenu("Stock Open");
		JMenu closeMenuItem = new JMenu("Stock Close");
		JMenu highMenuItem = new JMenu("Stock High");
		JMenu lowMenuItem = new JMenu("Stock Low");
		JMenu mcapMenuItem = new JMenu("Stock Market Cap");
		JMenuItem nameAscMenuItem = new JMenuItem("Ascending");
		JMenuItem nameDescMenuItem = new JMenuItem("Descending");
		JMenuItem symbolAscMenuItem = new JMenuItem("Ascending");
		JMenuItem symbolDescMenuItem = new JMenuItem("Descending");
		JMenuItem sopenAscMenuItem = new JMenuItem("Ascending");
		JMenuItem sopenDescMenuItem = new JMenuItem("Descending");
		JMenuItem closeAscMenuItem = new JMenuItem("Ascending");
		JMenuItem closeDescMenuItem = new JMenuItem("Descending");
		JMenuItem highAscMenuItem = new JMenuItem("Ascending");
		JMenuItem highDescMenuItem = new JMenuItem("Descending");
		JMenuItem lowAscMenuItem = new JMenuItem("Ascending");
		JMenuItem lowDescMenuItem = new JMenuItem("Descending");
		JMenuItem mcapAscMenuItem = new JMenuItem("Ascending");
		JMenuItem mcapDescMenuItem = new JMenuItem("Descending");
		nameMenuItem.add(nameAscMenuItem);
		nameMenuItem.add(nameDescMenuItem);
		symbolMenuItem.add(symbolAscMenuItem);
		symbolMenuItem.add(symbolDescMenuItem);
		sopenMenuItem.add(sopenAscMenuItem);
		sopenMenuItem.add(sopenDescMenuItem);
		closeMenuItem.add(closeAscMenuItem);
		closeMenuItem.add(closeDescMenuItem);
		highMenuItem.add(highAscMenuItem);
		highMenuItem.add(highDescMenuItem);
		lowMenuItem.add(lowAscMenuItem);
		lowMenuItem.add(lowDescMenuItem);
		mcapMenuItem.add(mcapAscMenuItem);
		mcapMenuItem.add(mcapDescMenuItem);
		newMenuItem.addActionListener(new newItemListener());
		openMenuItem.addActionListener(new openItemListener());
		saveMenuItem.addActionListener(new saveItemListener());
		saveAsMenuItem.addActionListener(new saveAsItemListener());
		exitMenuItem.addActionListener(new exitItemListener());
		addStockMenuItem.addActionListener(new addStockItemListener());
		openStockMenuItem.addActionListener(new openStockItemListener());
		editStockMenuItem.addActionListener(new editStockItemListener());
		nameAscMenuItem.addActionListener(new nameAscItemListener());
		nameDescMenuItem.addActionListener(new nameDescItemListener());
		symbolAscMenuItem.addActionListener(new symbolAscItemListener());
		symbolDescMenuItem.addActionListener(new symbolDescItemListener());
		sopenAscMenuItem.addActionListener(new sopenAscItemListener());
		sopenDescMenuItem.addActionListener(new sopenDescItemListener());
		closeAscMenuItem.addActionListener(new closeAscItemListener());
		closeDescMenuItem.addActionListener(new closeDescItemListener());
		highAscMenuItem.addActionListener(new highAscItemListener());
		highDescMenuItem.addActionListener(new highDescItemListener());
		lowAscMenuItem.addActionListener(new lowAscItemListener());
		lowDescMenuItem.addActionListener(new lowDescItemListener());
		mcapAscMenuItem.addActionListener(new mcapAscItemListener());
		mcapDescMenuItem.addActionListener(new mcapDescItemListener());
		fileMenu.add(newMenuItem);
		fileMenu.add(openMenuItem);
		fileMenu.add(saveMenuItem);
		fileMenu.add(saveAsMenuItem);
		fileMenu.add(exitMenuItem);
		stockMenu.add(addStockMenuItem);
		stockMenu.add(openStockMenuItem);
		stockMenu.add(editStockMenuItem);
		viewMenu.add(nameMenuItem);
		viewMenu.add(symbolMenuItem);
		viewMenu.add(sopenMenuItem);
		viewMenu.add(closeMenuItem);
		viewMenu.add(highMenuItem);
		viewMenu.add(lowMenuItem);
		viewMenu.add(mcapMenuItem);
		add(fileMenu);
		add(stockMenu);
		add(viewMenu);
		viewMenu.setVisible(false);
		gui.add(basePanel);
	}

	/**
	 * Search for user-defined stock and displays stock
	 */
	private void searchStock() {
		searchPanel.removeAll();
		searchPanel.setVisible(true);
		final JButton back = new JButton("Back");
		back.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				gui.remove(searchPanel);
				fileMenu.setVisible(true);
				stockMenu.setVisible(true);
				basePanel.setVisible(true);
				gui.revalidate();
				gui.repaint();
			}
		});
		JLabel space1 = new JLabel();
		space1.setPreferredSize(new Dimension(600, 5));
		final JTextField searchField = new JTextField(
				"Search by stock name or symbol");
		searchField.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent me) {
				searchField.setText("");
			}
		});
		searchField.setColumns(20);
		final JButton submit = new JButton("Search");
		submit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				for (Model i : list)
					if (i.getName().equalsIgnoreCase(searchField.getText())
							|| i.getSymbol().equalsIgnoreCase(
									searchField.getText())) {
						JLabel label = new JLabel(i.getName() + " ("
								+ i.getSymbol() + ") - Open: " + i.getOpen()
								+ "  Close: " + i.getClose() + "  High: "
								+ i.getHigh() + "  Low: " + i.getLow()
								+ "  Market Cap: " + i.getMCap());
						searchPanel.removeAll();
						searchPanel.add(searchField);
						searchPanel.add(submit);
						searchPanel.add(back);
						searchPanel.add(label);
						gui.add(searchPanel);
						gui.revalidate();
						gui.repaint();
					}
			}
		});

		searchPanel.add(searchField);
		searchPanel.add(submit);
		searchPanel.add(back);
		basePanel.setVisible(false);
		fileMenu.setVisible(false);
		stockMenu.setVisible(false);
		gui.add(searchPanel);
		gui.revalidate();
	}

	/**
	 * Displays all stock including details Allows user to edit stocks by
	 * clicking on stock name
	 */
	private void viewStock() {
		viewPanel.removeAll();
		viewMenu.setVisible(true);
		JButton back = new JButton("Back");
		back.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				gui.remove(viewPanel);
				fileMenu.setVisible(true);
				stockMenu.setVisible(true);
				basePanel.setVisible(true);
				viewMenu.setVisible(false);
				gui.revalidate();
				gui.repaint();
			}
		});
		JLabel space = new JLabel();
		space.setPreferredSize(new Dimension(600, 5));
		for (Model i : list) {
			JLabel label = new JLabel(i.getName() + " (" + i.getSymbol()
					+ ") - Open: " + i.getOpen() + "  Close: " + i.getClose()
					+ "  High: " + i.getHigh() + "  Low: " + i.getLow()
					+ "  Market Cap: " + i.getMCap());
			label.addMouseListener(new MouseAdapter() {
				public void mousePressed(MouseEvent me) {
					if (me.getClickCount() == 2) {
						JLabel l = (JLabel) me.getSource();
						for (Model i : list)
							if (l.getText().equals(i.test())) {
								int edit = 0;
								for (int x = 0; x < list.size(); x++)
									if (i == list.get(x))
										edit = x;
								viewPanel.setVisible(false);
								editStock(i, edit, "view", viewPanel);
							}
					}
				}
			});
			viewPanel.add(label);
		}
		basePanel.setVisible(false);
		fileMenu.setVisible(false);
		stockMenu.setVisible(false);
		viewPanel.add(space);
		viewPanel.add(back);
		gui.add(viewPanel);
		gui.revalidate();
		gui.repaint();
	}

	/**
	 * Allows user to edit a stock
	 * 
	 * @param i
	 *            Contains stock object
	 * @param edit
	 *            Contains index of stock to be edited from LinkedList
	 * @param panel
	 *            Indicates which panel called the editStock function
	 * @param viewPanel
	 *            If viewStock function called editStock, allows editStock to
	 *            return to previous screen after editing
	 */
	private void editStock(final Model i, final int edit, final String panel,
			final JPanel viewPanel) {
		final JPanel editPanel = new JPanel(new GridLayout(0, 2, 5, 2));
		JLabel stockNameLabel = new JLabel("Stock Name : ");
		final JTextField stockNameField = new JTextField(i.getName());
		stockNameField.setColumns(20);
		JLabel stockSymbolLabel = new JLabel("Stock Symbol : ");
		final JTextField stockSymbolField = new JTextField(i.getSymbol());
		stockSymbolField.setColumns(10);
		JLabel stockOpenLabel = new JLabel("Stock Open : ");
		final JTextField stockOpenField = new JTextField(i.getOpen());
		stockOpenField.setColumns(10);
		JLabel stockCloseLabel = new JLabel("Stock Close : ");
		final JTextField stockCloseField = new JTextField(i.getClose());
		stockCloseField.setColumns(10);
		JLabel stockHighLabel = new JLabel("Stock High : ");
		final JTextField stockHighField = new JTextField(i.getHigh());
		stockHighField.setColumns(10);
		JLabel stockLowLabel = new JLabel("Stock Low : ");
		final JTextField stockLowField = new JTextField(i.getLow());
		stockLowField.setColumns(10);
		JLabel stockMarketCapLabel = new JLabel("Stock Market Cap : ");
		final JTextField stockMarketCapField = new JTextField(i.getMCap());
		stockMarketCapField.setColumns(10);
		JButton back = new JButton("Back");
		back.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				gui.remove(editPanel);
				fileMenu.setVisible(true);
				stockMenu.setVisible(true);
				viewMenu.setVisible(true);
				if (panel.equals("base"))
					basePanel.setVisible(true);
				else if (panel.equals("view"))
					viewPanel.setVisible(true);
				gui.revalidate();
				gui.repaint();
				if (panel.equals("view"))
					viewStock();
			}
		});
		JButton submit = new JButton("Submit");
		submit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				i.setName(stockNameField.getText());
				i.setSymbol(stockSymbolField.getText());
				i.setOpen(stockOpenField.getText());
				i.setClose(stockCloseField.getText());
				i.setHigh(stockHighField.getText());
				i.setLow(stockLowField.getText());
				i.setMCap(stockMarketCapField.getText());
				list.set(edit, i);
				gui.remove(editPanel);
				fileMenu.setVisible(true);
				stockMenu.setVisible(true);
				viewMenu.setVisible(true);
				if (panel.equals("base"))
					basePanel.setVisible(true);
				else if (panel.equals("view"))
					viewPanel.setVisible(true);
				gui.revalidate();
				gui.repaint();
				if (panel.equals("view"))
					viewStock();
			}
		});
		JButton remove = new JButton("Remove");
		remove.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				list.remove(edit);
				gui.remove(editPanel);
				fileMenu.setVisible(true);
				stockMenu.setVisible(true);
				viewMenu.setVisible(true);
				if (panel.equals("base"))
					basePanel.setVisible(true);
				else if (panel.equals("view"))
					viewPanel.setVisible(true);
				gui.revalidate();
				gui.repaint();
				if (panel.equals("view"))
					viewStock();
			}
		});

		editPanel.add(stockNameLabel);
		editPanel.add(stockNameField);
		editPanel.add(stockSymbolLabel);
		editPanel.add(stockSymbolField);
		editPanel.add(stockOpenLabel);
		editPanel.add(stockOpenField);
		editPanel.add(stockCloseLabel);
		editPanel.add(stockCloseField);
		editPanel.add(stockHighLabel);
		editPanel.add(stockHighField);
		editPanel.add(stockLowLabel);
		editPanel.add(stockLowField);
		editPanel.add(stockMarketCapLabel);
		editPanel.add(stockMarketCapField);
		editPanel.add(submit);
		editPanel.add(back);
		editPanel.add(remove);
		fileMenu.setVisible(false);
		stockMenu.setVisible(false);
		viewMenu.setVisible(false);
		gui.add(editPanel);
		gui.revalidate();

	}

	/**
	 * Allows user to add a new stock
	 */
	private void newStock() {
		final JPanel editPanel = new JPanel(new GridLayout(0, 2, 5, 2));
		JLabel stockNameLabel = new JLabel("Stock Name : ");
		final JTextField stockNameField = new JTextField();
		stockNameField.setColumns(20);
		JLabel stockSymbolLabel = new JLabel("Stock Symbol : ");
		final JTextField stockSymbolField = new JTextField();
		stockSymbolField.setColumns(10);
		JLabel stockOpenLabel = new JLabel("Stock Open : ");
		final JTextField stockOpenField = new JTextField();
		stockOpenField.setColumns(10);
		JLabel stockCloseLabel = new JLabel("Stock Close : ");
		final JTextField stockCloseField = new JTextField();
		stockCloseField.setColumns(10);
		JLabel stockHighLabel = new JLabel("Stock High : ");
		final JTextField stockHighField = new JTextField();
		stockHighField.setColumns(10);
		JLabel stockLowLabel = new JLabel("Stock Low : ");
		final JTextField stockLowField = new JTextField();
		stockLowField.setColumns(10);
		JLabel stockMarketCapLabel = new JLabel("Stock Market Cap : ");
		final JTextField stockMarketCapField = new JTextField();
		stockMarketCapField.setColumns(10);
		JButton submit = new JButton("Submit");
		submit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				final String stockName = stockNameField.getText();
				final String stockSymbol = stockSymbolField.getText();
				final String stockOpen = stockOpenField.getText();
				final String stockClose = stockCloseField.getText();
				final String stockHigh = stockHighField.getText();
				final String stockLow = stockLowField.getText();
				final String stockMarketCap = stockMarketCapField.getText();
				Model model = new Model(stockName, stockSymbol, stockOpen,
						stockClose, stockHigh, stockLow, stockMarketCap);
				list.add(model);
				gui.remove(editPanel);
				fileMenu.setVisible(true);
				stockMenu.setVisible(true);
				basePanel.setVisible(true);
				gui.revalidate();
				gui.repaint();
			}
		});
		JButton back = new JButton("Back");
		back.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				gui.remove(editPanel);
				fileMenu.setVisible(true);
				stockMenu.setVisible(true);
				basePanel.setVisible(true);
				gui.revalidate();
				gui.repaint();
			}
		});

		editPanel.add(stockNameLabel);
		editPanel.add(stockNameField);
		editPanel.add(stockSymbolLabel);
		editPanel.add(stockSymbolField);
		editPanel.add(stockOpenLabel);
		editPanel.add(stockOpenField);
		editPanel.add(stockCloseLabel);
		editPanel.add(stockCloseField);
		editPanel.add(stockHighLabel);
		editPanel.add(stockHighField);
		editPanel.add(stockLowLabel);
		editPanel.add(stockLowField);
		editPanel.add(stockMarketCapLabel);
		editPanel.add(stockMarketCapField);
		editPanel.add(submit);
		editPanel.add(back);
		fileMenu.setVisible(false);
		stockMenu.setVisible(false);
		basePanel.setVisible(false);
		gui.add(editPanel);
		gui.revalidate();
	}

	/**
	 * Allows user to view a specific stock
	 * 
	 * @param i
	 *            Stock object to be viewed
	 */
	private void openStock(Model i) {
		final JPanel editPanel = new JPanel();
		JLabel space1 = new JLabel();
		space1.setPreferredSize(new Dimension(600, 25));
		JLabel space2 = new JLabel();
		space2.setPreferredSize(new Dimension(600, 25));
		JLabel space3 = new JLabel();
		space3.setPreferredSize(new Dimension(600, 25));
		JLabel space4 = new JLabel();
		space4.setPreferredSize(new Dimension(600, 25));
		JLabel space5 = new JLabel();
		space5.setPreferredSize(new Dimension(600, 25));
		JLabel space6 = new JLabel();
		space6.setPreferredSize(new Dimension(600, 25));
		JLabel space7 = new JLabel();
		space7.setPreferredSize(new Dimension(600, 5));
		JLabel stockNameLabel = new JLabel("Stock Name : ");
		JLabel stockNameField = new JLabel(i.getName());
		JLabel stockSymbolLabel = new JLabel("Stock Symbol : ");
		JLabel stockSymbolField = new JLabel(i.getSymbol());
		JLabel stockOpenLabel = new JLabel("Stock Open : ");
		JLabel stockOpenField = new JLabel(i.getOpen());
		JLabel stockCloseLabel = new JLabel("Stock Close : ");
		JLabel stockCloseField = new JLabel(i.getClose());
		JLabel stockHighLabel = new JLabel("Stock High : ");
		JLabel stockHighField = new JLabel(i.getHigh());
		JLabel stockLowLabel = new JLabel("Stock Low : ");
		JLabel stockLowField = new JLabel(i.getLow());
		JLabel stockMarketCapLabel = new JLabel("Stock Market Cap : ");
		JLabel stockMarketCapField = new JLabel(i.getMCap());
		JButton back = new JButton("Back");
		back.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				gui.remove(editPanel);
				fileMenu.setVisible(true);
				stockMenu.setVisible(true);
				basePanel.setVisible(true);
				gui.revalidate();
				gui.repaint();
			}
		});
		editPanel.add(stockNameLabel);
		editPanel.add(stockNameField);
		editPanel.add(space1);
		editPanel.add(stockSymbolLabel);
		editPanel.add(stockSymbolField);
		editPanel.add(space2);
		editPanel.add(stockOpenLabel);
		editPanel.add(stockOpenField);
		editPanel.add(space3);
		editPanel.add(stockCloseLabel);
		editPanel.add(stockCloseField);
		editPanel.add(space4);
		editPanel.add(stockHighLabel);
		editPanel.add(stockHighField);
		editPanel.add(space5);
		editPanel.add(stockLowLabel);
		editPanel.add(stockLowField);
		editPanel.add(space6);
		editPanel.add(stockMarketCapLabel);
		editPanel.add(stockMarketCapField);
		editPanel.add(space7);
		editPanel.add(back);
		fileMenu.setVisible(false);
		stockMenu.setVisible(false);
		basePanel.setVisible(false);
		gui.add(editPanel);
		gui.revalidate();
	}

	/**
	 * Listener for creating a new stock
	 */
	class addStockItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			newStock();
		}
	}

	/**
	 * Listener for opening a new stock
	 */
	class openStockItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			if (list.isEmpty()) {
				JOptionPane.showMessageDialog(basePanel,
						"You have not added any stocks", "Error",
						JOptionPane.ERROR_MESSAGE);
				return;
			}
			int found = 0;
			String input = JOptionPane.showInputDialog(basePanel,
					"Enter stock name or symbol: ", "Open Stock",
					JOptionPane.PLAIN_MESSAGE);
			if (input == null)
				return;
			if (input.equals(""))
				return;
			for (Model i : list) {
				if (i.getName().equalsIgnoreCase(input)
						|| i.getSymbol().equalsIgnoreCase(input)) {
					openStock(i);
					found = 1;
				}
			}

			if (found == 0 && !list.isEmpty())
				JOptionPane.showMessageDialog(basePanel, input + " not found",
						"Error", JOptionPane.ERROR_MESSAGE);

		}
	}

	/**
	 * Listener for edit a stock
	 */
	class editStockItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			if (list.isEmpty()) {
				JOptionPane.showMessageDialog(basePanel,
						"You have not added any stocks", "Error",
						JOptionPane.ERROR_MESSAGE);
				return;
			}
			int found = 0;
			String input = JOptionPane.showInputDialog(basePanel,
					"Enter stock name or symbol: ", "Edit Stock",
					JOptionPane.PLAIN_MESSAGE);
			if (input == null)
				return;
			if (input.equals(""))
				return;
			for (Model i : list) {
				if (i.getName().equalsIgnoreCase(input)
						|| i.getSymbol().equalsIgnoreCase(input)) {
					basePanel.setVisible(false);
					int edit = 0;
					for (int x = 0; x < list.size(); x++)
						if (i == list.get(x))
							edit = x;
					editStock(i, edit, "base", null);
					found = 1;
				}
			}
			if (found == 0 && !list.isEmpty())
				JOptionPane.showMessageDialog(basePanel, input + " not found",
						"Error", JOptionPane.ERROR_MESSAGE);
		}
	}

	/**
	 * Listener for exiting program
	 */
	class exitItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			int reply = JOptionPane
					.showConfirmDialog(
							basePanel,
							"Are you sure you want to exit? \nAll progress will be lost",
							"Exit", JOptionPane.YES_NO_OPTION);
			if (reply == JOptionPane.YES_OPTION)
				System.exit(0);

		}
	}

	/**
	 * Listener for sorting name in ascending order
	 */
	class nameAscItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (o1.getName().compareTo(o2.getName()) > 0)
					return 1;
				else if (o1.getName().compareTo(o2.getName()) == 0)
					return 0;
				else
					return -1;
			}
		}
	}

	/**
	 * Listener for sorting name in descending order
	 */
	class nameDescItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (o1.getName().compareToIgnoreCase(o2.getName()) > 0)
					return -1;
				else if (o1.getName().compareToIgnoreCase(o2.getName()) == 0)
					return 0;
				else
					return 1;
			}
		}
	}

	/**
	 * Listener for sorting symbol in ascending order
	 */
	class symbolAscItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (o1.getSymbol().compareToIgnoreCase(o2.getSymbol()) > 0)
					return 1;
				else if (o1.getSymbol().compareToIgnoreCase(o2.getSymbol()) == 0)
					return 0;
				else
					return -1;
			}
		}
	}

	/**
	 * Listener for sorting symbol in descending order
	 */
	class symbolDescItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (o1.getSymbol().compareToIgnoreCase(o2.getSymbol()) > 0)
					return -1;
				else if (o1.getSymbol().compareToIgnoreCase(o2.getSymbol()) == 0)
					return 0;
				else
					return 1;
			}
		}
	}

	/**
	 * Listener for sorting stock high in ascending order
	 */
	class highAscItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {
			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (Integer.compare(Integer.parseInt(o1.getHigh()),
						Integer.parseInt(o2.getHigh())) > 0)
					return 1;
				else if (Integer.compare(Integer.parseInt(o1.getHigh()),
						Integer.parseInt(o2.getHigh())) == 0)
					return 0;
				else
					return -1;
			}
		}
	}

	/**
	 * Listener for sorting stock high in descending order
	 */
	class highDescItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (Integer.compare(Integer.parseInt(o1.getHigh()),
						Integer.parseInt(o2.getHigh())) > 0)
					return -1;
				else if (Integer.compare(Integer.parseInt(o1.getHigh()),
						Integer.parseInt(o2.getHigh())) == 0)
					return 0;
				else
					return 1;
			}
		}

	}

	/**
	 * Listener for sorting stock low in ascending order
	 */
	class lowAscItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (Integer.compare(Integer.parseInt(o1.getLow()),
						Integer.parseInt(o2.getLow())) > 0)
					return 1;
				else if (Integer.compare(Integer.parseInt(o1.getLow()),
						Integer.parseInt(o2.getLow())) == 0)
					return 0;
				else
					return -1;
			}
		}
	}

	/**
	 * Listener for sorting stock low in descending order
	 */
	class lowDescItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (Integer.compare(Integer.parseInt(o1.getLow()),
						Integer.parseInt(o2.getLow())) > 0)
					return -1;
				else if (Integer.compare(Integer.parseInt(o1.getLow()),
						Integer.parseInt(o2.getLow())) == 0)
					return 0;
				else
					return 1;
			}
		}
	}

	/**
	 * Listener for sorting stock open in ascending order
	 */
	class sopenAscItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (Integer.compare(Integer.parseInt(o1.getOpen()),
						Integer.parseInt(o2.getOpen())) > 0)
					return 1;
				else if (Integer.compare(Integer.parseInt(o1.getOpen()),
						Integer.parseInt(o2.getOpen())) == 0)
					return 0;
				else
					return -1;
			}
		}
	}

	/**
	 * Listener for sorting stock open in descending order
	 */
	class sopenDescItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (Integer.compare(Integer.parseInt(o1.getOpen()),
						Integer.parseInt(o2.getOpen())) > 0)
					return -1;
				else if (Integer.compare(Integer.parseInt(o1.getOpen()),
						Integer.parseInt(o2.getOpen())) == 0)
					return 0;
				else
					return 1;
			}
		}
	}

	/**
	 * Listener for sorting stock close in ascending order
	 */
	class closeAscItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (Integer.compare(Integer.parseInt(o1.getClose()),
						Integer.parseInt(o2.getClose())) > 0)
					return 1;
				else if (Integer.compare(Integer.parseInt(o1.getClose()),
						Integer.parseInt(o2.getClose())) == 0)
					return 0;
				else
					return -1;
			}
		}
	}

	/**
	 * Listener for sorting stock close in descending order
	 */
	class closeDescItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (Integer.compare(Integer.parseInt(o1.getClose()),
						Integer.parseInt(o2.getClose())) > 0)
					return -1;
				else if (Integer.compare(Integer.parseInt(o1.getClose()),
						Integer.parseInt(o2.getClose())) == 0)
					return 0;
				else
					return 1;
			}
		}
	}

	/**
	 * Listener for sorting market cap in ascending order
	 */
	class mcapAscItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (o1.getMCap().compareTo(o2.getMCap()) > 0)
					return 1;
				else if (o1.getMCap().compareTo(o2.getMCap()) == 0)
					return 0;
				else
					return -1;
			}
		}
	}

	/**
	 * Listener for sorting market cap in descending order
	 */
	class mcapDescItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Collections.sort(list, new stockCompare());
			gui.remove(viewPanel);
			viewStock();
		}

		class stockCompare implements Comparator<Model> {

			@Override
			public int compare(Model o1, Model o2) {
				// write comparison logic here like below , it's just a sample
				if (o1.getMCap().compareToIgnoreCase(o2.getMCap()) > 0)
					return -1;
				else if (o1.getMCap().compareToIgnoreCase(o2.getMCap()) == 0)
					return 0;
				else
					return 1;
			}
		}
	}

	/**
	 * Listener for viewing the list of stocks
	 */
	class viewItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			viewStock();
		}
	}

	/**
	 * Listener for searching for a stock
	 */
	class searchItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			searchStock();
		}
	}

	/**
	 * Listener for adding a new item
	 */
	class addItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			newStock();
		}
	}

	/**
	 * Listener for creating a new list
	 */
	class newItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			int reply = JOptionPane.showConfirmDialog(basePanel,
					"Are you sure you want to create a new stock list? "
							+ "\nAll unsaved progress will be lost", "New",
					JOptionPane.YES_NO_OPTION);
			if (reply == JOptionPane.YES_OPTION) {
				list = new LinkedList<Model>();
				inputFile = "";
			}
			gui.setTitle("Stocks");

		}
	}

	/**
	 * Listener for opening a list
	 */
	class openItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			String input = JOptionPane.showInputDialog(basePanel,
					"Enter file name: ", "Open Saved Stocks",
					JOptionPane.PLAIN_MESSAGE);
			if (input == null || input.equals(""))
				return;
			List<Model> openList = utility.parseInput(input);
			if (openList.isEmpty()) {
				JOptionPane.showMessageDialog(basePanel, input + " not found",
						"Error", JOptionPane.ERROR_MESSAGE);
				return;
			} else {
				list = openList;
				inputFile = input;
			}
			gui.setTitle("Stocks (" + inputFile + ")");
		}
	}

	/**
	 * Listener for saving a list
	 */
	class saveItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Utility utility = new Utility();
			String fileName = new String();
			if (list.isEmpty()) {
				JOptionPane.showMessageDialog(basePanel,
						"You have not added any stocks", "Error",
						JOptionPane.ERROR_MESSAGE);
				return;
			}
			if (inputFile.equals("")) {
				String input = JOptionPane.showInputDialog(basePanel,
						"Enter file name: ", "Save", JOptionPane.PLAIN_MESSAGE);
				if (input == null)
					return;
				if (input.equals("")) {
					JOptionPane.showMessageDialog(basePanel,
							"File name missing", "Error",
							JOptionPane.ERROR_MESSAGE);
					return;
				}
				fileName = input;
			} else
				fileName = inputFile;
			utility.parseOutput(list, fileName);
		}
	}

	/**
	 * Listener for saving a list with new name
	 */
	class saveAsItemListener implements ActionListener {
		public void actionPerformed(ActionEvent evt) {
			Utility utility = new Utility();
			if (list.isEmpty()) {
				JOptionPane.showMessageDialog(basePanel,
						"You have not added any stocks", "Error",
						JOptionPane.ERROR_MESSAGE);
				return;
			}
			String input = JOptionPane.showInputDialog(basePanel,
					"Enter file name: ", "Save As", JOptionPane.PLAIN_MESSAGE);
			if (input == null)
				return;
			if (input.equals("")) {
				JOptionPane.showMessageDialog(basePanel, "File name missing",
						"Error", JOptionPane.ERROR_MESSAGE);
				return;
			}
			inputFile = input;
			utility.parseOutput(list, input);
			gui.setTitle("Stocks (" + inputFile + ")");
		}
	}
}
