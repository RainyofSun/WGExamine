/*----------------------------------------------------------------
 * 版权所有 (c) 北京中电科电子装备有限公司 保留所有权利。
 * 公司名称：北京中电科电子装备有限公司
 * 
 * 创建者：刘冉
 * 创建时间：2024-9-20
 * 版本：V1.0.0
 * 描述：泰治SECS消息
 *
 * ----------------------------------------------------------------
 * 修改人：
 * 时间：
 * 修改说明：
 *
 * 版本：
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
	 * 功能：读取事件配置
	 * 输入：
			param1: （CString）配置文件路径
	 */ 
	void SECSLoadReportConfig(CString filePath);

	/**
	 * 功能：SCES建连消息
		param1: （SECSCommandParameters） 初始参数
	 * 输出：
			（CString）消息体
	 */ 

	CString SCESConnectMsg(SECSCommandParameters paramters);

	/**
	 * 功能：SCES断开连接消息
		param1: (int) 消息id
	 * 输出：
			(CString)消息体
	 */ 
	CString SCESCloseMsg(int txid);
	
	/**
	 * 功能：ACK 回复
	 */ 
	CString AckReplyInfo(string &strAcktxid,string &strAckeid);

	/**
	 * 功能：查询SV变量
	 */ 
	CString SvGetInfo(CString strSvtxid,CString dtrSveid, std::map<CString, CString> svMap);

	/**
	 * 功能：事件上报
	 * 输入：
			param1: etxid 消息ID
			param2: ev 事件ID
			param3: reportID 事件绑定的上报ID
			param4: bindingValue 绑定的事件：801：20240920
	 * 输出：
			CString 拼接之后的字符串
	 */ 
	CString EventReport(string etxid, int ev, CString reportID, std::map<CString, CString> bindingValue);

	/**
	 * 功能：报警事件上报
	 */ 
	CString AlarmReport(string etxid,int alarmID);

	/**
	 * 功能：消警事件上报
	 */ 
	CString ClearAlarmReport(string etxid, int alarmID);

private:
	CString replyInfo(CString &strtype,CString &strmeth,CString &ntxid,CString &neid,Json::Value jvdata_sr);
};

