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

        bool isCollision(Position position){
            return find(this->body.begin(), this->body.end(), position) != this->body.end();
        };
    public:
        Snake(Position position);
        ~Snake();

        Position getHead();
        Position getTail();

        bool move(Direction direction);
};

#endif