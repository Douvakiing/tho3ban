#include <cstdlib>
#include "types.h"
#include "game.h"

Position::Position(){}

Position::Position(int x, int y){
    this->x = x;
    this->y = y;
}
int Position::getX(){
    return this->x;
}
int Position::getY(){
    return this->y;
}
void Position::setX(int x){
    this->x = x;
}
void Position::setY(int y){
    this->y = y;
}
void Position::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

void Position::randomizePosition(int limit){
    this->x = std::rand() % limit + 1;
    this->y = std::rand() % limit + 1;
}

Position Position::operator+( const Position& rhs )
{
    return Position{ this->x + rhs.x, this->y + rhs.y };
}

bool Position::operator==( const Position& rhs ) const
{
    return this->x == rhs.x && this->y == rhs.y;
}

bool Position::operator!=( const Position& rhs )const
{
    return !( this->x == rhs.x && this->y == rhs.y );
}