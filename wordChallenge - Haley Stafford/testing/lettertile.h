#pragma once
#include "lexicon.h"
#include "set.h"
#include <string>
#include "testing/MemoryDiagnostics.h"

/**
 * Type representing a letter tile in the gameboard.
 */
struct LetterTile {
    std::string letter;    /// stores tile's letter as a string
    int depth;             /// stores ring depth of tile where 1 = outer, 2 = middle, 3 = inner ring
    int uniqueID;          /// stores tile's unique ID to differentiate tiles with the same letter and depth
    int value;             /// stores tile's point value which is calculated from letter and depth

    /**
     * This LetterTile constructor initializes the letter and depth
     * of a letter tile where the first parameter is a string letter,
     * the second parameter is an int depth, and the final parameter
     * is an int for the tile's unique ID. The tile's point value is
     * determined by the depth level and specific tile letter. It
     * cannot be initialized to a different value.
     *
     * Ex) LetterTile tile("a", 1, 13);
     *
     */
    LetterTile(std::string singleLetter, int layerNumber, int id){
        letter = singleLetter;
        depth = layerNumber;
        uniqueID = id;

        int letterMultiplier = 0;
        Set<std::string> onePoint = {"a","e","i","l","n","o","s","r"};
        Set<std::string> twoPoint = {"b","g","d","h","c","m","t"};
        Set<std::string> threePoint = {"f","u","k","y"};
        Set<std::string> fourPoint = {"v","w","p"};
        Set<std::string> fivePoint = {"x","z","q"};

        if (onePoint.contains(letter)){
            letterMultiplier = 1;
        }
        else if (twoPoint.contains(letter)){
            letterMultiplier = 2;
        }
        else if (threePoint.contains(letter)){
            letterMultiplier = 3;
        }
        else if (fourPoint.contains(letter)){
            letterMultiplier = 4;
        }
        else {
            letterMultiplier = 5;
        }

        value = depth + (depth - 1)*letterMultiplier;
    }
};

/**
 * Allows LetterTile to be comparable and a value of a Set.
 */
bool operator< (const LetterTile& lhs, const LetterTile& rhs) {
    using namespace stanfordcpplib::collections;
    return compareTo(lhs.letter,    rhs.letter,
                     lhs.depth, rhs.depth,
                     lhs.uniqueID, rhs.uniqueID) == -1;
}

/**
 * Allows LetterTile to be printed to screen.
 */
std::ostream& operator<< (std::ostream& out, const LetterTile& tile);

/**
 * Given a string of characters and an integer representing the depth of
 * letter tiles in the gameboard, returns a Set of LetterTile structs
 * containing a single letter character, its depth in the gameboard, and
 * a unique tile ID.
 */
Set<LetterTile> stringtoLetterTile(std::string s, int depth);

/** The getBoardInputs() takes in the user's input for every ring of
 * the game board, prints out the game board, and updates the available
 * letter tiles to match the user's inputs.
 */
void getBoardInputs(Set<LetterTile>& availableTiles);

/**
 * Given a set of LetterTiles representing the current available tiles to
 * choose and a current LetterTile, returns a modified set of the available
 * tiles given any potential change in depth of the current tile.
 */
Set<LetterTile> updateAvailableTiles(Set<LetterTile> availableTiles, LetterTile curTile);

/* * * * * * STUDENT FUNCTIONS * * * * * */

/* * * * * * SOLUTION ONE * * * * * */

/** The getBoardInputs() takes in the user's input for every ring of
 * the game board, prints out the game board, and updates the available
 * letter tiles to match the user's inputs.
 */
void findAllWordsHelper(Stack<LetterTile> pathway, Set<LetterTile> remainingTiles, std::string curWord, Lexicon& lex, Set<std::string>& validWords);

/* * * * * * SOLUTION TWO * * * * * */
