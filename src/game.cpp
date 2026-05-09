#include <cstdlib>
#include "apple.h"
#include "game.h"
#include "snake.h"

Game::Game()
    : snake( Position{ 5, 5 }, 3 )
    , apple( Position{std::rand() % Game::getGridSize() , std::rand() % Game::getGridSize()} )
    , isGameOver( false )
    , gridSize( totalSize ) // HARD CODED FOR NOW, CAUSES A RUNTIME ERROR WHEN totalSize IS USED
    , CurrentScore( 0 )
    , HighScore(0)
    , speed( 1 )
    , inputCache( Direction::Right )
    , grid{} // GRID INITIALIZATION
{
}

Game::~Game() = default;
void Game::draw() {}

void Game::update(Direction input){
    // Don't move if we're dead
    if(isGameOver) return;
    
    if (!isOppositeDirection(input, inputCache)) inputCache = input;
    
    // Self-collision
    Position newHead = snake.getNewPosition(inputCache);
    if(grid[newHead.getY()][newHead.getX()] == true && newHead != snake.getTail()){
         isGameOver = true;
         return;
    }

    updateOccupation();

    // Increment CurrentScore & randomize new apple position 
    if(newHead == apple.getPosition()) {
        CurrentScore += 10;
        if(CurrentScore > HighScore) HighScore = CurrentScore;
        snake.move(inputCache, true);
        
        Position newApplePos;
        do{
            newApplePos.randomizePosition();
        }
        while( grid[newApplePos.getY()][newApplePos.getX()] );
        apple = Apple(newApplePos);
    }
    else{

        snake.move(inputCache, false); 
    }
    
}

void Game::updateOccupation(){
    if(!initialized){
        for(int i = 0; i < snake.getSize(); i++){
            grid[snake.getHead().getY()][snake.getHead().getX() - i + 1] = true;
        }
        initialized = true;
    }
    else{
        grid[snake.getTail().getY()][snake.getTail().getX()] = false;

        Position newHead = snake.getNewPosition(inputCache);
        grid[newHead.getY()][newHead.getX()] = true;

    }
}

void Game::resetGame(){
    snake = Snake( Position{ 5, 5 }, 3 );
    apple = Apple( Position{ 0, 0 } );
    isGameOver = false;
    gridSize = totalSize; // HARD CODED FOR NOW, CAUSES A RUNTIME ERROR WHEN totalSize IS USED
    CurrentScore = 0;
    speed = 1;
    inputCache = Direction::Right;
    bool temp[20][20]{};
    for(int i =0;i<20;i++){
        for(int j = 0;j<20;j++){
            grid[i][j] =false;
        }
    }
}

int Game::getGridSize() {
    return totalSize;
}
