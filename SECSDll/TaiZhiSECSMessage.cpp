#include "StdAfx.h"
#include "TaiZhiSECSMessage.h"


CTaiZhiSECSMessage::CTaiZhiSECSMessage(void)
{
}


CTaiZhiSECSMessage::~CTaiZhiSECSMessage(void)
{
}

CString CTaiZhiSECSMessage::SCESConnectMsg(SECSCommandParameters paramters)
{
	CString str = "";
	Json::Value jsonObj;
	jsonObj["IP"] = paramters.strIp.GetBuffer();
	jsonObj["Port"] = paramters.strPort.GetBuffer();
	jsonObj["DeviceID"] = paramters.strDeviceId.GetBuffer();
	jsonObj["T3"] = paramters.strSecsT3.GetBuffer();
	jsonObj["T5"] = paramters.strSecsT5.GetBuffer();
	jsonObj["T6"] = paramters.strSecsT6.GetBuffer();
	jsonObj["T7"] = paramters.strSecsT7.GetBuffer();
	jsonObj["T8"] = paramters.strSecsT8.GetBuffer();
	jsonObj["LinkTest"] = paramters.strSecsLinkTime.GetBuffer();
	CString strBaseType = "BaseComm";
	CString strBathMeth = "init";
	CString strBaseTxid = to_string(paramters.rpt_txid).c_str();
	CString strBaseEid = "1";

	str = replyInfo(strBaseType, strBathMeth, strBaseTxid, strBaseEid, jsonObj);

	return str;
}

CString CTaiZhiSECSMessage::SCESCloseMsg(int txid)
{
	CString strBaseType = "BaseComm";
	CString strBathMeth = "Disable";
	CString strBaseTxid;
	CString strBaseEid = "1";
	strBaseTxid.Format("%d", txid);

	Json::Value jsonObj;

	CString str = replyInfo(strBaseType, strBathMeth, strBaseTxid, strBaseEid, jsonObj);

	return str;
}

CString CTaiZhiSECSMessage::AckReplyInfo(string &strAcktxid,string &strAckeid)
{
	CString str = "";
	CString strAckType = "REPLY";
	CString strAckMeth = "ACK";

	Json::Value jvdata_ack;

	str = replyInfo(strAckType, strAckMeth, CString(strAcktxid.c_str()), CString(strAckeid.c_str()), jvdata_ack);

	return str;
}

CString CTaiZhiSECSMessage::SvGetInfo(CString strSvtxid,CString dtrSveid, std::map<CString, CString> svMap)
{
	CString strMsg = "";
	std::map<CString, CString>::iterator iter;
	Json::Value svArrayJson;
	for (iter = svMap.begin(); iter != svMap.end(); ++iter) 
	{
		Json::Value tempJson;
		CString tempStr;
		tempStr.Format("%s", iter->first);
		tempJson["SVID"] = tempStr.GetBuffer();
		tempStr.Format("%s", iter->second);
		tempJson["SV"] = tempStr.GetBuffer();
		svArrayJson.append(tempJson);
	}

	CString strListType = "REPLY";
	CString strListMeth = "ANS";

	strMsg = replyInfo(strListType, strListMeth, strSvtxid, dtrSveid, svArrayJson);

	return strMsg;
}

CString CTaiZhiSECSMessage::EventReport(string etxid, int ev, CString reportID, std::map<CString, CString> bindingValue)
{
	CString str = "";
	Json::Value jsonBaseObj, svArrayJson;
	CString strEventType = "Notification";
	CString strEventMethod = "EventReport";
	jsonBaseObj["EVENTID"] = to_string((long long) ev);
	if (reportID.IsEmpty() == FALSE)
	{
		jsonBaseObj["REPORTID"] = reportID.GetBuffer();
	}

	std::map<CString, CString>::iterator iter;
	for (iter = bindingValue.begin(); iter != bindingValue.end(); ++iter) 
	{
		Json::Value tempJson;
		CString tempStr;
		tempStr.Format("%s", iter->first);
		tempJson["SVID"] = tempStr.GetBuffer();
		tempStr.Format("%s", iter->second);
		tempJson["SV"] = tempStr.GetBuffer();
		svArrayJson.append(tempJson);
	}
	
	jsonBaseObj["SVList"] = svArrayJson;
	CString eid = "1";

	str = replyInfo(strEventType, strEventMethod, CString(etxid.c_str()), eid, jsonBaseObj);

	return str;
}

CString CTaiZhiSECSMessage::AlarmReport(string etxid,int alarmID)
{
	CString str = "";
	Json::Value jsonBaseObj;
	CString strEventType = "Notification";
	CString strEventMethod = "alarm";
	jsonBaseObj["ALID"] = to_string((long long) alarmID);
	jsonBaseObj["ALCD"] = "1";
	CString eid = "1";

	str = replyInfo(strEventType, strEventMethod, CString(etxid.c_str()), eid, jsonBaseObj);

	return str;
}

CString CTaiZhiSECSMessage::ClearAlarmReport(string etxid, int alarmID)
{
	CString str = "";
	Json::Value jsonBaseObj;
	CString strEventType = "Notification";
	CString strEventMethod = "alarm";
	CString eid = "1";
	jsonBaseObj["ALID"] = to_string((long long) alarmID);
	jsonBaseObj["ALCD"] = "1";
	
	str = replyInfo(strEventType, strEventMethod, CString(etxid.c_str()), eid, jsonBaseObj);

	return str;
}

CString CTaiZhiSECSMessage::replyInfo(CString &strtype,CString &strmeth,CString &ntxid,CString &neid,Json::Value jvdata_sr)
{
	CString strSendData = "";
	Json::Value eventSendMes;
	eventSendMes["type"] = strtype.GetBuffer();
	eventSendMes["method"] = strmeth.GetBuffer();
	eventSendMes["txid"] = ntxid.GetBuffer();
	eventSendMes["eid"] = neid.GetBuffer();
	eventSendMes["data"] = jvdata_sr;

	JsonTool::JsonObjectToString(eventSendMes, strSendData);

	return strSendData;
}
