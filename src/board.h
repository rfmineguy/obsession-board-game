#include <vector>

struct Board {
    Board() {
        boardPieceStates.reserve(20);
    }

    std::vector<int> boardPieceStates;
    int turn;
};
