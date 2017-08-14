//*****************************
//���ƣ�Tetris
//��飺����˹����
//���ڣ�2016��3��1��
//���ߣ�����
//*****************************

#include <vector>
#include <list>
#include <map>
#include <queue>

//����ɫ
enum BlockColor
{
	//��ɫ
	BC_RED,
	//��ɫ
	BC_GREEN,
	//��ɫ
	BC_BLUE,
	//��ɫ
	BC_YELLOW,
};

//��״̬
enum BlockState
{
	//Ĭ��
	BS_DEFAUT,
	//ʹ��
	BS_USE,
};

//����˹����Ԫ��
enum UnitType
{
	//һ����
	UT_LINE,
	//������
	UT_QUAD,
	//Ѽ����
	UT_DUCK,
	//��ǹ��
	UT_GUN,
};

//����˹����
struct TetrisBlock
{
	//�к�
	int Row;
	//�к�
	int Col;
	//��ɫ
	int Color;
	//״̬
	int State;
};

//����˹�������
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
	//������
	int m_nRows;
	//������
	int m_nCols;
	std::vector<std::vector<TetrisBlock*>> m_vecBlocks;
};

//����˹����
class Tetris
{
public:
	Tetris();
	~Tetris();

public:
	//����
	bool create();
	//����
	void update(float t);

public:
	//�����
	void clear();
	//����
	void account();

protected:
	//���
	TetrisBoard* m_pBoard;
	//Ԫ�ض���
	std::queue<int> m_pUnits;
	//�ٶ�
	float m_fSpeed;
};
