#include "StdAfx.h"
#include "MyTimer.h"


CMyTimer::CMyTimer(void)
{
	try
	{
		m_dSetTime = 0.0;
	}
	catch (...)
	{
	}
}


CMyTimer::~CMyTimer(void)
{
}

void CMyTimer::StartTimer(double dSetTime)
{
	try
	{
		m_dSetTime = dSetTime;
		QueryPerformanceFrequency(&m_iFrequency);
		QueryPerformanceCounter(&m_iStartTime);
	}
	catch (...)
	{

	}
}

double CMyTimer::GetPaseTime()
{
	try
	{
		LARGE_INTEGER iEndTime;
		double dTime = 0.0;
		QueryPerformanceCounter(&iEndTime);
		dTime = double(iEndTime.QuadPart - m_iStartTime.QuadPart)/double(m_iFrequency.QuadPart)*1000.0;//ms
		return dTime;
	}
	catch (...)
	{
	}
}

bool CMyTimer::JudgeTimer()
{
	try
	{
		LARGE_INTEGER iEndTime;
		double dTime = 0.0;
		QueryPerformanceCounter(&iEndTime);
		dTime = double(iEndTime.QuadPart - m_iStartTime.QuadPart)/double(m_iFrequency.QuadPart)*1000.0;
		if (dTime >= m_dSetTime)
		{
			return true;
		} 
		else
		{
			return false;
		}
	}
	catch (...)
	{

	}
}

void CMyTimer::MySleep(double dSetTime)
{
	try
	{
		StartTimer(dSetTime);
		do 
		{
			if (JudgeTimer())
			{
				return;
			}
		} while (true);
	}
	catch (...)
	{
	}
}