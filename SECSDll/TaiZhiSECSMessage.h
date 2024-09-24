/*----------------------------------------------------------------
 * ��Ȩ���� (c) �����е�Ƶ���װ�����޹�˾ ��������Ȩ����
 * ��˾���ƣ������е�Ƶ���װ�����޹�˾
 * 
 * �����ߣ���Ƚ
 * ����ʱ�䣺2024-9-20
 * �汾��V1.0.0
 * ������̩��SECS��Ϣ
 *
 * ----------------------------------------------------------------
 * �޸��ˣ�
 * ʱ�䣺
 * �޸�˵����
 *
 * �汾��
 *----------------------------------------------------------------*/
#pragma once
#include "SECSConfig.h"
#include "JsonTool.h"

class CTaiZhiSECSMessage
{
public:
	CTaiZhiSECSMessage(void);
	~CTaiZhiSECSMessage(void);

	/**
	 * ���ܣ���ȡ�¼�����
	 * ���룺
			param1: ��CString�������ļ�·��
	 */ 
	void SECSLoadReportConfig(CString filePath);

	/**
	 * ���ܣ�SCES������Ϣ
		param1: ��SECSCommandParameters�� ��ʼ����
	 * �����
			��CString����Ϣ��
	 */ 

	CString SCESConnectMsg(SECSCommandParameters paramters);

	/**
	 * ���ܣ�SCES�Ͽ�������Ϣ
		param1: (int) ��Ϣid
	 * �����
			(CString)��Ϣ��
	 */ 
	CString SCESCloseMsg(int txid);
	
	/**
	 * ���ܣ�ACK �ظ�
	 */ 
	CString AckReplyInfo(string &strAcktxid,string &strAckeid);

	/**
	 * ���ܣ���ѯSV����
	 */ 
	CString SvGetInfo(CString strSvtxid,CString dtrSveid, std::map<CString, CString> svMap);

	/**
	 * ���ܣ��¼��ϱ�
	 * ���룺
			param1: etxid ��ϢID
			param2: ev �¼�ID
			param3: reportID �¼��󶨵��ϱ�ID
			param4: bindingValue �󶨵��¼���801��20240920
	 * �����
			CString ƴ��֮����ַ���
	 */ 
	CString EventReport(string etxid, int ev, CString reportID, std::map<CString, CString> bindingValue);

	/**
	 * ���ܣ������¼��ϱ�
	 */ 
	CString AlarmReport(string etxid,int alarmID);

	/**
	 * ���ܣ������¼��ϱ�
	 */ 
	CString ClearAlarmReport(string etxid, int alarmID);

private:
	CString replyInfo(CString &strtype,CString &strmeth,CString &ntxid,CString &neid,Json::Value jvdata_sr);
};

