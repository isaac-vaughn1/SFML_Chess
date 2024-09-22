#include "pawn.h"

Pawn::Pawn() : Piece(color) {

}

Bitboard Pawn::generatemoves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) {  // still needs edge case handling (pawn reaches other side, board wrapping, etc.)
	Bitboard location = (1ULL << pieceIndex);
	Bitboard startingRank = this->color == WHITE ? 0x00FF000000000000ULL : 0x000000000000FF00ULL;
	Bitboard forward = 0;
	Bitboard doubleForward = 0;
	Bitboard captures = 0;
	Bitboard moves = 0;

	forward = this->color == WHITE ? (location >> 8) : (location << 8);  // shift piece forward one spac; direction depends on color

	if ((location & startingRank) != 0)  // look for double moves if pawn is on starting rank
		doubleForward = this->color == WHITE ? (location >> 16) : (location << 16);

	// find forward moves where other pieces aren't
	forward &= ~(allySquares | enemySquares);
	doubleForward &= ~(allySquares | enemySquares);

	if (forward == 0)  // no valid forward move means no valid double forward move
		doubleForward = 0;

	captures = this->color == WHITE ? (location >> 7 | location >> 9) : (location << 7 | location << 9);  // find diagonal captures

	captures &= ~allySquares;  // remove captures where there are ally pieces
	captures &= enemySquares;  // keep captures where there are enemy pieces

	moves |= (forward | doubleForward | captures);  // combine everything into one Bitboard

	return moves;
}