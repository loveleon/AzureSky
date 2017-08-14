#pragma once

#include "Header.h"

//���ֽ��̻��߳�ͬ�� http://blog.csdn.net/anddy926/article/details/7828173
//�ٽ���:ֻ����ͬ�����ڣ����ܿ����
//������:ͬһʱ�̶���Դ�Ķ�������
//�ź���:�ź��������߳�ͬʱʹ�ù�����Դ������Ҫ�޶�����
//�¼�:  

//���ӿ���   
class ILock
{
public:
	virtual void Lock() const = 0;
	virtual void Unlock() const = 0;
};

//�����������   
class Mutex : public ILock
{
public:
	Mutex();
	~Mutex();

	virtual void Lock() const;
	virtual void Unlock() const;

private:
	HANDLE m_mutex;
};

//�ٽ�������   
class CriticalSection : public ILock
{
public:
	CriticalSection();
	~CriticalSection();

	virtual void Lock() const;
	virtual void Unlock() const;

private:
	CRITICAL_SECTION m_criticalSection;
};

