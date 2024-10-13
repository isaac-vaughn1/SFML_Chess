#include "rook.h"
#include "magic.h"

Rook::Rook() : Piece(color) {

}

Bitboard Rook::generate_moves(Bitboard& allySquares, Bitboard& enemySquares, int pieceIndex) {
	init_sliders_attacks(0, (enemySquares | allySquares));

	return get_rook_attacks(pieceIndex, (enemySquares | allySquares));
}