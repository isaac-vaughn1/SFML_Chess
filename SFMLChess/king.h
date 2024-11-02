#ifndef KING_H
#define KING_H

#include "piece.h"

using Bitboard = uint64_t;
class King : public Piece {
public:
    King();

    Bitboard generate_moves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) override;

private:
    bool in_checkmate();
    bool in_check(Bitboard& kingLocation);
};

#endif  // KING_H