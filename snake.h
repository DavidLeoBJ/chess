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

	//�ڵ�
	struct Point
	{
		//������
		int x;
		int y;

		//ָ����
		Point * next;
	};

	//��ʼ��
	void initSnake();//��ӽڵ㣬��֮ǰ����wall.set/get������һ��
	//���ٽڵ�
	void destroyPoint();
	//��ӽڵ�
	void addPoint(int x, int y);
	//ɾ���ڵ�
	void delPoint();//����Ҫ������ɾ�����һ���ڵ㣬�������ƶ�
	//�ƶ� ����ֵ�����Ƿ�ɹ�
	bool move(char key);

	//�趨�Ѷ�:ˢ��ʱ����ߵ���γ���
	//ˢ��ʱ��
	int getSleepTime();
	//�ߵ���γ���
	int countList();

	//�Ƿ�
	int getScore();

	Point * pHead;//ͷ�ڵ�
	Wall & wall;//��Ҫ����wall.h
	Food & food;
	bool isRool;//�ƶ�ʱͷ��β�����
};