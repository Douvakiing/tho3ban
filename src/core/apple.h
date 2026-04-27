using namespace std;

#include "types.h"

class Apple
{
    private:
        Position position;

    public:
        Apple(Position position){
            this->position = position;
        };
        ~Apple(){
            this->position = Position{0, 0};
        };
        Position getPosition(){
            return position;
        };
};