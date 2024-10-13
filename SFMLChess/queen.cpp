#include "queen.h"
#include "magic.h"

Queen::Queen() : Piece(color) {

}

Bitboard Queen::generate_moves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) {
	init_sliders_attacks(1, (enemySquares | allySquares));
	Bitboard diagonalMoves = get_bishop_attacks(pieceIndex, (enemySquares | allySquares));

	init_sliders_attacks(0, (enemySquares | allySquares));
	Bitboard straightMoves = get_rook_attacks(pieceIndex, (enemySquares | allySquares));

	return (diagonalMoves | straightMoves);
}