#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
#include "wall.h"
#include "snake.h"
#include "food.h"
#include <ctime>
#include <Windows.h>
#include <conio.h>

/*
����
��ϷԪ��
ǽ�ڡ��ߡ�ʳ��ߵĻ������Ҳ���ʾ��
ǽ�ڣ�*��ʾ��*��Χ�ķ�Χ���߿��Ի�����򣬵�������ǽ������gameover
�ߣ�����ͷ���߰㣬��ͷ��@��ʾ��������=�򣬵��߳Ե�ʳ��ʱ������+1��̰���߿���ͨ�����ϳ�ʳ���������Լ������塣
ʳ�#��ʾ ��������ʳ��Ὣʳ��Ե�
���ƶ����򣺿ո��ʾ �����߿����ƶ�������
��ʾ��Ϣ���Ҳ�չʾ��������ʾ��ǰ̰���ߵİ汾�ţ��Ƽ��ˣ���Ϸ�ڷ�����ʾ��Ϣ

��Ϸ����
������ʱ����Ϸ�����Ǿ�ֹ�����ģ�����Ĭ����ͷ���ң���Ϸ��������wsad4�������ֱ�����������ң�Ҳ���û��Ƚϳ��õķ��򰴼������û�
����w����s����dʱ������Ϸ��ע������a�����Լ����Ϊ�߲���180��ת�䣬����ߵ��ƶ�����ֻ����һֱ��ǰ����90����ת��
���߳Ե�ʳ��ʱ����ʱ�߻�����һ����Σ�����ʳ����Ҫ������������õ���Ļ�ϡ�
��Ϸ������ʽ�ж���һ��������ǽ����Ϊ������������ͷ���������ӣ����Լ��Ե�Ҳ��Ϊ������
������Ʒ�����ʹ�õ��ӱ��excellģ��

�������
������ڣ�Game.cpp
�����û����룬��������ģ��������һ����ָ�ӵ�����
��Σ����Ǽ򵥵�ģ�����֣�ǽ�����ڲ�ֻҪ��ά��һ����ά���鼴�ɣ�
Ȼ������ģ�飬��������ߵ���Ϊ
���ʳ��ģ��
�ܽ᣺��Ϸ��Ϊ��������ڡ�ǽ���ߡ�ʳ���ĸ�ģ��

ǽģ�飺wall.cpp,wall.h
	��ά���飺gameArray[][]������������������Զ����һ��ö�٣���Ϸ������Ϊ26X26��enum[ROW = 26][COL = 26];
	��Ҫ�ӿ��� ��ʼ��ǽinitwall,��ӡǽ��Ҳ���ǽ���ά�����е����ݴ�ӡ������̨�У�draw��������Ҫ�ṩ��һ�������޸Ķ�ά����
	Ԫ�صķ����Լ�����������ȡ��ά����Ԫ�صķ�����getwall,setwall;
*/

/*
���ӣ�
1���Ѷ��趨
	ˢ��ʱ���������йأ��磺100��200��300ms��
	�����߳��ĳ�����ȷ��ˢ��ʱ��������Խ��˵��������Խ�࣬��Ӧ�üӴ��Ѷȡ�
	����д����ģ����
	�������Ҫ�����ǿ�������ģ����������API:countList��ȡ�߳�������getsleepTime��ȡˢ��ʱ����
2����ҵ÷�ͳ��
	�÷ֺ��߳����йأ������*100
	��ģ��������һ��������getScore()
	cout << "Score:" << snake.getScore() << endl;�������ֱ��������������ã�
	1����gameģ���������ƶ�������У�����ǽ�������������ƶ�ˢ��
	2����snakeģ��������ʱ
	3���ڸս������ʱ
3������¼������
*/

/*
�Ż���
ˢ�����������ᣡʹ�õķ����ǰ��α��ƶ�һ�¾Ϳ����ˣ�����ȫ��ˢ�������������Ϻ������Ҳ��ü�����
�С���궨λ��
����д��gameģ����main��������
ע�⣺��δ�����Ҫ<Windows.h>ͷ�ļ�
�����main�л�ǽ����ԣ�����ʱע���ά���������ϵ�������Ļ����ϵ��x��y�෴��
��main�а����ж������������ӡ����������gotoxy()�ٴ�ӡ��

snake.cpp:�����
���븴�Ƶ�snake.cppģ���У�ȫ�ֵģ���Ҫ��������),ע��snake.cpp��Ҫ����<Windows.h>
������ȫ�ֵģ���Ҫ��gotoxy,hOut������Ϊgotoxy1,hOut1�������ͻ�ˡ�
Ȼ��������wall.setWall(pHead->x,pHead->y,'X'),����Xָ���Ǵ�ӡ���ַ��ŵ���䣬������룺
gotoxy1(hOut1,pHead->y*2,pHead->x);

food.xppͬ��


����ϸ�ڣ�
���ù���ƶ�ֱ������Ļд����ôsetWall���������������ڲ�ά����ά���飬�������Ϸ��Ҫ�������������á�

���⣬snake�е�Point�Ľṹ�壬ʹ�õ���struct������Ҳ����ʹ��list<pair<int,int>> 1Snake; 
�ж�β�ڵ㣺
while(1Snake.empty() != true)
{
	//�����е��ַ���Ϊ��  ����
	pair<int,in> p = 1Snake.front();
	1Snake.pop_front();
}

�����ڵ㣬push_back,push_fron
ɾ���ڵ㣺pop_back();//̫�����ˣ�Ҫ��Ŀǰ�ⷽ����ʡ�ܶ���롣

*/

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;		//������
	pos.Y = y;		//������
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//������ʾ���������


