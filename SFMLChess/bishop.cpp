#include "bishop.h"
#include "magic.h"

Bishop::Bishop() : Piece(color) {

}

Bitboard Bishop::generate_moves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) {
	init_sliders_attacks(1, (enemySquares | allySquares));

	return get_bishop_attacks(pieceIndex, (enemySquares | allySquares));
}