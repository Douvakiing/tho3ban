#ifndef THO3BAN_SRC_CORE_GAME_H
#define THO3BAN_SRC_CORE_GAME_H

using namespace std;

#include "snake.h"
#include "apple.h"
#include "types.h"
#include <vector>

class Game
{
    private:
        const int static totalSize = 20; // fixed width and height used for the square game grid

        Snake snake;
        Apple apple;
        bool isGameOver;
        int gridSize;
        int CurrentScore;
        int HighScore;
        
        Direction inputCache;
        
        bool grid[20][20] = {}; // stores which grid cells are occupied by the snake body
        bool initialized = false; // tells updateOccupation to fill the starting snake cells once
        
        //keeps the occupation grid in sync with the snake movement for collision checks
        void updateOccupation();
        
        //keeps generating apple positions until it finds an empty grid cell
        void randomizeApplePos();
    public:
        //sets the initial snake, apple, score, direction cache, and collision grid
        Game();
        ~Game();

        //restarts the main game objects to their default starting values
        void start(){
            snake = Snake(Position{5,5}, 3);
            apple = Apple(Position{0,0});
            isGameOver = false;
            CurrentScore = 0;
        };

        //applies one tick of input, collision checking, movement, scoring, and apple spawning
        void update(Direction input);

        //clears the current round and rebuilds the starting snake, apple, score, and grid
        void resetGame();

        //simple accessors used by the GUI to draw score, snake, apple, and game state
        int getCurrentScore(){
            return CurrentScore;
        }

        int getHighScore(){
            return HighScore;
        }
        
        static int getGridSize();

        Snake getSnake(){
            return snake;
        }

        Apple getApple(){
            return apple;
        }

        bool getGameState(){
            return isGameOver;
        }

};

#endif
