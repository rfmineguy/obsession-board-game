#pragma once

#include <iostream>
#include <sstream>
#include <climits>
#include <string>
#include <vector>
#include "board.hpp"

inline void ClearCIN() {
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}

inline void moveCursor(std::ostream& os, int col, int row) {
    os << "\033[" << col << ";" << row << "H";
}

inline void clearConsole() {
    system("clear");
}


namespace Color {
//console color functions
inline void setOutBackroundColor(int r, int g, int b) {
    std::cout << "\e[48;2;" << r << ";" << g << ";" << b << "m";
}

inline void setOutTextColor(int r, int g, int b) {
    std::cout << "\e[38;2;" << r << ";" << g << ";" << b << "m";
}

inline void printColor(const char* message, int r, int g, int b) {
    setOutTextColor(r, g, b);
    std::cout << "\e[37m";
}
}

inline void RandomizeTurn(Board& board) {
    int random = rand() % 2;
    board.currentMove = random == 0 ? Side::WHITE : Side::BROWN;
}

namespace CommandUtil {
    inline std::vector<Command> ParseCommands(std::string s, Board& board) {
        std::vector<std::string> commandStrings;
        std::vector<Command> commands;
        std::stringstream ss(s);
        std::string inter;
        while (getline(ss, inter, ' ')) {
            commandStrings.push_back(inter);
        }

        for (int i = 0; i < commandStrings.size(); i++) {
            std::string command = commandStrings.at(i);
        
            std::string numberComponent = command.substr(2);
            bool isForward = (command.find('+') != std::string::npos);
            bool isWhite =
             (s.find('w') != std::string::npos) ||
             (s.find('W') != std::string::npos);         // is there a white command?
            bool choseCurrent = 
             (s.find('c') != std::string::npos) || 
             (s.find('C') != std::string::npos);

            int index = stoi(numberComponent);
            int piecePos = board.GetState(index - 1);
            
            if (choseCurrent)
                commands.emplace_back(isForward, board.currentMove == Side::WHITE, index - 1);
            else
                commands.emplace_back(isForward, isWhite, index - 1);
        }
        return commands;
    } 

    inline Command ParseCommand(std::string s, Board& board) {
        std::vector<Command> commands = CommandUtil::ParseCommands(s, board);
        if (commands.size() > 1) {
            std::cerr << "Misuse of ParseCommand() function, only expected single command strings" << std::endl;
        }
        return commands.at(0);
    } 
    
    //WIP
    inline std::vector<std::string> FindAvailableMoves() {
        return { "WIP" };
    };

    inline std::string ToString(Command& c) {
        std::string turn = c.isWhite ? "w" : "b";
        return "+" + turn + std::to_string(c.piece); 
    }

    inline std::string GetPrompt(Command& c) {
        std::string color = c.isWhite ? " white" : " brown";
        int piece         = c.piece + 1; //c.piece is the actual index of the piece
        std::string dir   = c.isForward ? " ⬆." : " ⬇.";
        return "Move" + color + " piece #" + std::to_string(piece) + dir; 
    }
}

