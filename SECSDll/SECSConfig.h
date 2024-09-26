#pragma once
#include <string>

enum SECSManufacturers
{
	SECSManufacturers_TaiZhi,
	SECSManufacturers_KingEx
};

enum SECSConnectModel
{
	// 离线模式
	CONNECT_MODEL_OFFLINE = 42,
	// 本地模式
	CONNECT_MODEL_LOCAL = 44,
	// 远端模式
	CONNECT_MODEL_REMOTE = 45 
};

enum SECSConnectStatus
{
	// 已连接
	SECS_CONNECTED,
	// 连接关闭
	SECS_CLOSE
};

enum SECSRecipeOperation 
{
	SECSRecipeOperation_Create = 1,
	SECSRecipeOperation_Edit,
	SECSRecipeOperation_Delete
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
	// 接收消息回调窗口的注册名
	CString hwndRegisterName;
	// 亚控配置文件路径
	CString kingKGPRJFilePath;
	// 亚控配置配方路径
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

////////////////////////////// 泰治 SECS 消息 ////////////////////////////////////////////
#define WM_TAIZHI_SOCKET_RECEIVE	WM_USER+100
#define WM_TAIZHI_SOCKET_CLOSE		WM_USER+101
////////////////////////////// 亚控 SECS 消息 ////////////////////////////////////////////
#define WM_YK_REMOTE_COMMAND		WM_USER+200
// secs online、offline 状态切换
#define WM_YK_SECS_MODE_CHANGE		WM_USER+201
// 查询配方列表
#define WM_YK_REQ_PP_LIST			WM_USER+202
// 删除配方
#define WM_YK_DELETE_PP				WM_USER+203
// 终端消息
#define WM_YK_TERMINAL_MSG			WM_USER+204

////////////////////////////// 亚控消息透传结构体 ////////////////////////////////////////////
// 远端指令结构体
struct YTRemoteCommandStruct 
{
	// 指令集
	CString sRcmd;
	std::string* sRcmdPanelName;
	std::string* psVals; 
};

// 常量字符
const static CString REPORT_ID_KEY = "REPORT_ID";