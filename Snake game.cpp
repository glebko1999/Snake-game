#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;  
bool GameOver;
const int height = 10;
const int width = 20;
int X, Y, FruitX, FruitY, Score;
int TailX[100], TailY[100];
int nTail = 0;

enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void Setup()
{
    GameOver = false;
    dir = STOP;
    X = width / 2;
    Y = height / 2;
    FruitX = rand() % width;
    FruitY = rand() % height;
}
void Draw()
{
    system("cls");
    for (int i = 0; i < width+2; i++)
    {
        cout << '-';
    }
    cout << endl;
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "|";               
            }  
            if (i == Y && j == X)
            {
                cout << "O";
            }
            else if (i == FruitY && j == FruitX)
            {
                cout << "F";
            }
            else 
            { 
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
           
                    if (TailX[k] == j && TailY[k] == i)
                    {
                        cout << '~'; 
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << ' ';
                }

            }
            if (j == width - 1)
            {
                cout << "|";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width+2; i++)
    {
        cout << '-';
    }
    cout << endl;
    cout << "Score:" << Score << endl;
}
void Input()
{

    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a': if (dir != RIGHT) { dir = LEFT; } break;
        case 'w': if (dir != DOWN) { dir = UP; } break;
        case 's': if (dir != UP) { dir = DOWN; } break;
        case 'd': if (dir != LEFT) { dir = RIGHT; } break;
        case 'x': GameOver = true; break;
        }

    }
}
void Logic()
{
    int prevX = TailX[0];
    int prevY = TailY[0];
    int prevX2, prevY2;
    TailX[0] = X;
    TailY[0] = Y;
    for (int i = 1; i < nTail; i++)
    {
        prevX2 = TailX[i];
        prevY2 = TailY[i];
        TailY[i] = prevY;
        TailX[i] = prevX;
        prevX = prevX2;
        prevY = prevY2;
    }
    switch (dir)
    {
    case LEFT:
        X--;
        break;
    case RIGHT:
        X++;
        break;
    case UP:
        Y--;
        break;
    case DOWN:
        Y++;
        break;
    default:
        break;
    }
    if (X > width-1)
    {
        X = 0;
    }
    if (X < 0)
    {
        X = width-1;
    }
    if (Y >  height)
    {
        Y = 0;
    }
    if (Y < 0)
    {
        Y = height;
    }
    for (int i = 0; i < nTail; i++)
    {
        if (TailX[i] == X && TailY[i] == Y)
        {
            GameOver = true;
        }
    }
    if (X == FruitX && Y == FruitY)
    {
        nTail++;
        Score += 10;
        FruitX = rand() % width;
        FruitY = rand() % height;
    }
}

int main()
{
    Setup();
    while (!GameOver)
    {
        Draw();
        Input();
        Logic();
    }
    std::cout << "GAME OVER!\n" << endl;
    std::cout << "Score:" << Score << endl;
}
