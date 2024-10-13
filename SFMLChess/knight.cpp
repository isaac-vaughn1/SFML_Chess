#include "knight.h"

Knight::Knight() : Piece(color) {

}

Bitboard Knight::generate_moves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) {  // still requires board wrap prevention
	Bitboard location = (1ULL << pieceIndex);
	Bitboard moves = 0;
	

	moves = (location << 17 | location << 15 | location << 10 | location << 6 
		     | location >> 17 | location >> 15 | location >> 10 | location >> 6);

	moves &= ~allySquares;

	return moves;
}