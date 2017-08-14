#include "Lift.h"

void Floor::Up()
{
	Cmd* cmd = new Cmd;
	cmd->Type = CT_UP;
	cmd->Param1 = m_nNumber;
	LiftSystem::Instance()->addCmd(cmd);
}

void Floor::Down()
{
	Cmd* cmd = new Cmd;
	cmd->Type = CT_DOWN;
	cmd->Param1 = m_nNumber;
	LiftSystem::Instance()->addCmd(cmd);
}

void Lift::Go(int f)
{
	Cmd* cmd = new Cmd;
	cmd->Type = CT_GO;
	cmd->Param1 = f;
	LiftSystem::Instance()->addCmd(cmd);
}

void Lift::Open()
{
	Cmd* cmd = new Cmd;
	cmd->Type = CT_OPEN;
	LiftSystem::Instance()->addCmd(cmd);
}

void Lift::Close()
{
	Cmd* cmd = new Cmd;
	cmd->Type = CT_CLOSE;
	LiftSystem::Instance()->addCmd(cmd);
}

LiftSystem* LiftSystem::Instance()
{
	static LiftSystem* system = nullptr;
	if (!system)
	{
		system = new LiftSystem;
	}
	return system;
}

void LiftSystem::init(int floor, int lift)
{
	m_bFlag = false;
	m_fStepTime = 3.0f;
	m_fOpenTime = 2.0f;
	m_fWaitTime = 5.0f;
	m_fCloseTime = 2.0f;

	m_vecFloors.reserve(floor);
	for (int i = 1; i <= floor; ++i)
	{
		Floor* f = new Floor;
		f->m_nNumber = i;
		m_vecFloors.push_back(f);
	}

	m_mapLifts.clear();
	for (int i = 1; i <= lift; ++i)
	{
		Lift* t = new Lift;
		t->m_nNumber = i;
		t->m_nLevel = 1;
		t->m_nState = LS_FREE;
		t->m_fPos = 1.0f;
		m_mapLifts[i] = t;
	}

	m_queCmds.clear();
}

void LiftSystem::destroy()
{
	for (auto item : m_queCmds)
	{
		delete item;
		item = nullptr;
	}

	for (auto item : m_vecFloors)
	{
		delete item;
		item = nullptr;
	}

	for (auto item : m_mapLifts)
	{
		delete item.second;
		item.second = nullptr;
	}
}

bool LiftSystem::findCmd(Cmd* cmd)
{
	bool bFind = false;
	for (auto item : m_queCmds)
	{
		if (item->Type == cmd->Type)
		{
			if (CT_OPEN == cmd->Type || CT_CLOSE == cmd->Type)
			{
				bFind = true;
				break;
			}
			else if (item->Param1 == cmd->Param1)
			{
				bFind = true;
				break;
			}
		}
	}
	return bFind;
}

void LiftSystem::addCmd(Cmd* cmd)
{
	if (findCmd(cmd))
	{
		return;
	}
	
	if (m_bFlag)
	{
		m_queTemp.push_back(cmd);
	}

	m_queCmds.push_back(cmd);
}

void LiftSystem::update(float t)
{
	if (!m_bFlag && !m_queTemp.empty())
	{
		for (auto item : m_queTemp)
		{
			addCmd(item);
		}
		m_queTemp.clear();
	}

	processCmd(t);
}

