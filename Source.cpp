#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <thread>

using namespace std;

bool gameover{};

const int width = 20, height = 20;

int x, y, fruitX, fruitY, score, nTail;

int tailX[100], tailY[100];

enum eDirection
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

eDirection dir;

void Setup()
{
	gameover = false;

	dir = STOP;

	x = width / 2 - 1;

	y = height / 2 - 1;

	fruitX = rand() % width;

	fruitY = rand() % height;

	score = 0;
}

void Draw()
{
	system("cls");

	for (int i = 0; i < (2 * width) + 1; i++)
	{
		cout << "=";
	}

	cout << "\n";

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				cout << "||";
			}

			if (i == y && j == x)
			{
				cout << "0";
			}
			else
			{
				if (i == fruitY && j == fruitX)
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
							print = true;

							cout << 'o';
						}
					}

					if (!print)
					{
						cout << " ";
					}
				}
			}

			cout << " ";
		}

		cout << "\n";
	}

	for (int i = 0; i < (2 * width) + 1; i++)
	{
		cout << "=";
	}

	cout << "\nScore: " << score << "\n";
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

		case 'd':
			dir = RIGHT;
			break;

		case 'w':
			dir = UP;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'x':
			gameover = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0], prevY = tailY[0], prev2X, prev2Y;

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
	case LEFT:
		x--;
		break;

	case RIGHT:
		x++;
		break;

	case UP:
		y--;
		break;

	case DOWN:
		y++;
		break;
	}

	if (x >= width - 1)
	{
		x = 0;
	}

	if (x < 0)
	{
		x = width - 2;
	}

	if (y >= height)
	{
		y = 0;
	}

	if (y < 0)
	{
		y = height - 2;
	}


	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameover = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		score++;

		fruitX = rand() % width;

		fruitY = rand() % height;

		nTail++;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	ios::sync_with_stdio(0);

	cin.tie(0);

	cout.tie(0);

	HWND console = GetConsoleWindow();

	BOOL moveSuccessful = MoveWindow(console, 0, 0, 1280, 720, TRUE);

	Setup();

	while (!gameover)
	{
		Draw();

		Input();

		Logic();
	}

	return 0;
}