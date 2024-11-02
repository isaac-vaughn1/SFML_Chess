#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "common.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include <vector>
#include <utility>


class Board {
public:
	Board(sf::RenderWindow& win, std::vector<sf::Sprite>& pieces, int squareSize);
	void update(); // handles game logic


private:
	GameState state;

	Pawn pawn;
	Rook rook;
	Knight knight;
	Bishop bishop;
	Queen queen;
	King king;

	Bitboard whitePieces;
	Bitboard blackPieces;
	Bitboard allPieces;

	Color playerTurn;
	enum ClickState { NONE, FIRST_CLICK };
	ClickState clickstate;
	sf::RenderWindow& window;
	std::vector<sf::Sprite>& pieces;
	std::pair<int, int> firstClick;

	int squareSize;

	void handle_click(sf::Vector2i clickCoords);
	int coords_to_bit_index(std::pair<int, int> coords);
	bool piece_exists(int index);
	bool move_is_valid(Bitboard moves, int moveIndex);
	Bitboard& find_piece_bitboard(int index);
	Piece* find_piece_type(int index);
	void shift_bitboard(Bitboard& piece, int oldIndex, int newIndex);
	void move_sprite(std::pair<int, int> oldCoords, std::pair<int, int> newCoords);
	void capture_piece(int captureIndex);
};

#endif // BOARD_H