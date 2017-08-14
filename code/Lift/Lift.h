#include "Header.h"

#pragma once

//电梯状态
enum LiftState
{
	LS_FREE,		//空闲中
	LS_REPAIR,		//维修中
	LS_UPWARD,		//上行中
	LS_DOWNWARD,	//下行中
	LS_OPENING,		//开门中
	LS_CLOSING,		//关门中
	LS_WAITING		//等待中
};

//命令类型
enum CmdType
{
	CT_NULL,		//空
	CT_UP,			//上
	CT_DOWN,		//下
	CT_OPEN,		//开
	CT_CLOSE,		//关
	CT_GO			//去
};

//命令
struct Cmd
{
	Cmd(){ Type = CT_NULL; Param1 = 0; Param2 = 0; }
	Cmd(int t, int p1, int p2){ Type = t; Param1 = p1; Param2 = p2; }
	int Type;			//命令类型
	int Param1;			//参数1
	int Param2;			//参数2
};

//楼层
class Floor
{
public:
	void Up();			//向上
	void Down();		//向下
public:
	int m_nNumber;		//楼层号
};

//电梯
class Lift
{
	void Go(int f);		//去
	void Open();		//开门
	void Close();		//关门
public:
	int m_nNumber;		//电梯编号
	int m_nLevel;		//电梯层
	int m_nState;		//电梯状态
	float m_fPos;		//电梯位置
};

//电梯系统
class LiftSystem
{
public:
	static LiftSystem* Instance();
	void init(int floor, int lift = 1);
	void destroy();
	void update(float t);

public:
	void addCmd(Cmd* cmd);
	bool findCmd(Cmd* cmd);
	void reorderCmd(int state);

protected:
	void processCmd(float t);
	void executeCmd(Cmd* cmd);
	
protected:
	bool					m_bFlag;		//正在遍历
	float					m_fStepTime;    //换层时间
	float					m_fOpenTime;	//开门时间
	float					m_fWaitTime;	//等待时间
	float					m_fCloseTime;	//关门时间
	std::deque<Cmd*>		m_queCmds;		//命令队列
	std::deque<Cmd*>		m_queTemp;		//临时队列
	std::map<int, Lift*>	m_mapLifts;		//电梯集合
	std::vector<Floor*>		m_vecFloors;	//楼层集合
};

