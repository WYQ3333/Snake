#pragma once

#include<Windows.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define WALL "■"
#define FOOD "●"

#define INIT_X 20
#define INIT_Y 18
typedef struct SnakeNode
{
	int x;
	int y;
	struct SnakeNode *next;
}SnakeNode, *pSnakeNode;

//蛇的方向
enum Diretion
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//状态
enum GameState
{
	OK,
	NORMAL_END,
	KILL_BY_WALL,
	KILL_BY_SELF
};
//游戏结构体
typedef struct Snake
{
	pSnakeNode _psnake;//维护蛇身的指针
	pSnakeNode _pFood;//维护食物的位置
	int _TotalScore;//总分数
	int _AddScore;//增加的分数
	int _SleepTime;//休眠时间
	enum Direction  _Dir;
	enum GameStatus _Status;
}Snake, *pSnake;

void GameStart(pSnake ps);
void WelcomeToGame();//欢迎界面函数
void SetPos(int x, int y);
void CreateMap();//创建地图
void InitSnake(pSnake ps);
void CreateFood(pSnake ps);//创建食物
void GameRun(pSnake ps);//运行游戏
void pause();//暂停函数

void snakmove(pSnake ps);
int NextHasFood(pSnakeNode pn, pSnakeNode pf);//判断下个结点是否为食物
void EatFood(pSnake ps,pSnakeNode pn);//吃食物
void NoFood(pSnake ps, pSnakeNode pn);//没有食物
void KillBYWALL(pSnake ps);
void KillBySelf(pSnake ps);
void GameEnd(pSnake ps);