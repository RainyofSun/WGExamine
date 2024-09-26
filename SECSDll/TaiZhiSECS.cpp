#include "StdAfx.h"
#include "TaiZhiSECS.h"

UINT TaiZhiEventSocketThread(LPVOID lpParameter);

CTaiZhiSECS::CTaiZhiSECS(void)
{
	m_socket = nullptr;
}

CTaiZhiSECS::~CTaiZhiSECS(void)
{
	
}

void CTaiZhiSECS::SECS_Connect()
{
	if (m_socket != nullptr)
	{
		return;
	}

	if (m_parameters.hwndRegisterName.IsEmpty() == TRUE)
	{
		return;
	}
	
	HWND main_hwnd = FindWindow(m_parameters.hwndRegisterName, NULL);
	if (main_hwnd == NULL)
	{
		return;
	}

	m_socket = new CSECSSocket(main_hwnd);

	BOOL bSuccess = m_socket->Create();
	if (bSuccess == FALSE)
	{
		delete m_socket;
		m_socket = nullptr;
		AfxMessageBox("socket create fail");
		return;
	}

	bSuccess = m_socket->Connect(m_parameters.strIp, 12000);
	if (bSuccess == FALSE)
	{
		delete m_socket;
		m_socket = nullptr;
	} 
	else
	{
		m_parameters.secsStatus = SECS_CONNECTED;
		CString sBase = secsMessage.SCESConnectMsg(m_parameters);
		SECS_SendMessage(sBase);
		m_parameters.rpt_txid --;

		resumeSECSThread(TaiZhiEventSocketThread);
	}
}

void CTaiZhiSECS::SECS_Disconnect()
{
	if (m_socket == nullptr)
	{
		return;
	}

	CString sBase = secsMessage.SCESCloseMsg(m_parameters.rpt_txid);
	SECS_SendMessage(sBase);
	m_parameters.rpt_txid --;
	m_parameters.secsStatus = SECS_CLOSE;
	m_parameters.secsModel = CONNECT_MODEL_OFFLINE;

	m_socket->ShutDown(SD_BOTH);
	delete m_socket;
	m_socket = nullptr;
}

void CTaiZhiSECS::SECS_EventReport(int evID, std::map<CString, CString> stringMap)
{
	m_eventArray.Add(evID);
	m_reportStringMap.insert(std::pair<int, std::map<CString, CString>>(evID, stringMap));
}

void CTaiZhiSECS::SECS_AlarmReport(int alID)
{
	m_alarmArray.Add(alID);
}

void CTaiZhiSECS::SECS_ClearAlarmReport(int alID)
{
	m_clearArray.Add(alID);
}

void CTaiZhiSECS::SECS_SendMessage(CString &strSend)
{
	if (m_socket == nullptr || m_parameters.secsStatus != SECS_CONNECTED)
	{
		return;
	}

	CString strSendData = strSend;
	strSendData += ";";
	int nLength = strSendData.GetLength();
	TCHAR *pBuffer = strSendData.GetBuffer(nLength);
	m_socket->Send(pBuffer, nLength);
	strSendData.ReleaseBuffer();
}

/*  消息事件发送  */
UINT TaiZhiEventSocketThread(LPVOID lpParameter)
{
	CTaiZhiSECS *secs = (CTaiZhiSECS *)lpParameter;
	while(!secs->bExitEventSocketThread)
	{
		while (secs->m_eventArray.IsEmpty() == FALSE)
		{
			Sleep(100);
			int eventID = secs->m_eventArray.First();
			std::map<CString, CString> reportValue = secs->m_reportStringMap[eventID];
			CString reportID = "";
			auto isFind = reportValue.find(REPORT_ID_KEY);
			if (isFind != reportValue.end())
			{
				reportID = isFind->second;
				reportValue.erase(REPORT_ID_KEY);
			}

			CString msg = secs->secsMessage.EventReport(to_string(secs->m_parameters.rpt_txid), eventID, reportID, reportValue);
			secs->SECS_SendMessage(msg);
			secs->m_reportStringMap.erase(eventID);
			secs->m_eventArray.RemoveAt(0);
			secs->m_parameters.rpt_txid --;
		}

		while (secs->m_alarmArray.IsEmpty() == FALSE)
		{
			Sleep(100);
			CString msg = secs->secsMessage.AlarmReport(to_string(secs->m_parameters.alm_txid), secs->m_alarmArray.First());
			secs->SECS_SendMessage(msg);
			secs->m_alarmArray.RemoveAt(0);
			secs->m_parameters.alm_txid --;
		}

		while (secs->m_clearArray.IsEmpty() == FALSE)
		{
			Sleep(100);
			CString msg = secs->secsMessage.ClearAlarmReport(to_string(secs->m_parameters.clalm_txid), secs->m_clearArray.First());
			secs->SECS_SendMessage(msg);
			secs->m_clearArray.RemoveAt(0);
			secs->m_parameters.clalm_txid --;
		}
	}

	return 1;
}