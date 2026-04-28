#ifndef THO3BAN_SRC_CORE_SNAKE_H
#define THO3BAN_SRC_CORE_SNAKE_H

#include <deque>
#include <algorithm>
#include "types.h"

using namespace std;

class Snake
{
    private:
        deque<Position> body;
        Position head;
        Position tail;

        int size;

        Position getNewPosition(Direction direction);

    public:
        Snake(Position position, int snakeSize);
        ~Snake();

        Position getHead();
        Position getTail();
        int getSize();

        Position move(Direction direction, bool grow = false);
        deque<Position> getBody();
};

#endif