#include "window.h"
#include "board.h"
#include <SFML/Graphics.hpp>
#include <utility>


Board::Board(sf::RenderWindow& win, std::vector<sf::Sprite>& pieces, int squareSize)
	: squareSize(squareSize), playerTurn(WHITE), window(win), pieces(pieces), clickstate(NONE) {

	state = {
		 0x000000000000FF00ULL,  // black pawns
		 0x0000000000000081ULL,  // black rooks
		 0x0000000000000042ULL,  // black knights
		 0x0000000000000024ULL,  // black bishops
		 0x0000000000000008ULL,  // black queens
		 0x0000000000000010ULL,  // black king
		 0x00FF000000000000ULL,  // white pawns
		 0x8100000000000000ULL,  // white rooks
		 0x4200000000000000ULL,  // white knights
		 0x2400000000000000ULL,  // white bishops
		 0x0800000000000000ULL,  // white queens
		 0x1000000000000000ULL  // white king
	};

	blackPieces = 0x000000000000FFFFULL;
	whitePieces = 0xFFFF000000000000ULL;
	allPieces = 0xFFFF00000000FFFFULL;
}

void Board::update() {

	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:  // end program on window close
			window.close();
			break;

		case (sf::Event::MouseButtonPressed):
			if (event.mouseButton.button == sf::Mouse::Left) {
				handle_click(sf::Mouse::getPosition(window));  // handle click if left mouse button is pressed
			}
			break;
		}
	}

	// for every piece in pieces, redraw the piece
	for (const auto& piece : pieces) {
		window.draw(piece);
	}

}

void Board::handle_click(sf::Vector2i clickCoords) {
	// runs on our first click
	if (clickstate == NONE) {
		clickstate = FIRST_CLICK;
		firstClick = std::make_pair(clickCoords.x, clickCoords.y);  // collect coords of the click
		return;
	}

	// runs on our second click
	else if (clickstate == FIRST_CLICK) {
		clickstate = NONE;

		Bitboard potentialMoves = 0;

		// get the bit index from the coordinates of our first and second click
		int oldIndex = coords_to_bit_index(std::make_pair(firstClick.first / squareSize, firstClick.second / squareSize));  
		int newIndex = coords_to_bit_index(std::make_pair(clickCoords.x / squareSize, clickCoords.y / squareSize));


		if (piece_exists(oldIndex) && oldIndex != newIndex) {
			// find the bitboard where our piece lies and shift it
			Bitboard& pieceBoard = find_piece_bitboard(oldIndex);
			Piece* pieceType = find_piece_type(oldIndex);
			pieceType->setColor(playerTurn);

			if (playerTurn == WHITE) {
				potentialMoves = pieceType->generate_moves(whitePieces, blackPieces, oldIndex);
			}
			else {
				potentialMoves = pieceType->generate_moves(blackPieces, whitePieces, oldIndex);
			}

			// bitboard and sprite shifts if we have a valid move
			if (move_is_valid(potentialMoves, newIndex)) {
				move_sprite(std::make_pair(firstClick.first, firstClick.second), std::make_pair(clickCoords.x, clickCoords.y));
				shift_bitboard(pieceBoard, oldIndex, newIndex);
			}
		}
	}

	return;
}

int Board::coords_to_bit_index(std::pair<int, int> coords) {
	// we do y * 8 + x instead of  x * 8 + y because of the way we generated the board (0,0 is the top left instead of bottom left and now we're in too deep to make the change)
	return coords.second * 8 + coords.first;
}

bool Board::piece_exists(int index) {
	Bitboard source = (1ULL << index);  // convert the old bit index into a bitboard with only that index filled

	if (playerTurn == WHITE) {
		return ((whitePieces & source) != 0);  // ensure only p1 moves white
	}

	else if (playerTurn == BLACK) {
		return (blackPieces & source) != 0;  // ensure only p2 moves black
	}
	
	return false;
}

bool Board::move_is_valid(Bitboard moves, int moveIndex) {
	Bitboard chosenMove = (1ULL << moveIndex);

	if ((chosenMove & moves) != 0)
		return true;

	return false;
}

