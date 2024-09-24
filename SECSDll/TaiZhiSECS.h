/*----------------------------------------------------------------
 * 版权所有 (c) 北京中电科电子装备有限公司 保留所有权利。
 * 公司名称：北京中电科电子装备有限公司
 * 
 * 创建者：刘冉
 * 创建时间：2024-9-20
 * 版本：V1.0.0
 * 描述：泰治SECS的连接
 *
 * ----------------------------------------------------------------
 * 修改人：
 * 时间：
 * 修改说明：
 * 版本：
 *----------------------------------------------------------------*/
#pragma once
#include "SECSConnectBase.h"
#include "SECSSocket.h"
#include "TaiZhiSECSMessage.h"
#include "SafeArray.h"

class CTaiZhiSECS: public CSECSConnectBase
{
public:
	CTaiZhiSECS(void);
	~CTaiZhiSECS(void);

	// 事件数组
	CSafeArray m_eventArray;
	// 报警数组
	CSafeArray m_alarmArray;
	// 消警数组
	CSafeArray m_clearArray;

	std::map<int, std::map<CString, CString>> m_reportStringMap;

	CTaiZhiSECSMessage secsMessage;

	void SECS_Connect();
	void SECS_Disconnect();
	void SECS_EventReport(int evID, std::map<CString, CString> stringMap);
	void SECS_AlarmReport(int alID);
	void SECS_ClearAlarmReport(int alID);
	void SECS_SendMessage(CString &strSend);

private:
	CSECSSocket *m_socket;
};

