/*----------------------------------------------------------------
 * 版权所有 (c) 北京中电科电子装备有限公司 保留所有权利。
 * 公司名称：北京中电科电子装备有限公司
 * 
 * 创建者：刘冉
 * 创建时间：2024-9-24
 * 版本：V1.0.0
 * 描述：
 *		亚太SECS控制
 * ----------------------------------------------------------------
 * 修改人：
 * 时间：
 * 修改说明：
 *
 * 版本：
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
	 * 功能：SECS 状态切换
	 * 输入：
			param1: (SECSConnectModel) 要切换到的模式
	 * 输出：
			(SECSConnectModel)切换之后的模式
	 */ 
	SECSConnectModel SECS_SwitchConnectModel(SECSConnectModel targetModel);

	/**
	 * 功能：设置设备状态
	 * 输入：
			param1: (ProcessingState) 设备状态
	 */ 
	int SECS_SetProcessingCommand(ProcessingState processingState);

private:
	void RegisterGemEvent();

private:
	KingExGem m_pExGem;
};

