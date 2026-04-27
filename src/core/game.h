using namespace std;

#include "snake.h"
#include "apple.h"

class Game
{
    private:
        Snake snake;
        Apple apple;
        bool isGameOver;
        int gridSize;
        int score;
        int speed;

        Position inputCache;

    public:
        Game();
        ~Game();
        void start();
        void update(Position input){
            if (input != Position{0,0}){
                snake.move(input);
                input = Position{0,0};
            }
            if ((input - inputCache) % 2 == 0){
                snake.move(input);
            }
        };
        void draw();
};