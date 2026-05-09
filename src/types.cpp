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
    int limit = Game::getGridSize();
    this->x = (x % limit + limit) % limit;
}
void Position::setY(int y){
    int limit = Game::getGridSize();
    this->y = (y % limit + limit) % limit;
}
void Position::setPosition(int x, int y){
    int limit = Game::getGridSize();
    this->x = (x % limit + limit) % limit;
    this->y = (y % limit + limit) % limit;
}

void Position::randomizePosition(){
    int limit = Game::getGridSize();
    this->x = std::rand() % limit;
    this->y = std::rand() % limit;
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