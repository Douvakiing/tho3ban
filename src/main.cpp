#include <SFML/Graphics.hpp>
#include <iostream>
#include "core/snake.h"
#include "core/game.h"
#include "core/types.h"

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
	game.start();
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

		while ( tickClock.getElapsedTime().asSeconds() >= tickSeconds )
		{
			game.update(inputDirection);

			cout << game.getSnake().getHead().getX() << " " << game.getSnake().getHead().getY() << endl;

			tickClock.restart();
		}

		window.display();
	}
}
