#include "Lock.h"

Mutex::Mutex()
{
	m_mutex = ::CreateMutex(NULL, FALSE, NULL);
}

Mutex::~Mutex()
{
	::CloseHandle(m_mutex);
}

void Mutex::Lock() const
{
	::WaitForSingleObject(m_mutex, INFINITE);
}

void Mutex::Unlock() const
{
	::ReleaseMutex(m_mutex);
}

CriticalSection::CriticalSection()
{
	::InitializeCriticalSection(&m_criticalSection);
}

CriticalSection::~CriticalSection()
{
	::DeleteCriticalSection(&m_criticalSection);
}

void CriticalSection::Lock() const
{
	::EnterCriticalSection((LPCRITICAL_SECTION)&m_criticalSection);
}

void CriticalSection::Unlock() const
{
	::LeaveCriticalSection((LPCRITICAL_SECTION)&m_criticalSection);
}

