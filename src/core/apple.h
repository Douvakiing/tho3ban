using namespace std;

#include "types.h"

class Apple
{
    private:
        Position position;

    public:
        Apple(Position position);
        ~Apple();
        Position getPosition();
};