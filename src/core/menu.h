#ifndef THO3BAN_SRC_CORE_MENU_H
#define THO3BAN_SRC_CORE_MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

// Define the different screens of our game
enum class GameState { Menu, Playing };

class Menu {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text promptText;
    sf::RectangleShape buttonShape; // Added a background for the text to look like a button
    bool fontLoaded;
    
    std::vector<sf::RectangleShape> logoBlocks;

public:
    Menu(float windowWidth, float windowHeight);
    
    // Handles key presses when on the menu screen
    void handleInput(sf::Keyboard::Scancode key, GameState& currentState);
    
    // Draws the menu shapes to the window
    void draw(sf::RenderWindow& window);
};

#endif