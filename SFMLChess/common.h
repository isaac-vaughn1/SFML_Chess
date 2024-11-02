#ifndef COMMON_H
#define COMMON_H

#include <cstdint>

enum Color {WHITE, BLACK};
using Bitboard = uint64_t;

struct GameState {
	Bitboard blackPawns;
	Bitboard blackRooks;
	Bitboard blackKnights;
	Bitboard blackBishops;
	Bitboard blackQueens;
	Bitboard blackKing;
	Bitboard whitePawns;
	Bitboard whiteRooks;
	Bitboard whiteKnights;
	Bitboard whiteBishops;
	Bitboard whiteQueens;
	Bitboard whiteKing;
};

#endif // COMMON_H