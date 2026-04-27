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