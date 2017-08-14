#pragma once

#include <deque>

using namespace std;

//单元状态
enum SnakeCellState
{
	//无效的
	SCS_INVALID,
	//默认的
	SCS_DEFAULT,
	//食物
	SCS_FOOD,
	//躯干
	SCS_BODY,
};

//方向
enum SnakeDirection
{
	//无效的
	SD_INVALID,
	//上
	SD_UP,
	//下
	SD_DOWN,
	//左
	SD_LEFT,
	//右
	SD_RIGHT,
};

//单元格
struct SnakeCell
{
	//行号
	int Row;
	//列号
	int Col;
	//方向
	SnakeDirection Dir;
	//状态
	SnakeCellState State;
};

//贪食蛇
class Snake
{
public:
	Snake(int rows, int cols);
	~Snake();
public:
	//构造单元格
	void CreateGrid();
	//创建食物
	void CreateFood();
	//创建蛇身
	void CreateSnake();
	//游戏结束
	void GameOver();
	//更新
	bool Update(float deltaTime);
	//外部控制
	void Control(SnakeDirection dir);
public:
	//行数
	int m_nRows;
	//列数
	int m_nCols;
	//食物所在的行号
	int m_nFoodR;
	//食物所在的列号
	int m_nFoodC;
	//速度
	float m_fDeltaTime;
	//网格对象
	SnakeCell** m_Grid;
	//蛇集合
	deque<SnakeCell*> m_Snake;
};