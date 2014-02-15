import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

/**
 * File: LexicalAnalyzer.java
 * 
 * @author Charbel Boutros
 * 
 *         Parses and returns tokens from an InputStream or file
 */

public class LexicalAnalyzer {
	// Enumerations
	public enum CHAR_CLASS {
		LETTER, DIGIT, SYMBOL
	}

	// Private instance fields
	private boolean eofReached = false;
	private String lexeme;
	private List<String> tokenList = new ArrayList<String>();
	private List<String> lexemeList = new ArrayList<String>();
	private char nextChar;
	private char peekChar;
	private CHAR_CLASS charClass;
	private CHAR_CLASS peekCharClass;
	private String nextToken;
	private InputStream input;

	/**
	 * Input stream constructor
	 * 
	 * @param userInput
	 *            Input file with user's input
	 */
	public LexicalAnalyzer(InputStream userInput) {
		input = userInput;
		getChar();
		while (eofReached == false)
			analyze();
	}

	/**
	 * File name constructor
	 * 
	 * @param fileName
	 *            used to retrieve data from local file
	 */
	public LexicalAnalyzer(String fileName) {
		try {
			// opens input file
			FileInputStream fstream = new FileInputStream(fileName);
			BufferedReader br = new BufferedReader(new InputStreamReader(
					fstream));
			String strLine = new String();
			String str = new String();
			// read file line by line and stores in Arraylist
			while ((strLine = br.readLine()) != null)
				str += strLine;
			// String to inputStream
			input = new ByteArrayInputStream(str.getBytes());
			fstream.close(); // close input stream
		} catch (Exception e) {// catch exception if any
			System.err.println("Error: " + e.getMessage());
		}
		getChar();
		while (eofReached == false)
			analyze();
	}

	/**
	 * Builds tokens and prints out tokens information
	 */
	public void analyze() {
		lexeme = new String();
		while (Character.isWhitespace(nextChar)) {
			getChar();
		}
		if (eofReached == true) {
			System.out.println("eof reached");

			return;
		}
		switch (charClass) {
		case LETTER:
			handleLetter();
			break;
		case DIGIT:
			handleDigit();
			break;
		case SYMBOL:
			handleSymbol();
			break;
		}
		tokenList.add(nextToken);
		lexemeList.add(lexeme);
	}

