#pragma once

struct Command {
    Command(bool isForward, bool isWhite, int piece)
    :isForward(isForward), isWhite(isWhite), piece(piece) {}
    
    bool isForward;
    bool isWhite;
    int piece;
};


