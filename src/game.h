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
        const int static totalSize = 20; // NEW VARIABLE TO ADJUST SIZE

        Snake snake;
        Apple apple;
        bool isGameOver;
        int gridSize;
        int CurrentScore;
        int HighScore;
        int speed;
        
        Direction inputCache;
        
        vector<vector<bool>> grid; // NEW GRID FOR COLLISION DETECTION
        bool initialized = false; // FOR FIRST TIME INITALIZATION
        
        void updateOccupation();
    public:
        Game();
        ~Game();

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

        void start(){
            snake = Snake(Position{5,5}, 3);
            apple = Apple(Position{0,0});
            isGameOver = false;
            CurrentScore = 0;
            speed = 1;
        };

        void update(Direction input);

        void draw();

        void resetGame();

        int getCurrentScore(){
            return CurrentScore;
        }

        int getHighScore(){
            return HighScore;
        }

};

#endif