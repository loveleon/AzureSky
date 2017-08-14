#pragma once

#include "Header.h"

//线程创建方式
//CreateThread：Windows的API函数,提供操作系统级别的创建线程的操作
//_beginthreadex：MS对C Runtime库的扩展SDK函数，实质上windows上还是调用CreateThread，仅使用Runtime Library时，可以用_beginthread
//AfxBeginThread：MFC中线程创建的MFC函数,即可用于界面线程,实质上调用_beginthreadex
//pthread_create：跨平台的 POSIX pthread第三方库，同时还有boost的线程库boost::thread
//thread：C++11支持的线程
//子线程join就会阻塞主线程
//支持lambda，但最好使用传值方式

class IThread
{
public:
	virtual void create() = 0;
	virtual void release() = 0;
};

class ThreadWin : public IThread
{
public:
	static DWORD WINAPI fun(LPVOID lpParam);
	virtual void create();
	virtual void release();
private:
	HANDLE handle;
};

class ThreadCR : public IThread
{
public:
	static void fun(void* p);
	static unsigned __stdcall funEx(void* p);
	virtual void create();
	virtual void release();
private:
	HANDLE handle;
	HANDLE handleEx;
};

class Thread11 : public IThread
{
public:
	void fun(int n);
	virtual void create();
	virtual void release();
private:
	std::mutex mutex;
};


