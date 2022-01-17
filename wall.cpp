#include "wall.h"

/*
二维数组坐标系(x,y)：
（0，0） (0,1)  (0,2)  (0,3)  (0,4)  (0,5)  (0,6)...
（1，0）
（2，0）
（3，0）
（4，0）
（5，0）
（6，0）...                                 (6,6)
...

这与电脑是完全不同的（电脑屏幕左上角往右x不断增加，向下Y不断增加）。所以一定要注意
*/

//初始化墙壁
void Wall::initWall()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			//放墙：i==0 or j==0 or i==ROW-1 OR j==COL-1
			if (i==0||j==0||i==ROW-1||j==COL-1)
			{
				gameArray[i][j] = '*';
			}
			else
			{
				gameArray[i][j] = ' ';
			}

		}
	}
}

//画墙
void Wall::drawWall()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cout << gameArray[i][j] << " ";//后面加了一个空格显示，好看一点，否则太挤。这样做并不改变数据内容。			
		}

		if (i == 2)
		{
			cout << "CopyRight:2021@";
		}
		if (i == 3)
		{
			cout << "Version 1.0";
		}
		if (i == 4)
		{
			cout << "Created by Liao";
		}
		if (i == 6)
		{
			cout << "A:left";
		}
		if (i == 7)
		{
			cout << "D:right";
		}
		if (i == 8)
		{
			cout << "W:up";
		}
		if (i == 9)
		{
			cout << "S:down";
		}

		if (i == 11)
		{
			cout << "Rules of the game";//#It's food
		}

		if (i == 12)
		{
			cout << "======================";
		}

		if (i == 13)
		{
			cout << "# It's food";
		}
		if (i == 14)
		{
			cout << "= = @ It's a snake";
		}
		if (i == 15)
		{
			cout << "Eat and grow up";
		}
		if (i == 16)
		{
			cout << "Touch the wall and die";
		}
		if (i == 17)
		{
			cout << "Eat yourself and die";
		}

		if (i == 18)
		{
			cout << "Good luck,and enjoy!";
		}
		if (i == 19)
		{
			cout << "======================";
		}

		


		cout << endl;
	}
}
//这是本游戏的最初的设计，按照推荐尺寸26X26显示明显有一个问题，控制台容器太小不能全部显示出来。有办法：控制台可
//修改属性把窗口高度设为30，以后再打开控制台的默认高度也会改为30.

//根据索引设置  二维数组里的内容
void Wall::setWall(int x, int y, char c)
{
	gameArray[x][y] = c;
}
//根据索引获取当前位置的符号
char Wall::getWall(int x, int y)
{
	return gameArray[x][y];
}