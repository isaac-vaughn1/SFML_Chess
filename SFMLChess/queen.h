#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
public:
    Queen();

    Bitboard generate_moves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) override;
};

#endif  // QUEEN_H