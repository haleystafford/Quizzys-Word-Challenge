#include <iostream>
#include <string>
#include "console.h"
#include "testing/lettertile.h"
#include "set.h"
#include "grid.h"
#include "lexicon.h"
#include "vector.h"
#include "simpio.h"
using namespace std;

/* * * * * * * * * * * * * * * * INTERNAL FUNCTIONS * * * * * * * * * * * * * * * */

/** Enables LetterTile struct to be printed to screen for viewing and debugging
 * purposes.
 */
ostream& operator<< (ostream& out, const LetterTile& tile) {
    return out << "[ " << quotedVersionOf(tile.letter) << ", " << tile.depth << ", " << tile.uniqueID << " ]";
}

/** The stringToLetterTile() function takes in a string s of letters and an int
 * depth representing the ring layer of those letters where 1 = outer, 2 = middle,
 * and 3 = inner ring. It then returns a vector of LetterTiles where LetterTile.letter
 * equals the a single character of the string, LetterTile.depth equals the depth
 * of that letter, and LetterTile.uniqueID equals the unique ID of that letter.
 */
Set<LetterTile> stringToLetterTile(string s, int depth){
    Set<LetterTile> result;
    s = toLowerCase(s);
    int i = 1;
    for (char letter:s){
        string newLetter = charToString(letter);
        LetterTile newTile(newLetter,depth,i);
        result.add(newTile);
        i++;
    }
    return result;
}

/** The stringToCharVector() function takes in a string input and outputs a
 * vector of char populated by every character in the original string input.
 */
Vector<char> stringToCharVector(string s){
    Vector<char> result;
    for (char letter:s){
        result.add(toUpperCase(letter));
    }
    return result;
}

/** The verifyInput() function takes in a string input and parses through
 * each of its characters to ensure that they are valid letters. If the
 * string contains any non-alphanumeric characters, verifyInput() returns
 * false;
 */
bool verifyInput(string s){
    bool result = true;
    for (char letter:s){
        if (!isalpha(letter)){
            result = false;
        }
    }
    return result;
}

/** The buildBoard() function takes in a Vector containing each of the
 * vectors of characters for the outer, middle, and inner rings of
 * letters and prints a Grid<char> representing the gameboard.
 */
void buildBoard(Vector<Vector<char>> threeRings){
    Grid<char> board;
    board.resize(5,5);

    Vector<char> outerRing = threeRings[0];
    Vector<char> middleRing = threeRings[1];
    Vector<char> innerRing = threeRings[2];

/* Populate board with ring letters clockwise */ // HELP: is there a way to do this prettier
    board[0][0] = outerRing[0];
    board[0][1] = outerRing[1];
    board[0][2] = outerRing[2];
    board[0][3] = outerRing[3];
    board[0][4] = outerRing[4];
    board[1][4] = outerRing[5];
    board[2][4] = outerRing[6];
    board[3][4] = outerRing[7];
    board[4][4] = outerRing[8];
    board[4][3] = outerRing[9];
    board[4][2] = outerRing[10];
    board[4][1] = outerRing[11];
    board[4][0] = outerRing[12];
    board[3][0] = outerRing[13];
    board[2][0] = outerRing[14];
    board[1][0] = outerRing[15];
    board[1][1] = middleRing[0];
    board[1][2] = middleRing[1];
    board[1][3] = middleRing[2];
    board[2][3] = middleRing[3];
    board[3][3] = middleRing[4];
    board[3][2] = middleRing[5];
    board[3][1] = middleRing[6];
    board[2][1] = middleRing[7];
    board[2][2] = innerRing[0];

    cout << endl;
    cout << "|| GAMEBOARD ||" << endl;
    for (int r = 0; r < 5; r++){
        for (int c = 0; c < 5; c++){
            cout << " " << board[r][c] << " ";
        }
        cout << endl;
    }
}

/** The getBoardInputs() function takes in an empty Set of LetterTile
 * structs 'availableTiles' by reference and asks the user to give a
 * 16-letter input of char for the outerRing of letters, an 8-letter
 * input of char for the middleRing of letters, and a single-letter
 * input for the innerRing of the gameboard. It gives an error if any
 * input is invalid and updates 'availableTiles' to match the user's input.
 * It also calls the buildBoard() function to print out the user's input
 * as a Grid of char.
 */
