#include"snake.h"

void test()
{
	srand((unsigned)time(NULL));
	Snake snake = { 0 };//´´½¨Ì°³ÔÉß
	GameStart(&snake);
	GameRun(&snake);
	GameEnd(&snake);
}

int main()
{
	test();
	system("pause");
	return 0;
}