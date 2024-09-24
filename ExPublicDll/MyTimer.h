#pragma once
class  AFX_EXT_CLASS CMyTimer
{
public:
	CMyTimer(void);
	~CMyTimer(void);
public:
	void StartTimer(double dSetTime = 1000.0);
	double GetPaseTime();
	bool JudgeTimer();
	void MySleep(double dSetTime);
private:
	double m_dSetTime;
	LARGE_INTEGER m_iStartTime;
	LARGE_INTEGER m_iFrequency;
};

