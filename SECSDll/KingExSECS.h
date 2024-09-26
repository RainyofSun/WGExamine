/*----------------------------------------------------------------
 * ��Ȩ���� (c) �����е�Ƶ���װ�����޹�˾ ��������Ȩ����
 * ��˾���ƣ������е�Ƶ���װ�����޹�˾
 * 
 * �����ߣ���Ƚ
 * ����ʱ�䣺2024-9-24
 * �汾��V1.0.0
 * ������
 *		�ǿ�SECS����
 * ----------------------------------------------------------------
 * �޸��ˣ�
 * ʱ�䣺
 * �޸�˵����
 * 1.sv�����İ��߼�
   3.�䷽����ɾ���������޸��߼�
 * �汾��
 *----------------------------------------------------------------*/
#pragma once
#include "SECSConnectBase.h"
#include "KingExGem.h"
#include "KingExGemDefine.h"
#include "Helper.h"

class CKingExSECS: public CSECSConnectBase
{
public:
	CKingExSECS(void);
	~CKingExSECS(void);
	
	void SECS_Connect();
	void SECS_Disconnect();
	void SECS_EventReport(int evID, std::map<CString, CString> stringMap);
	void SECS_AlarmReport(int alID);
	void SECS_ClearAlarmReport(int alID); 

	/**
	 * ���ܣ�SECS ״̬�л�
	 * ���룺
			param1: (SECSConnectModel) Ҫ�л�����ģʽ
	 * �����
			(SECSConnectModel)�л�֮���ģʽ
	 */ 
	SECSConnectModel SECS_SwitchConnectModel(SECSConnectModel targetModel);

	/**
	 * ���ܣ������豸״̬
	 * ���룺
			param1: (ProcessingState) �豸״̬
	 */ 
	int SECS_SetProcessingCommand(ProcessingState processingState);
	
	/**
	 * ���ܣ����豸����ֵ
	 * ���룺
			param1: ��pnVid��Ҫ���õĳ���ID
			param2: ��psValue��Ҫ���õĳ���ֵ
	 * �����
			int �Ƿ����óɹ� 0 - �ɹ�
	 */ 
	int SECS_BindingEquipmentECValue(long *pnVid, string *psValue);

	/**
	 * ���ܣ����豸�ı���ֵ
	 * ���룺
			param1: ��pnVid��Ҫ���õı���id
			param2: ��psValue��Ҫ���õı���ֵ
	 * �����
			int �Ƿ����óɹ��� 0 - �ɹ�
	 */ 
	int SECS_BindingEquipmentSVValue(long *pnVid, string *psValue);

	//////////////////////////////// �䷽ָ�� //////////////////////////////////////////
	/**
	 * ���ܣ��䷽״̬�ı�
	 * ���룺
			param1: (SECSRecipeOperation) �䷽״̬
			param2: (ppID) �䷽����
	 * �����
			int �Ƿ����óɹ� 0 - �ɹ�
	 */ 
	int SECS_PPChanged(SECSRecipeOperation operation, CString ppId);

	/**
	 * ���ܣ�ѡ���䷽
	 * ���룺
			param1: (ppid) �䷽����
	 * �����
			int �Ƿ����óɹ� 0 - �ɹ�	
	 */ 
	int SECS_PPSelected(CString ppId);

	/**
	 * ���ܣ��ϴ��䷽�б�
	 * ���룺
			param1: (ppids) �䷽�б�
	 * �����
			int �Ƿ��ϴ��ɹ� 0 - �ɹ�	
	 */ 
	int SECS_UploadPPList(CArray<CString>* ppids, long nMsgId);

	/**
	 * ���ܣ��ϴ��䷽���ַ�����
	 * ���룺
			param1: (strPPBody) �䷽���ݣ�ת��json�ַ�������
			param2: (strPPid) �䷽����
	 * �����
			int �Ƿ��ϴ��ɹ� 0 - �ɹ�
	 */ 
	int SECS_SendPPBody(CString strPPBody, CString strPPid);

protected:
	///////////////////////////////// ��Ϣ�ص� /////////////////////////////////////////
	static void OnGEMMessage(CBHANDLE hdcb, cSemion *pMessage);
	static void OnGEMEvent(CBHANDLE hdcb, short nEventId, long lParam);
	static void OnGEMRemoteEvent(CBHANDLE hdcb, WORD nPort, short nEventId, long lParam);
	// ���䷽��׼����ص�
	static void OnGEMReqPP(CBHANDLE hdcb, long nMsgID, string sPpid);
	// �����ļ��Ǳ�׼�䷽�ص�
	static void OnGEMReqPPEx(CBHANDLE hdcb, long nMsgId, string sPpid, string sRecipePath);
	// �����ͷǱ�׼�䷽�ص�
	static void OnGEMReqPPSend(CBHANDLE hdcb, long nMsgid, string sPpid, DWORD nLength, unsigned char* pbBody);
	static void OnGEMReqPPFmt(CBHANDLE hdCB, long nMsgId, string sPpid);
	static void OnGEMReqPPFmtSend(CBHANDLE hdCB, long nMsgId, string sPpid, string sMdln, string sSoftRev, DWORD nCount, string* psCCode, DWORD* pnParamCount, string* psParamNames);
	static void OnGEMReqPPList(CBHANDLE hdCB, long nMsgId);
	static void OnGEMReqPPDelete(CBHANDLE hdCB, long nMsgId, DWORD nCount, string* psPpid);
	static void OnGEMReqOnline(CBHANDLE hdCB, long lMsgId, long lFromState, long lToState);
	static void OnGEMReqOffline(CBHANDLE hdCB, long lMsgId, long lFromState, long lToState);
	static void OnGEMReqRemoteCommand(CBHANDLE hdCB, long nMsgId, string sRcmd, DWORD nCount, string* psNames, string* psVals);
	static void OnGEMReqEnhancedRemoteCommand(CBHANDLE hdCB, long nMsgId, string sObjspec, string sRcmd, DWORD nCount, string* psNames, string* psVals);
	static void OnGEMTerminalMessage(CBHANDLE hdCB, long nMsgId,long nTid, string sMsg);

private:
	void RegisterGemEvent();

public:
	KingExGem m_pExGem;	
	HWND m_hwnd;
};

