#include "board.hpp"
#include "util.hpp"
#include <iostream>
#include <iomanip>
#include <ostream>
#include <string>

using namespace std;

Board::Board(bool computerEnabled) :computerEnabled(computerEnabled), dice1(0), dice2(0)
{
    currentMove = Side::WHITE;
    boardPieces = std::vector<int>(20);
    srand(time(0));
}

//Updates the state of the boad based on the supplied command
//  * isForward
//  * isWhite
//  * piece index
//  return true if the update was successful
bool Board::UpdateState(const std::vector<Command>& commands) {
    for (Command c : commands) {
       int direction = c.isForward ? 1 : -1;
       int piece = c.piece;
       int offset = c.isWhite ? 0 : 10;
       if (piece != dice1 - 1 && piece != dice2 -1 && piece != diceTotal - 1) {
           cout << "Piece != dice -> Piece = " << piece << "  Dice = " << dice1 << dice2 << diceTotal << endl;
           return false;
       }
       int state = GetState(piece);
       if (state + direction > 1 && state + direction < 0)
           return false;
       boardPieces[piece + offset] += direction;
    }
    return true; 
}

//Called when the player's turn starts
//  moves the currently up pieces into their safe positions
//
void Board::SavePieces() {
    cout << "Moving pieces to safety" << endl;
    int offset = currentMove == Side::WHITE ? 0 : 10;
    for (int i = 0; i < 10; i++) {
        if (boardPieces[i + offset] == 1) {
            boardPieces[i + offset] = 2;
        }
    }
}

//Returns the state of the piece given the side and index [0-9]
int Board::GetState(Side side, int index) {
    return side == Side::WHITE ? boardPieces.at(index) : boardPieces.at(index + 10); 
}
//Returns the state of the piece at index [0-19]
int Board::GetState(int index) {
    return currentMove == Side::WHITE ? boardPieces.at(index) : boardPieces.at(index + 10);
}

//Roll random numbers on the die
void Board::RollDie() {
    dice1 = (rand() % 6) + 1;
    dice2 = (rand() % 6) + 1;
    diceTotal = dice1 + dice2;
}

//Command Parsing functions moved to util.hpp

/* Displays the board in its current state
 *   arg: clearC
 *     - whether we should clear the console 
 */

void Board::DisplayBoard(bool clearC) {
    if (clearC) clearConsole();

    setOutTextColor(255, 255, 255);
    cout << "Current State" << endl;


    //white pieces (row #1)
    //
   
    if (currentMove == Side::WHITE)
        cout << "Turn : WHITE" << endl;
    else
        cout << "Turn : BROWN" << endl;
    
    setOutTextColor(255, 226, 190);
    cout << "\t\t    WHITE" << endl;
    PrintNumbers();
    PrintRow(Side::WHITE, 0);
    PrintRow(Side::WHITE, 1);
    PrintRow(Side::WHITE, 2);

    setOutTextColor(255, 141, 0);
    PrintDie();

    setOutTextColor(153, 121, 61);
    PrintRow(Side::BROWN, 2);
    PrintRow(Side::BROWN, 1);
    PrintRow(Side::BROWN, 0);
    PrintNumbers();
    cout << "\t\t    BROWN" << endl;
    
    setOutTextColor(255, 255, 255);
    
    cout << endl;
}

/* Rows
 *    0 - farthest back spot
 *    1 - up one spot
 *    2 - safe spot
 */
void Board::PrintRow(Side side, int row) {
    cout << " - ";
    int offset = side == Side::WHITE ? 0 : 10;

    for (int i = offset; i < offset + 10; i++) {
        if (boardPieces[i] == row) {
            cout << " " << boardPieces[i] << "  ";
        } else {
            boardPieces[i] > row ? cout << " |  " : cout << "    ";
        }
    }
    if (side == currentMove) {
        cout << "  |";
    }
    cout << endl;
}

/* Displays numbers 1-10 for each side of the board
 */
void Board::PrintNumbers() {
   cout << " - ";
   for (int i = 1; i < 11; i++) {
        cout << "[" << i << "] ";
   }
   cout << endl;
}


/* Prints the dice centered-ish in the board
 */
void Board::PrintDie() {
    cout << "\t\t    " << dice1 << "   " << dice2 << endl;
}


/* Finds all the valid moves for the current dice values
 * returns list of valid commands in string form
 * current board state is not taken into account here
 *          WIP
 */
std::vector<std::string> Board::FindAvailableMoves() {
    std::vector<std::string> validCommands;

    string turn = currentMove == Side::WHITE ? "w" : "b";
    string other = turn == "w" ? "b" : "w";
   
    //test case
    //  'turn' is WHITE -> 'w'
    //  'dice1'         ->  4
    //  'dice2'         ->  3
    if (dice1 != dice2) {
        validCommands.push_back("+" + turn + to_string(dice1) + " +" + turn + to_string(dice2));   //+w4 +w3
        validCommands.push_back("+" + turn + to_string(dice1) + " -" + other + to_string(dice2));  //+w4 -b3
        validCommands.push_back("+" + turn + to_string(dice2) + " -" + other + to_string(dice1));  //+w3 -b4
        validCommands.push_back("-" + other + to_string(dice1) + " -" + other + to_string(dice2)); //-b4 -b3
        if (diceTotal < 11) //the two dice must not be [5 and 6] or [6 and 6] for this to be true
        {
            validCommands.push_back("+" + turn + to_string(diceTotal));                                       //+w7
            validCommands.push_back("-" + other + to_string(diceTotal));                                      //-b7
        }
    }
    else {
        validCommands.push_back("+" + turn + to_string(dice1) + " -" + other + to_string(dice2));  //
        validCommands.push_back("+" + turn + to_string(diceTotal));
    }

    return validCommands;
}


/* Expects output of Board::FindAvailableMoves()
 *  and sifts out the moves that aren't possible
 *  for the current board state
 *  WIP
 */  
std::vector<std::string> Board::SortPossibleMoves(std::vector<std::string>& possible) {
    std::vector<std::string> possibleMoves;
    for (std::string s : possible) {
        //max two commands per packet
        std::vector<Command> cmds = CommandUtil::ParseCommands(s, *this);
        for (Command c : cmds) {
            
           //TODO: check if the command supplied is fully possible
           //          every aspect of it must succeed
           //          this will be used for the display of possible
           //          moves to the player
        }
    }
    return possibleMoves;
}


/* Changes the 'currentMove' to the opposite
 */
void Board::SwapSides() {
    currentMove = currentMove == Side::WHITE ? Side::BROWN : Side::WHITE;
}

/* checks if the current player is the winner
 * winning means having all pieces in either position 1 or 2
 */
bool Board::IsWinner() {
    int startIndex = currentMove == Side::WHITE ? 0 : 10;
    for (int i = startIndex; i < startIndex + 10; i++) {
       if (boardPieces.at(i) == 0)
           return false; 
    }
    return true;
}
