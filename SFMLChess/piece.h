#ifndef PIECE_H
#define PIECE_H

#include "common.h"
#include <cstdint>

class Piece {
protected:
    Color color;

public:

    Piece(Color color) : color(color) {}

    void setColor(Color newColor) {
        color = newColor;
    }

    virtual Bitboard generate_moves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) = 0;

    virtual ~Piece() {}
};

#endif  // PIECE_H