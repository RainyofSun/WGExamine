/*----------------------------------------------------------------
 * ��Ȩ���� (c) �����е�Ƶ���װ�����޹�˾ ��������Ȩ����
 * ��˾���ƣ������е�Ƶ���װ�����޹�˾
 * 
 * �����ߣ���Ƚ
 * ����ʱ�䣺2024-9-20
 * �汾��V1.0.0
 * ������SECS ���ӻ���
 *
 * ----------------------------------------------------------------
 * �޸��ˣ�
 * ʱ�䣺
 * �޸�˵����
 *
 * �汾��
 *----------------------------------------------------------------*/
#pragma once
#include "SECSConfig.h"
#include <map>

using namespace std;

UINT EventSocketThread(LPVOID lpParameter);

#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT CSECSConnectBase
{
public:
	CSECSConnectBase(void);
	~CSECSConnectBase(void);

	/**
	 * ���ܣ�����������Ϣ
	 * ���룺
			param1: (SECSCommandParameters) ������Ϣ
	 */ 
	virtual void SECS_SetCommandParameters(SECSCommandParameters parameters){m_parameters = parameters;};

	/**
	 * ���ܣ���ʼ����SECS
	 */ 
	virtual void SECS_Connect(){};

	/**
	 * ���ܣ��Ͽ�����SECS
	 */ 
	virtual void SECS_Disconnect(){};
	/**
	 * ���ܣ��¼��ϱ�
	 * ���룺
			param1: evID �¼�ID
			param2: stringMap �¼��󶨵�ReportID �� ReportID �󶨵Ķ�Ӧ�ĳ���ֵ
	 */ 
	virtual void SECS_EventReport(int evID, std::map<CString, CString> stringMap){};

	/**
	 * ���ܣ������ϱ�
	 */ 
	virtual void SECS_AlarmReport(int alID){};

	/**
	 * ���ܣ������¼��ϱ�
	 */ 
	virtual void SECS_ClearAlarmReport(int alID){};

protected:
	/**
	 * ���ܣ������¼��߳�
	 */ 
	void resumeSECSThread();

public:
	SECSCommandParameters m_parameters;
	bool bExitEventSocketThread;

protected:
	CWinThread *m_pEventSocketThread;
};

