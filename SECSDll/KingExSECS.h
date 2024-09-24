/*----------------------------------------------------------------
 * ��Ȩ���� (c) �����е�Ƶ���װ�����޹�˾ ��������Ȩ����
 * ��˾���ƣ������е�Ƶ���װ�����޹�˾
 * 
 * �����ߣ���Ƚ
 * ����ʱ�䣺2024-9-24
 * �汾��V1.0.0
 * ������
 *		��̫SECS����
 * ----------------------------------------------------------------
 * �޸��ˣ�
 * ʱ�䣺
 * �޸�˵����
 *
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

private:
	void RegisterGemEvent();

private:
	KingExGem m_pExGem;
};

