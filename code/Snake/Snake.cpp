#include "Snake.h"
#include <time.h>

Snake::Snake(int rows, int cols)
{
	m_nRows = rows;
	m_nCols = cols;
	m_nFoodR = 0;
	m_nFoodR = 0;
	m_fDeltaTime = 1.0f;
	CreateGrid();
}

Snake::~Snake()
{
	for(int i = 0; i < m_nFoodR; i++)
	{
		delete[] m_Grid[i];
	}
	delete[] m_Grid;
	m_Grid = nullptr;
	for(auto iter : m_Snake)
	{
		iter = nullptr;
	}
	m_Snake.clear();
}

void Snake::CreateGrid()
{
	m_Grid = new SnakeCell* [m_nRows];
	for(int i = 0; i < m_nRows; i++)
	{
		m_Grid[i] = new SnakeCell[m_nCols];
		for(int j = 0; j < m_nCols; j++)
		{
			m_Grid[i][j].Row = 0;
			m_Grid[i][j].Col = 0;
			m_Grid[i][j].Dir = SD_INVALID;
			m_Grid[i][j].State = SCS_DEFAULT;
		}
	}
}

void Snake::CreateFood()
{
	int r = 0;
	int c = 0;
	while(true)
	{
		srand((int)time(0));
		r = int(rand() % m_nRows);
		c = int(rand() % m_nCols);
		bool flag = false;
		for(auto item : m_Snake)
		{
			int rr = item->Row;
			int cc = item->Col;
			if (rr == r && cc == c)
			{
				flag = true;
			}
		}
		if(!flag)
		{
			break;
		}
	}
	m_nFoodR = r;
	m_nFoodC = c;
	m_Grid[m_nFoodR][m_nFoodC].State = SCS_FOOD;
}

void Snake::CreateSnake()
{
	int r = 0;
	int c = 0;
	while(true)
	{
		srand((int)time(0));
		r = int(rand() % m_nRows);
		c = int(rand() % m_nCols);
		if(r != m_nFoodR || c != m_nFoodC)
		{
			break;
		}
	}
	m_Grid[r][c].Row = r;
	m_Grid[r][c].Col = c;
	m_Grid[r][c].State = SCS_BODY;
	int deltaR = r - m_nFoodR;
	int deltaC = c - m_nFoodC;
	if(abs(deltaR) >= abs(deltaC))
	{
		m_Grid[r][c].Dir = (deltaR > 0 ? SD_UP : SD_DOWN);
	}
	else
	{
		m_Grid[r][c].Dir = (deltaC > 0 ? SD_LEFT : SD_RIGHT);
	}

	m_Snake.push_front(&(m_Grid[r][c]));
}

void Snake::GameOver()
{
	for(int i = 0; i < m_nRows; i++)
	{
		for(int j = 0; j < m_nCols; j++)
		{
			m_Grid[i][j].Row = 0;
			m_Grid[i][j].Col = 0;
			m_Grid[i][j].Dir = SD_INVALID;
			m_Grid[i][j].State = SCS_INVALID;
		}
	}
	for(auto item : m_Snake)
	{
		item = nullptr;
	}
	m_Snake.clear();
}

bool Snake::Update(float deltaTime)
{
	static float total = 0;
	total += deltaTime;
	if(total > m_fDeltaTime)
	{
		auto element = m_Snake.front();
		int r = element->Row;
		int c = element->Col;
		switch(element->Dir)
		{
		case SD_UP:
			{
				r -= 1;
				break;
			}
		case SD_DOWN:
			{
				r += 1;
				break;
			}
		case SD_LEFT:
			{
				c -= 1;
				break;
			}
		case SD_RIGHT:
			{
				c += 1;
				break;
			}
		}

		//撞到边缘，游戏结束
		if(r < 0 || r >= m_nRows || c < 0 || c >= m_nCols)
		{
			GameOver();
			return false;
		}

		//撞到自身，游戏结束
		for(auto iter : m_Snake)
		{
			int rr = iter->Row;
			int cc = iter->Col;
			if (rr == r && cc == c)
			{
				GameOver();
				return false;
			}
		}

		//把新块置为蛇身
		m_Grid[r][c].Row = r;
		m_Grid[r][c].Col = c;
		m_Grid[r][c].State = SCS_BODY;
		m_Grid[r][c].Dir = element->Dir;
		m_Snake.push_front(&(m_Grid[r][c]));

		//是不是食物
		if(r != m_nFoodR || c != m_nFoodC)
		{
			auto head = m_Snake.back();
			head->Dir = SD_INVALID;
			head->State = SCS_DEFAULT;
			m_Snake.pop_back();
		}
		else
		{
			CreateFood();
		}

		total -= m_fDeltaTime;
		
		//控制速度，每5节就加速12.5%
		static bool b = true;
		if (!m_Snake.empty() && m_Snake.size() % 5 == 0)
		{
			if(b)
			{
				m_fDeltaTime *= 0.8f;
				b = false;
			}
		}
		else
		{
			b = true;
		}
	}
	return true;
}

void Snake::Control(SnakeDirection dir)
{
	auto element = m_Snake.front();
	element->Dir = dir;
}