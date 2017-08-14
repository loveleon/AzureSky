//*****************************
//名称：Tetris
//简介：俄罗斯方块
//日期：2016年3月1日
//作者：江南
//*****************************

#include <vector>
#include <list>
#include <map>
#include <queue>

//块颜色
enum BlockColor
{
	//红色
	BC_RED,
	//绿色
	BC_GREEN,
	//蓝色
	BC_BLUE,
	//黄色
	BC_YELLOW,
};

//块状态
enum BlockState
{
	//默认
	BS_DEFAUT,
	//使用
	BS_USE,
};

//俄罗斯方块元素
enum UnitType
{
	//一字型
	UT_LINE,
	//田字形
	UT_QUAD,
	//鸭子型
	UT_DUCK,
	//手枪型
	UT_GUN,
};

//俄罗斯方块
struct TetrisBlock
{
	//行号
	int Row;
	//列号
	int Col;
	//颜色
	int Color;
	//状态
	int State;
};

//俄罗斯方块面板
class TetrisBoard
{
public:
	TetrisBoard();
	TetrisBoard(int r, int c);
	~TetrisBoard();

public:
	int getBlockState(int r, int c);
	void setBlockState(int r, int c, int s);

protected:
	//总行数
	int m_nRows;
	//总列数
	int m_nCols;
	std::vector<std::vector<TetrisBlock*>> m_vecBlocks;
};

//俄罗斯方块
class Tetris
{
public:
	Tetris();
	~Tetris();

public:
	//创建
	bool create();
	//更新
	void update(float t);

public:
	//清除行
	void clear();
	//结算
	void account();

protected:
	//面板
	TetrisBoard* m_pBoard;
	//元素队列
	std::queue<int> m_pUnits;
	//速度
	float m_fSpeed;
};
