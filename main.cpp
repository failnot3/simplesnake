#include <iostream>
#include <conio.h> // For _kbhit() and _getch() functions
#include <windows.h> // For Sleep() function

using namespace std;

bool gameover; // Flag to indicate whether the game is over
const int width = 20; // Width of the game area
const int height = 10; // Height of the game area
int x, y, fruitX, fruitY, score; // Variables for snake position, fruit position, and score
int tailX[100], tailY[100]; // Arrays to store the positions of the snake's tail segments
int nTail; // Length of the snake (number of tail segments)
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN }; // Enumeration for snake movement directions
eDirecton dir; // Current direction of the snake

void setup()
{
    gameover = false; // Initialize game over flag
    dir = STOP; // Initial direction is stopped
    x = width / 2; // Initial x position of the snake
    y = height / 2; // Initial y position of the snake
    fruitX = rand() % width; // Random x position of the fruit within the game area
    fruitY = rand() % height; // Random y position of the fruit within the game area
    score = 0; // Initialize score to zero
    nTail = 0; // Initialize the length of the snake to zero
}

void draw()
{
    system("cls"); // Clear the console screen
    // Draw the top boundary of the game area
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    // Draw the game area and its contents
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "|"; // Draw left boundary of the game area

            // Draw snake's head or fruit at their respective positions
            if (i == y && j == x)
                cout << "0"; // Snake's head
            else if (i == fruitY && j == fruitX)
                cout << "A"; // Fruit
            else
            {
                bool print = false;
                // Check if the current position is occupied by a tail segment
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // Draw tail segment
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; // Empty space
            }

            if (j == width - 1)
                cout << "|"; // Draw right boundary of the game area
        }
        cout << endl;
    }

    // Draw the bottom boundary of the game area
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;
    cout << "Score: " << score << endl; // Display current score
}

void input()
{
    if (_kbhit()) // Check if a keyboard key is pressed
    {
        switch (_getch()) // Get the pressed key
        {
        case 'a':
            dir = LEFT; // Set direction to Left
            cout << "LEFT" << endl;
            break;
        case 'd':
            dir = RIGHT; // Set direction to Right
            cout << "RIGHT" << endl;
            break;
        case 'w':
            dir = UP; // Set direction to Up
            cout << "UP" << endl;
            break;
        case 's':
            dir = DOWN; // Set direction to Down
            cout << "DOWN" << endl;
            break;
        case 'x':
            gameover = true; // Set game over flag to True
            cout << "GAME OVER" << endl;
            break;
        }
    }
}

void algorithm()
{
    // Move the snake's head based on the current direction
    int prevX = x;
    int prevY = y;

    switch (dir)
    {
    case LEFT:
        x--; // Move left
        break;
    case RIGHT:
        x++; // Move right
        break;
    case UP:
        y--; // Move up
        break;
    case DOWN:
        y++; // Move down
        break;
    default:
        break;
    }

     // Debugging statements
    cout << "Head position: (" << x << ", " << y << ")" << endl;
    for (int i = 0; i < nTail; i++)
        cout << "Tail segment " << i << " position: (" << tailX[i] << ", " << tailY[i] << ")" << endl;

    // Wrap around the game area if the snake hits the boundaries
    if (x >= width) 
        x = 0; // Wrap around from right to left
    else if (x < 0) 
        x = width - 1; // Wrap around from left to right
    if (y >= height) 
        y = 0; // Wrap around from bottom to top
    else if (y < 0) 
        y = height - 1; // Wrap around from top to bottom

    // Check for collision with the snake's tail
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = true; // Collision with tail, set game over flag

    // Update the positions of the tail segments based on the previous positions of the head
    int prev2X, prev2Y;
    tailX[0] = prevX;
    tailY[0] = prevY; // Update first tail segment to previous head position

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY; // Update each tail segment to previous position of the segment in front
        prevX = prev2X;
        prevY = prev2Y;
    }

    // If the snake eats the fruit, increase score, generate a new fruit, and increase the snake's length
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    setup(); // Initialize the game
    while (!gameover) // Main game loop
    {
        draw(); // Draw the game
        input(); // Get user input
        algorithm(); // Update game state
        Sleep(100); // Sleep for 100 milliseconds to control the speed of the game
    }

    return 0;
}
