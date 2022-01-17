#include "wall.h"

/*
��ά��������ϵ(x,y)��
��0��0�� (0,1)  (0,2)  (0,3)  (0,4)  (0,5)  (0,6)...
��1��0��
��2��0��
��3��0��
��4��0��
��5��0��
��6��0��...                                 (6,6)
...

�����������ȫ��ͬ�ģ�������Ļ���Ͻ�����x�������ӣ�����Y�������ӣ�������һ��Ҫע��
*/

//��ʼ��ǽ��
void Wall::initWall()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			//��ǽ��i==0 or j==0 or i==ROW-1 OR j==COL-1
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

//��ǽ
void Wall::drawWall()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cout << gameArray[i][j] << " ";//�������һ���ո���ʾ���ÿ�һ�㣬����̫���������������ı��������ݡ�			
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
//���Ǳ���Ϸ���������ƣ������Ƽ��ߴ�26X26��ʾ������һ�����⣬����̨����̫С����ȫ����ʾ�������а취������̨��
//�޸����԰Ѵ��ڸ߶���Ϊ30���Ժ��ٴ򿪿���̨��Ĭ�ϸ߶�Ҳ���Ϊ30.

//������������  ��ά�����������
void Wall::setWall(int x, int y, char c)
{
	gameArray[x][y] = c;
}
//����������ȡ��ǰλ�õķ���
char Wall::getWall(int x, int y)
{
	return gameArray[x][y];
}