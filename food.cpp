#include "food.h"
#include<Windows.h>


void gotoxy2(HANDLE hOut2, int x, int y)
{
	COORD pos;
	pos.X = x;		//������
	pos.Y = y;		//������
	SetConsoleCursorPosition(hOut2, pos);
}
HANDLE hOut2 = GetStdHandle(STD_OUTPUT_HANDLE);//������ʾ���������

Food::Food(Wall &tempWall) :wall(tempWall)
{

}

//����
void Food::setFood()
{
	while (true)
	{ 
		//����� 1-12X1-12
		foodX = rand() % (Wall::ROW - 2) + 1;//��Ҫ��food.h�а���wall.h
		foodY = rand() % (Wall::COL - 2) + 1;

		//������λ��ǡ�����ߵ�λ�ã���������
		if (wall.getWall(foodX, foodY) == ' ')
		{
			wall.setWall(foodX, foodY, '#');
			gotoxy2(hOut2,foodY * 2, foodX);
			cout << "#";
			break;
		}
	}
	

}