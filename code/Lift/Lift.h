#include "Header.h"

#pragma once

//����״̬
enum LiftState
{
	LS_FREE,		//������
	LS_REPAIR,		//ά����
	LS_UPWARD,		//������
	LS_DOWNWARD,	//������
	LS_OPENING,		//������
	LS_CLOSING,		//������
	LS_WAITING		//�ȴ���
};

//��������
enum CmdType
{
	CT_NULL,		//��
	CT_UP,			//��
	CT_DOWN,		//��
	CT_OPEN,		//��
	CT_CLOSE,		//��
	CT_GO			//ȥ
};

//����
struct Cmd
{
	Cmd(){ Type = CT_NULL; Param1 = 0; Param2 = 0; }
	Cmd(int t, int p1, int p2){ Type = t; Param1 = p1; Param2 = p2; }
	int Type;			//��������
	int Param1;			//����1
	int Param2;			//����2
};

//¥��
class Floor
{
public:
	void Up();			//����
	void Down();		//����
public:
	int m_nNumber;		//¥���
};

//����
class Lift
{
	void Go(int f);		//ȥ
	void Open();		//����
	void Close();		//����
public:
	int m_nNumber;		//���ݱ��
	int m_nLevel;		//���ݲ�
	int m_nState;		//����״̬
	float m_fPos;		//����λ��
};

//����ϵͳ
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
	bool					m_bFlag;		//���ڱ���
	float					m_fStepTime;    //����ʱ��
	float					m_fOpenTime;	//����ʱ��
	float					m_fWaitTime;	//�ȴ�ʱ��
	float					m_fCloseTime;	//����ʱ��
	std::deque<Cmd*>		m_queCmds;		//�������
	std::deque<Cmd*>		m_queTemp;		//��ʱ����
	std::map<int, Lift*>	m_mapLifts;		//���ݼ���
	std::vector<Floor*>		m_vecFloors;	//¥�㼯��
};

