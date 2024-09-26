/*----------------------------------------------------------------
 * 版权所有 (c) 北京中电科电子装备有限公司 保留所有权利。
 * 公司名称：北京中电科电子装备有限公司
 * 
 * 创建者：刘冉
 * 创建时间：2024-9-23
 * 版本：V1.0.0
 * 描述：SECS的管理类
 *
 * ----------------------------------------------------------------
 * 修改人：刘冉
 * 时间：2024-9-24
 * 修改说明：
 *	1.完成泰治SECS测试
 * 版本：V1.0.0
 *----------------------------------------------------------------*/
#pragma once
#include "SECSConnectBase.h"

#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT CSECSManager
{
public:
	CSECSManager(void);
	~CSECSManager(void);

	/////////////////////////////////// 通用接口 ////////////////////////////////////////////
	void SECS_SetCommandParameters(SECSCommandParameters parameters);
	void SECS_Connect();
	void SECS_Disconnect();
	void SECS_EventReport(int evID, std::map<CString, CString> stringMap);
	void SECS_AlarmReport(int alID);
	void SECS_ClearAlarmReport(int alID);
	// SECS 当前的模式
	SECSConnectModel SECS_ConnectModel();
	// SECS 连接状态
	SECSConnectStatus SECS_ConnectStatus();

	/////////////////////////////////// 泰治SECS 接口 ///////////////////////////////////////
	void SECS_AckReplyInfo(string &strAcktxid,string &strAckeid);
	void SECS_SvGetInfo(CString strSvtxid,CString dtrSveid, std::map<CString, CString> svMap);
	// 切换 SECS 的模式
	SECSConnectModel SECS_SwitchModel(SECSConnectModel targetModel, bool sendEvent = true);

	/////////////////////////////////// 亚控 SECS 接口 ///////////////////////////////////////
	void SECS_UploadPPList(CArray<CString>* ppids, long nMsgId);
	void SECS_UploadPPBody(CString ppBody, CString ppid);

private:
	CSECSConnectBase *m_secs;
	SECSManufacturers m_manufacturner;
};

