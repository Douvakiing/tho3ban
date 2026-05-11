#ifndef THO3BAN_SRC_CORE_APPLE_H
#define THO3BAN_SRC_CORE_APPLE_H

using namespace std;

#include "types.h"

class Apple
{
    private:
        //stores the apple cell so the game can compare it with the snake head
        Position position;

    public:
        //creates an apple at the position chosen by the game
        Apple(Position position);

        //returns the current apple cell for drawing and collision checks
        Position getPosition();
};

#endif
