#ifndef QUEEN_H
#define QUEEN_H

#include <cstdint>
#include "piece.h"

using Bitboard = uint64_t;

class Queen : public Piece {
public:
    Queen();

    Bitboard generatemoves(Bitboard& occupiedSquares, int pieceIndex) override;
};

#endif  // QUEEN_H