	/**
	 * Retrieves the next available character from stream
	 */
	public void getChar() {
		int i;
		try {
			if ((i = input.read()) != -1)
				nextChar = (char) i;
			else {
				charClass = null;
				eofReached = true;
				return;
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		// Checks character type
		if (Character.isDigit(nextChar))
			charClass = CHAR_CLASS.DIGIT;
		else if (Character.isLetter(nextChar))
			charClass = CHAR_CLASS.LETTER;
		else
			charClass = CHAR_CLASS.SYMBOL;
	}

	/**
	 * Concatenates next character to lexeme
	 * 
	 * @param status
	 *            status 1 - add one character, status 2 - add two characters
	 */
	public void addChar(int status) {
		if (status == 2) {
			lexeme += nextChar;
			lexeme += peekChar;
		} else
			lexeme += nextChar;
	}

	/**
	 * Peeks at the next character to determine token identification
	 */
	public void peekCharacter() {
		int i;
		try {
			if ((i = input.read()) != -1)
				peekChar = (char) i;
			else {
				eofReached = true;
				return;
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		// Checks character type
		if (Character.isDigit(peekChar))
			peekCharClass = CHAR_CLASS.DIGIT;
		else if (Character.isLetter(peekChar))
			peekCharClass = CHAR_CLASS.LETTER;
		else
			peekCharClass = CHAR_CLASS.SYMBOL;
	}

	/**
	 * Removes next token from list and returns it to caller
	 */
	public String nextToken() {
		if (tokenList.size() > 0) {
			String token = tokenList.get(0);
			tokenList.remove(0);
			return token;
		}
		return "EOF";
	}

	/**
	 * Returns the next available token, but does not remove from token list
	 */
	public String peekToken() {
		if (tokenList.size() > 0) {
			String token = tokenList.get(0);
			return token;
		}
		return "EOF";
	}

	/**
	 * Input handler for letters
	 */
	public void handleLetter() {
		addChar(1);
		getChar();
		while (charClass == CHAR_CLASS.LETTER || charClass == CHAR_CLASS.DIGIT) {
			addChar(1);
			getChar();
			if (nextChar == '_') {
				addChar(1);
				getChar();
			}
		}
		nextToken = "IDENT";
		literalLookup();
	}

	/**
	 * Input handler for digits
	 */
	public void handleDigit() {
		addChar(1);
		getChar();
		while (charClass == CHAR_CLASS.DIGIT) {
			addChar(1);
			getChar();
		}
		if (charClass == CHAR_CLASS.LETTER)
			try {
				throw new IllegalVariableException(
						"\nVariable names cannot start with numbers: " + lexeme
								+ nextChar + "...");
			} catch (IllegalVariableException e) {
				e.printStackTrace();
				System.exit(0);

			}
		nextToken = "INT_LIT";
	}

	/**
	 * Input handler for symbols
	 */
	public void handleSymbol() {
		try {
			symbolLookup();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(0);
		}
	}

	/**
	 * Symbol lookup used to identify token types
	 */
	public void symbolLookup() throws Exception {
		peekCharacter();
		switch (nextChar) {
		case '&':
			if (peekChar == '&') {
				addChar(2);
				getChar();
				nextToken = "AND";
			} else {
				addChar(1);
				nextChar = peekChar;
				charClass = peekCharClass;
				nextToken = "INVALIDAND";
			}
			break;
		case '|':
			if (peekChar == '|') {
				addChar(2);
				getChar();
				nextToken = "OR";
			} else {
				addChar(1);
				nextChar = peekChar;
				charClass = peekCharClass;
				nextToken = "INVALIDOR";
			}
			break;
		case '=':
			if (peekChar == '=') {
				addChar(2);
				getChar();
				nextToken = "COMPAREEQUAL";
			} else {
				addChar(1);
				nextChar = peekChar;
				charClass = peekCharClass;
				nextToken = "ASSIGNEQUAL";
			}
			break;
		case '!':
			if (peekChar == '=') {
				addChar(2);
				getChar();
				nextToken = "NOTEQUAL";
			} else {
				addChar(1);
				nextChar = peekChar;
				charClass = peekCharClass;
				nextToken = "NOT";
			}
			break;
		case '<':
			if (peekChar == '=') {
				addChar(2);
				getChar();
				peekChar = ' ';
				nextToken = "LESSTHANEQUAL";
			} else {
				addChar(1);
				nextChar = peekChar;
				charClass = peekCharClass;
				nextToken = "LESSTHAN";
			}
			break;
		case '>':
			if (peekChar == '=') {
				addChar(2);
				getChar();
				nextToken = "GREATERTHANEQUAL";
			} else {
				addChar(1);
				nextChar = peekChar;
				nextToken = "GREATERTHAN";
			}
			break;
		case '+':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "ADD_OP";
			break;
		case '-':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "SUB_OP";
			break;
		case '*':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "MULT_OP";
			break;
		case '/':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "DIV_OP";
			break;
		case '(':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "LEFTPAREN";
			break;
		case ')':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "RIGHTPAREN";
			break;
		case '[':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "LEFTBRACKET";
			break;
		case ']':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "RIGHTBRACKET";
			break;
		case '\'':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "SINGLEQUOTE";
			break;
		case '\"':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "DOUBLEQUOTE";
			break;
		case ';':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "SEMICOLON";
			break;
		case ':':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "COLON";
			break;
		case '$':
			addChar(1);
			if (peekCharClass == CHAR_CLASS.LETTER && !eofReached) {
				addChar(1);
				getChar();
				while (charClass == CHAR_CLASS.LETTER
						|| charClass == CHAR_CLASS.DIGIT) {
					addChar(1);
					getChar();
				}
				nextToken = "IDENT";
				literalLookup();
			} else {
				nextChar = peekChar;
				charClass = peekCharClass;
				nextToken = "DOLLARSIGN";
			}
			break;
		case '.':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "PERIOD";
			break;
		case '_':
			addChar(1);
			if (peekCharClass == CHAR_CLASS.LETTER && !eofReached) {
				addChar(1);
				getChar();
				while (charClass == CHAR_CLASS.LETTER
						|| charClass == CHAR_CLASS.DIGIT) {
					addChar(1);
					getChar();
				}
				nextToken = "IDENT";
				literalLookup();
			} else {
				nextChar = peekChar;
				charClass = peekCharClass;
				nextToken = "UNDERSCORE";
			}
			break;
		case '\\':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "BACKSLASH";
			break;
		case '%':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "PERCENT";
			break;
		case '?':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "QUESTIONMARK";
			break;
		case '{':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "LEFTTCURLYBRACE";
			break;
		case '}':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "RIGHTCURLYBRACE";
			break;
		case ',':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "COMMA";
			break;
		case '@':
			addChar(1);
			nextChar = peekChar;
			charClass = peekCharClass;
			nextToken = "AT-SYMBOL";
			break;
		}
	}

	/**
	 * Literal lookup used to identify string literal types
	 */
	public void literalLookup() {
		switch (lexeme) {
		case "null":
			nextToken = "NULL";
			break;
		case "true":
			nextToken = "TRUE";
			break;
		case "false":
			nextToken = "FALSE";
			break;
		case "this":
			nextToken = "THIS";
			break;
		case "new":
			nextToken = "NEW";
			break;
		case "int":
			nextToken = "INT_LIT";
			break;
		case "char":
			nextToken = "CHAR_LIT";
			break;
		case "String":
			nextToken = "STRING_LIT";
			break;
		case "class":
			nextToken = "CLASS";
			break;
		case "extends":
			nextToken = "EXTENDS";
			break;
		case "static":
			nextToken = "STATIC";
			break;
		case "boolean":
			nextToken = "BOOLEAN";
			break;
		case "void":
			nextToken = "VOID";
			break;
		case "public":
			nextToken = "PUBLIC";
			break;
		case "throws":
			nextToken = "THROWS";
			break;
		case "if":
			nextToken = "IF";
			break;
		case "else":
			nextToken = "ELSE";
			break;
		case "while":
			nextToken = "WHILE";
			break;
		case "for":
			nextToken = "FOR";
			break;
		case "return":
			nextToken = "RETURN";
			break;
		case "break":
			nextToken = "BREAK";
			break;
		case "continue":
			nextToken = "CONTINUE";
			break;
		case "super":
			nextToken = "SUPER";
			break;
		}
	}
}

@SuppressWarnings("serial")
class IllegalVariableException extends Exception {
	public IllegalVariableException(String message) {
		super(message);
	}
}
