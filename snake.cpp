#include "snake.h"
#include<Windows.h>


void gotoxy1(HANDLE hOut1, int x, int y)
{
	COORD pos;
	pos.X = x;		//横坐标
	pos.Y = y;		//纵坐标
	SetConsoleCursorPosition(hOut1, pos);
}
HANDLE hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量



//构造函数
Snake::Snake(Wall & tempWall, Food & tempFood) :wall(tempWall), food(tempFood)
{
	pHead = NULL;
}

//初始化
void Snake::initSnake() //添加节点，即之前测试wall.set/get方法那一套
{
	destroyPoint();
	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);
}
//销毁节点
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
	//创建新节点
	Point * newPoint = new Point;
	newPoint->x = x;
	newPoint->y = y;
	//如果原来头不为空改为身子
	if (pHead != NULL)
	{
		wall.setWall(pHead->x,pHead->y,'=');
		gotoxy1(hOut1, pHead->y * 2, pHead->x);
		cout << "=";
	}
	newPoint->next = pHead;//指原来的（没更新的）头
	pHead = newPoint;//更新头部
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy1(hOut1, pHead->y * 2, pHead->x);
	cout << "@";
}

//删除节点 实现蛇的移动效果
void Snake::delPoint()
{
	//删除只删尾节点，怎么找到尾节点：从头节点开始，一直next，直到next为空，则当前节点就是尾节点
	//具体做法：1，找到尾节点，2，删尾节点，3，把上个节点点变成尾节点（上一个节点的next变成空就是尾节点特征）
	//两个节点以上，才去做删除操作
	if (pHead == NULL || pHead->next==NULL)
	{
		return;//pHead == NULL没有节点；pHead->next==NULL只有一个节点
	}
	Point * pCur = pHead->next;
	Point * pPre = pHead;
	while (pCur->next !=NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	//删除尾节点
	wall.setWall(pCur->x, pCur->y, ' ');
	gotoxy1(hOut1, pCur->y * 2, pCur->x);
	cout << " ";

	delete pCur;
	pCur = NULL;
	pPre->next = NULL;
}

//移动
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

	//判断：如果下次移动碰到的是尾巴不应该算失败，因为是动态移动的，等对到了尾就走开了。
	//下面这段代码是从删除节点中复制来的，它的作用是找到尾巴pCur的坐标信息
	Point * pCur = pHead->next;
	Point * pPre = pHead;
	while (pCur->next != NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	//如果pCur->x==x && pCur->y==y就是碰到尾巴的情况，为了便于维护，再给snake.h中增加一个bool isRool;//移动时头碰尾的情况,
	//并在其构造初始化时赋值false,就在这里进行判断，如果是头碰尾则赋值为true
	//否则，将原来的gameover判断写在否则里面
	if (pCur->x==x && pCur->y==y)
	{
		isRool = true;
	}
	else
	{
		//判断用户要走的这一步是否可以允许
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
		{
			//这里还有一个bug：当蛇靠近墙时就死了这不对，应该还能再走一步才死，所以增加以下三行：
			addPoint(x, y);
			delPoint();//如果觉得死的时候是吃了墙而增长了身体则注释此句，相反觉得不应该长身体则保留此句
			system("cls");
			wall.drawWall();
			cout << "Score:" << getScore() << endl;

			cout << "GAME OVER!!!" << endl;
			return false;
		}
	}
	
	
	//移动成功有两种情况：吃到食物和未吃到食物
	if (wall.getWall(x, y) == '#')
	{
		addPoint(x, y);//蛇吃到食物要长大
		//重新设置食物，需要使用食物方法，所以要拿到食物方法与拿到墙是一样的：在snake.h中维护一个Food & food(包含头文件),构造函数中再加一个Food &food参数把它传进来。
		food.setFood();
	}
	else
	{
		
		addPoint(x,y);
		delPoint();
		//bug:在连续头碰尾的情况下发生时，蛇头被隐藏
		if (isRool == true)
		{
			wall.setWall(x, y, '@');
			gotoxy1(hOut1, y * 2, x);
			cout << "@";
		}
	}
	return true;
}

//刷屏时间 根据蛇身段长度，蛇身段长度越长说明玩家玩得经验越丰富，难度就越大，则刷屏越快。
//写了这个方法在哪里使用它？game中移动蛇时刷屏时需要给刷屏时间参数，就把它作为参数给Sleep()
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
//蛇的身段长度
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

//记分
int Snake::getScore()
{
	int size = countList();
	int score = (size - 3) * 100;//初始化时有3个身段，所以要-3。不可能让玩家一上来就300分。
	return score;
}