void getBoardInputs(Set<LetterTile>& availableTiles){
    Vector<Vector<char>> threeRings(3); // stores the outer, middle and inner rings of letters

    /* Gets user inputs for outer, middle, and inner rings of letters */
    while (true) {
        cout << endl << endl;
        string outerRingInput = getLine("Enter a 16-letter input for the outer ring of letters: ");
        while (!verifyInput(outerRingInput) || outerRingInput.length() != 16){
            cout << "Invalid input." << endl;
            outerRingInput = getLine("Enter a 16-letter input for the outer ring of letters: ");
        }
        Set<LetterTile> outerTiles = stringToLetterTile(outerRingInput,1);

        string middleRingInput = getLine("Enter an 8-letter input for the middle ring of letters: ");
        while (!verifyInput(middleRingInput) || middleRingInput.length() != 8){
            cout << "Invalid input." << endl;
            middleRingInput = getLine("Enter an 8-letter input for the middle ring of letters: ");
        }
        Set<LetterTile> middleTiles = stringToLetterTile(middleRingInput,2);

        string innerRingInput = getLine("Enter a single-character input for the innermost letter: ");
        while (!verifyInput(innerRingInput) || innerRingInput.length() != 1){
            cout << "Invalid input." << endl;
            innerRingInput = getLine("Enter a single-character input for the innermost letter: ");
        }
        Set<LetterTile> innerTile = stringToLetterTile(innerRingInput,3);

        /* Update availableTiles set of LetterTiles */
        availableTiles = outerTiles + middleTiles + innerTile;

        /* Populate threeRings Vector<Vector<char>> */
        threeRings[0] = stringToCharVector(outerRingInput);
        threeRings[1] = stringToCharVector(middleRingInput);
        threeRings[2] = stringToCharVector(innerRingInput);
        buildBoard(threeRings);
        return;
    }
}

/** The findLongestWords() function takes in a set of words and returns
 * a set containing all of the longest words in the set.
 */
