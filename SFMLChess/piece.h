#ifndef PIECE_H
#define PIECE_H

#include <cstdint>

enum Color { WHITE, BLACK };
using Bitboard = uint64_t;

class Piece {

public:
    Color color;

    Piece(Color color) : color(color) {}

    virtual Bitboard generatemoves(Bitboard& occupiedSquares, int pieceIndex) = 0;

    virtual ~Piece() {}
};

#endif  // PIECE_H