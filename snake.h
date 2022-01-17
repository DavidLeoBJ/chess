#pragma once
#include <iostream>
#include "wall.h"
#include "food.h"
using namespace std;

class Snake
{
public:
	Snake(Wall & tempWall, Food &food);

	enum {UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd'};

	//节点
	struct Point
	{
		//数据域
		int x;
		int y;

		//指针域
		Point * next;
	};

	//初始化
	void initSnake();//添加节点，即之前测试wall.set/get方法那一套
	//销毁节点
	void destroyPoint();
	//添加节点
	void addPoint(int x, int y);
	//删除节点
	void delPoint();//不需要参数，删除最后一个节点，用于蛇移动
	//移动 返回值代表是否成功
	bool move(char key);

	//设定难度:刷屏时间和蛇的身段长度
	//刷屏时间
	int getSleepTime();
	//蛇的身段长度
	int countList();

	//记分
	int getScore();

	Point * pHead;//头节点
	Wall & wall;//需要包含wall.h
	Food & food;
	bool isRool;//移动时头碰尾的情况
};