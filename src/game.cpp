#include <cstdlib>
#include "apple.h"
#include "game.h"
#include "snake.h"

Game::Game()
    : snake( Position{ 5, 5 }, 3 )
    , apple( Position{0,0} )
    , isGameOver( false )
    , gridSize( totalSize ) // copies the static grid size into this game instance
    , CurrentScore( 0 )
    , HighScore(0)
    , inputCache( Direction::Right )
    , grid{} // starts every occupation cell as false
{
    randomizeApplePos();
}

Game::~Game() = default;

//generates random positions until the apple lands on a cell not occupied by the snake
void Game::randomizeApplePos(){
    Position newApplePos;
        do{
            newApplePos.randomizePosition();
        }
        while( grid[newApplePos.getY()][newApplePos.getX()] );
        apple = Apple(newApplePos);
}

//runs one frame of the game: save valid input, check collision, move snake, then handle apple eating
void Game::update(Direction input){
    //once the game is over, ignore any more movement input
    if(isGameOver) return;
    
    if (!isOppositeDirection(input, inputCache)) inputCache = input;
    
    //the next head cell is checked before moving so the snake cannot enter its own body
    Position newHead = snake.getNewPosition(inputCache);
    if(grid[newHead.getY()][newHead.getX()] == true && newHead != snake.getTail()){
        if(CurrentScore > HighScore) HighScore = CurrentScore; 
         isGameOver = true;
         return;
    }

    updateOccupation();

    //when the head reaches the apple, keep the tail so the snake grows by one segment
    if(newHead == apple.getPosition()) {
        CurrentScore += 10;
        snake.move(inputCache, true);
        
        randomizeApplePos();
    }
    else{

        snake.move(inputCache, false); 
    }
    
}

//updates the boolean grid by removing the old tail cell and marking the incoming head cell
void Game::updateOccupation(){
    if(!initialized){
        //on the first update, mark every starting snake segment before normal movement begins
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

//returns the game to its starting state and clears every occupied cell from the collision grid
void Game::resetGame(){
    snake = Snake( Position{ 5, 5 }, 3 );
    apple = Apple( Position{0,0} );
    randomizeApplePos();
    isGameOver = false;
    gridSize = totalSize; // restores the instance grid size to the default value
    CurrentScore = 0;
    inputCache = Direction::Right;
    bool temp[20][20]{};
    for(int i =0;i<20;i++){
        for(int j = 0;j<20;j++){
            grid[i][j] =false;
        }
    }
}

//provides the shared grid size to Position so coordinates can wrap around the board
int Game::getGridSize() {
    return totalSize;
}
