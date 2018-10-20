#include"snake.h"
void  SetPos(int x, int y)
{
	COORD pos = { 0 };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x; pos.Y = y;
	SetConsoleCursorPosition(handle, pos);//�ѹ�궨λ��������Ҫ��λ����
}
void WelcomeToGame()//��ӭ���溯��
{
	//���ô��ڴ�С
	system("mode con cols=100 lines=30");
	SetPos(40, 13);//��װ�ĺ���������λ���
	printf("��ӭ����̰����С��Ϸ\n");
	SetPos(35, 25);
	system("pause");//��ͣ
	system("cls");//�����Ļ
	SetPos(30, 9);
	printf("�á��������������������ߵ��ƶ���F1Ϊ���٣�F2Ϊ����\n");
	SetPos(40, 11);
	printf("���ٻ�÷�������\n");
	SetPos(35, 25);
	system("pause");
	system("cls");
}

void CreateMap()
{
	int i = 0;
	//��
	for (i = 0; i <= 58; i += 2)
	{
		SetPos(i, 0);
		printf(WALL);
	}
	//��
	for (i = 0; i <= 58; i += 2)
	{
		SetPos(i, 27);
		printf(WALL);
	}
	//��
	for (i = 1; i <= 26; i++)
	{
		SetPos(0, i);
		printf(WALL);
	}
	//��
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
	pSnakeNode first = BuyNode();//������ͷ
	pSnakeNode cur = NULL;
	first->x = INIT_X;
	first->y = INIT_Y;
	int i = 0;
	for (i = 1; i <= 4; i++)
	{
		cur = BuyNode();//��������
		cur->x = first->x + 2;
		cur->y = first->y;
		cur->next = first;
		first = cur;
	}
	//��ӡ��
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
		pfood->x = rand() % 55 + 2;//0-54,+2����2-56
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
	//��ӡ��ӭ����
	WelcomeToGame();
	//������ͼ����ǽ
	CreateMap();
	//��ʼ����
	InitSnake(ps);
	//��ʼ��ʳ��
	CreateFood(ps);
	//��Ϸ����
	ps->_AddScore = 10;//ÿ�����ӵķ���
	ps->_TotalScore = 0;//�ܷ�
	ps->_Dir = RIGHT;//����
	ps->_SleepTime = 200;//0.2��
	ps->_Status = OK;//״̬
}

void pause()//��ͣ����
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

void EatFood(pSnake ps, pSnakeNode pn)//��ʳ��
{
	pSnakeNode cur = NULL;
	pn->next = ps->_psnake;//ͷ��
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

void NoFood(pSnake ps, pSnakeNode pn)//û��ʳ��
{
	pSnakeNode cur = NULL;
	pn->next = ps->_psnake;//ͷ��
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

void snakmove(pSnake ps)//�ߵ��ƶ�
{
	pSnakeNode pNextNode = BuyNode();
	SetPos(65, 8);
	printf("�ܷ�:%d", ps->_TotalScore);
	SetPos(65, 9);
	printf("ÿ��ʳ��ĵ÷֣�%d ", ps->_AddScore);
	//��
	switch (ps->_Dir)
	{
		case UP:
		{
			pNextNode->x = ps->_psnake->x;
			pNextNode->y = ps->_psnake->y - 1;
			if (NextHasFood(pNextNode,ps->_pFood))
			{
				//��һ���ڵ���ʳ��
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
		 	 //��һ���ڵ���ʳ��
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
				//��һ���ڵ���ʳ��
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
				 //��һ���ڵ���ʳ��
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
	printf("�á��������������������ߵ��ƶ�");//��λ��꣬��ӡҪ��ӡ�Ķ���
	SetPos(65, 12);
	printf("F1Ϊ���٣�F2Ϊ����\n");//ͨ������˯��ʱ����ʵ�ּ��ټ��٣�˯��ʱ��ӳ������ٷ�֮����
	SetPos(65, 13);
	printf("���ٻ�÷�������\n");
	SetPos(65, 14);
	printf("���ո���ͣ��Ϸ\n");

}

void GameEnd(pSnake ps)
{
	pSnakeNode cur = ps->_psnake;
	SetPos(25, 14);
	if (ps->_Status == NORMAL_END)
	{
		SetPos(70, 20);
		printf("��Ϸ�����ӽ���\n");
		SetPos(70, 21);
	}
	else if (ps->_Status == KILL_BY_SELF)
	{
		SetPos(70, 20);
		printf("��ײ���Լ���\n");
		SetPos(70, 21);
	}
	else if (ps->_Status == KILL_BY_WALL)
	{
		SetPos(70, 20);
		printf("ײ��ǽ��\n");
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
		//ȷ������
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
			//��ͣ��Ϸ
			pause();
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			//������Ϸ
			ps->_Status = NORMAL_END;
			break;
		}
		else if (GetAsyncKeyState(VK_F1))
		{
			//����
			if (ps->_SleepTime >= 40)
			{
				ps->_SleepTime -= 20;
				ps->_AddScore += 2;
			}
		}
		else if (GetAsyncKeyState(VK_F2))
		{
			//����
			if (ps->_SleepTime <= 300)
			{
				ps->_SleepTime += 20;
				ps->_AddScore -= 2;
			}
			if (ps->_SleepTime > 300)
			{
				ps->_AddScore = 1;//����һֱ��
			}
		}
		Sleep(ps->_SleepTime);//˯��
		//�ߵ��ƶ�
		snakmove(ps);
		KillBYWALL(ps);
		KillBySelf(ps);
	} while (ps->_Status == OK);
}