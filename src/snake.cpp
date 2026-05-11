#include "snake.h"

//places the first segment at the given position, then appends the rest to the left of it
Snake::Snake(Position position, int snakeSize){
    this->body.push_front(position);
    this->size = snakeSize;


    for(int i = 1; i <= size-1; i++){
        this->body.push_back(Position(position.getX() - i, position.getY()));
    }
}

//removes all stored body positions from the deque
Snake::~Snake(){
    this->body.clear();
};

//uses the current direction to calculate the next head position while leaving the body unchanged
Position Snake::getNewPosition(Direction direction){
    Position newPosition = this->getHead();
    switch (direction){
        case Direction::Up:
            newPosition = Position(this->getHead().getX(), this->getHead().getY() - 1);
            break;
        case Direction::Down:
            newPosition = Position(this->getHead().getX(), this->getHead().getY() + 1);
            break;
        case Direction::Left:
            newPosition = Position(this->getHead().getX() - 1 , this->getHead().getY());
            break;
        case Direction::Right:
            newPosition = Position(this->getHead().getX() + 1, this->getHead().getY());
            break;
    }
    return newPosition;
}

//the head is always stored at the front of the deque
Position Snake::getHead(){
    return this->body.front();
};

//the tail is always stored at the back of the deque
Position Snake::getTail(){
    return this->body.back();
};

//size is updated separately when the snake grows
int Snake::getSize(){
    return this->size;
}

//moves by pushing a new head; normal movement pops the tail, while growth keeps it
Position Snake::move(Direction direction, bool grow){
    
    Position newPosition = this->getNewPosition(direction);
    
    this->body.push_front(newPosition);

    if (!grow){
        this->body.pop_back();
    }
    else{
        size++;
    }

    this->getHead() = newPosition;
    this->getTail() = this->body.back();

    return newPosition;
};

//returns a copy of the deque so the GUI can draw every segment
deque<Position> Snake::getBody() {
    return this->body;
}
