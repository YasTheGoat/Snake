#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
bool gameOver;
const int width = 100;
const int height = 25;
int tailX[100], tailY[100];
int nTail;
int x, y, fruitX, fruitY, score;

enum eDirection
{
    STOP = 0,
    RIGHT,
    LEFT,
    UP,
    DOWN
};
eDirection dir;

void Setup()
{
    gameOver = false;

    x = width / 2;
    y = height / 2;

    fruitX = rand() % width;
    fruitY = rand() % height;
}

void Draw()
{

    system("cls");

    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "#";
            }
            if (j == x && i == y)
            {
                cout << "&";
            }
            else if (j == fruitX && i == fruitY)
            {

                cout << "F";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {

                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }

                if (!print)
                {
                    cout << " ";
                }
            }

            if (j == width - 1)
            {
                cout << "#";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }

    cout << endl;
    cout << "Score: " << score << endl;
}

void Input()
{
    if (_kbhit())
    {

        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 120:
            gameOver = true;
            break;
        }
    }
}

void Logic()
{

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case RIGHT:
        x++;
        break;
    case LEFT:
        x--;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x > width || x < 0 || y > height || y < 0)
    {
        gameOver = true;
    }

    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY)
    {
        nTail++;
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
    }

    cout << endl;
    cout << "You Lost";
    cout << "Thank you for playing";
    cout << endl;

    cin.get();
}
