#ifndef THO3BAN_SRC_CORE_SNAKE_H
#define THO3BAN_SRC_CORE_SNAKE_H

#include <deque>
#include <algorithm>
#include "types.h"

using namespace std;

class Snake
{
    private:
        //deque stores the head at the front and the tail at the back for fast movement updates
        deque<Position> body;

        //tracks the number of body segments, including any growth after eating apples
        int size;
        
        public:
        //builds the snake from a head position and extends the body to the left
        Snake(Position position, int snakeSize);

        //clears the deque when the snake object is destroyed
        ~Snake();
        
        //return the current front, back, and saved length of the body deque
        Position getHead();
        Position getTail();
        int getSize();
        
        //adds a new head in the requested direction and removes the tail unless growing
        Position move(Direction direction, bool grow = false);
        
        //calculates where the head would be after moving without changing the snake yet
        Position getNewPosition(Direction direction);

        deque<Position> getBody();
};

#endif
