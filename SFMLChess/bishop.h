#ifndef BISHOP_H
#define BISHOP_H

#include <cstdint>
#include "piece.h"

using Bitboard = uint64_t;

class Bishop : public Piece {
public:
    Bishop();

    Bitboard generatemoves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) override;
};

#endif  // BISHOP_H