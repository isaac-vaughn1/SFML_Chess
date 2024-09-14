#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>

class Window {
public:
    Window();
    void run();

private:
    void drawBoard(sf::RenderWindow& window);
    void drawPieces(sf::RenderWindow& window);
    void loadTextures();
    void setupPieces();

    int squareSize;
    sf::Color lightSquareColor, darkSquareColor;
    std::vector<sf::Sprite> pieces;

    // Textures for pieces
    sf::Texture blackKingTexture, blackQueenTexture, blackBishopTexture, blackKnightTexture, blackRookTexture, blackPawnTexture;
    sf::Texture whiteKingTexture, whiteQueenTexture, whiteBishopTexture, whiteKnightTexture, whiteRookTexture, whitePawnTexture;
};

#endif // WINDOW_H
