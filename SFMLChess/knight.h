#ifndef KNIGHT_H
#define KNIGHT_H

#include <cstdint>
#include "piece.h"

using Bitboard = uint64_t;

class Knight : public Piece {
public:
    Knight();

    Bitboard generatemoves(Bitboard& occupiedSquares, int pieceIndex) override;
};

#endif  // KNIGHT_H