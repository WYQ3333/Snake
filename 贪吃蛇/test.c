#include"snake.h"

void test()
{
	srand((unsigned)time(NULL));
	Snake snake = { 0 };//����̰����
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