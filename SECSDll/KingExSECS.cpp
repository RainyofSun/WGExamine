#include "StdAfx.h"
#include "KingExSECS.h"

UINT KingEventSocketThread(LPVOID lpParameter);

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

	// 初始化完毕，启动亚控
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
	// 开启事件线程
	resumeSECSThread(KingEventSocketThread);
	m_parameters.secsStatus = SECS_CONNECTED;
	
	if (m_parameters.hwndRegisterName.IsEmpty() == TRUE)
	{
		return;
	}

	m_hwnd = FindWindow(m_parameters.hwndRegisterName, NULL);
}

void CKingExSECS::SECS_Disconnect()
{
	// 关闭连接
	m_pExGem.GEMSetConnectionEnable(false);
	// 停止亚控
	m_pExGem.GEMStop();
	// 关闭
	m_pExGem.GEMClose();
	m_parameters.secsStatus = SECS_CLOSE;
}

void CKingExSECS::SECS_EventReport(int evID, std::map<CString, CString> stringMap)
{
	m_eventArray.Add(evID);
}

void CKingExSECS::SECS_AlarmReport(int alID)
{
	m_alarmArray.Add(alID);
}

void CKingExSECS::SECS_ClearAlarmReport(int alID)
{
	m_clearArray.Add(alID);
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

int CKingExSECS::SECS_BindingEquipmentECValue(long *pnVid, string *psValue)
{
	if (m_parameters.secsStatus != SECS_CONNECTED)
	{
		return -1;
	}
	return m_pExGem.GEMSetEcvValue(1, pnVid, psValue);
}

int CKingExSECS::SECS_BindingEquipmentSVValue(long *pnVid, string *psValue)
{
	if (m_parameters.secsStatus != SECS_CONNECTED)
	{
		return -1;
	}
	return m_pExGem.GEMSetVariable(1, pnVid, psValue);
}

//////////////////////////////// 配方指令 //////////////////////////////////////////
int CKingExSECS::SECS_PPChanged(SECSRecipeOperation operation, CString ppId)
{
	if (ppId.IsEmpty() == TRUE)
	{
		return -1;
	}

	return m_pExGem.GEMSetPPChanged(operation, ppId.GetBuffer());
}

int CKingExSECS::SECS_PPSelected(CString ppId)
{
	if (ppId.IsEmpty() == TRUE)
	{
		return -1;
	}

	return m_pExGem.GEMSetPPSelected(ppId.GetBuffer());
}

int CKingExSECS::SECS_UploadPPList(CArray<CString>* ppids, long nMsgId)
{
	int size = ppids->GetSize();
	string* ppidsArray = new string[size + 1];
	for (int i = 0; i < size; i ++)
	{
		ppidsArray[i] = ppids->GetAt(i);
	}

	return m_pExGem.GEMRspPPList(nMsgId, size, ppidsArray);
}

int CKingExSECS::SECS_SendPPBody(CString strPPBody, CString strPPid)
{
	if (strPPBody.IsEmpty() == TRUE || strPPid.IsEmpty() == TRUE)
	{
		return -1;
	}

	BYTE* pData = new BYTE[strPPBody.GetLength() + 1];
	LPSTR pStr = strPPBody.GetBuffer(strPPBody.GetLength());
	memcpy(pData, pStr, strPPBody.GetLength());

	DWORD nLen = strlen((char *)pData);

	return m_pExGem.GEMReqPPSend(strPPid.GetBuffer(), nLen, pData);
}

void CKingExSECS::RegisterGemEvent()
{
	m_pExGem.GEMSetCallBackHandle(this);
	m_pExGem.RegistOnGEMMessage(OnGEMMessage);
	m_pExGem.RegistOnGEMEvent(OnGEMEvent);
	m_pExGem.RegistOnGEMRemoteEvent(OnGEMRemoteEvent);

	m_pExGem.RegistOnGEMReqPP(OnGEMReqPP);
	m_pExGem.RegistOnGEMReqPPEx(OnGEMReqPPEx);
	m_pExGem.RegistOnGEMReqPPSend(OnGEMReqPPSend);
	m_pExGem.RegistOnGEMReqPPFmt(OnGEMReqPPFmt);
	m_pExGem.RegistOnGEMReqPPFmtSend(OnGEMReqPPFmtSend);
	m_pExGem.RegistOnGEMReqPPList(OnGEMReqPPList);
	m_pExGem.RegistOnGEMReqPPDelete(OnGEMReqPPDelete);

	m_pExGem.RegistOnGEMReqOnline(OnGEMReqOnline);
	m_pExGem.RegistOnGEMReqOffline(OnGEMReqOffline);
	m_pExGem.RegistOnGEMReqRemoteCommand(OnGEMReqRemoteCommand);
	m_pExGem.RegistOnGEMReqEnhancedRemoteCommand(OnGEMReqEnhancedRemoteCommand);
	m_pExGem.RegistOnGEMTerminalMessage(OnGEMTerminalMessage);
}

/*  消息事件发送  */
UINT KingEventSocketThread(LPVOID lpParameter)
{
	CKingExSECS *secs = (CKingExSECS *)lpParameter;
	while(!secs->bExitEventSocketThread)
	{
		while (secs->m_eventArray.IsEmpty() == FALSE)
		{
			Sleep(100);
			int eventID = secs->m_eventArray.First();
			int rsp = secs->m_pExGem.GEMSetEvent(eventID);
			if (rsp == 0)
			{
				secs->m_eventArray.RemoveAt(0);
			}
		}

		while (secs->m_alarmArray.IsEmpty() == FALSE)
		{
			Sleep(100);
			int alarmID = secs->m_alarmArray.First();
			int rsp = secs->m_pExGem.GEMSetAlarm(alarmID, TRUE);
			if (rsp == 0)
			{
				secs->m_alarmArray.RemoveAt(0);
			}
		}

		while (secs->m_clearArray.IsEmpty() == FALSE)
		{
			Sleep(100);
			int clearAlarmID = secs->m_clearArray.First();
			int rsp = secs->m_pExGem.GEMSetAlarm(clearAlarmID, FALSE);
			if (rsp == 0)
			{
				secs->m_clearArray.RemoveAt(0);
			}
		}
	}

	return 1;
}

void CKingExSECS::OnGEMMessage(CBHANDLE hdcb, cSemion *pMessage)
{

}

void CKingExSECS::OnGEMEvent(CBHANDLE hdcb, short nEventId, long lParam)
{

}

void CKingExSECS::OnGEMRemoteEvent(CBHANDLE hdcb, WORD nPort, short nEventId, long lParam)
{

}

void CKingExSECS::OnGEMReqPP(CBHANDLE hdcb, long nMsgID, string sPpid)
{

}

void CKingExSECS::OnGEMReqPPEx(CBHANDLE hdcb, long nMsgId, string sPpid, string sRecipePath)
{

}

void CKingExSECS::OnGEMReqPPSend(CBHANDLE hdcb, long nMsgid, string sPpid, DWORD nLength, unsigned char* pbBody)
{

}

void CKingExSECS::OnGEMReqPPFmt(CBHANDLE hdCB, long nMsgId, string sPpid)
{

}

void CKingExSECS::OnGEMReqPPFmtSend(CBHANDLE hdCB, long nMsgId, string sPpid, string sMdln, string sSoftRev, DWORD nCount, string* psCCode, DWORD* pnParamCount, string* psParamNames)
{

}

void CKingExSECS::OnGEMReqPPList(CBHANDLE hdCB, long nMsgId)
{
	CKingExSECS *pThis = (CKingExSECS *)hdCB;
	if (pThis->m_hwnd == NULL)
	{
		return;
	}

	PostMessage(pThis->m_hwnd, WM_YK_REQ_PP_LIST, 0, nMsgId);
}

void CKingExSECS::OnGEMReqPPDelete(CBHANDLE hdCB, long nMsgId, DWORD nCount, string* psPpid)
{
	CKingExSECS *pThis = (CKingExSECS *)hdCB;
	if (pThis->m_hwnd == NULL)
	{
		return;
	}

	CArray<CString>* deletePPIDs = new CArray<CString>();
	for (DWORD i = 0; i < nCount; i++)
	{
		deletePPIDs->Add(toCString(psPpid[i]));
	}
	pThis->m_pExGem.GEMRspPPDelete(nMsgId, 0);

	PostMessage(pThis->m_hwnd, WM_YK_DELETE_PP, (WPARAM)deletePPIDs, 0);
}

void CKingExSECS::OnGEMReqOnline(CBHANDLE hdCB, long lMsgId, long lFromState, long lToState)
{
	CKingExSECS *pThis = (CKingExSECS *)hdCB;
	pThis->m_parameters.secsModel = CONNECT_MODEL_LOCAL;
	pThis->m_pExGem.GEMRspOnline(lMsgId, 0);
	if (pThis->m_hwnd == NULL)
	{
		return;
	}

	PostMessage(pThis->m_hwnd, WM_YK_SECS_MODE_CHANGE, 0, 0);
}

void CKingExSECS::OnGEMReqOffline(CBHANDLE hdCB, long lMsgId, long lFromState, long lToState)
{
	CKingExSECS *pThis = (CKingExSECS *)hdCB;
	pThis->m_parameters.secsModel = CONNECT_MODEL_OFFLINE;
	pThis->m_pExGem.GEMRspOffline(lMsgId, 0);
	if (pThis->m_hwnd == NULL)
	{
		return;
	}

	PostMessage(pThis->m_hwnd, WM_YK_SECS_MODE_CHANGE, 0, 0);
}

void CKingExSECS::OnGEMReqRemoteCommand(CBHANDLE hdCB, long nMsgId, string sRcmd, DWORD nCount, string* psNames, string* psVals)
{
	CKingExSECS *pThis = (CKingExSECS *)hdCB;
	YTRemoteCommandStruct *cmdStruct = new YTRemoteCommandStruct;
	cmdStruct->sRcmd = toCString(sRcmd);
	cmdStruct->psVals = psVals;
	cmdStruct->sRcmdPanelName = psNames;
	
	byte* pCpAck = new byte[nCount + 1];
	for (DWORD i = 0; i < nCount; i ++)
	{
		pCpAck[i] = 0;
	}
	pThis->m_pExGem.GEMRspRemoteCommand(nMsgId, 0, nCount, psNames, pCpAck);
	
	if (pThis->m_hwnd == NULL)
	{
		return;
	}

	PostMessage(pThis->m_hwnd, WM_YK_REMOTE_COMMAND, (WPARAM)cmdStruct, 0);
}

void CKingExSECS::OnGEMReqEnhancedRemoteCommand(CBHANDLE hdCB, long nMsgId, string sObjspec, string sRcmd, DWORD nCount, string* psNames, string* psVals)
{

}

void CKingExSECS::OnGEMTerminalMessage(CBHANDLE hdCB, long nMsgId,long nTid, string sMsg)
{
	CKingExSECS *pThis = (CKingExSECS *)hdCB;

	if (pThis->m_hwnd == NULL)
	{
		return;
	}

	// PostMessage 传递字符串，因为PostMessage 是异步操作，会导致字符串提前释放，传递的字符串会变乱码
	SendMessage(pThis->m_hwnd, WM_YK_TERMINAL_MSG, 0, (LPARAM)(LPCTSTR)toCString(sMsg));
}