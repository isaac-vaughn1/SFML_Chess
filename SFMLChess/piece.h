#ifndef PIECE_H
#define PIECE_H

#include <cstdint>

using Bitboard = uint64_t;

class Piece {
public:
    enum class Color { WHITE, BLACK };
    Color color;


    Piece(Color c) : color(c) {}

    virtual Bitboard generateMoves(Bitboard occupiedSquares) = 0;

    virtual ~Piece() {}
};

#endif