#include "snake.h"

    Snake::Snake(Position position){
        this->body.push_front(position);
        this->head = position;
    }
    Snake::~Snake(){
        this->body.clear();
    };

    Position Snake::getHead(){
        return this->head;
    };
    Position Snake::getTail(){
        return this->tail;
    };

    bool Snake::move(Direction direction){

        Position newPosition = this->head;

        switch (direction){
            case Direction::Up:
                newPosition = Position(this->head.getX(), this->head.getY() + 1);
                break;
            case Direction::Down:
                newPosition = Position(this->head.getX(), this->head.getY() - 1);
                break;
            case Direction::Left:
                newPosition = Position(this->head.getX() - 1 , this->head.getY());
                break;
            case Direction::Right:
                newPosition = Position(this->head.getX() + 1, this->head.getY());
                break;
        }
        
        
        if (isCollision(newPosition)){
            return false;
        }
        
        this->body.push_front(newPosition);
        this->body.pop_back();

        this->head = newPosition;
        this->tail = this->body.front();
        
        return true;
    };