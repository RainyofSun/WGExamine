/*----------------------------------------------------------------
 * 版权所有 (c) 北京中电科电子装备有限公司 保留所有权利。
 * 公司名称：北京中电科电子装备有限公司
 * 
 * 创建者：刘冉
 * 创建时间：2024-9-24
 * 版本：V1.0.0
 * 描述：
 *		亚控SECS控制
 * ----------------------------------------------------------------
 * 修改人：
 * 时间：
 * 修改说明：
 * 1.sv变量的绑定逻辑
   3.配方操作删除、参数修改逻辑
 * 版本：
 *----------------------------------------------------------------*/
#pragma once
#include "SECSConnectBase.h"
#include "KingExGem.h"
#include "KingExGemDefine.h"
#include "Helper.h"

class CKingExSECS: public CSECSConnectBase
{
public:
	CKingExSECS(void);
	~CKingExSECS(void);
	
	void SECS_Connect();
	void SECS_Disconnect();
	void SECS_EventReport(int evID, std::map<CString, CString> stringMap);
	void SECS_AlarmReport(int alID);
	void SECS_ClearAlarmReport(int alID); 

	/**
	 * 功能：SECS 状态切换
	 * 输入：
			param1: (SECSConnectModel) 要切换到的模式
	 * 输出：
			(SECSConnectModel)切换之后的模式
	 */ 
	SECSConnectModel SECS_SwitchConnectModel(SECSConnectModel targetModel);

	/**
	 * 功能：设置设备状态
	 * 输入：
			param1: (ProcessingState) 设备状态
	 */ 
	int SECS_SetProcessingCommand(ProcessingState processingState);
	
	/**
	 * 功能：绑定设备常量值
	 * 输入：
			param1: （pnVid）要设置的常量ID
			param2: （psValue）要设置的常量值
	 * 输出：
			int 是否设置成功 0 - 成功
	 */ 
	int SECS_BindingEquipmentECValue(long *pnVid, string *psValue);

	/**
	 * 功能：绑定设备的变量值
	 * 输入：
			param1: （pnVid）要设置的变量id
			param2: （psValue）要设置的变量值
	 * 输出：
			int 是否设置成功， 0 - 成功
	 */ 
	int SECS_BindingEquipmentSVValue(long *pnVid, string *psValue);

	//////////////////////////////// 配方指令 //////////////////////////////////////////
	/**
	 * 功能：配方状态改变
	 * 输入：
			param1: (SECSRecipeOperation) 配方状态
			param2: (ppID) 配方名字
	 * 输出：
			int 是否设置成功 0 - 成功
	 */ 
	int SECS_PPChanged(SECSRecipeOperation operation, CString ppId);

	/**
	 * 功能：选中配方
	 * 输入：
			param1: (ppid) 配方名字
	 * 输出：
			int 是否设置成功 0 - 成功	
	 */ 
	int SECS_PPSelected(CString ppId);

	/**
	 * 功能：上传配方列表
	 * 输入：
			param1: (ppids) 配方列表
	 * 输出：
			int 是否上传成功 0 - 成功	
	 */ 
	int SECS_UploadPPList(CArray<CString>* ppids, long nMsgId);

	/**
	 * 功能：上传配方（字符串）
	 * 输入：
			param1: (strPPBody) 配方内容，转成json字符串发送
			param2: (strPPid) 配方名字
	 * 输出：
			int 是否上传成功 0 - 成功
	 */ 
	int SECS_SendPPBody(CString strPPBody, CString strPPid);

protected:
	///////////////////////////////// 消息回调 /////////////////////////////////////////
	static void OnGEMMessage(CBHANDLE hdcb, cSemion *pMessage);
	static void OnGEMEvent(CBHANDLE hdcb, short nEventId, long lParam);
	static void OnGEMRemoteEvent(CBHANDLE hdcb, WORD nPort, short nEventId, long lParam);
	// 非配方标准请求回调
	static void OnGEMReqPP(CBHANDLE hdcb, long nMsgID, string sPpid);
	// 请求文件非标准配方回调
	static void OnGEMReqPPEx(CBHANDLE hdcb, long nMsgId, string sPpid, string sRecipePath);
	// 请求发送非标准配方回调
	static void OnGEMReqPPSend(CBHANDLE hdcb, long nMsgid, string sPpid, DWORD nLength, unsigned char* pbBody);
	static void OnGEMReqPPFmt(CBHANDLE hdCB, long nMsgId, string sPpid);
	static void OnGEMReqPPFmtSend(CBHANDLE hdCB, long nMsgId, string sPpid, string sMdln, string sSoftRev, DWORD nCount, string* psCCode, DWORD* pnParamCount, string* psParamNames);
	static void OnGEMReqPPList(CBHANDLE hdCB, long nMsgId);
	static void OnGEMReqPPDelete(CBHANDLE hdCB, long nMsgId, DWORD nCount, string* psPpid);
	static void OnGEMReqOnline(CBHANDLE hdCB, long lMsgId, long lFromState, long lToState);
	static void OnGEMReqOffline(CBHANDLE hdCB, long lMsgId, long lFromState, long lToState);
	static void OnGEMReqRemoteCommand(CBHANDLE hdCB, long nMsgId, string sRcmd, DWORD nCount, string* psNames, string* psVals);
	static void OnGEMReqEnhancedRemoteCommand(CBHANDLE hdCB, long nMsgId, string sObjspec, string sRcmd, DWORD nCount, string* psNames, string* psVals);
	static void OnGEMTerminalMessage(CBHANDLE hdCB, long nMsgId,long nTid, string sMsg);

private:
	void RegisterGemEvent();

public:
	KingExGem m_pExGem;	
	HWND m_hwnd;
};

