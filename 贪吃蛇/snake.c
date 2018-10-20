#include"snake.h"
void  SetPos(int x, int y)
{
	COORD pos = { 0 };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x; pos.Y = y;
	SetConsoleCursorPosition(handle, pos);//把光标定位到我们需要的位置了
}
void WelcomeToGame()//欢迎界面函数
{
	//设置窗口大小
	system("mode con cols=100 lines=30");
	SetPos(40, 13);//分装的函数用来定位光标
	printf("欢迎来到贪吃蛇小游戏\n");
	SetPos(35, 25);
	system("pause");//暂停
	system("cls");//清空屏幕
	SetPos(30, 9);
	printf("用↑，↓，←，→来控制蛇的移动，F1为加速，F2为减速\n");
	SetPos(40, 11);
	printf("加速获得分数更多\n");
	SetPos(35, 25);
	system("pause");
	system("cls");
}

void CreateMap()
{
	int i = 0;
	//上
	for (i = 0; i <= 58; i += 2)
	{
		SetPos(i, 0);
		printf(WALL);
	}
	//下
	for (i = 0; i <= 58; i += 2)
	{
		SetPos(i, 27);
		printf(WALL);
	}
	//左
	for (i = 1; i <= 26; i++)
	{
		SetPos(0, i);
		printf(WALL);
	}
	//右
	for (i = 1; i <= 26; i++)
	{
		SetPos(58, i);
		printf(WALL);
	}
}
pSnakeNode BuyNode()
{
	pSnakeNode pRet = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (pRet == NULL)
	{
		perror("BuyNode::malloc()");
		exit(EXIT_FAILURE);
	}
	pRet->x = 0;
	pRet->y = 0;
	pRet->next = NULL;
	return pRet;
}
void InitSnake(pSnake ps)
{
	pSnakeNode first = BuyNode();//创建蛇头
	pSnakeNode cur = NULL;
	first->x = INIT_X;
	first->y = INIT_Y;
	int i = 0;
	for (i = 1; i <= 4; i++)
	{
		cur = BuyNode();//创建蛇身
		cur->x = first->x + 2;
		cur->y = first->y;
		cur->next = first;
		first = cur;
	}
	//打印蛇
	while (cur)
	{
		SetPos(cur->x, cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	ps->_psnake = first;
}

void CreateFood(pSnake ps)
{
	pSnakeNode pfood = BuyNode();
	pSnakeNode cur = ps->_psnake;
	pfood->y = rand() % 26 + 1;
	do
	{
		pfood->x = rand() % 55 + 2;//0-54,+2产生2-56
	} while (pfood->x % 2 != 0);
	while (cur)
	{
		if (cur->x == pfood->x&&cur->y == pfood->y)
		{
			CreateFood(ps);
		}
		cur = cur->next;
	}
	ps->_pFood = pfood;
	SetPos(pfood->x, pfood->y);
	printf(FOOD);
}

void GameStart(pSnake ps)
{
	//打印欢迎界面
	WelcomeToGame();
	//创建地图，画墙
	CreateMap();
	//初始化蛇
	InitSnake(ps);
	//初始化食物
	CreateFood(ps);
	//游戏运行
	ps->_AddScore = 10;//每次增加的分数
	ps->_TotalScore = 0;//总分
	ps->_Dir = RIGHT;//方向
	ps->_SleepTime = 200;//0.2秒
	ps->_Status = OK;//状态
}

void pause()//暂停函数
{
	while (1)
	{
		Sleep(100);
		if (GetAsyncKeyState(VK_SPACE))
		{
			return;
		}
	}
}

int NextHasFood(pSnakeNode pn, pSnakeNode pf)
{
	return (pn->x == pf->x) && (pn->y == pf->y);
}

void EatFood(pSnake ps, pSnakeNode pn)//吃食物
{
	pSnakeNode cur = NULL;
	pn->next = ps->_psnake;//头插
	ps->_psnake = pn;
	cur = ps->_psnake;
	ps->_TotalScore += ps->_AddScore;
	while (cur)
	{
		SetPos(cur->x, cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	CreateFood(ps);
}

void NoFood(pSnake ps, pSnakeNode pn)//没有食物
{
	pSnakeNode cur = NULL;
	pn->next = ps->_psnake;//头插
	ps->_psnake = pn;
	cur = ps->_psnake;
	while (cur->next->next)
	{
		SetPos(cur->x, cur->y);
		printf(FOOD);
		cur = cur->next;
	}
	SetPos(cur->x, cur->y);
	printf(FOOD);
	SetPos(cur->next->x, cur->next->y);
	printf(" ");
	free(cur->next);
	cur->next = NULL;
}

void snakmove(pSnake ps)//蛇的移动
{
	pSnakeNode pNextNode = BuyNode();
	SetPos(65, 8);
	printf("总分:%d", ps->_TotalScore);
	SetPos(65, 9);
	printf("每个食物的得分：%d ", ps->_AddScore);
	//上
	switch (ps->_Dir)
	{
		case UP:
		{
			pNextNode->x = ps->_psnake->x;
			pNextNode->y = ps->_psnake->y - 1;
			if (NextHasFood(pNextNode,ps->_pFood))
			{
				//下一个节点是食物
				EatFood(ps,pNextNode);
			}
			else
			{
				NoFood(ps,pNextNode);
			}
			break;
		}
		case DOWN:
		{
			pNextNode->x = ps->_psnake->x;
			pNextNode->y = ps->_psnake->y + 1;
			if (NextHasFood(pNextNode, ps->_pFood))
			{
		 	 //下一个节点是食物
     			 EatFood(ps, pNextNode);
	     	 }
			else
			{
		     	 NoFood(ps, pNextNode);
			}
			break;
		}
		case LEFT:
		{
			pNextNode->x = ps->_psnake->x-2;
			pNextNode->y = ps->_psnake->y;
			if (NextHasFood(pNextNode, ps->_pFood))
			{
				//下一个节点是食物
				EatFood(ps, pNextNode);
			}
			else
			{
				NoFood(ps, pNextNode);
			}
			break;
		}
		case RIGHT:
		{
			pNextNode->x = ps->_psnake->x+2;
			pNextNode->y = ps->_psnake->y ;
			if (NextHasFood(pNextNode, ps->_pFood))
			{
				 //下一个节点是食物
				EatFood(ps, pNextNode);
			}
			else
			{
				NoFood(ps, pNextNode);
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

void KillBYWALL(pSnake ps)
{
	if ((ps->_psnake->x == 0) ||
		(ps->_psnake->x == 58) || 
		(ps->_psnake->y == 0) ||
		(ps->_psnake->y == 27))
	{
		ps->_Status = KILL_BY_WALL;
	}
}

void KillBySelf(pSnake ps)
{
	pSnakeNode tnext = ps->_psnake->next;
	while (tnext)
	{
		if ((tnext->x == ps->_psnake->x) && (tnext->y == ps->_psnake->y))
		{
			ps->_Status = KILL_BY_SELF;
			return;
		}
		tnext = tnext->next;
	}

}
void PrintHelpInfo()
{
	SetPos(65, 11);
	printf("用↑，↓，←，→来控制蛇的移动");//定位光标，打印要打印的东西
	SetPos(65, 12);
	printf("F1为加速，F2为减速\n");//通过控制睡眠时间来实现加速减速，睡眠时间加长，减速反之加速
	SetPos(65, 13);
	printf("加速获得分数更多\n");
	SetPos(65, 14);
	printf("按空格暂停游戏\n");

}

void GameEnd(pSnake ps)
{
	pSnakeNode cur = ps->_psnake;
	SetPos(25, 14);
	if (ps->_Status == NORMAL_END)
	{
		SetPos(70, 20);
		printf("游戏正常接结束\n");
		SetPos(70, 21);
	}
	else if (ps->_Status == KILL_BY_SELF)
	{
		SetPos(70, 20);
		printf("蛇撞到自己了\n");
		SetPos(70, 21);
	}
	else if (ps->_Status == KILL_BY_WALL)
	{
		SetPos(70, 20);
		printf("撞到墙了\n");
		SetPos(70, 21);
	}
	while (cur)
	{
		pSnakeNode del = cur;
		cur = cur->next;
		free(del);
		del = NULL;
	}
	ps->_psnake = NULL;
	free(ps->_pFood);
	ps->_pFood = NULL;
}

void GameRun(pSnake ps)
{
	PrintHelpInfo();
	do
	{
		//确定方向
		if (GetAsyncKeyState(VK_UP)&&(ps->_Dir!=DOWN))
		{
			ps->_Dir = UP;
		}
		else if (GetAsyncKeyState(VK_DOWN) && ps->_Dir != UP)
		{
			ps->_Dir = DOWN;
		}
		else if (GetAsyncKeyState(VK_LEFT) && ps->_Dir != RIGHT)
		{
			ps->_Dir = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && ps->_Dir != LEFT)
		{
			ps->_Dir = RIGHT;
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			//暂停游戏
			pause();
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			//结束游戏
			ps->_Status = NORMAL_END;
			break;
		}
		else if (GetAsyncKeyState(VK_F1))
		{
			//加速
			if (ps->_SleepTime >= 40)
			{
				ps->_SleepTime -= 20;
				ps->_AddScore += 2;
			}
		}
		else if (GetAsyncKeyState(VK_F2))
		{
			//减速
			if (ps->_SleepTime <= 300)
			{
				ps->_SleepTime += 20;
				ps->_AddScore -= 2;
			}
			if (ps->_SleepTime > 300)
			{
				ps->_AddScore = 1;//不能一直减
			}
		}
		Sleep(ps->_SleepTime);//睡眠
		//蛇的移动
		snakmove(ps);
		KillBYWALL(ps);
		KillBySelf(ps);
	} while (ps->_Status == OK);
}