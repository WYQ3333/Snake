#include"snake.h"

void test()
{
	srand((unsigned)time(NULL));
	Snake snake = { 0 };//创建贪吃蛇
	GameStart(&snake);//游戏开始
	GameRun(&snake);//游戏运行
	GameEnd(&snake);//游戏结束
}

int main()
{
	test();
	system("pause");
	return 0;
}