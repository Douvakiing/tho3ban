#include <deque>
#include <algorithm>
#include "types.h"

using namespace std;

class Snake
{
    private:
        deque<Position> body;
        Position head;
        Position tail;

        bool isCollision(Position position){
            return find(this->body.begin(), this->body.end(), position) != this->body.end();
        };
    public:
        Snake(Position position){
            this->body.push_front(position);
            this->head = position;
        };
        ~Snake(){
            this->body.clear();
        };

        Position getHead(){
            return this->head;
        };
        Position getTail(){
            return this->tail;
        };

        bool move(Direction direction){

            switch (direction){
                case Direction::Up:
                    direction = Position{0, -1};
                    break;
                case Direction::Down:
                    direction = Position{0, 1};
                    break;
                case Direction::Left:
                    direction = Position{-1, 0};
                    break;
                case Direction::Right:
                    direction = Position{1, 0};
                    break;
            }
            
            Position newPosition = this->head + direction;
            if (isCollision(newPosition)){
                return false;
            }
            
            this->body.push_front(newPosition);
            this->body.pop_back();

            this->head = newPosition;
            this->tail = this->body.front();
            
            return true;
        };
};