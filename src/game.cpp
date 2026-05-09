#include "game.h"
#include "snake.h"

Game::Game()
    : snake( Position{ 5, 5 }, 3 )
    , apple( Position{ 0, 0 } )
    , isGameOver( false )
    , gridSize( totalSize ) // HARD CODED FOR NOW, CAUSES A RUNTIME ERROR WHEN totalSize IS USED
    , score( 0 )
    , speed( 1 )
    , inputCache( Direction::Right )
    , grid(totalSize, vector<bool>(20, false)) // GRID INITIALIZATION
{
}

Game::~Game() = default;
void Game::draw() {}

void Game::update(Direction input){
    if (!isOppositeDirection(input, inputCache)) inputCache = input;
    updateOccupation();
    snake.move(inputCache);
}
void Game::updateOccupation(){
    if(!initialized){
        for(int i = 0; i < snake.getSize(); i++){
            grid[snake.getHead().getY()][snake.getHead().getX() - i] = true;
        }
        initialized = true;
    }
    else{
        // TBD
    }
}

