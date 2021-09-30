#include <iostream>
#include "board.hpp"
#include <climits>
#include "util.hpp"

/**
 * Structures needed
 *   - Board
 *   - Board manager
 *   - Game manager (?)
 *
 */

/**
 *  Obession systems
 *    + Command system
 *      - +/-           -> direction
 *      - w/b           -> color
 *      - #             -> piece
 *      
 *      1. +w2 +w4      -> move white2 forward, move white4 forward
 *      2. +b3 -w5      -> move brown3 forward, move white5 backward
 *      
 *    + Available moves system (WIP)
 *      - controls the flow of the game
 *      - decides whether the player can keep playing or not
 *      - generate a vector of commands that are valid for current board state (dice and piece positions)?
 */

using namespace std;

int main() {
    bool running = true;
    char userInput;
    int pieceInput;
    Board board(false);
    board.RollDie();

    RandomizeTurn(board); //util.hpp

    while (running) {
        
        /**
         * DISPLAY MENU AND GATHER USER INPUT
         */

        board.DisplayBoard(false);
        cout << "[R]  Roll Die" << endl;
        cout << "[C]  Movement Command" << endl;
        cout << "[M]  Move Pieces to Safety" << endl;
        //cout << "[F]  Move Piece Forward" << endl;    
        //cout << "[B]  Move Piece Backward" << endl;
        cout << "[N]  Next Turn" << endl;
        cout << "[X]  Exit" << endl;
        cin >> userInput;
        ClearCIN();
        userInput = std::tolower(userInput, std::locale());

        if (board.IsWinner()) {
            string winner = board.currentMove == Side::BROWN ? "Brown " : "White ";
            cout << winner << " is the winner!" << endl;
        } else {
            cout << "The game wasn't over" << endl;
        }
        /**
         * UTILIZE USER INPUT AND PROCESS THE REQUEST
         */
        switch (userInput) {

            //EXIT PROGRAM
            case 'x':
                running = false;
                break;

            //ROLL THE DICE
            case 'r':
                board.RollDie();
                break;
            
            //MOVEMENT COMMAND MODE
            case 'c':
                while (true) {
                    int chosenCommand = 0;

                    std::vector<std::string> availableMoves = board.FindAvailableMoves();
                    for (int i = 0; i < availableMoves.size(); i++) {
                       
                        std::vector<Command> commands = CommandUtil::ParseCommands(availableMoves.at(i), board);
                        cout << i << endl;
                        cout << availableMoves[i] << endl;
                        for (Command c : commands) {
                            cout << "  - " << CommandUtil::GetPrompt(c) << endl;
                        }
                    }                       
                    cout << endl;
                    
                    cout << "Enter a command index ('-1' to quit) : ";
                    cin >> chosenCommand;
                    ClearCIN();
                    
                    //exit
                    if (chosenCommand == -1) break;

                    //continue on with the 'c'ommand
                    std::vector<Command> commands = CommandUtil::ParseCommands(availableMoves.at(chosenCommand), board);
                    if (board.UpdateState(commands)) {
                        board.RollDie();
                        break;
                    } else {
                        setOutTextColor(200, 0, 0);
                        std::cout << "Failed" << std::endl;
                        setOutTextColor(255, 255, 255);
                    }
                }
                break;

            case 'm':
                board.SavePieces();
                break;
            
            //SWAP ACTIVE SIDE
            case 'n':
                board.SwapSides();
                board.RollDie();
                break;

            default:
                cerr << "Not an option bucko" << endl;
                break;
        }
        
    }
}
