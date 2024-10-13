#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
public:
    Rook();

    Bitboard generate_moves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) override;
};

#endif  // ROOK_H