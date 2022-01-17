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
需求
游戏元素
墙壁、蛇、食物、蛇的活动区域和右侧提示区
墙壁：*表示，*包围的范围是蛇可以活动的区域，但不能碰墙，否则gameover
蛇：有蛇头，蛇般，蛇头用@表示，蛇向用=球，当蛇吃到食物时，蛇身+1，贪吃蛇可以通过不断吃食物来增加自己的身体。
食物：#表示 ，蛇碰到食物会将食物吃掉
可移动区域：空格表示 代表蛇可以移动的区域
提示信息：右侧展示，可以显示当前贪吃蛇的版本号，制件人，游戏于法等提示信息

游戏规则：
当运行时，游戏画面是静止不动的，可以默认蛇头朝右，游戏中设置了wsad4个按键分别代表上下左右，也是用户比较常用的方向按键，当用户
输入w或者s或者d时激活游戏，注意输入a不可以激活，因为蛇不可180度转弯，因此蛇的移动方向只可以一直向前或者90度旋转。
当蛇吃掉食物时，此时蛇会增加一个身段，另外食物需要重新随机地设置到屏幕上。
游戏结束方式有二：一、蛇碰到墙壁视为死亡，二、蛇头碰到蛇身子，把自己吃掉也视为死亡。
辅助设计方法：使用电子表格excell模拟

代码分析
程序入口：Game.cpp
负责用户输入，调度其他模块来发挥一个总指挥的作用
其次，从是简单的模块入手：墙，其内部只要能维护一个二维数组即可，
然后，是蛇模块，负责管理蛇的行为
最后，食物模块
总结：游戏分为：程序入口、墙、蛇、食物四个模块

墙模块：wall.cpp,wall.h
	二维数组：gameArray[][]具体进行数和列数可以定义出一个枚举，游戏中设置为26X26，enum[ROW = 26][COL = 26];
	主要接口是 初始化墙initwall,打印墙，也就是将二维数组中的内容打印到控制台中，draw方法。还要提供出一个可以修改二维数组
	元素的方法以及根据索引获取二维数组元素的方法：getwall,setwall;
*/

/*
增加：
1，难度设定
	刷屏时间间隔与难有关，如：100，200，300ms，
	根据蛇长的长度来确定刷屏时间间隔，蛇越长说明玩家玩得越多，就应该加大难度。
	可以写入蛇模块中
	根据这个要求我们可以在蛇模块中增加新API:countList获取蛇长方法和getsleepTime获取刷屏时间间隔
2，玩家得分统计
	得分和蛇长度有关，蛇身段*100
	蛇模块中增加一个方法：getScore()
	cout << "Score:" << snake.getScore() << endl;这条语句分别在以下三处调用：
	1、在game模块中正常移动代码块中，画完墙后。这是正常的移动刷屏
	2、在snake模块中死亡时
	3、在刚进入程序时
3，、记录、排名
*/

/*
优化：
刷屏很令人讨厌！使用的方法是把游标移动一下就可以了，不用全部刷屏，代码在网上很容易找不用记它。
叫“光标定位”
把它写在game模块中main函数外面
注意：这段代码需要<Windows.h>头文件
这段在main中画墙后测试，测试时注意二维数组的坐标系与电脑屏幕坐标系的x，y相反。
在main中把所有对外输出包括打印分数，都先gotoxy()再打印。

snake.cpp:把这段
代码复制到snake.cpp模块中（全局的，不要放在类中),注意snake.cpp需要引入<Windows.h>
正因是全局的，需要将gotoxy,hOut，改名为gotoxy1,hOut1。否则冲突了。
然后在所有wall.setWall(pHead->x,pHead->y,'X'),其中X指的是打印各种符号的语句，下面插入：
gotoxy1(hOut1,pHead->y*2,pHead->x);

food.xpp同上


技术细节：
采用光标移动直接向屏幕写，那么setWall方法还有用吗？它内部维护二维数组，如果有游戏需要保存数据则有用。

此外，snake中的Point的结构体，使用的是struct制作，也可以使用list<pair<int,int>> 1Snake; 
判断尾节点：
while(1Snake.empty() != true)
{
	//将其中的字符设为‘  ’：
	pair<int,in> p = 1Snake.front();
	1Snake.pop_front();
}

新增节点，push_back,push_fron
删除节点：pop_back();//太方便了，要比目前这方案节省很多代码。

*/

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;		//横坐标
	pos.Y = y;		//纵坐标
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量


int main(){
	srand( (unsigned int)time(NULL) );

	//死亡标识
	bool isDead = false;//默认为false，然后把用户输入循环条件改为:!isDead

	Wall wall;
	wall.initWall();//这时还看不到wall，需要一个显示wall的方法
	wall.drawWall();//画墙
	//食物要在蛇前,因在开发过程中将蛇构造函数增加了food参数
	Food food(wall);
	food.setFood();

	Snake snake(wall,food);
	snake.initSnake();


	//测试删除节点功能
	//snake.delPoint();

	//测试蛇移动,应该蛇头向左，蛇身上下折叠，如果是这样就说明这个模块已经成功。
	/*snake.move('w');
	snake.move('w');
	snake.move('a');*/

	//wall.drawWall();//画墙
	gotoxy(hOut, 0, Wall::ROW);//把刷屏改为移动光标直接写了。注意：这时一定要把前面draw移到最前面的initWall之后，否则屏幕是乱的。
	cout << "Score:" << snake.getScore() << endl;
	

	//下一步：接受用户输入操作
	char preKey = NULL;//变量保存上一次按键 解决游戏一开始按一左就死掉的bug
	while (!isDead)
	{
		char key = _getch();//#include <conio.h>

		//解决游戏一开始按一左就死掉的bug		
		if ((preKey == NULL) && (key == snake.LEFT))
		{
			continue;
		}

		do
		{
			//限制只接受这四个按键，其他按键按最后一次有效按键计
			if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT)
			{
				//判断是否与上次按键冲突
				if ( (key == snake.LEFT &&preKey == snake.RIGHT) ||
					(key == snake.RIGHT &&preKey == snake.LEFT) ||
					(key == snake.UP &&preKey == snake.DOWN) ||
					(key == snake.DOWN &&preKey == snake.UP))
				{
					key = preKey;
				}
				else
				{ 
					preKey = key;//不是冲突的才可以更新按键
				}

				//判断移动是否是成功的
				if (snake.move(key))
				{
					//移动成功  改成移动光标不刷屏了，所以以下两句不要了，但要增加gotoxy();
					//system("cls");//清屏
					//wall.drawWall();
					gotoxy(hOut,0,Wall::ROW);
					cout << "Score:" << snake.getScore() << endl;
					//这里一开始创建和测试时都是直接填写300或100的数值，最后阶段增强功能令其自动根据玩的情况调整刷屏时间也就是难度
					Sleep(snake.getSleepTime());//首字母大写！！！ 需要<windows.h>
				}
				else
				{
					isDead = true;
					break;
				}
			}
			else
			{
				key = preKey;//强制令无效按键按上次有效按键计
			}
		} while (!_kbhit());//当没键盘输入时返回0，作用：当没有键盘输入时按之前输入的再执行，就当作你在连续按一个方向操控，直到有新的不同的方向输入 	
	}
	


	//测试getWall,setWall  OK
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