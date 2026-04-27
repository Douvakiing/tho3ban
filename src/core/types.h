#ifndef THO3BAN_SRC_CORE_TYPES_H
#define THO3BAN_SRC_CORE_TYPES_H

using namespace std;

class Position
{
    private:
        int x;
        int y;
    public:
        Position();
        Position(int x, int y);

        int getX();
        int getY();
        void setX(int x);
        void setY(int y);
        void setPosition(int x, int y);
        
        Position operator+( const Position& rhs );
        
        Position operator-( const Position& rhs );
        
        bool operator==( const Position& rhs ) const;
        
        bool operator!=( const Position& rhs ) const;
};

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

inline bool isOppositeDirection(Direction a, Direction b)
{
    return (a == Direction::Up && b == Direction::Down) ||
           (a == Direction::Down && b == Direction::Up) ||
           (a == Direction::Left && b == Direction::Right) ||
           (a == Direction::Right && b == Direction::Left);
}

#endif