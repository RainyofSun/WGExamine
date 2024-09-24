#pragma once

enum SECSManufacturers
{
	SECSManufacturers_TaiZhi,
	SECSManufacturers_KingEx
};

enum SECSConnectModel
{
	// ����ģʽ
	CONNECT_MODEL_OFFLINE = 42,
	// ����ģʽ
	CONNECT_MODEL_LOCAL = 44,
	// Զ��ģʽ
	CONNECT_MODEL_REMOTE = 45 
};

enum SECSConnectStatus
{
	// ������
	SECS_CONNECTED,
	// ���ӹر�
	SECS_CLOSE
};

struct SECSCommandParameters 
{
	CString strIp;
	CString strPort;
	CString strDeviceId;
	CString strSecsT3;
	CString strSecsT5;
	CString strSecsT6;
	CString strSecsT7;
	CString strSecsT8;
	CString strSecsLinkTime;
	CString strTerlMessage;
	long long int rpt_txid;
	long long int alm_txid;
	long long int clalm_txid;
	SECSConnectStatus secsStatus;
	SECSConnectModel secsModel;
	SECSManufacturers manufacturer;
	// ������Ϣ�ص����ڵ�ע����
	CString hwndRegisterName;
	// ��̫�����ļ�·��
	CString kingKGPRJFilePath;
	// ��̫�����䷽·��
	CString kingRecipeFilePath;

	SECSCommandParameters()
	{
		strIp = "127.0.0.1";
		strDeviceId = "1";
		strPort = "5000";
		strSecsT3 = "45";
		strSecsT5 = "10";
		strSecsT6 = "10";
		strSecsT7 = "5";
		strSecsT8 = "10";
		strSecsLinkTime = "1";
		hwndRegisterName = "";
		rpt_txid = -1;
		alm_txid = -500000;
		clalm_txid = -1000000;
		secsStatus = SECS_CLOSE;
		secsModel = CONNECT_MODEL_OFFLINE;
		manufacturer = SECSManufacturers_TaiZhi;
	}
};

#define WM_SOCKET_RECEIVE	WM_USER+100
#define WM_SOCKET_CLOSE		WM_USER+101

// �����ַ�
const static CString REPORT_ID_KEY = "REPORT_ID";