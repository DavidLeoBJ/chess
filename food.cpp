#include "food.h"
#include<Windows.h>


void gotoxy2(HANDLE hOut2, int x, int y)
{
	COORD pos;
	pos.X = x;		//横坐标
	pos.Y = y;		//纵坐标
	SetConsoleCursorPosition(hOut2, pos);
}
HANDLE hOut2 = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量

Food::Food(Wall &tempWall) :wall(tempWall)
{

}

//设置
void Food::setFood()
{
	while (true)
	{ 
		//随机的 1-12X1-12
		foodX = rand() % (Wall::ROW - 2) + 1;//需要在food.h中包含wall.h
		foodY = rand() % (Wall::COL - 2) + 1;

		//如果随机位置恰好是蛇的位置，就重生成
		if (wall.getWall(foodX, foodY) == ' ')
		{
			wall.setWall(foodX, foodY, '#');
			gotoxy2(hOut2,foodY * 2, foodX);
			cout << "#";
			break;
		}
	}
	

}