#include "pawn.h"

Pawn::Pawn() : Piece(color) {

}

Bitboard Pawn::generatemoves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) {  // still needs edge case handling (pawn reaches other side, moving off of the board, etc.)
	Bitboard pieceLocation = (1ULL << pieceIndex);
	Bitboard startingRank = this->color == WHITE ? 0x00FF000000000000ULL : 0x000000000000FF00ULL;
	Bitboard forward = 0;
	Bitboard doubleForward = 0;
	Bitboard captures = 0;
	Bitboard moves = 0;

	forward = this->color == WHITE ? (pieceLocation >> 8) : (pieceLocation << 8);  // shift piece forward one spac; direction depends on color

	if ((pieceLocation & startingRank) != 0)  // look for double moves if pawn is on starting rank
		doubleForward = this->color == WHITE ? (pieceLocation >> 16) : (pieceLocation << 16);

	// find forward moves where other pieces aren't
	forward &= ~(allySquares | enemySquares);
	doubleForward &= ~(allySquares | enemySquares);

	if (forward == 0)  // no valid forward move means no valid double forward move
		doubleForward = 0;

	captures = this->color == WHITE ? (pieceLocation >> 7 | pieceLocation >> 9) : (pieceLocation << 7 | pieceLocation << 9);  // find diagonal captures

	captures &= ~allySquares;  // remove captures where there are ally pieces
	captures &= enemySquares;  // keep captures where there are enemy pieces

	moves |= (forward | doubleForward | captures);  // combine everything into one Bitboard

	return moves;
}