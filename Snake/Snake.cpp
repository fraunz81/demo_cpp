/*
 * Snake.cpp
 * 
 * Copyright 2015 Franz Habison <habison.franz@gmx.at>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//#include <curses.h>


using namespace std;



int kbhit(void);
int getch();


bool gameOver;

const int width = 20;
const int height = 20;

int x, y;	// Head
int fruitX, fruitY;
int score;
int tailX[100], tailY[100];
int nTail;


enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


int kbhit(void)
{
	struct termios term, oterm;
	int fd = 0;
	int c = 0;

	tcgetattr(fd, &oterm);
	memcpy(&term, &oterm, sizeof(term));
	term.c_lflag = term.c_lflag & (!ICANON);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 1;
	tcsetattr(fd, TCSANOW, &term);
	c = getchar();
	tcsetattr(fd, TCSANOW, &oterm);
	if (c != -1)
	ungetc(c, stdin);
	return ((c != -1) ? 1 : 0);
}


int getch()
{
   static int ch = -1, fd = 0;
   struct termios neu, alt;

   fd = fileno(stdin);
   tcgetattr(fd, &alt);
   neu = alt;
   neu.c_lflag &= ~(ICANON|ECHO);
   tcsetattr(fd, TCSANOW, &neu);
   ch = getchar();
   tcsetattr(fd, TCSANOW, &alt);

   return ch;
}

/*
static void clrscr(void)
{
	const char *ptr = tigetstr("clear");
	putp(ptr);
}
*/



void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("clear"); //system("cls"); windows
	//clrscr();
	for (int i = 0; i < width + 2; i++)
		cout << "#";

	cout << endl;
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
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
					cout << " ";
			}
				
			if (j == width - 1)
				cout << "#";
		}
		
		cout << endl;
	}
	
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input()
{
	if (kbhit())
	{
		switch (getch())
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
	
	switch(dir)
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
		
		case STOP:
			//gameOver = true;
			break;
	}
	
	//if (x > width || x < 0 || y > height || y < 0)
		//gameOver = true;
	
	if (x >= width) x = 0;
	else if (x < 0) x = width - 1;

	if (y >= height) y = 0;
	else if (y < 0) y = height - 1;
	
	
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}


int main(int argc, char **argv)
{
	Setup();
	while(!gameOver)
	{
		Draw();
		Input();
		Logic();
		//Sleep(10);
		//sleep(1);
		//break;
	}
	
	return 0;
}

















