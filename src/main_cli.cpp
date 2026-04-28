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
        game.update(inputDirection);

        // --- 3. Rendering ---
        string frame = "";
        Position head = game.getSnake().getHead();
        Position tail = game.getSnake().getTail();

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
                
                if (current == head) {
                    frame += " O |"; // Head with right divider
                } else if (current == tail) {
                    frame += " o |"; // Tail with right divider
                } else {
                    frame += "   |"; // Empty space with right divider
                }
            }
            frame += "\n";
            frame += horizontalDivider; // Row bottom divider
        }
        
        frame += "Use Arrow Keys to move. Press X to quit.\n";
        frame += "Notice: Only Head (O) and Tail (o) are drawn without editing core files.\n";

        // Move the cursor to the top left to overwrite the old frame smoothly
        cout << "\033[H" << frame;

        this_thread::sleep_for(chrono::milliseconds(300));
    }

    return 0;
}