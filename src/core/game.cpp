#include "game.h"

Game::Game()
    : snake( Position{ 0, 0 } )
    , apple( Position{ 0, 0 } )
    , isGameOver( false )
    , gridSize( 20 )
    , score( 0 )
    , speed( 1 )
    , inputCache( Direction::Right )
{
}

Game::~Game() = default;

void Game::draw() {}
