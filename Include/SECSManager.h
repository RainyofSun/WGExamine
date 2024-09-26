/*----------------------------------------------------------------
 * ��Ȩ���� (c) �����е�Ƶ���װ�����޹�˾ ��������Ȩ����
 * ��˾���ƣ������е�Ƶ���װ�����޹�˾
 * 
 * �����ߣ���Ƚ
 * ����ʱ�䣺2024-9-23
 * �汾��V1.0.0
 * ������SECS�Ĺ�����
 *
 * ----------------------------------------------------------------
 * �޸��ˣ���Ƚ
 * ʱ�䣺2024-9-24
 * �޸�˵����
 *	1.���̩��SECS����
 * �汾��V1.0.0
 *----------------------------------------------------------------*/
#pragma once
#include "SECSConnectBase.h"

#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT CSECSManager
{
public:
	CSECSManager(void);
	~CSECSManager(void);

	/////////////////////////////////// ͨ�ýӿ� ////////////////////////////////////////////
	void SECS_SetCommandParameters(SECSCommandParameters parameters);
	void SECS_Connect();
	void SECS_Disconnect();
	void SECS_EventReport(int evID, std::map<CString, CString> stringMap);
	void SECS_AlarmReport(int alID);
	void SECS_ClearAlarmReport(int alID);
	// SECS ��ǰ��ģʽ
	SECSConnectModel SECS_ConnectModel();
	// SECS ����״̬
	SECSConnectStatus SECS_ConnectStatus();

	/////////////////////////////////// ̩��SECS �ӿ� ///////////////////////////////////////
	void SECS_AckReplyInfo(string &strAcktxid,string &strAckeid);
	void SECS_SvGetInfo(CString strSvtxid,CString dtrSveid, std::map<CString, CString> svMap);
	// �л� SECS ��ģʽ
	SECSConnectModel SECS_SwitchModel(SECSConnectModel targetModel, bool sendEvent = true);

	/////////////////////////////////// �ǿ� SECS �ӿ� ///////////////////////////////////////
	void SECS_UploadPPList(CArray<CString>* ppids, long nMsgId);
	void SECS_UploadPPBody(CString ppBody, CString ppid);

private:
	CSECSConnectBase *m_secs;
	SECSManufacturers m_manufacturner;
};

