class Position
{
    private:
        int x;
        int y;
    public:
        Position();

        Position(int x, int y){
            this->x = x;
            this->y = y;
        };
        ~Position(){
            this->x = 0;
            this->y = 0;
        };
        int getX(){
            return this->x;
        };
        int getY(){
            return this->y;
        };
        void setX(int x){
            this->x = x;
        };
        void setY(int y){
            this->y = y;
        };
        void setPosition(int x, int y){
            this->x = x;
            this->y = y;
        };
        
        Position operator+( const Position& rhs )
        {
            return Position{ this->x + rhs->x, this->y + rhs->y };
        }
        
        Position operator-( const Position& rhs )
        {
            return Position{ this->x - rhs->x, this->y - rhs->y };
        }
        
        bool operator==( const Position& rhs )
        {
            return this->x == rhs->x && this->y == rhs->y;
        }
        
        bool operator!=( const Position& rhs )
        {
            return !( this->x == rhs->x && this->y == rhs->y );
        }
};

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};