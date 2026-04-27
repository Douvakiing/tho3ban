#include "apple.h"

    Apple::Apple(Position position){
        this->position = position;
    }
    Apple::~Apple(){
        this->position = Position{0, 0};
    }
    Position Apple::getPosition(){
        return position;
    }
