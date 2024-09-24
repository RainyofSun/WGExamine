/*----------------------------------------------------------------
 * ��Ȩ���� (c) �����е�Ƶ���װ�����޹�˾ ��������Ȩ����
 * ��˾���ƣ������е�Ƶ���װ�����޹�˾
 * 
 * �����ߣ���Ƚ
 * ����ʱ�䣺2024-9-20
 * �汾��V1.0.0
 * ������̩��SECS������
 *
 * ----------------------------------------------------------------
 * �޸��ˣ�
 * ʱ�䣺
 * �޸�˵����
 * �汾��
 *----------------------------------------------------------------*/
#pragma once
#include "SECSConnectBase.h"
#include "SECSSocket.h"
#include "TaiZhiSECSMessage.h"
#include "SafeArray.h"

class CTaiZhiSECS: public CSECSConnectBase
{
public:
	CTaiZhiSECS(void);
	~CTaiZhiSECS(void);

	// �¼�����
	CSafeArray m_eventArray;
	// ��������
	CSafeArray m_alarmArray;
	// ��������
	CSafeArray m_clearArray;

	std::map<int, std::map<CString, CString>> m_reportStringMap;

	CTaiZhiSECSMessage secsMessage;

	void SECS_Connect();
	void SECS_Disconnect();
	void SECS_EventReport(int evID, std::map<CString, CString> stringMap);
	void SECS_AlarmReport(int alID);
	void SECS_ClearAlarmReport(int alID);
	void SECS_SendMessage(CString &strSend);

private:
	CSECSSocket *m_socket;
};

