#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <string>
#include "core/snake.h"
#include "core/game.h"
#include "core/types.h"

using namespace std;

int main() {
    constexpr int gridSize = 10;
    
    Game game = Game();
    game.start();
    Direction inputDirection = Direction::Right;

    // Variables to store the characters we will draw for the head and tail
    char headChar = '>';
    char tailChar = 'o';

    system("cls");

    while (true) {
        // --- 1. Input Handling ---
        if (_kbhit()) {
            int ch = _getch();
            
            if (ch == 224 || ch == 0) {
                ch = _getch();
                switch (ch) {
                    case 72: inputDirection = Direction::Down; break; 
                    case 80: inputDirection = Direction::Up; break;    
                    case 75: inputDirection = Direction::Left; break;  
                    case 77: inputDirection = Direction::Right; break; 
                }
            } 
            else if (ch == 'x' || ch == 'X') {
                return 0; 
            }
        }

       // --- 2. Logic Update ---
        // Grab the state BEFORE the update
        Snake oldSnake = game.getSnake();
        Position prevHead = oldSnake.getHead();
        Position prevTail = oldSnake.getTail();

        game.update(inputDirection);

        // Grab the new state AFTER the update
        Snake Whitesnake = game.getSnake();
        Position head = Whitesnake.getHead();
        Position tail = Whitesnake.getTail();
        deque<Position> body = Whitesnake.getBody();

        // Determine Head Direction Character
        if (head.getX() > prevHead.getX()) headChar = '>';
        else if (head.getX() < prevHead.getX()) headChar = '<';
        else if (head.getY() > prevHead.getY()) headChar = 'v';
        else if (head.getY() < prevHead.getY()) headChar = '^';

        // Determine Tail Direction Character
        if (tail.getX() > prevTail.getX()) tailChar = '<';
        else if (tail.getX() < prevTail.getX()) tailChar = '>';
        else if (tail.getY() > prevTail.getY()) tailChar = '^';
        else if (tail.getY() < prevTail.getY()) tailChar = 'v';

        // Determine body orientation
        


        // --- 3. Rendering ---
        string frame = "";

        // Create the horizontal divider string (+---+---+...+)
        string horizontalDivider = "+";
        for (int i = 0; i < gridSize; i++) {
            horizontalDivider += "---+";
        }
        horizontalDivider += "\n";

        // Top Border
        frame += horizontalDivider;

        // Draw Grid with vertical and horizontal dividers
        for (int y = 0; y < gridSize; y++) {
            frame += "|"; // Leftmost wall
            
            for (int x = 0; x < gridSize; x++) {
                Position current(x, y);
                // Check if current position is part of the body (excluding head and tail)
                bool isBody = false;
                char currentBodyChar = '-'; // Default
                // body[0] is head, body.back() is tail, so we check the ones in between
                for (int i = 1; i < body.size() - 1; i++) {
                    if (current == body[i]) {
                        isBody = true;
                        if (body[i-1].getX() == body[i+1].getX()) {
                            currentBodyChar = '|'; // Vertical segment
                        } else if (body[i-1].getY() == body[i+1].getY()) {
                            currentBodyChar = '-'; // Horizontal segment
                        } else {
                            currentBodyChar = '+'; // Corner piece
                        }
                        break;
                    }
                }
                
                if (current == head) {
                    // Draw the directional head
                    frame += " ";
                    frame += headChar;
                    frame += " |";
                } else if (current == tail) {
                    // Draw the directional tail
                    frame += " ";
                    frame += tailChar;
                    frame += " |";
                } else if(isBody){
                    frame += " ";
                    frame += currentBodyChar;
                    frame += " |";
                } else {
                    frame += "   |"; // Empty space with right divider
                }
            }
            frame += "\n";
            frame += horizontalDivider; // Row bottom divider
        }

        frame += "Score: " + to_string(game.getScore()) + "\n";

        frame += "Use Arrow Keys to move. Press X to quit.\n";
        frame += "Notice: Only Head and Tail are drawn without editing core files.\n";

        // Move the cursor to the top left to overwrite the old frame smoothly
        cout << "\033[H" << frame;

        this_thread::sleep_for(chrono::milliseconds(300));
    }

    return 0;
}