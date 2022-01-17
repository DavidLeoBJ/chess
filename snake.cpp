#include "snake.h"
#include<Windows.h>


void gotoxy1(HANDLE hOut1, int x, int y)
{
	COORD pos;
	pos.X = x;		//������
	pos.Y = y;		//������
	SetConsoleCursorPosition(hOut1, pos);
}
HANDLE hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);//������ʾ���������



//���캯��
Snake::Snake(Wall & tempWall, Food & tempFood) :wall(tempWall), food(tempFood)
{
	pHead = NULL;
}

//��ʼ��
void Snake::initSnake() //��ӽڵ㣬��֮ǰ����wall.set/get������һ��
{
	destroyPoint();
	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);
}
//���ٽڵ�
void Snake::destroyPoint()
{
	Point * pCur = pHead;
	while (pHead != NULL)
	{
		pCur = pHead->next;
		delete pHead;
		pHead = pCur;
	}
}

void Snake::addPoint(int x, int y)
{
	//�����½ڵ�
	Point * newPoint = new Point;
	newPoint->x = x;
	newPoint->y = y;
	//���ԭ��ͷ��Ϊ�ո�Ϊ����
	if (pHead != NULL)
	{
		wall.setWall(pHead->x,pHead->y,'=');
		gotoxy1(hOut1, pHead->y * 2, pHead->x);
		cout << "=";
	}
	newPoint->next = pHead;//ָԭ���ģ�û���µģ�ͷ
	pHead = newPoint;//����ͷ��
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy1(hOut1, pHead->y * 2, pHead->x);
	cout << "@";
}

//ɾ���ڵ� ʵ���ߵ��ƶ�Ч��
void Snake::delPoint()
{
	//ɾ��ֻɾβ�ڵ㣬��ô�ҵ�β�ڵ㣺��ͷ�ڵ㿪ʼ��һֱnext��ֱ��nextΪ�գ���ǰ�ڵ����β�ڵ�
	//����������1���ҵ�β�ڵ㣬2��ɾβ�ڵ㣬3�����ϸ��ڵ����β�ڵ㣨��һ���ڵ��next��ɿվ���β�ڵ�������
	//�����ڵ����ϣ���ȥ��ɾ������
	if (pHead == NULL || pHead->next==NULL)
	{
		return;//pHead == NULLû�нڵ㣻pHead->next==NULLֻ��һ���ڵ�
	}
	Point * pCur = pHead->next;
	Point * pPre = pHead;
	while (pCur->next !=NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	//ɾ��β�ڵ�
	wall.setWall(pCur->x, pCur->y, ' ');
	gotoxy1(hOut1, pCur->y * 2, pCur->x);
	cout << " ";

	delete pCur;
	pCur = NULL;
	pPre->next = NULL;
}

//�ƶ�
bool Snake::move(char key)
{
	int x = pHead->x;
	int y = pHead->y;

	switch (key)
	{
	case UP:
		x--;
		break; 
	case DOWN:
			x++;
			break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	default:
		break;
	}

	//�жϣ�����´��ƶ���������β�Ͳ�Ӧ����ʧ�ܣ���Ϊ�Ƕ�̬�ƶ��ģ��ȶԵ���β���߿��ˡ�
	//������δ����Ǵ�ɾ���ڵ��и������ģ������������ҵ�β��pCur��������Ϣ
	Point * pCur = pHead->next;
	Point * pPre = pHead;
	while (pCur->next != NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	//���pCur->x==x && pCur->y==y��������β�͵������Ϊ�˱���ά�����ٸ�snake.h������һ��bool isRool;//�ƶ�ʱͷ��β�����,
	//�����乹���ʼ��ʱ��ֵfalse,������������жϣ������ͷ��β��ֵΪtrue
	//���򣬽�ԭ����gameover�ж�д�ڷ�������
	if (pCur->x==x && pCur->y==y)
	{
		isRool = true;
	}
	else
	{
		//�ж��û�Ҫ�ߵ���һ���Ƿ��������
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
		{
			//���ﻹ��һ��bug�����߿���ǽʱ�������ⲻ�ԣ�Ӧ�û�������һ�����������������������У�
			addPoint(x, y);
			delPoint();//�����������ʱ���ǳ���ǽ��������������ע�ʹ˾䣬�෴���ò�Ӧ�ó����������˾�
			system("cls");
			wall.drawWall();
			cout << "Score:" << getScore() << endl;

			cout << "GAME OVER!!!" << endl;
			return false;
		}
	}
	
	
	//�ƶ��ɹ�������������Ե�ʳ���δ�Ե�ʳ��
	if (wall.getWall(x, y) == '#')
	{
		addPoint(x, y);//�߳Ե�ʳ��Ҫ����
		//��������ʳ���Ҫʹ��ʳ�﷽��������Ҫ�õ�ʳ�﷽�����õ�ǽ��һ���ģ���snake.h��ά��һ��Food & food(����ͷ�ļ�),���캯�����ټ�һ��Food &food����������������
		food.setFood();
	}
	else
	{
		
		addPoint(x,y);
		delPoint();
		//bug:������ͷ��β������·���ʱ����ͷ������
		if (isRool == true)
		{
			wall.setWall(x, y, '@');
			gotoxy1(hOut1, y * 2, x);
			cout << "@";
		}
	}
	return true;
}

//ˢ��ʱ�� ��������γ��ȣ�����γ���Խ��˵�������þ���Խ�ḻ���ѶȾ�Խ����ˢ��Խ�졣
//д���������������ʹ������game���ƶ���ʱˢ��ʱ��Ҫ��ˢ��ʱ��������Ͱ�����Ϊ������Sleep()
int Snake:: getSleepTime()
{
	int sleepTime = 0;
	int size = countList();
	if (size<5)
	{
		sleepTime = 300;
	}
	else if (size >= 5 && size <= 8)
	{
		sleepTime = 250;
	}
	else if(size > 8 && size <= 20)
	{
		sleepTime = 200;
	}
	else if(size > 20 && size <= 50)
	{
		sleepTime = 150;
	}
	else
	{
		sleepTime = 100;
	}
	return sleepTime;
}
//�ߵ���γ���
int Snake:: countList()
{
	int size = 0;
	Point * curPoint = pHead;
	while (curPoint != NULL)
	{
		size++;
		curPoint = curPoint->next;
	}
	return size;
}

//�Ƿ�
int Snake::getScore()
{
	int size = countList();
	int score = (size - 3) * 100;//��ʼ��ʱ��3����Σ�����Ҫ-3�������������һ������300�֡�
	return score;
}