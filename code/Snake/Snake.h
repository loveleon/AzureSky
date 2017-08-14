#pragma once

#include <deque>

using namespace std;

//��Ԫ״̬
enum SnakeCellState
{
	//��Ч��
	SCS_INVALID,
	//Ĭ�ϵ�
	SCS_DEFAULT,
	//ʳ��
	SCS_FOOD,
	//����
	SCS_BODY,
};

//����
enum SnakeDirection
{
	//��Ч��
	SD_INVALID,
	//��
	SD_UP,
	//��
	SD_DOWN,
	//��
	SD_LEFT,
	//��
	SD_RIGHT,
};

//��Ԫ��
struct SnakeCell
{
	//�к�
	int Row;
	//�к�
	int Col;
	//����
	SnakeDirection Dir;
	//״̬
	SnakeCellState State;
};

//̰ʳ��
class Snake
{
public:
	Snake(int rows, int cols);
	~Snake();
public:
	//���쵥Ԫ��
	void CreateGrid();
	//����ʳ��
	void CreateFood();
	//��������
	void CreateSnake();
	//��Ϸ����
	void GameOver();
	//����
	bool Update(float deltaTime);
	//�ⲿ����
	void Control(SnakeDirection dir);
public:
	//����
	int m_nRows;
	//����
	int m_nCols;
	//ʳ�����ڵ��к�
	int m_nFoodR;
	//ʳ�����ڵ��к�
	int m_nFoodC;
	//�ٶ�
	float m_fDeltaTime;
	//�������
	SnakeCell** m_Grid;
	//�߼���
	deque<SnakeCell*> m_Snake;
};