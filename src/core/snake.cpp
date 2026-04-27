#include "snake.h"

Snake::Snake(Position position, int snakeSize){
    this->body.push_front(position);
    this->head = position;
    this->size = snakeSize;


    for(int i = 1; i <= size-1; i++){
        this->body.push_back(Position(position.getX() - i, position.getY()));
    }
}

Snake::~Snake(){
    this->body.clear();
};

Position Snake::getNewPosition(Direction direction){
    Position newPosition = this->head;
    switch (direction){
        case Direction::Up:
            newPosition = Position(this->head.getX(), this->head.getY() - 1);
            break;
        case Direction::Down:
            newPosition = Position(this->head.getX(), this->head.getY() + 1);
            break;
        case Direction::Left:
            newPosition = Position(this->head.getX() - 1 , this->head.getY());
            break;
        case Direction::Right:
            newPosition = Position(this->head.getX() + 1, this->head.getY());
            break;
    }
    return newPosition;
}

Position Snake::getHead(){
    return this->head;
};
Position Snake::getTail(){
    return this->tail;
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

    this->head = newPosition;
    this->tail = this->body.back();

    return newPosition;
};