#ifndef THO3BAN_SRC_CORE_TYPES_H
#define THO3BAN_SRC_CORE_TYPES_H

using namespace std;

class Position
{
    private:
        //x and y are stored after wrapping them inside the game grid limits
        int x;
        int y;
    public:
        //constructors either leave the position empty or initialize it through setPosition
        Position();
        Position(int x, int y);

        //setters normalize coordinates so moving past an edge wraps to the opposite side
        int getX() const;
        int getY() const;
        void setX(int x);
        void setY(int y);
        void setPosition(int x, int y);

        //uses the current game grid size as the limit for random x and y values
        void randomizePosition();
        
        //adds two positions and returns the wrapped result through the Position constructor
        Position operator+( const Position& rhs );
        
        bool operator==( const Position& rhs ) const;
        
        bool operator!=( const Position& rhs ) const;
};

//represents the four movement directions accepted by the snake
enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

//prevents an instant 180-degree turn by comparing the new input with the current direction
inline bool isOppositeDirection(Direction a, Direction b)
{
    return (a == Direction::Up && b == Direction::Down) ||
           (a == Direction::Down && b == Direction::Up) ||
           (a == Direction::Left && b == Direction::Right) ||
           (a == Direction::Right && b == Direction::Left);
}

#endif
