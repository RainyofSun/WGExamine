#pragma once
#include "afxmt.h"

class CSafeArray
{
public:
	CSafeArray(void);
	~CSafeArray(void);

public:
	void SetSize(int size);
	void Add(int element);
	void RemoveAt(int index);
	void RemoveAll();
	BOOL IsEmpty();
	int GetAt(int index);
	int GetCount();
	int First();
	void SetAt(int index, int element);

private:
	CMutex m_mutex;
	CArray<int> safeArray;
};

