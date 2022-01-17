#ifndef _WALL_HEAD
#define _WALL_HEAD
#include<iostream>
using namespace std;

//防止头文件重复加载，与之前使用的方法不同，但作用是一样的。

class Wall
{
public:
	enum 
	{
		ROW=26,
		COL=26
	};
	
	
	//初始化墙壁
	void initWall();

	//画墙
	void drawWall();

	//墙应该还有更多的作用：
	//根据索引设置  二维数组里的内容
	void setWall(int x, int y, char c);
	//根据索引获取当前位置的符号
	char getWall(int x, int y);

private:
	char gameArray[ROW][COL];
};



#endif