#ifndef PAWN_H
#define PAWN_H

#include <cstdint>
#include "piece.h"

using Bitboard = uint64_t;

class Pawn : public Piece {
public:
    Pawn(Color color);

    Bitboard generatemoves(Bitboard occupiedSquares, int pieceIndex) override;
};

#endif  // PAWN_H