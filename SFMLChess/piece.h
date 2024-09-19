#ifndef PIECE_H
#define PIECE_H

#include <cstdint>
#include "common.h"
 
using Bitboard = uint64_t;

class Piece {
protected:
    Color color;

public:

    Piece(Color color) : color(color) {}

    void setColor(Color newColor) {
        color = newColor;
    }

    virtual Bitboard generatemoves(Bitboard& occupiedSquares, int pieceIndex) = 0;

    virtual ~Piece() {}
};

#endif  // PIECE_H