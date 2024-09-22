#include "king.h"

King::King() : Piece(color) {

}

Bitboard King::generatemoves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) {
	Bitboard location = (1ULL << pieceIndex);
	Bitboard moves = 0;

	moves = (location >> 1 | location >> 7 | location >> 8 | location >> 9
		     | location << 1 | location << 7 | location << 8 | location << 9);

	moves &= ~allySquares;

	return moves;
}