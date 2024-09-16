#ifndef PAWN_H
#define PAWN_H

#include <cstdint>
#include "piece.h"


class Pawn : public Piece {
public:
    Pawn(Color color);

    Bitboard generatemoves(Bitboard& occupiedSquares, int pieceIndex) override;
    Bitboard generateattacks(Bitboard& occupiedSquares, int pieceIndex);
};

#endif  // PAWN_H