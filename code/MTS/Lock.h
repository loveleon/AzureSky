#pragma once

#include "Header.h"

//四种进程或线程同步 http://blog.csdn.net/anddy926/article/details/7828173
//临界区:只能在同进程内，不能跨进程
//互斥量:同一时刻对资源的独立访问
//信号量:信号允许多个线程同时使用共享资源，但是要限定个数
//事件:  

//锁接口类   
class ILock
{
public:
	virtual void Lock() const = 0;
	virtual void Unlock() const = 0;
};

//互斥对象锁类   
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

//临界区锁类   
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

