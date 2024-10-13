#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>

class Window {
public:
    Window();
    void run();

private:
    void draw_board(sf::RenderWindow& window);
    void draw_pieces(sf::RenderWindow& window);
    void load_textures();
    void setup_pieces();

    int squareSize;
    sf::Color lightSquareColor, darkSquareColor;
    std::vector<sf::Sprite> pieces;

    // Textures for pieces
    sf::Texture blackKingTexture, blackQueenTexture, blackBishopTexture, blackKnightTexture, blackRookTexture, blackPawnTexture;
    sf::Texture whiteKingTexture, whiteQueenTexture, whiteBishopTexture, whiteKnightTexture, whiteRookTexture, whitePawnTexture;
};

#endif // WINDOW_H
