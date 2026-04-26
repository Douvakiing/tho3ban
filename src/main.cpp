#include <SFML/Graphics.hpp>

int main()
{
	constexpr int gridSize = 20;
	constexpr float cellSize = 32.f;
	constexpr float tickSeconds = 0.5f;
	constexpr float gridOffset = 20.f;

	const float windowSize = gridOffset * 2.f + ( cellSize * gridSize );
	sf::RenderWindow window(
		sf::VideoMode( { static_cast<unsigned int>( windowSize ), static_cast<unsigned int>( windowSize ) } ),
		"20x20 Grid Traversal" );

	sf::RectangleShape cell( { cellSize, cellSize } );
	cell.setFillColor( sf::Color::Transparent );
	cell.setOutlineColor( sf::Color( 70, 70, 70 ) );
	cell.setOutlineThickness( 1.f );

	sf::RectangleShape traveler( { cellSize - 4.f, cellSize - 4.f } );
	traveler.setFillColor( sf::Color::Green );

	int currentIndex = 0;
	sf::Clock tickClock;

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
			{
				window.close();
			}
		}

		while ( tickClock.getElapsedTime().asSeconds() >= tickSeconds )
		{
			currentIndex = ( currentIndex + 1 ) % ( gridSize * gridSize );
			tickClock.restart();
		}

		const int row = currentIndex / gridSize;
		const int col = currentIndex % gridSize;
		traveler.setPosition(
			{ gridOffset + ( col * cellSize ) + 2.f, gridOffset + ( row * cellSize ) + 2.f } );

		window.clear( sf::Color::Black );

		for ( int y = 0; y < gridSize; ++y )
		{
			for ( int x = 0; x < gridSize; ++x )
			{
				cell.setPosition( { gridOffset + ( x * cellSize ), gridOffset + ( y * cellSize ) } );
				window.draw( cell );
			}
		}

		window.draw( traveler );
		window.display();
	}
}
