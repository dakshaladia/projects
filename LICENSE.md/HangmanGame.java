

import java.util.*;
import java.io.*;

class FileToString{
		static String readFile(String file) throws IOException {
	    BufferedReader reader = new BufferedReader(new FileReader (file));
	    String         line = null;
	    StringBuilder  stringBuilder = new StringBuilder();
	    String         ls = System.getProperty("line.separator");

	    try {
	        while((line = reader.readLine()) != null) {
	            stringBuilder.append(line);
	            stringBuilder.append(ls);
	        }

	        return stringBuilder.toString();
	    } finally {
	        reader.close();
	    }
	}

}
class Hangman{
	String secret, guess;
	ArrayList<Character> guessedLetters;
	char[] alphabet = "abcdefghijklmnopqrstuvwxyz".toCharArray();

	Hangman(){
		secret = "";
		guess="";
		guessedLetters = new ArrayList<Character>();

	}

	boolean contains(char someChar, ArrayList<Character> someArray){
		for(int i=0;i<someArray.size();i++)
			if(someChar == someArray.get(i))
				return true;
		return false;
	}

	boolean isWordGuessed(String secretWord, ArrayList<Character> lettersGuessed){
		int num =0;
		for (int i=0;i<secretWord.length(); i++){
			if (contains(secretWord.charAt(i),lettersGuessed))
				num+=1;
		}
		if (num==secretWord.length())
			return true;
		else
			return false;


	}
	// boolean isCharGuessed(char secretWord, char[] lettersGuessed){
	// 	int num =0;
	// 	for (int i=0;i<secretWord.length(); i++){
	// 		if (contains(secretWord.charAt(i),lettersGuessed))
	// 			num+=1;
	// 	}
	// 	if (num==secretWord.length())
	// 		return true;
	// 	else
	// 		return false;


	// }

	String getGuessedWord(String secretWord, ArrayList<Character> lettersGuessed){
		String guess="";
		for(int i=0; i<secretWord.length(); i++){

			if (contains(secretWord.charAt(i),lettersGuessed)){
				guess += secretWord.charAt(i);
				guess += ' ';
			}
			else{
				guess+= '_';
				guess+=' ';
			}
		}
		return guess;

	}

	String getAvailableLetters(ArrayList<Character> lettersGuessed){
		ArrayList<Character> alpha = new ArrayList<Character>();
		for(char c : alphabet){alpha.add(c);}



		for(int i=0; i<lettersGuessed.size(); i++){
			alpha.remove(lettersGuessed.get(i));
		}


		String availableLetters="";
		for(int i=0; i<alpha.size();i++) {
			availableLetters+=alpha.get(i);
		}

		return availableLetters;
	}

	void start(String secret){
		this.secret = secret;
		char guess;
		Scanner in = new Scanner(System.in);
		ArrayList<Character>secretList = new ArrayList<Character>();
		for(char c : secret.toCharArray()){secretList.add(c);}


		System.out.println("\n\n\t\t\t\tWelcome to Hangman");
		System.out.println("\t\tI am thinking of a word that is "+ secret.length() + " letters long.");
		System.out.println("\t\t------------------------------------------------");

		int nguess=8;
		while (nguess>0){
			System.out.println("\t\tYou have "+ nguess + " guesses left.");
			System.out.println("\t\tAvailable letters: "+getAvailableLetters(guessedLetters));
			System.out.print("\t\tYour guess: ");
			guess = (in.nextLine()).charAt(0);
			String guessString = Character.toString(guess);

			if(isWordGuessed(guessString, guessedLetters)){
				System.out.println("\t\tOops! You've already guessed that letter: " + getGuessedWord(secret, guessedLetters));
				System.out.println("\t\t------------------------------------------------");
			}

			else if (isWordGuessed(guessString, secretList)){
				guessedLetters.add(guess);
				System.out.println("\t\tGood guess: "+ getGuessedWord(secret,guessedLetters));
				System.out.println("\t\t------------------------------------------------");
				if(isWordGuessed(secret,guessedLetters))
					break;

			}else{
				guessedLetters.add(guess);
				nguess--;
				System.out.println("\t\tOops! That letter is not in my word: "+ getGuessedWord(secret,guessedLetters));
				System.out.println("\t\t------------------------------------------------");

			}

		}

		if(isWordGuessed(secret,guessedLetters))
			System.out.println("\t\tCongratulations, you won!");
		else if (nguess==0)
			System.out.println("\t\tSorry, you ran out of guesses. The word was "+ secret+".");


	}


}

class HangmanGame{
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		Hangman h = new Hangman();
		int u=0;

		do{
			String[] words={""};
			try{
				words = FileToString.readFile(args[0]).split(" ");
			}

			catch (IOException e){
				System.out.println("\t\tIOException");
			}
			catch (ArrayIndexOutOfBoundsException e){
				System.out.println("\t\tGive file address - java HangmanGame /path/to/words.txt");
				return;
			}

			Random rand = new Random();
			int n = rand.nextInt(words.length);

			h.start(words[n]);

			System.out.print("\t\tEnter 0 to play again\n\t\tYour Input: ");

			try{
				u=in.nextInt();
			}
			catch (InputMismatchException e) {
				u=1;
			}
		}while(u==0);

	}
}
