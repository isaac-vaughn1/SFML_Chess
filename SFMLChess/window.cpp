#include "window.h"
#include "board.h"
#include <iostream>

Window::Window() : squareSize(100) {
    lightSquareColor = sf::Color(240, 217, 181); // Hex: #f0d9b5 (beige)
    darkSquareColor = sf::Color(181, 136, 99);   // Hex: #b58863 (light brown)
    load_textures();
    setup_pieces();
}

void Window::load_textures() {
    // Load textures for all pieces (handle errors as necessary)
    if (!blackKingTexture.loadFromFile("resources/blackKing.png") ||
        !blackQueenTexture.loadFromFile("resources/blackQueen.png") ||
        !blackBishopTexture.loadFromFile("resources/blackBishop.png") ||
        !blackKnightTexture.loadFromFile("resources/blackKnight.png") ||
        !blackRookTexture.loadFromFile("resources/blackRook.png") ||
        !blackPawnTexture.loadFromFile("resources/blackPawn.png") ||
        !whiteKingTexture.loadFromFile("resources/whiteKing.png") ||
        !whiteQueenTexture.loadFromFile("resources/whiteQueen.png") ||
        !whiteBishopTexture.loadFromFile("resources/whiteBishop.png") ||
        !whiteKnightTexture.loadFromFile("resources/whiteKnight.png") ||
        !whiteRookTexture.loadFromFile("resources/whiteRook.png") ||
        !whitePawnTexture.loadFromFile("resources/whitePawn.png")) {
        std::cerr << "Error loading textures!" << std::endl;
    }
}

void Window::setup_pieces() {
    // Black pieces
    pieces.emplace_back(blackKingTexture);    pieces.back().setPosition(4 * squareSize, 0 * squareSize); // Black King on e8
    pieces.emplace_back(blackQueenTexture);   pieces.back().setPosition(3 * squareSize, 0 * squareSize); // Black Queen on d8
    pieces.emplace_back(blackBishopTexture);  pieces.back().setPosition(2 * squareSize, 0 * squareSize); // Black Bishop on c8
    pieces.emplace_back(blackBishopTexture);  pieces.back().setPosition(5 * squareSize, 0 * squareSize); // Black Bishop on f8
    pieces.emplace_back(blackKnightTexture);  pieces.back().setPosition(1 * squareSize, 0 * squareSize); // Black Knight on b8
    pieces.emplace_back(blackKnightTexture);  pieces.back().setPosition(6 * squareSize, 0 * squareSize); // Black Knight on g8
    pieces.emplace_back(blackRookTexture);    pieces.back().setPosition(0 * squareSize, 0 * squareSize); // Black Rook on a8
    pieces.emplace_back(blackRookTexture);    pieces.back().setPosition(7 * squareSize, 0 * squareSize); // Black Rook on h8
    for (int col = 0; col < 8; ++col) { // Black Pawns on row 7 (a7-h7)
        pieces.emplace_back(blackPawnTexture);
        pieces.back().setPosition(col * squareSize, 1 * squareSize);  // Black Pawn on 2nd row
    }

    // White pieces
    pieces.emplace_back(whiteKingTexture);    pieces.back().setPosition(4 * squareSize, 7 * squareSize); // White King on e1
    pieces.emplace_back(whiteQueenTexture);   pieces.back().setPosition(3 * squareSize, 7 * squareSize); // White Queen on d1
    pieces.emplace_back(whiteBishopTexture);  pieces.back().setPosition(2 * squareSize, 7 * squareSize); // White Bishop on c1
    pieces.emplace_back(whiteBishopTexture);  pieces.back().setPosition(5 * squareSize, 7 * squareSize); // White Bishop on f1
    pieces.emplace_back(whiteKnightTexture);  pieces.back().setPosition(1 * squareSize, 7 * squareSize); // White Knight on b1
    pieces.emplace_back(whiteKnightTexture);  pieces.back().setPosition(6 * squareSize, 7 * squareSize); // White Knight on g1
    pieces.emplace_back(whiteRookTexture);    pieces.back().setPosition(0 * squareSize, 7 * squareSize); // White Rook on a1
    pieces.emplace_back(whiteRookTexture);    pieces.back().setPosition(7 * squareSize, 7 * squareSize); // White Rook on h1
    for (int col = 0; col < 8; ++col) { // White Pawns on row 2 (a2-h2)
        pieces.emplace_back(whitePawnTexture);
        pieces.back().setPosition(col * squareSize, 6 * squareSize);  // White Pawn on 7th row
    }

    // Scale all pieces to fit within the squares
    for (auto& piece : pieces) {
        piece.setScale(
            static_cast<float>(squareSize) / piece.getTexture()->getSize().x,
            static_cast<float>(squareSize) / piece.getTexture()->getSize().y
        );
    }
}


void Window::draw_board(sf::RenderWindow& window) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition(col * squareSize, row * squareSize);
            if ((row + col) % 2 == 0)
                square.setFillColor(lightSquareColor);
            else
                square.setFillColor(darkSquareColor);
            window.draw(square);
        }
    }
}

void Window::draw_pieces(sf::RenderWindow& window) {
    for (const auto& piece : pieces) {
        window.draw(piece);
    }
}

void Window::run() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    Board board(window, pieces, squareSize);  // create instance of board

    while (window.isOpen()) {

        window.clear();
        draw_board(window);
        board.update();
        window.display();
    }
}
