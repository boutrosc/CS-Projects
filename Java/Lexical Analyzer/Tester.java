import java.io.InputStream;
import java.io.ByteArrayInputStream;

public class Tester {

	public static void main(String[] args) {
		// Tests program using input file
//		LexicalAnalyzer tokenizer = new LexicalAnalyzer("ParserTestInput.txt"); 

		 String str = "[]&&||==!=<><=>=+-*/()!INT CHAR STRING A 324 he_llo _world $test test /";
		 InputStream input = new ByteArrayInputStream(str.getBytes());
		 LexicalAnalyzer tokenizer = new LexicalAnalyzer(input); // Tests program using InputStream


		System.out.println("Peek token is: "+tokenizer.peekToken());
		String token = " ";
		while (token != "EOF") {
			token = tokenizer.nextToken();
			System.out.println("Next token is: " + token);
		}
	}

}
