#include "StdAfx.h"
#include "KingExSECS.h"

CKingExSECS::CKingExSECS(void)
{
	RegisterGemEvent();
}


CKingExSECS::~CKingExSECS(void)
{
}

void CKingExSECS::SECS_Connect()
{
	long Rsp = 0;
	Rsp = m_pExGem.GEMInitialize(m_parameters.kingKGPRJFilePath.GetBuffer());
	if (Rsp != 0)
	{
		return;
	}

	// 报警初始化
	m_pExGem.GEMGetAllAlarmInfo();
	// 事件初始化
	m_pExGem.GEMGetAllEventInfo();
	// report 初始化
	m_pExGem.GEMGetAllReportInfo();
	// sv 初始化
	m_pExGem.GEMGetAllSVInfo();
	// dv 初始化
	m_pExGem.GEMGetAllDVInfo();
	// ec 初始化
	m_pExGem.GEMGetAllEcvInfo();

	// 初始化完毕，启动亚太
	Rsp = m_pExGem.GEMStart();
	if (Rsp != 0)
	{
		// 连接失败
		return;
	}
	
	// 开始连接
	Rsp = m_pExGem.GEMSetConnectionEnable(true);
	if (Rsp != 0)
	{
		return;
	}

	// 设置 recipe 路径
	m_pExGem.GEMSetParam("RecipePath", m_parameters.kingRecipeFilePath.GetBuffer());
}

void CKingExSECS::SECS_Disconnect()
{
	// 关闭连接
	m_pExGem.GEMSetConnectionEnable(false);
	// 停止亚太
	m_pExGem.GEMStop();
	// 关闭
	m_pExGem.GEMClose();
}

void CKingExSECS::SECS_EventReport(int evID, std::map<CString, CString> stringMap)
{

}

void CKingExSECS::SECS_AlarmReport(int alID)
{

}

void CKingExSECS::SECS_ClearAlarmReport(int alID)
{

}

SECSConnectModel CKingExSECS::SECS_SwitchConnectModel(SECSConnectModel targetModel)
{
	int rsp = 0;
	if (targetModel == CONNECT_MODEL_OFFLINE)
	{
		rsp = m_pExGem.GEMSetControlState(Control_EqOffline);
	}

	if (targetModel == CONNECT_MODEL_LOCAL)
	{
		rsp = m_pExGem.GEMSetControlState(Control_Local);
	}

	if (targetModel == CONNECT_MODEL_REMOTE)
	{
		rsp = m_pExGem.GEMSetControlState(Control_Remote);
	}

	if (rsp == 0)
	{
		m_parameters.secsModel = targetModel;
	}

	return m_parameters.secsModel;
}

int CKingExSECS::SECS_SetProcessingCommand(ProcessingState processingState)
{
	return m_pExGem.GEMSetProcessingCommand(processingState);
}

void CKingExSECS::RegisterGemEvent()
{
	/*m_pExGem.GEMSetCallBackHandle(this);
	m_pExGem.RegistOnGEMMessage(OnGEMMessage);
	m_pExGem.RegistOnGEMEvent(OnGEMEvent);
	m_pExGem.RegistOnGEMRemoteEvent(OnGEMRemoteEvent);
	m_pExGem.RegistOnGEMStateEvent(OnGEMStateEvent);
	m_pExGem.RegistOnGEMErrorMessage(OnGEMErrorMessage);
	m_pExGem.RegistOnGEMCommStateChanged(OnGEMCommStateChanged);
	m_pExGem.RegistOnGEMControlStateChanged(OnGEMControlStateChanged);
	m_pExGem.RegistOnGEMProcessingStateChanged(OnGEMProcessingStateChanged);
	m_pExGem.RegistOnGEMErrorEvent(OnGEMErrorEvent);
	m_pExGem.RegistOnGEMLogMessage(OnGEMLogMessage);

	m_pExGem.RegistOnGEMRspAllSvInfo(OnGEMRspAllSVInfo);
	m_pExGem.RegistOnGEMRspAllDvInfo(OnGEMRspAllDVInfo);
	m_pExGem.RegistOnGEMRspAllEcvInfo(OnGEMRspAllEcvInfo);
	m_pExGem.RegistOnGEMRspAllReportInfo(OnGEMRspAllReportInfo);
	m_pExGem.RegistOnGEMRspAllEventInfo(OnGEMRspAllEventInfo);
	m_pExGem.RegistOnGEMRspAllAlarmInfo(OnGEMRspAllAlarmInfo);

	m_pExGem.RegistOnGEMReqPPLoadInquire(OnGEMReqPPLoadInquire);
	m_pExGem.RegistOnGEMRspPPLoadInquire(OnGEMRspPPLoadInquire);
	m_pExGem.RegistOnGEMReqPP(OnGEMReqPP);
	m_pExGem.RegistOnGEMRspPP(OnGEMRspPP);
	m_pExGem.RegistOnGEMReqPPSend(OnGEMReqPPSend);
	m_pExGem.RegistOnGEMRspPPSend(OnGEMRspPPSend);
	m_pExGem.RegistOnGEMReqPPFmt(OnGEMReqPPFmt);
	m_pExGem.RegistOnGEMRspPPFmt(OnGEMRspPPFmt);
	m_pExGem.RegistOnGEMReqPPFmtSend(OnGEMReqPPFmtSend);
	m_pExGem.RegistOnGEMRspPPFmtSend(OnGEMRspPPFmtSend);
	m_pExGem.RegistOnGEMReqPPList(OnGEMReqPPList);
	m_pExGem.RegistOnGEMReqPPDelete(OnGEMReqPPDelete);

	m_pExGem.RegistOnGEMEventSend(OnGEMEventSend);
	m_pExGem.RegistOnGEMReqChangeECV(OnGEMReqChangeECV);
	m_pExGem.RegistOnGEMECVChanged(OnGEMECVChanged);
	m_pExGem.RegistOnGEMRspDateTime(OnGEMRspDateTime);
	m_pExGem.RegistOnGEMReqDateTime(OnGEMReqDateTime);
	m_pExGem.RegistOnGEMReqDateTimeSend(OnGEMReqDateTimeSend);
	m_pExGem.RegistOnGEMRspLoopback(OnGEMRspLoopback);
	m_pExGem.RegistOnGEMReqOnline(OnGEMReqOnline);
	m_pExGem.RegistOnGEMReqOffline(OnGEMReqOffline);
	m_pExGem.RegistOnGEMReqSimpleRemoteCommand(OnGEMReqSimpleRemoteCommand);
	m_pExGem.RegistOnGEMReqRemoteCommand(OnGEMReqRemoteCommand);
	m_pExGem.RegistOnGEMReqEnhancedRemoteCommand(OnGEMReqEnhancedRemoteCommand);
	m_pExGem.RegistOnGEMAlarmEnableStateChanged(OnGEMAlarmEnableStateChanged);
	m_pExGem.RegistOnGEMEventEnableStateChanged(OnGEMEventEnableStateChanged);
	m_pExGem.RegistOnGEMTerminalMessage(OnGEMTerminalMessage);
	m_pExGem.RegistOnGEMTerminalMultiMessage(OnGEMTerminalMultiMessage);
	m_pExGem.RegistOnGEMBroadcast(OnGEMBroadcast);*/
}
