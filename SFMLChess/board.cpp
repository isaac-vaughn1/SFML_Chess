#include "window.h"
#include "board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>


Board::Board(sf::RenderWindow& win, std::vector<sf::Sprite>& pieces, int squareSize)
	: squareSize(squareSize), window(win), pieces(pieces), clickstate(NONE) {
	// black pieces
	blackPawns = 0x000000000000FF00ULL;
	blackRooks = 0x0000000000000081ULL;
	blackKnights = 0x0000000000000042ULL;
	blackBishops = 0x0000000000000024ULL;
	blackQueens = 0x0000000000000008ULL;
	blackKing = 0x0000000000000010ULL;

	// white pieces
	whitePawns = 0x00FF000000000000ULL;
	whiteRooks = 0x8100000000000000ULL;
	whiteKnights = 0x4200000000000000ULL;
	whiteBishops = 0x2400000000000000ULL;
	whiteQueens = 0x0800000000000000ULL;
	whiteKing = 0x1000000000000000ULL;

	allPieces = 0xFFFF00000000FFFFULL;

	// fill the boards array
	boards[0] = whitePawns;
	boards[1] = whiteRooks;
	boards[2] = whiteKnights;
	boards[3] = whiteBishops;
	boards[4] = whiteQueens;
	boards[5] = whiteKing;
	boards[6] = blackPawns;
	boards[7] = blackRooks;
	boards[8] = blackKnights;
	boards[9] = blackBishops;
	boards[10] = blackQueens;
	boards[11] = blackKing;
}

void Board::update() {

	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;

		case (sf::Event::MouseButtonPressed):
			if (event.mouseButton.button == sf::Mouse::Left) {
				handleclick(sf::Mouse::getPosition(window));
			}
			break;
		}
	}

	// redraw the pieces
	for (const auto& piece : pieces) {
		window.draw(piece);
	}

}

void Board::handleclick(sf::Vector2i clickCoords) {
	if (clickstate == NONE) {
		clickstate = FIRST_CLICK;
		firstClick = std::make_pair(clickCoords.x, clickCoords.y);
		return;
	}

	else if (clickstate == FIRST_CLICK) {
		clickstate = NONE;

		int oldIndex = coordstobitindex(std::make_pair(firstClick.first / squareSize, firstClick.second / squareSize));
		int newIndex = coordstobitindex(std::make_pair(clickCoords.x / squareSize, clickCoords.y / squareSize));

		if (pieceexists(oldIndex)) {
			Bitboard& piece = findpiece(oldIndex);
			shiftbitboard(piece, oldIndex, newIndex);
			shiftbitboard(allPieces, oldIndex, newIndex);
			movesprite(std::make_pair(firstClick.first, firstClick.second), std::make_pair(clickCoords.x, clickCoords.y));
		}
	}

	return;
}

int Board::coordstobitindex(std::pair<int, int> coords) {
	return coords.second * 8 + coords.first;
}

bool Board::pieceexists(int index) {
	Bitboard source = (1ULL << index);

	return (allPieces & source) != 0;
}

Bitboard& Board::findpiece(int index) {
	Bitboard location = (1Ull << index);

	for (Bitboard& board : boards) {
		if ((board & location) != 0)
			return board;
	}

	throw std::runtime_error("Piece not found at the specified index!");
}

void Board::shiftbitboard(Bitboard& piece, int oldIndex, int newIndex) {
	Bitboard oldLocation = (1ULL << oldIndex);
	Bitboard newLocation = (1ULL << newIndex);

	piece &= ~oldLocation;
	piece |= newLocation;

	allPieces &= ~oldLocation;
	allPieces |= newLocation;

	return;
}

void Board::movesprite(std::pair<int, int> oldCoords, std::pair<int, int> newCoords) {
	float oldX = static_cast<float>(oldCoords.first);
	float oldY = static_cast<float>(oldCoords.second);

	int newX = newCoords.first / squareSize;
	int newY = newCoords.second / squareSize;

	for (auto& piece : pieces) {
		if (piece.getGlobalBounds().contains(oldX, oldY)) {
			piece.setPosition(newX * squareSize, newY * squareSize);
			break;
		}
	}

	return;
}