Bitboard& Board::find_piece_bitboard(int index) {
	Bitboard location = (1ULL << index);  // convert the old bit index into a bitboard with only that index filled

	// Check each piece type in the state struct
	if (state.whitePawns & location) return state.whitePawns;
	if (state.blackPawns & location) return state.blackPawns;
	if (state.whiteKnights & location) return state.whiteKnights;
	if (state.blackKnights & location) return state.blackKnights;
	if (state.whiteRooks & location) return state.whiteRooks;
	if (state.blackRooks & location) return state.blackRooks;
	if (state.whiteBishops & location) return state.whiteBishops;
	if (state.blackBishops & location) return state.blackBishops;
	if (state.whiteQueens & location) return state.whiteQueens;
	if (state.blackQueens & location) return state.blackQueens;
	if (state.whiteKing & location) return state.whiteKing;
	if (state.blackKing & location) return state.blackKing;

	throw std::runtime_error("Piece not found at the specified index!");
}

Piece* Board::find_piece_type(int index) {
	Bitboard location = (1ULL << index);

	// return piece type pointer at location
	if ((state.whitePawns & location) != 0 || (state.blackPawns & location) != 0) {
		return &pawn;
	}
	else if ((state.whiteRooks & location) != 0 || (state.blackRooks & location) != 0) {
		return &rook;
	}
	else if ((state.whiteKnights & location) != 0 || (state.blackKnights & location) != 0) {
		return &knight;
	}
	else if ((state.whiteBishops & location) != 0 || (state.blackBishops & location) != 0) {
		return &bishop;
	}
	else if ((state.whiteQueens & location) != 0 || (state.blackQueens & location) != 0) {
		return &queen;
	}
	else if ((state.whiteKing & location) != 0 || (state.blackKing & location) != 0) {
		return &king;
	}

	throw std::runtime_error("Piece not found at the specified index!");
}

void Board::shift_bitboard(Bitboard& piece, int oldIndex, int newIndex) {
	// remove the bit from the old index and fill the bit in the new index for all pieces, the piece's bitboard, and the corresponding color bitboard
	Bitboard oldLocation = (1ULL << oldIndex);
	Bitboard newLocation = (1ULL << newIndex);

	piece &= ~oldLocation;
	piece |= newLocation;

	if (playerTurn == WHITE) {
		playerTurn = BLACK;
		whitePieces &= ~oldLocation;
		whitePieces |= newLocation;
	}

	else if (playerTurn == BLACK) {
		playerTurn = WHITE;
		blackPieces &= ~oldLocation;
		blackPieces |= newLocation;
	}

	allPieces &= ~oldLocation;
	allPieces = whitePieces | blackPieces;

	return;
}

void Board::move_sprite(std::pair<int, int> oldCoords, std::pair<int, int> newCoords) {  // Future Self: this isn't updating BB's when a capture occurs that's why everything is funky rn
	float oldX = static_cast<float>(oldCoords.first);
	float oldY = static_cast<float>(oldCoords.second);
	float tempX = static_cast<float>(newCoords.first);
	float tempY = static_cast<float>(newCoords.second);

	int newX = newCoords.first / squareSize;
	int newY = newCoords.second / squareSize;
	int captureIndex = coords_to_bit_index(std::make_pair(newX, newY));

	for (auto& piece : pieces) {  // search all sprites for the one containing the old coords and move it to the new coords
		if (piece.getGlobalBounds().contains(tempX, tempY)) {
			capture_piece(captureIndex);
			piece.setPosition(-100, -100);
		}
		if (piece.getGlobalBounds().contains(oldX, oldY)) {
			piece.setPosition(newX * squareSize, newY * squareSize);
		}
	}

	return;
}

void Board::capture_piece(int captureIndex) {
	Bitboard& capturedPiece = find_piece_bitboard(captureIndex);
	Bitboard capturedSquare = (1ULL << captureIndex);

	capturedPiece &= ~capturedSquare;

	// update colored and all piece bitboards to remove captured piece
	if (playerTurn == WHITE && (capturedSquare & blackPieces)) {
		blackPieces &= ~capturedSquare;
	}
	else if (playerTurn == BLACK && (capturedSquare & whitePieces)) {
		whitePieces &= ~capturedSquare;
	}

	allPieces = whitePieces | blackPieces;

	return;
}
