#include <SFML/Graphics.hpp>
#include <iostream>
#include "core/snake.h"
#include "core/game.h"
#include "core/types.h"
#include "core/menu.h" // Added menu header

using namespace std;

int main()
{
    constexpr int gridSize = 20;
    constexpr int cellSize = 32;
    constexpr float tickSeconds = 0.5f;

    sf::RenderWindow window(
        sf::VideoMode( { 800u, 600u } ),
        "tho3ban" );

    sf::Clock tickClock;

    Game game = Game();
    Menu menu(800.f, 600.f); // Create the menu based on your 800x600 window
    GameState currentState = GameState::Menu; // Start in the Menu state
    
    Direction inputDirection = Direction::Right;

    while ( window.isOpen() )
    {
        while ( const std::optional event = window.pollEvent() )
        {
            if ( event->is<sf::Event::Closed>() )
            {
                window.close();
            }

            if ( const auto* keyPressed = event->getIf<sf::Event::KeyPressed>() )
            {
                if (currentState == GameState::Menu)
                {
                    // Let the menu handle input (waiting for Enter)
                    menu.handleInput(keyPressed->scancode, currentState);
                    
                    // If Enter was pressed, start the game
                    if (currentState == GameState::Playing) {
                        game.start();
                        inputDirection = Direction::Right;
                        tickClock.restart();
                    }
                }
                else if (currentState == GameState::Playing)
                {
                    // Your original snake controls
                    switch ( keyPressed->scancode )
                    {
                        case sf::Keyboard::Scancode::Up:
                            inputDirection = Direction::Up;
                            break;
                        case sf::Keyboard::Scancode::Left:
                            inputDirection = Direction::Left;
                            break;
                        case sf::Keyboard::Scancode::Down:
                            inputDirection = Direction::Down;
                            break;
                        case sf::Keyboard::Scancode::Right:
                            inputDirection = Direction::Right;
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        // Only update game logic if we are actively playing
        if (currentState == GameState::Playing)
        {
            while ( tickClock.getElapsedTime().asSeconds() >= tickSeconds )
            {
                game.update(inputDirection);

                cout << game.getSnake().getHead().getX() << " " << game.getSnake().getHead().getY() << endl;

                tickClock.restart();
            }
        }

        // Clear the screen before drawing (required for SFML graphics)
        window.clear(sf::Color::Black);

        // Draw the menu if we are in the Menu state
        if (currentState == GameState::Menu)
        {
            menu.draw(window);
        }

        window.display();
    }
}