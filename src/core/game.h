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
        const int totalSize = 20; // NEW VARIABLE TO ADJUST SIZE

        Snake snake;
        Apple apple;
        bool isGameOver;
        int gridSize;
        int score;
        int speed;
        
        Direction inputCache;
        
        vector<vector<bool>> grid; // NEW GRID FOR COLLISION DETECTION
        bool initialized = false; // FOR FIRST TIME INITALIZATION
        
        void updateOccupation();
    public:
        Game();
        ~Game();

        Snake getSnake(){
            return snake;
        }

        void start(){
            snake = Snake(Position{0,0}, 3);
            apple = Apple(Position{0,0});
            isGameOver = false;
            score = 0;
            speed = 1;
        };

        void update(Direction input){};

        void draw();

};

#endif