Set<string> findLongestWords(Set<string> allWords){
    Set<string> longestWords = {""};
    for (string word:allWords){
        string curLongest = longestWords.first();
        if (word.length() > curLongest.length()){
            longestWords.clear();
            longestWords = longestWords + word;
        }
        else if (word.length() == curLongest.length()){
            longestWords = longestWords + word;
        }
    }
    return longestWords;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            PROVIDED HELPER FUNCTION                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/** updateAvailableTiles() passes in a Set of LetterTiles 'remainingTiles' and a
 * current LetterTile 'curTile' and alters the Set of LetterTiles by removing
 * any tile whose depth is less that that of the current LetterTile.
 */
Set<LetterTile> updateAvailableTiles(Set<LetterTile> availableTiles, LetterTile curTile){
    Set<LetterTile> newAvailableTiles = availableTiles - curTile;
    for (LetterTile tile:availableTiles){
        if (curTile.depth > tile.depth){
            newAvailableTiles.remove(tile);
        }
    }
    return newAvailableTiles;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                 SOLUTION ONE                                  */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/** The findAllWordsHelper() function takes in a Set of LetterTile 'availableTiles',
 * a string 'curWord', a Lexicon 'lex' dictionary, and a Set of string 'validWords'
 * by reference and updates the 'validWords' set with every possible word that can
 * be made from the letters in 'remainingTiles' through recursive backtracking
 * and pruning.
 */
// void findAllWordsHelper(Set<LetterTile> availableTiles, string curWord, Lexicon& lex, Set<string>& validWords){
//    if (lex.contains(curWord) && curWord.length() >= 4 && curWord.length() <= 8){
//        validWords.add(curWord);
//    }
//    if (!lex.containsPrefix(curWord) || availableTiles.isEmpty()){
//        return; // Base Case: return if building invalid word or if no more tiles
//    }
//    for (LetterTile tile: availableTiles){
//        Set<LetterTile> newRemainingTiles = updateAvailableTiles(availableTiles,tile);
//        string newWord = curWord + tile.letter;
//        findAllWordsHelper(newRemainingTiles, newWord, lex, validWords); // Recursive Case: explore if building valid word
//    }
//}

/** The finalAllWords() function takes in a Lexicon dictionary called 'lex' and
 * a Set of Letter Tiles 'availableTiles', calls the findAllWordsHelper()
 * function, and prints and returns the Set of strings it creates that contains
 * every valid word in the gameboard.
 */
//Set<string> findAllWords(Lexicon& lex, Set<LetterTile> availableTiles){
//    string curWord = "";
//    Set<string> validWords;
//    findAllWordsHelper(availableTiles, curWord, lex, validWords);
//    cout << validWords << endl;
//    return validWords;
//}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                 SOLUTION TWO                                  */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/** The findAllWordsHelper() function takes in a Set of LetterTile 'availableTiles',
 * a string 'curWord', a Lexicon 'lex' dictionary, and a Set of string 'validWords'
 * by reference and returns a 'validWords' set with every possible word that can
 * be made from the letters in 'remainingTiles' through recursive backtracking
 * and pruning.
 */
Set<string> findAllWordsHelper(Set<LetterTile> availableTiles, string curWord, Lexicon& lex, Set<string>& validWords){
    for (LetterTile tile: availableTiles){
        Set<LetterTile> newRemainingTiles = updateAvailableTiles(availableTiles,tile);
        string newWord = curWord + tile.letter;
        if (lex.contains(newWord) && newWord.length() > 3 && newWord.length() < 9){
            validWords.add(newWord);
        }
        if (lex.containsPrefix(newWord) && !newRemainingTiles.isEmpty() && newWord.length() < 8){
            validWords + findAllWordsHelper(newRemainingTiles, newWord, lex, validWords); // Recursive Case: explore if building valid word
        }
    }
    return validWords;
}

/** The finalAllWords() function takes in a Lexicon dictionary called 'lex' and
 * a Set of Letter Tiles 'availableTiles', calls the findAllWordsHelper()
 * function, and prints and returns the Set of strings it creates that contains
 * every valid word in the gameboard.
 */
Set<string> findAllWords(Lexicon& lex, Set<LetterTile> availableTiles){
    string curWord = "";
    Set<string> validWords;
    validWords = findAllWordsHelper(availableTiles, curWord, lex, validWords);
    cout << validWords << endl;
    return validWords;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                   TEST CASES                                  */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/** Copied below copied from Assignment 3 **/
/*
 * Test helper function to return shared copy of Lexicon. Use to
 * avoid (expensive) re-load of word list on each test case. */

static Lexicon& sharedLexicon() {
    static Lexicon lex("EnglishWords.txt");
    return lex;
}

/** Code above copied from Assignment 3 **/

PROVIDED_TEST("Verify findAllWords functionality, no tiles"){
    Set<LetterTile> availableTiles = {};
    Lexicon lex = sharedLexicon();
    Set<string> validWords = findAllWords(lex, availableTiles);
    EXPECT_EQUAL(validWords,{});
}

PROVIDED_TEST("Verify findAllWords functionality, no valid words"){
    Lexicon lex = sharedLexicon();
    Set<LetterTile> outerTiles = stringToLetterTile("",1);
    Set<LetterTile> middleTiles = stringToLetterTile("WEXXXXXX",2);
    Set<LetterTile> innerTile = stringToLetterTile("R",3);
    Set<LetterTile> availableTiles = outerTiles + middleTiles + innerTile;
    Set<string> validWords = findAllWords(lex, availableTiles);
    EXPECT_EQUAL(validWords,{});
}

PROVIDED_TEST("Verify findAllWords functionality, no valid words"){
    Lexicon lex = sharedLexicon();
    Set<LetterTile> outerTiles = stringToLetterTile("AR",1);
    Set<LetterTile> middleTiles = stringToLetterTile("O",2);
    Set<LetterTile> innerTile = stringToLetterTile("R",3);
    Set<LetterTile> availableTiles = outerTiles + middleTiles + innerTile;
    Set<string> validWords = findAllWords(lex, availableTiles);
    EXPECT_EQUAL(validWords,{});
}

PROVIDED_TEST("Verify findAllWords functionality, no valid words"){
    Lexicon lex = sharedLexicon();
    Set<LetterTile> outerTiles = stringToLetterTile("ZJQIOOJ",1);
    Set<LetterTile> middleTiles = stringToLetterTile("X",2);
    Set<LetterTile> innerTile = stringToLetterTile("X",3);
    Set<LetterTile> availableTiles = outerTiles + middleTiles + innerTile;
    Set<string> validWords = findAllWords(lex, availableTiles);
    EXPECT_EQUAL(validWords,{});
}

PROVIDED_TEST("Verify findAllWords functionality, one valid word"){
    Lexicon lex = sharedLexicon();
    Set<LetterTile> outerTiles = stringToLetterTile("MOOO",1);
    Set<LetterTile> middleTiles = stringToLetterTile("",2);
    Set<LetterTile> innerTile = stringToLetterTile("N",3);
    Set<LetterTile> availableTiles = outerTiles + middleTiles + innerTile;
    Set<string> validWords = findAllWords(lex, availableTiles);
    EXPECT_EQUAL(validWords,{"moon"});
}

PROVIDED_TEST("Verify findAllWords functionality, seven valid words"){
    Lexicon lex = sharedLexicon();
    Set<LetterTile> outerTiles = stringToLetterTile("POR",1);
    Set<LetterTile> middleTiles = stringToLetterTile("WE",2);
    Set<LetterTile> innerTile = stringToLetterTile("R",3);
    Set<LetterTile> availableTiles = outerTiles + middleTiles + innerTile;
    Set<string> validWords = findAllWords(lex, availableTiles);
    EXPECT_EQUAL(validWords,
                 {"pore", "power", "prow", "prower", "rope", "roper", "rower"});
}

PROVIDED_TEST("Verify findAllWords functionality, eight valid words"){
    Lexicon lex = sharedLexicon();
    Set<LetterTile> outerTiles = stringToLetterTile("qxvtIZxUwzQixzi",1);
    Set<LetterTile> middleTiles = stringToLetterTile("jpquxzd",2);
    Set<LetterTile> innerTile = stringToLetterTile("u",3);
    Set<LetterTile> availableTiles = outerTiles + middleTiles + innerTile;
    Set<string> validWords = findAllWords(lex, availableTiles);
    EXPECT_EQUAL(validWords.size(), 8);
}

PROVIDED_TEST("Verify findAllWords functionality, 65 valid words"){
    Lexicon lex = sharedLexicon();
    Set<LetterTile> outerTiles = stringToLetterTile("qxetIZxUwkQixzr",1);
    Set<LetterTile> middleTiles = stringToLetterTile("jpquxzd",2);
    Set<LetterTile> innerTile = stringToLetterTile("u",3);
    Set<LetterTile> availableTiles = outerTiles + middleTiles + innerTile;
    Set<string> validWords = findAllWords(lex, availableTiles);
    EXPECT_EQUAL(validWords.size(), 65);
}

PROVIDED_TEST("Verify findAllWords functionality, 400 valid words"){
    Lexicon lex = sharedLexicon();
    Set<LetterTile> outerTiles = stringToLetterTile("zqwrtuopjikqezxv",1);
    Set<LetterTile> middleTiles = stringToLetterTile("ugztyeio",2);
    Set<LetterTile> innerTile = stringToLetterTile("t",3);
    Set<LetterTile> availableTiles = outerTiles + middleTiles + innerTile;
    Set<string> validWords = findAllWords(lex, availableTiles);
    EXPECT_EQUAL(validWords.size(), 400);
}

/* Write your STUDENT_TEST functions here */

STUDENT_TEST("Allow user to input letter tiles"){
    Lexicon lex = sharedLexicon();
    Set<LetterTile> availableTiles;
    getBoardInputs(availableTiles);
    Set<string> validWords = findAllWords(lex, availableTiles);
    cout << "Longest Words: " << findLongestWords(validWords) << endl;


}

