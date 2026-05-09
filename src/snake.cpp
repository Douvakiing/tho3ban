#include "snake.h"

Snake::Snake(Position position, int snakeSize){
    this->body.push_front(position);
    this->size = snakeSize;


    for(int i = 1; i <= size-1; i++){
        this->body.push_back(Position(position.getX() - i, position.getY()));
    }
}

Snake::~Snake(){
    this->body.clear();
};

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

Position Snake::getHead(){
    return this->body.front();
};
Position Snake::getTail(){
    return this->body.back();
};
int Snake::getSize(){
    return this->size;
}

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

deque<Position> Snake::getBody() {
    return this->body;
}