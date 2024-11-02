#include "king.h"

King::King() : Piece(color) {

}

Bitboard King::generate_moves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) {  // still need piece wrapping prevention
	Bitboard location = (1ULL << pieceIndex);
	Bitboard moves = 0;

	moves = (location >> 1 | location >> 7 | location >> 8 | location >> 9
		     | location << 1 | location << 7 | location << 8 | location << 9);

	moves &= ~allySquares;

	return moves;
}

bool King::in_checkmate() {
	return false;
}

bool King::in_check(Bitboard& kingLocation) {
	return false;
}