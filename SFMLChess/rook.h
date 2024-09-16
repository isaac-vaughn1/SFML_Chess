#ifndef ROOK_H
#define ROOK_H

#include <cstdint>
#include "piece.h"

using Bitboard = uint64_t;

class Rook : public Piece {
public:
    Rook(Color color);

    Bitboard generatemoves(Bitboard& occupiedSquares, int pieceIndex) override;
};

#endif  // ROOK_H