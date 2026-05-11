#include <cstdlib>
#include "types.h"
#include "game.h"

//default constructor leaves the coordinates unchanged until a setter assigns them
Position::Position(){}

//initializes both coordinates through setPosition so wrapping rules are applied immediately
Position::Position(int x, int y){
    this->setPosition(x, y);
}

//returns the current wrapped x coordinate
int Position::getX() const {
    return this->x;
}

//returns the current wrapped y coordinate
int Position::getY() const {
    return this->y;
}

//wraps the x coordinate into the range 0 to gridSize - 1, including negative inputs
void Position::setX(int x){
    int limit = Game::getGridSize();
    this->x = (x % limit + limit) % limit;
}

//wraps the y coordinate into the range 0 to gridSize - 1, including negative inputs
void Position::setY(int y){
    int limit = Game::getGridSize();
    this->y = (y % limit + limit) % limit;
}

//sets both coordinates with the same wrap-around formula used by the single-axis setters
void Position::setPosition(int x, int y){
    int limit = Game::getGridSize();
    this->x = (x % limit + limit) % limit;
    this->y = (y % limit + limit) % limit;
}

//chooses random x and y values between 0 and the last valid grid index
void Position::randomizePosition(){
    int limit = Game::getGridSize();
    this->x = std::rand() % limit;
    this->y = std::rand() % limit;
}

//combines two positions and lets the constructor wrap the result if it crosses the grid edge
Position Position::operator+( const Position& rhs )
{
    return Position{ this->x + rhs.x, this->y + rhs.y };
}

//two positions are equal only when both coordinates match
bool Position::operator==( const Position& rhs ) const
{
    return this->x == rhs.x && this->y == rhs.y;
}

//reuses the equality check logic by returning the opposite result
bool Position::operator!=( const Position& rhs )const
{
    return !( this->x == rhs.x && this->y == rhs.y );
}
