#include "common.h"

#ifndef MAGIC_H
#define MAGIC_H

// square encoding
enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1, no_sq
};

// rook & bishop flags
enum { rook, bishop };

// rook relevant occupancy bits
extern int rook_relevant_bits[64];

// bishop relevant occupancy bits
extern int bishop_relevant_bits[64];

// masks
extern Bitboard bishop_masks[64];
extern Bitboard rook_masks[64];

// attacks
extern Bitboard bishop_attacks[64][512];
extern Bitboard rook_attacks[64][4096];

// rook magic numbers
extern const Bitboard rook_magics[64];

// bishop magic number
extern const Bitboard bishop_magics[64];

Bitboard mask_bishop_attacks(int square);

Bitboard mask_rook_attacks(int square);

Bitboard bishop_attacks_on_the_fly(int square, Bitboard block);

Bitboard rook_attacks_on_the_fly(int square, Bitboard block);

void init_sliders_attacks(int is_bishop, Bitboard current_occupancy);

Bitboard get_bishop_attacks(int square, Bitboard occupancy);

Bitboard get_rook_attacks(int square, Bitboard occupancy);


#endif  // MAGIC_H