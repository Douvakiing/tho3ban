#include "menu.h"
#include <iostream>

// Use member initializer list to pass the font safely
Menu::Menu(float windowWidth, float windowHeight) 
    : fontLoaded(false), titleText(font), promptText(font) 
{
    // --- 1. Build the pixel-art snake logo (Center) ---
    float blockSize = 40.f;
    float startX = (windowWidth / 2.f) - (blockSize * 2.f);
    float startY = (windowHeight / 2.f) - (blockSize / 2.f);

    for (int i = 0; i < 5; i++) {
        sf::RectangleShape block({blockSize - 2.f, blockSize - 2.f});
        if (i == 4) block.setFillColor(sf::Color::Green); // Head
        else block.setFillColor(sf::Color(0, 150, 0)); // Body
        
        if (i < 3) block.setPosition({startX + (i * blockSize), startY});
        else block.setPosition({startX + (2 * blockSize), startY - ((i - 2) * blockSize)});
        
        logoBlocks.push_back(block);
    }
    
    sf::RectangleShape apple({blockSize - 10.f, blockSize - 10.f});
    apple.setFillColor(sf::Color::Red);
    apple.setPosition({startX + (3.5f * blockSize), startY - (2 * blockSize) + 5.f});
    logoBlocks.push_back(apple);

    // --- 2. Load Font and Setup Text & Button Box ---
    if (font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        fontLoaded = true;

        // Title (Top)
        titleText.setString("Tho3ban++");
        titleText.setCharacterSize(60);
        titleText.setFillColor(sf::Color::Green);
        titleText.setPosition({ windowWidth / 2.f - 140.f, windowHeight / 6.f });

        // Button Background (Bottom)
        buttonShape.setSize({300.f, 60.f});
        buttonShape.setFillColor(sf::Color(40, 40, 40));
        buttonShape.setOutlineThickness(2.f);
        buttonShape.setOutlineColor(sf::Color::Green);
        buttonShape.setPosition({ windowWidth / 2.f - 150.f, windowHeight * 0.75f });

        // Prompt Text (Inside Button)
        promptText.setString("Press ENTER to Start");
        promptText.setCharacterSize(24);
        promptText.setFillColor(sf::Color::White);
        promptText.setPosition({ windowWidth / 2.f - 115.f, (windowHeight * 0.75f) + 15.f });
    } else {
        std::cout << "WARNING: Could not load font! Make sure arial.ttf is in the resources folder.\n";
    }
}

void Menu::handleInput(sf::Keyboard::Scancode key, GameState& currentState) {
    if (key == sf::Keyboard::Scancode::Enter) {
        currentState = GameState::Playing; // Switch state to start the game
    }
}

void Menu::draw(sf::RenderWindow& window) {
    // Draw Logo First
    for (const auto& block : logoBlocks) {
        window.draw(block);
    }
    
    // Draw Font-based UI
    if (fontLoaded) {
        window.draw(titleText);
        window.draw(buttonShape); // Draw button box first
        window.draw(promptText);  // Draw text on top
    }
}