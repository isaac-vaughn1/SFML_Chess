#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

using Bitboard = uint64_t;

class Board {
public:
	Board(sf::RenderWindow& win, std::vector<sf::Sprite>& pieces, int squareSize);
	void update(); // handles game logic


private:
	Bitboard whitePieces;
	Bitboard whitePawns;
	Bitboard whiteRooks;
	Bitboard whiteKnights;
	Bitboard whiteBishops;
	Bitboard whiteQueens;
	Bitboard whiteKing;

	Bitboard blackPieces;
	Bitboard blackPawns;
	Bitboard blackRooks;
	Bitboard blackKnights;
	Bitboard blackBishops;
	Bitboard blackQueens;
	Bitboard blackKing;

	Bitboard allPieces;

	Bitboard boards[12];

	enum ClickState { NONE, FIRST_CLICK };
	ClickState clickstate;
	sf::RenderWindow& window;
	std::vector<sf::Sprite>& pieces;
	std::pair<int, int> firstClick;

	int squareSize;

	void handleclick(sf::Vector2i clickCoords);
	int coordstobitindex(std::pair<int, int> coords);
	bool pieceexists(int index);
	Bitboard& findpiece(int index);
	void shiftbitboard(Bitboard& piece, int oldIndex, int newIndex);
	void movesprite(std::pair<int, int> oldCoords, std::pair<int, int> newCoords);
};

#endif // BOARD_H