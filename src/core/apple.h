#ifndef THO3BAN_SRC_CORE_APPLE_H
#define THO3BAN_SRC_CORE_APPLE_H

using namespace std;

#include "types.h"

class Apple
{
    private:
        Position position;

    public:
        Apple(Position position);
        Position getPosition();
};

#endif