// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<conio.h>
#include<vector>
#include<Windows.h>
#include<time.h>

class snake {
	
	std::vector <std::vector<int>> x;
	int food[2];
	bool foodstat;
	int Map[20][20];
	int dir =0;
	
public:
	enum MyEnum
	{
		Head, Tail, Food, Wallh, Wallv, Space
	};
	enum direction{Left,Right,Up,Down};
	snake()
	{

		x.push_back({ 10,10 });
		x.push_back({ 9,10 });
		x.push_back({ 8,10 });

		foodstat = false;
		for(int i=0;i<20;i++)
			for (int j = 0; j < 20; j++)
			{
				Map[i][j] = Space;
			}

				
	}

	bool spx(int x,int y)
	{
		for (int re =0; re < this->x.size(); re++)
		{
			if (this->x[re][0] == x && this->x[re][1] == y)
				return true;

		}
		return false;
	}

	void randposi()
	{

		do
		{
			food[0]= (int)rand()%18+1;
			food[1] = (int)rand()%18+1;
		} while (spx(food[0],food[1]));
	}


	void foodpos()
	{
		if (foodstat == false)
		{
			randposi();
			Map[food[0]][food[1]] = Food;
			foodstat = true;
		}

	}
	void snakemap(int temp[])
	{
			if(temp!=NULL)
		    Map[temp[0]][temp[1]] = Space;

			Map[x[0][0]][x[0][1]] = Head;
			
			for (int i = 1; i <x.size(); i++)
			{
				Map[x[i][0]][x[i][1]] = Tail; 
			}
			std::cout << x.size()-3 << "\n";
			
	}
	void snakemove()
	{
		int temp[2];
		temp[0] = x[x.size() - 1][0];
		temp[1] = x[x.size() - 1][1];
		int temp2[2];
		temp2[0] = x[0][0];
		temp2[1] = x[0][1];
		for (int i = x.size()-1; i > 0; --i)
			x[i] = x[i-1];
		
		switch (dir)
		{
		case Up:
			x[0][0] = x[0][0] - 1;
			break;
		case Down:
			x[0][0] = x[0][0] + 1;
			break;
		case Left:
			x[0][1] = x[0][1] - 1;
			break;
		case Right:
			x[0][1] = x[0][1] + 1;
			break;

		default:
			break;
		}
		
		if (x[0][0] == food[0] && x[0][1] == food[1])
		{
			snakeadd();
			foodstat = false;
		}
		snakemap(temp);
	}

	void snakeadd()
	{
		x.push_back({ food[0],food[1] });
		
	}

	void wall()
	{
		for (int i = 1; i <20; i++)
		{
			Map[i][0] = Wallv;
			Map[i][19] = Wallv;

		}
		for (int i = 1; i <20; i++)
		{
			Map[0][i] = Wallh;
			Map[19][i] = Wallh;

		}
	}

	void printMap()
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				switch (Map[i][j])
				{
				case Head:
					std::cout << "0 ";
					break;
				case Tail:
					std::cout << "~ ";
					break;
				case Food:
					std::cout << "x ";
					break;
				case Wallh:
					std::cout << "- ";
					break;
				case Wallv:
					std::cout << "| ";
					break;
				case Space:
					std::cout << "  ";
						break;
				default:
					break;}
				
			}
			std::cout << "\n";
		}
	}
	bool collision()
	{
		for (int i = 3; i < x.size(); i++)
		{

			if (x[0][0] == x[i][0] && x[0][1] == x[i][1] && foodstat==true)
			{
				 return true;
			}
		}
		if (x[0][0]==0 || x[0][0]==20 || x[0][1] == 0 || x[0][1] == 20)
			return true;
		else
			return false;
	}
	void keypress()
	{
		if (_kbhit() == 1)
		{
			char key = _getch();
			switch (key)
			{
			case 'a':
				if (dir == Right);
				else dir = Left;
				break;
			case 'w':
				if (dir == Down);
				else dir = Up;
				break;
			case 's':

				if (dir == Up);
				else dir = Down;
				break;
			case 'd':
				if (dir == Left);
				else dir = Right;
				break;
			default:
				break;
			}
		}
	}
	void start()
	{
		
		dir = Right;
		while (1)
		{
			wall();
			foodpos();
			snakemove();
			
			printMap();
			keypress();
			
			if (collision() == true)
			{
				break;
			}
			

			Sleep(100);

			system("CLS");
		}
	}


	
};


int main()
{
	srand(time(0));
	std::cout << "Start Game";
	while (_getch() == 'y')
	{
	snake first;
	first.start();
	std::cout << "Game Over!!!!!!!!!!!!!!";
	std::cout << "Do you want to restart again";
	}
   return 0;

}