void LiftSystem::processCmd(float t)
{
	static float total = 0.0f;
	total += t;
	for (auto lift : m_mapLifts)
	{
		int state = lift.second->m_nState;
		int lv = lift.second->m_nLevel;
		switch (state)
		{
		case LS_FREE:
			{
				//空闲的时候，执行第一个命令即可
				auto cmd = m_queCmds.front();
				if (!cmd)
				{
					break;
				}
				m_queCmds.pop_front();
				switch (cmd->Type)
				{
				case CT_UP:
				case CT_DOWN:
					{
						int user = cmd->Param1;
						lift.second->m_nState = (user < lv ? LS_DOWNWARD : user > lv ? LS_UPWARD : LS_OPENING);
						break;
					}
				case CT_OPEN:
					{
						lift.second->m_nState = LS_OPENING;
						break;
					}
				case CT_GO:
					{
						int user = cmd->Param1;
						lift.second->m_nState = (user < lv ? LS_DOWNWARD : user > lv ? LS_UPWARD : LS_FREE);
						break;
					}
				default:
					break;
				}
				total = 0.0f;
				delete cmd;
				cmd = nullptr;
				break;
			}
		case LS_UPWARD:
			{
				//上行的时候，向上和GO的命令优先，按差值从小到大排列
				reorderCmd(CT_UP);
				auto cmd = m_queCmds.front();
				if (!cmd)
				{
					break;
				}
				m_queCmds.pop_front();
				switch (cmd->Type)
				{
				case CT_UP:
				case CT_GO:
					{
						int user = cmd->Param1;
						if (user > lv)
						{
							lift.second->m_fPos = lift.second->m_nLevel + total / m_fStepTime;
							if (total > m_fStepTime)
							{
								lift.second->m_nLevel += 1;
								total -= m_fStepTime;
							}
						}
						else if (user == lv)
						{
							lift.second->m_fPos = (float)lift.second->m_nLevel;
							lift.second->m_nState = LS_OPENING;
							total = 0.0f;
							delete cmd;
							cmd = nullptr;
						}
						break;
					}
				default:
					break;
				}
				delete cmd;
				cmd = nullptr;
				break;
			}
		case LS_DOWNWARD:
			{
				//上行的时候，向上和GO的命令优先，按差值从小到大排列
				reorderCmd(CT_DOWN);
				auto cmd = m_queCmds.front();
				m_queCmds.pop_front();
				switch (cmd->Type)
				{
				case CT_DOWN:
				case CT_GO:
					{
						int user = cmd->Param1;
						if (user < lv)
						{
							lift.second->m_fPos = lift.second->m_nLevel + total / m_fStepTime;
							if (total > m_fStepTime)
							{
								lift.second->m_nLevel -= 1;
								total -= m_fStepTime;
							}
						}
						else if (user == lv)
						{
							lift.second->m_fPos = (float)lift.second->m_nLevel;
							lift.second->m_nState = LS_OPENING;
							total = 0.0f;
							delete cmd;
							cmd = nullptr;
						}
						break;
					}
				default:
					break;
				}
				break;
			}
		case LS_OPENING:
			{
				//如果是正在开门，2s之后，进入到等待状态
				if (total > m_fOpenTime)
				{
					lift.second->m_nState = LS_WAITING;
					total -= m_fOpenTime;
				}
			}
		case LS_CLOSING:
			{
				//如果是正在等待，5s之后，进入到关闭状态
				if (total > m_fCloseTime)
				{
					lift.second->m_nState = LS_FREE;
					total -= m_fCloseTime;
				}
			}
		case LS_WAITING:
			{
				//如果是正在等待，5s之后，进入到关闭状态
				if (total > m_fWaitTime)
				{
					lift.second->m_nState = LS_CLOSING;
					total -= m_fWaitTime;
				}
			}
		default:
			break;
		}
	}
}

void LiftSystem::executeCmd(Cmd* cmd)
{
	
}

void LiftSystem::reorderCmd(int state)
{
	m_bFlag = true;
	for (auto lift : m_mapLifts)
	{
		int lv = (lift.second)->m_nLevel;
		int size = m_queCmds.size();
		int index = 0;
		int count = 0;
		while (size - index)
		{
			auto type = m_queCmds[index]->Type;
			auto param = m_queCmds[index]->Param1;
			bool flag = (state == CT_UP) ? param > lv : param < lv;
			if ((state == type || CT_GO == type) && (flag))
			{
				std::swap(m_queCmds[index], m_queCmds[count]);
				++count;
			}
			++index;
		}
		for (int i = 0; i < count - 1; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				if ((m_queCmds[i]->Param1 - lv) >(m_queCmds[j]->Param1 - lv))
				{
					std::swap(m_queCmds[i], m_queCmds[j]);
				}
			}
		}
	}
	m_bFlag = false;
}



