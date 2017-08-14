#pragma once

#include "Header.h"

//�̴߳�����ʽ
//CreateThread��Windows��API����,�ṩ����ϵͳ����Ĵ����̵߳Ĳ���
//_beginthreadex��MS��C Runtime�����չSDK������ʵ����windows�ϻ��ǵ���CreateThread����ʹ��Runtime Libraryʱ��������_beginthread
//AfxBeginThread��MFC���̴߳�����MFC����,�������ڽ����߳�,ʵ���ϵ���_beginthreadex
//pthread_create����ƽ̨�� POSIX pthread�������⣬ͬʱ����boost���߳̿�boost::thread
//thread��C++11֧�ֵ��߳�
//���߳�join�ͻ��������߳�
//֧��lambda�������ʹ�ô�ֵ��ʽ

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