int main(){
	srand( (unsigned int)time(NULL) );

	//������ʶ
	bool isDead = false;//Ĭ��Ϊfalse��Ȼ����û�����ѭ��������Ϊ:!isDead

	Wall wall;
	wall.initWall();//��ʱ��������wall����Ҫһ����ʾwall�ķ���
	wall.drawWall();//��ǽ
	//ʳ��Ҫ����ǰ,���ڿ��������н��߹��캯��������food����
	Food food(wall);
	food.setFood();

	Snake snake(wall,food);
	snake.initSnake();


	//����ɾ���ڵ㹦��
	//snake.delPoint();

	//�������ƶ�,Ӧ����ͷ�������������۵��������������˵�����ģ���Ѿ��ɹ���
	/*snake.move('w');
	snake.move('w');
	snake.move('a');*/

	//wall.drawWall();//��ǽ
	gotoxy(hOut, 0, Wall::ROW);//��ˢ����Ϊ�ƶ����ֱ��д�ˡ�ע�⣺��ʱһ��Ҫ��ǰ��draw�Ƶ���ǰ���initWall֮�󣬷�����Ļ���ҵġ�
	cout << "Score:" << snake.getScore() << endl;
	

	//��һ���������û��������
	char preKey = NULL;//����������һ�ΰ��� �����Ϸһ��ʼ��һ���������bug
	while (!isDead)
	{
		char key = _getch();//#include <conio.h>

		//�����Ϸһ��ʼ��һ���������bug		
		if ((preKey == NULL) && (key == snake.LEFT))
		{
			continue;
		}

		do
		{
			//����ֻ�������ĸ��������������������һ����Ч������
			if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT)
			{
				//�ж��Ƿ����ϴΰ�����ͻ
				if ( (key == snake.LEFT &&preKey == snake.RIGHT) ||
					(key == snake.RIGHT &&preKey == snake.LEFT) ||
					(key == snake.UP &&preKey == snake.DOWN) ||
					(key == snake.DOWN &&preKey == snake.UP))
				{
					key = preKey;
				}
				else
				{ 
					preKey = key;//���ǳ�ͻ�Ĳſ��Ը��°���
				}

				//�ж��ƶ��Ƿ��ǳɹ���
				if (snake.move(key))
				{
					//�ƶ��ɹ�  �ĳ��ƶ���겻ˢ���ˣ������������䲻Ҫ�ˣ���Ҫ����gotoxy();
					//system("cls");//����
					//wall.drawWall();
					gotoxy(hOut,0,Wall::ROW);
					cout << "Score:" << snake.getScore() << endl;
					//����һ��ʼ�����Ͳ���ʱ����ֱ����д300��100����ֵ�����׶���ǿ���������Զ���������������ˢ��ʱ��Ҳ�����Ѷ�
					Sleep(snake.getSleepTime());//����ĸ��д������ ��Ҫ<windows.h>
				}
				else
				{
					isDead = true;
					break;
				}
			}
			else
			{
				key = preKey;//ǿ������Ч�������ϴ���Ч������
			}
		} while (!_kbhit());//��û��������ʱ����0�����ã���û�м�������ʱ��֮ǰ�������ִ�У��͵�������������һ������ٿأ�ֱ�����µĲ�ͬ�ķ������� 	
	}
	


	//����getWall,setWall  OK
	/*wall.setWall(5, 4, '=');
	wall.setWall(5, 5, '=');
	wall.setWall(5, 6, '@');
	wall.drawWall();
	cout << wall.getWall(0, 0) << endl;
	cout << wall.getWall(5, 4) << endl;
	cout << wall.getWall(5, 6) << endl;
	cout << wall.getWall(1, 1) << endl;*/

	system("pause");
	return EXIT_SUCCESS;
}