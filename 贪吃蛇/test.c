#include"snake.h"

void test()
{
	srand((unsigned)time(NULL));
	Snake snake = { 0 };//����̰����
	GameStart(&snake);//��Ϸ��ʼ
	GameRun(&snake);//��Ϸ����
	GameEnd(&snake);//��Ϸ����
}

int main()
{
	test();
	system("pause");
	return 0;
}