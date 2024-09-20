#ifndef PAWN_H
#define PAWN_H

#include <cstdint>
#include "piece.h"


class Pawn : public Piece {
public:
    Pawn();

    Bitboard generatemoves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) override;
    Bitboard generateattacks(Bitboard& occupiedSquares, int pieceIndex);
};

#endif  // PAWN_H