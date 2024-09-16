#ifndef KING_H
#define KING_H

#include <cstdint>
#include "piece.h"

using Bitboard = uint64_t;

class King : public Piece {
public:
    King(Color color);

    Bitboard generatemoves(Bitboard occupiedSquares, int pieceIndex) override;
};

#endif  // KING_H