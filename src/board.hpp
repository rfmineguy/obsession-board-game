#pragma once

#include <vector>
#include <string>
#include "side.hpp"
#include "command.h"

#define PIECE_SPACING 2

class Board {
public:
    Board(bool computerEnabled);
    ~Board() = default;

    /**
     * Change the state of the board based on
     *  &side   -> white/brown
     *  index   -> piece index
     *
     *  return whether it failed to update the state
     */
    bool UpdateState(const std::vector<Command>& command);
    void SavePieces();
    int GetState(Side side, int index);
    int GetState(int index);
    void RollDie();

    //Display Functions
    void DisplayBoard(bool clearConsole = true);
    void PrintNumbers();
    void PrintRow(Side side, int row);
    void PrintDie();

    //Game Flow Functions
    std::vector<std::string> FindAvailableMoves();
    std::vector<std::string> SortPossibleMoves(std::vector<std::string>&);
    void SwapSides();
    bool IsWinner();

public:
    Side currentMove;

private:
    bool computerEnabled;
    int dice1, dice2, diceTotal;

    //[0-9] white, [10-19] brown
    std::vector<int> boardPieces = std::vector<int>(20);
};
