#include "Thread.h"

DWORD WINAPI ThreadWin::fun(LPVOID lpParam)
{
	return 0;
}

void ThreadWin::create()
{
	handle = ::CreateThread(0, 0, ThreadWin::fun, 0, 0, 0);
}

void ThreadWin::release()
{
	CloseHandle(handle);
}

void ThreadCR::fun(void* p)
{
	_endthread();
}

unsigned __stdcall ThreadCR::funEx(LPVOID lpvoid)
{
	return 0;
}

void ThreadCR::create()
{
	_beginthread(fun, 0, 0);
	handleEx = (HANDLE)_beginthreadex(0, 0, ThreadCR::funEx, 0, 0, 0);
}

void ThreadCR::release()
{
	CloseHandle(handle);
}

void Thread11::fun(int n)
{

}

void Thread11::create()
{
	std::thread td(&Thread11::fun, this, 5);
	td.join();   

	std::thread td1([&]()
	{
		mutex.lock();
		std::this_thread::sleep_for(std::chrono::seconds(10));   //–›√ﬂ10√Î
		std::thread::id id = std::this_thread::get_id();
		mutex.unlock();
	});
}

void Thread11::release()
{

}