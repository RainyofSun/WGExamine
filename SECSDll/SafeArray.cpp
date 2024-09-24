#include "StdAfx.h"
#include "SafeArray.h"


CSafeArray::CSafeArray(void)
{
}


CSafeArray::~CSafeArray(void)
{
}

void CSafeArray::SetSize(int size)
{
	safeArray.SetSize(size);
}

void CSafeArray::Add(int element)
{
	CSingleLock lock = CSingleLock(&m_mutex);
	lock.Lock();
	if (lock.IsLocked())
	{
		safeArray.Add(element);
		lock.Unlock();
	}
}

void CSafeArray::RemoveAt(int index)
{
	CSingleLock lock = CSingleLock(&m_mutex);
	lock.Lock();
	if (lock.IsLocked())
	{
		safeArray.RemoveAt(index);
		lock.Unlock();
	}
}

void CSafeArray::RemoveAll()
{
	CSingleLock lock = CSingleLock(&m_mutex);
	lock.Lock();
	if (lock.IsLocked())
	{
		safeArray.RemoveAll();
		lock.Unlock();
	}
}

BOOL CSafeArray::IsEmpty()
{
	return safeArray.IsEmpty();
}

int CSafeArray::GetAt(int index)
{
	if (index >= safeArray.GetCount())
	{
		return -1;
	}

	return safeArray.GetAt(index);
}

int CSafeArray::GetCount()
{
	return safeArray.GetCount();
}

int CSafeArray::First()
{
	if (safeArray.IsEmpty())
	{
		return -1;
	}

	return GetAt(0);
}

void CSafeArray::SetAt(int index, int element)
{
	CSingleLock lock = CSingleLock(&m_mutex);
	lock.Lock();
	if (lock.IsLocked())
	{
		safeArray.SetAt(index, element);
		lock.Unlock();
	}
}