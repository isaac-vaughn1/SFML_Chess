#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
public:
    Bishop();

    Bitboard generate_moves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) override;
};

#endif  // BISHOP_H