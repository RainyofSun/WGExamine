#include "StdAfx.h"
#include "SECSManager.h"
#include "TaiZhiSECS.h"
#include "KingExSECS.h"

CSECSManager::CSECSManager(void)
{
	m_secs = nullptr;
}

CSECSManager::~CSECSManager(void)
{
	
}

void CSECSManager::SECS_SetCommandParameters(SECSCommandParameters parameters)
{
	m_manufacturner = parameters.manufacturer;
	if (parameters.manufacturer == SECSManufacturers_TaiZhi && m_secs == nullptr)
	{
		CTaiZhiSECS *secs = new CTaiZhiSECS();
		secs->m_parameters = parameters;
		m_secs = secs;
	}

	if (parameters.manufacturer == SECSManufacturers_KingEx && m_secs == nullptr)
	{
		CKingExSECS *secs = new CKingExSECS();
		secs->m_parameters = parameters;
		m_secs = secs;
	}
}

void CSECSManager::SECS_Connect()
{
	if (m_secs != nullptr)
	{
		m_secs->SECS_Connect();
	}
}

void CSECSManager::SECS_Disconnect()
{
	if (m_secs != nullptr)
	{
		m_secs->SECS_Disconnect();
		m_secs = nullptr;
	}
}

void CSECSManager::SECS_EventReport(int evID, std::map<CString, CString> stringMap)
{
	if (m_secs != nullptr)
	{
		m_secs->SECS_EventReport(evID, stringMap);
	}
}

void CSECSManager::SECS_AlarmReport(int alID)
{
	if (m_secs != nullptr)
	{
		m_secs->SECS_AlarmReport(alID);
	}
}

void CSECSManager::SECS_ClearAlarmReport(int alID)
{
	if (m_secs != nullptr)
	{
		m_secs->SECS_ClearAlarmReport(alID);
	}
}

void CSECSManager::SECS_AckReplyInfo(string &strAcktxid,string &strAckeid)
{
	if (m_manufacturner == SECSManufacturers_TaiZhi && m_secs != nullptr)
	{
		CTaiZhiSECS *taiZhi = dynamic_cast<CTaiZhiSECS *>(m_secs);
		CString ackInfo = taiZhi->secsMessage.AckReplyInfo(strAcktxid, strAckeid);
		taiZhi->SECS_SendMessage(ackInfo);
	}
}

void CSECSManager::SECS_SvGetInfo(CString strSvtxid,CString dtrSveid, std::map<CString, CString> svMap)
{
	if (m_manufacturner == SECSManufacturers_TaiZhi && m_secs != nullptr)
	{
		CTaiZhiSECS *taiZhi = dynamic_cast<CTaiZhiSECS *>(m_secs);
		CString svInfo = taiZhi->secsMessage.SvGetInfo(strSvtxid, dtrSveid, svMap);
		taiZhi->SECS_SendMessage(svInfo);
	}
}

SECSConnectModel CSECSManager::SECS_ConnectModel()
{
	return m_secs->m_parameters.secsModel;
}

SECSConnectStatus CSECSManager::SECS_ConnectStatus()
{
	return m_secs->m_parameters.secsStatus;
}

SECSConnectModel CSECSManager::SECS_SwitchModel(SECSConnectModel targetModel, bool sendEvent /* = true */)
{
	m_secs->m_parameters.secsModel = targetModel;
	if (m_manufacturner == SECSManufacturers_TaiZhi && m_secs != nullptr)
	{
		CTaiZhiSECS *taiZhi = dynamic_cast<CTaiZhiSECS *>(m_secs);
		if (sendEvent)
		{
			std::map<CString, CString> tempMap;
			taiZhi->SECS_EventReport(targetModel, tempMap);
		}
	}

	if (m_manufacturner == SECSManufacturers_KingEx && m_secs != nullptr)
	{
		CKingExSECS *king = dynamic_cast<CKingExSECS *>(m_secs);
		king->SECS_SwitchConnectModel(targetModel);
	}

	return m_secs->m_parameters.secsModel;
}

void CSECSManager::SECS_UploadPPList(CArray<CString>* ppids, long nMsgId)
{
	if (m_manufacturner != SECSManufacturers_KingEx || m_secs == nullptr)
	{
		return;
	}

	CKingExSECS *king = dynamic_cast<CKingExSECS *>(m_secs);
	king->SECS_UploadPPList(ppids, nMsgId);
}

void CSECSManager::SECS_UploadPPBody(CString ppBody, CString ppid)
{
	if (m_manufacturner != SECSManufacturers_KingEx || m_secs == nullptr)
	{
		return;
	}

	CKingExSECS *king = dynamic_cast<CKingExSECS *>(m_secs);
	king->SECS_SendPPBody(ppBody, ppid);
}