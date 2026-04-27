#ifndef THO3BAN_SRC_CORE_GAME_H
#define THO3BAN_SRC_CORE_GAME_H

using namespace std;

#include "snake.h"
#include "apple.h"
#include "types.h"

class Game
{
    private:
        Snake snake;
        Apple apple;
        bool isGameOver;
        int gridSize;
        int score;
        int speed;

        Direction inputCache;

    public:
        Game();
        ~Game();
        Snake getSnake(){
            return snake;
        }
        void start(){
            snake = Snake(Position{0,0});
            apple = Apple(Position{0,0});
            isGameOver = false;
            score = 0;
            speed = 1;
        };
        void update(Direction input){
            if (!isOppositeDirection(input, inputCache)) inputCache = input;

            snake.move(inputCache);
        };
        void draw();
};

#endif