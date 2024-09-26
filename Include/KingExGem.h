//=====================================================================================================//
/// <summary>
///		SECS/GEM Protocol EQ Side API.
/// </summary>
///	<file>
///		项目名: KingExGem
///		文件名: KingExGem.h
///		作  者: bo.tang
///	</file>
///	<copyright>
/// 	本代码所有版权为北京亚控科技所有，任何个人或者组织不得以任何方式复制、转载以挪作
/// 他用，否则将构成对北京亚控科技的产权知识侵权。
///	
///		联系: http://www.kingview.com/
///	</copyright>
///	<versions>
///		<version>
///			V2.0 : 基于v1.8版本升级
///		</version>
///	</versions>
//=====================================================================================================//

#pragma once
#ifdef KIINGEXGEM_EXPORTS
#define KINGEXGEM_API __declspec(dllexport)
#else
#define KINGEXGEM_API __declspec(dllimport)
#endif

#include "KingExGemDefine.h"

class Gem;

class KINGEXGEM_API KingExGem
{
public:
	KingExGem(void);
	~KingExGem(void);


public:

	//======================================================================================================//
	// 1. 主调接口
	//======================================================================================================//
#pragma region 主调接口

	/// <summary>
	///  初始化设置
	/// </summary>
	///
	long GEMInitialize(string strProjectPath);
	long GEMStart();
	long GEMStop();
	long GEMClose();

	/// <summary>
	///  可连接性,控制状态 和 处理状态
	/// </summary>
	///
	long GEMSetConnectionEnable(BOOL bState);
	long GEMSetControlState(long nState);
	long GEMSetProcessingCommand(long nCommand);
	long GEMReqOnlineTest();
	long GEMRspOffline(long nMsgId, BYTE bAck);
	long GEMRspOnline(long nMsgId, BYTE bAck);
	long GEMReqLoopDiagnostic(DWORD nCount, BYTE *pbABS);								

	/// <summary>
	///  数据组帧
	/// </summary>
	///
	static cSemion* GEMMakeObject(bool bMessage = true);
	static cSemion* GEMCopyObject(cSemion* hdObject);
	static void GEMCloseObject(cSemion* hdObject);
	static long GEMUsingStringSetItem(cSemion* hdObject, BYTE bItemType, string strValue);
	static long GEMSetListItem(cSemion* hdObject, DWORD nCount);
	static long GEMSetAsciiItem(cSemion* hdObject, const char * pchValue, DWORD nCount);
	static long GEMSetAsciiItem(cSemion* hdObject, string sValue);
	static long GEMSetBoolItem(cSemion* hdObject, BYTE * pbValue, DWORD nCount);
	static long GEMSetBinaryItem(cSemion* hdObject, BYTE * pbValue, DWORD nCount);
	static long GEMSetInt1Item(cSemion* hdObject, const char * pchValue, DWORD nCount);
	static long GEMSetInt2Item(cSemion* hdObject, short * psiValue, DWORD nCount);
	static long GEMSetInt4Item(cSemion* hdObject, long * plValue, DWORD nCount);
	static long GEMSetInt8Item(cSemion* hdObject, __int64 * pllValue, DWORD nCount);
	static long GEMSetUint1Item(cSemion* hdObject, BYTE * pbValue, DWORD nCount);
	static long GEMSetUint2Item(cSemion* hdObject, unsigned short * pusValue, DWORD nCount);
	static long GEMSetUint4Item(cSemion* hdObject, unsigned long * pulValue, DWORD nCount);
	static long GEMSetUint8Item(cSemion* hdObject, unsigned __int64 * pullValue, DWORD nCount);
	static long GEMSetFloat4Item(cSemion* hdObject, float * pfltValue, DWORD nCount);
	static long GEMSetFloat8Item(cSemion* hdObject, double * pdbValue, DWORD nCount);

	/// <summary>
	///  数据解析
	/// </summary>
	///
	static long GEMLoadSecsMsg(cSemion* hdObject, short &siDevId, BYTE &bStrm, BYTE &bFunc, long &nSysbyte,  BYTE &bWbit );
	static long GEMGetItemToString(cSemion* hdObject, string &strValue);
	static long GEMGetListItem(cSemion* hdObject, DWORD &nCount);
	static long GEMGetNextItemCount(cSemion* hdObject, DWORD& nCount);
	static long GEMGetAsciiItem(cSemion* hdObject, signed char * pchValue, DWORD nSize, DWORD &nCount);
	static long GEMGetAsciiItem(cSemion* hdObject, string &strValue);
	static long GEMGetBinaryItem(cSemion* hdObject, BYTE * pbValue, DWORD nSize, DWORD &nCount);
	static long GEMGetBoolItem(cSemion* hdObject, BYTE * pbValue, DWORD nSize, DWORD &nCount);
	static long GEMGetInt1Item(cSemion* hdObject, signed char * pchValue, DWORD nSize, DWORD &nCount);
	static long GEMGetInt2Item(cSemion* hdObject, short * psiValue, DWORD nSize, DWORD &nCount);
	static long GEMGetInt4Item(cSemion* hdObject, long * plValue, DWORD nSize, DWORD &nCount);
	static long GEMGetInt8Item(cSemion* hdObject, __int64 * pllValue, DWORD nSize, DWORD &nCount);
	static long GEMGetUint1Item(cSemion* hdObject, BYTE * pbValue, DWORD nSize, DWORD &nCount);
	static long GEMGetUint2Item(cSemion* hdObject, unsigned short * pusiValue, DWORD nSize, DWORD &nCount);
	static long GEMGetUint4Item(cSemion* hdObject, unsigned long * pulValue, DWORD nSize, DWORD &nCount);
	static long GEMGetUint8Item(cSemion* hdObject, unsigned __int64 * pullValue, DWORD nSize, DWORD &nCount);
	static long GEMGetFloat4Item(cSemion* hdObject, float * pfltValue, DWORD nSize, DWORD &nCount);
	static long GEMGetFloat8Item(cSemion* hdObject, double * pdbValue, DWORD nSize, DWORD &nCount);

	/// <summary>
	///  消息发送
	/// </summary>
	///
	long GEMSendSecsMessage(cSemion* hdObject, BYTE bStrm, BYTE bFunc, long nSysbyte = 0);

	/// <summary>
	///  参数设置与读取
	/// </summary>
	///
	long GEMSetParam(string strParamName, string strParamValue );
	long GEMGetParam(string strParamName, string &strParamValue );

	/// <summary>
	///  变量读写
	/// </summary>
	///
	long GEMSetVariable(DWORD nCount, long *pnVid, string *psValue);
	long GEMGetVariable(DWORD nCount, long *pnVid, string* psValue);
	long GEMSetVariable2(DWORD nCount, long *pnVid, string *psValue, DWORD &nErrPos);
	long GEMGetVariable2(DWORD nCount, long *pnVid, string* psValue, BYTE *pVarType);
	long GEMSetFmtVariable(long nVid, cSemion* hdObject);
	long GEMGetFmtVariable(long nVid, cSemion* hdObject, BYTE &bItemType);
	long GEMGetSVInfo(DWORD nCount, long * pnSvid, string *psName, string *psFormat, DWORD *pnLength, string * psMins, string * psMaxs, string * psUnits);
	long GEMGetDVInfo(DWORD nCount, long * pnDvid, string *psName, string *psFormat, DWORD *pnLength, string * psMins, string * psMaxs, string * psUnits);
	long GEMGetAllSVInfo();
	long GEMGetAllDVInfo();

	/// <summary>
	///  设备常量
	/// </summary>
	///
	long GEMSetEcvValue(DWORD nCount, long *pnVid, string* psValue);
	long GEMRspEcvChange(long nMsgId, BYTE bState);
	long GEMRspEcvChangeEx(long nMsgId, BYTE bState);
	long GEMGetEcvInfo(DWORD nCount, long * pnEcId, string * psName, string *psFormat, DWORD *pnLength,string * psDef, string * psMin, string * psMax, string * psUnit);
	long GEMGetAllEcvInfo();

	/// <summary>
	///  远程指令
	/// </summary>
	///
	long GEMRspSimpleRemoteCommand(long nMsgId, BYTE chAck);
	long GEMRspRemoteCommand(long nMsgId, BYTE nHCAck, DWORD nCount, string * psCpName, BYTE * pnCpAck);
	long GEMRspEnhancedRemoteCommand(long nMsgId, BYTE bHCAck, DWORD nCount, string * psCpName, BYTE * pnCepAck);

	/// <summary>
	///  日期时间
	/// </summary>
	///
	long GEMReqDateTime();
	long GEMRspDateTime(long nMsgId, string strTime);
	long GEMRspDateTimeSend(long nMsgId, BYTE bState);

	/// <summary>
	///  告警
	/// </summary>
	///
	long GEMSetAlarm(long alid, BOOL bState);
	long GEMSetAlarmEx(long alid, BOOL bState);
	long GEMSetAlarmReportEnabled(BOOL bState);
	long GEMSetAlarmEnableState(DWORD nCount, long * pnAlid, BOOL bEnable);
	long GEMGetAlarmEnableState(DWORD nCount, long * pnAlid, BOOL *pbEnable);
	long GEMGetAllEnabledAlarm();
	long GEMGetAlarmInfo(DWORD nCount, long * pnAlid, long * pnAlcd, string * psAltx,BOOL * pbEnable);
	long GEMGetAllAlarmInfo();

	/// <summary>
	///  事件和报告
	/// </summary>
	///
	long GEMSetEvent(long nCeid);
	long GEMSetEventEnableState(DWORD nCount, long * pnCeid, BOOL bEnable);
	long GEMGetEventEnableState(DWORD nCount, long * pnCeid, BOOL *pbEnable);
	long GEMGetAllEnabledEvent();
	long GEMGetRptidCountOfEvents(DWORD nCount, long* pnCeid, DWORD& RptidCount);
	long GEMGetEventInfo(DWORD nCount, long *pnCeid, string *psName, BOOL *pbEnable, string *psDescription, DWORD *pnRptidCount, long *pnReportID);
	long GEMGetVidCountOfReports(DWORD nCount, long* pnRptid, DWORD& VidCount);
	long GEMGetReportInfo(DWORD nCount, long *pnRptid, string *psName, DWORD *pnVidCount, long *pnVid);
	long GEMGetAllEventInfo();
	long GEMGetAllReportInfo();

	/// <summary>
	///  处理程序
	/// </summary>
	///
	long GEMSetPPChanged(long nMode, string strPpid);
	long GEMSetPPSelected(string strPpid);
	long GEMReqPPLoadInquire(string strPpid, DWORD nLength);
	long GEMRspPPLoadInquire(long nMsgId, BYTE bState);
	long GEMReqPPSend(string strPpid, DWORD nLength, BYTE * pbBody);
	long GEMReqPPSendEx(string sPpid);
	long GEMRspPPSend(long nMsgId, BYTE bState);
	long GEMReqPP(string strPpid);
	long GEMRspPPEx(long systembyte, string sPpid);
	long GEMRspPP(long nMsgId, string strPpid, DWORD nLength, BYTE * pbBody);
	long GEMReqPPFmtSend(string strPpid, string strMdln, string strSoftRev, DWORD nCount, string* psCCode, DWORD *pnParamCount, string* psParamNames);
	long GEMRspPPFmtSend(long nMsgId, BYTE bState);
	long GEMReqPPFmt(string strPpid);
	long GEMRspPPFmt(long nMsgId, string strPpid, string strMdln, string strSoftRev, DWORD nCount, string* psCCode, DWORD *pnParamCount, string* psParamNames);
	long GEMRspPPDelete(long nMsgId, BYTE bState);
	long GEMRspPPList(long nMsgId, DWORD nCount, string * psPpids);
	long GEMReqPPVerification(string strPpid, DWORD nCount, long* pnAck, DWORD* psSeqNumber, string* psError);
	long GEMReqPPVerificationInquire(DWORD nLength);

	/// <summary>
	///  终端消息
	/// </summary>
	///
	long GEMReqTerminalMessageSend(long nTid, string strMsg);
	long GEMRspTerminalMessageSend(long nMsgId, BYTE bState);
	long GEMRspMultiTerminalMessageSend(long nMsgId, BYTE bState);
	long GEMRspBroadcast(long systembyte, BYTE ack);

	/// <summary>
	///  MAP S12
	/// </summary>
	///	
	long GEMReqMapSetupDataSend(MapSetupDataSend& mapData);													//S12,F1 Map Set-up Data Send (MSDS) S,H<-E,reply
	long GEMReqMapSetupData(MapSetupDataReq& mapData);														//S12,F3 Map Set-up Data Request(MSDR) P,H<-E,reply
	long GEMReqMapTransmit(string sMaterialID, BYTE bIDType, BYTE bMapFormat, DWORD nMessageLength);		//S12,F5 Map Transmit Inquire (MAPTI) S,H<-E,reply
	long GEMReqMapDataSend2(string sMaterialID, BYTE bIDType, string sStartPosition, string sBinCodeList);	//S12,F9 Map Data Send Type 2 (MDS2) M,H<-E,reply
	long GEMReqMapData2(string sMaterialID, BYTE bIDType);													//S12,F15 Map Data Request Type 2 (MDR2) P,H<-E,reply
	long GEMReqMapErrorReport(BYTE bMapError, BYTE bDataLocation);											//S12,F19 Map Error Report Send (MERS) S,H<->E
	/// <summary>
	///  日志
	/// </summary>
	///
	long GEMSetLogEnable(bool bEnable);
	long GEMSendTestMessage(const char* fileName, size_t index);
	long GEMRecvTestMessage(const char* fileName, size_t index);

#pragma endregion


	//======================================================================================================//
	// 2. 回调注册接口
	//======================================================================================================//
#pragma region 回调注册

	/// <summary>
	///		设置回调对象指针
	/// </summary>
	long GEMSetCallBackHandle(CBHANDLE hdCB);

	/// <summary>
	///		通用回调
	/// </summary>
	long RegistOnGEMMessage(OnGEMMessage *callFunction);
	long RegistOnGEMEvent(OnGEMEvent *callFunction);
	long RegistOnGEMRemoteEvent(OnGEMRemoteEvent *callFunction);
	long RegistOnGEMStateEvent(OnGEMStateEvent *callFunction);
	long RegistOnGEMErrorMessage(OnGEMErrorMessage *callFunction);
	long RegistOnGEMCommStateChanged(OnGEMCommStateChanged *callFunction);
	long RegistOnGEMControlStateChanged(OnGEMControlStateChanged *callFunction);
	long RegistOnGEMProcessingStateChanged(OnGEMProcessingStateChanged *callFunction);
	long RegistOnGEMErrorEvent(OnGEMErrorEvent *callFunction);
	long RegistOnGEMLogMessage(OnGEMLogMessage *callFunction);

	/// <summary>
	///		设备信息获取回调
	/// </summary>
	long RegistOnGEMRspAllSvInfo(OnGEMRspAllSVInfo *callFunction);
	long RegistOnGEMRspAllDvInfo(OnGEMRspAllDVInfo *callFunction);
	long RegistOnGEMRspAllEcvInfo(OnGEMRspAllEcvInfo *callFunction);
	long RegistOnGEMRspAllAlarmInfo(OnGEMRspAllAlarmInfo *callFunction);
	long RegistOnGEMRspAllEventInfo(OnGEMRspAllEventInfo *callFunction);
	long RegistOnGEMRspAllReportInfo(OnGEMRspAllReportInfo *callFunction);
	long RegistOnGEMRspAllEnabledAlarm(OnGEMRspAllEnabledAlarm *callFunction);
	long RegistOnGEMRspAllEnabledEvent(OnGEMRspAllEnabledEvent *callFunction);

	/// <summary>
	///		设备一般回调
	/// </summary>
	long RegistOnGEMECVChanged(OnGEMECVChanged *callFunction);
	long RegistOnGEMReqChangeECV(OnGEMReqChangeECV *callFunction);
	long RegistOnGEMReqDateTimeSend(OnGEMReqDateTimeSend *callFunction);
	long RegistOnGEMReqDateTime(OnGEMReqDateTime *callFunction);
	long RegistOnGEMRspDateTime(OnGEMRspDateTime *callFunction);
	long RegistOnGEMReqOffline(OnGEMReqOffline *callFunction);
	long RegistOnGEMReqOnline(OnGEMReqOnline *callFunction);
	long RegistOnGEMReqSimpleRemoteCommand(OnGEMReqSimpleRemoteCommand *callFunction);
	long RegistOnGEMReqRemoteCommand(OnGEMReqRemoteCommand *callFunction);
	long RegistOnGEMReqEnhancedRemoteCommand(OnGEMReqEnhancedRemoteCommand *callFunction);
	long RegistOnGEMSecondaryMsgReceived(OnGEMSecondaryMsgReceived *callFunction);
	long RegistOnGEMTerminalMessage(OnGEMTerminalMessage *callFunction);
	long RegistOnGEMTerminalMultiMessage(OnGEMTerminalMultiMessage *callFunction);
	long RegistOnGEMBroadcast(OnGEMBroadcast* callFunction);
	long RegistOnGEMRspLoopback(OnGEMRspLoopback *callFunction);
	long RegistOnGEMAlarmEnableStateChanged(OnGEMAlarmEnableStateChanged *callFunction);
	long RegistOnGEMEventEnableStateChanged(OnGEMEventEnableStateChanged *callFunction);
	long RegistOnGEMEventSend(OnGEMEventSend *callFunction);

	/// <summary>
	///		设备配方管理回调
	/// </summary>
	long RegistOnGEMReqPPLoadInquire(OnGEMReqPPLoadInquire *callFunction);
	long RegistOnGEMReqPP(OnGEMReqPP *callFunction);
	long RegistOnGEMReqPPDelete(OnGEMReqPPDelete *callFunction);
	long RegistOnGEMReqPPEx(OnGEMReqPPEx *callFunction);
	long RegistOnGEMReqPPFmt(OnGEMReqPPFmt *callFunction);
	long RegistOnGEMReqPPFmtSend(OnGEMReqPPFmtSend *callFunction);
	long RegistOnGEMReqPPList(OnGEMReqPPList *callFunction);
	long RegistOnGEMReqPPSend(OnGEMReqPPSend *callFunction);
	long RegistOnGEMReqPPSendEx(OnGEMReqPPSendEx *callFunction);
	long RegistOnGEMRspPP(OnGEMRspPP *callFunction);
	long RegistOnGEMRspPPEx(OnGEMRspPPEx *callFunction);
	long RegistOnGEMRspPPFmt(OnGEMRspPPFmt *callFunction);
	long RegistOnGEMRspPPFmtSend(OnGEMRspPPFmtSend *callFunction);
	long RegistOnGEMRspPPLoadInquire(OnGEMRspPPLoadInquire *callFunction);
	long RegistOnGEMRspPPSend(OnGEMRspPPSend *callFunction);
	long RegistOnGEMRspPPSendEx(OnGEMRspPPSendEx *callFunction);
	long RegistOnGEMRspPPVerification(OnGEMRspPPVerification *callFunction);
	long RegistOnGEMRspPPVerificationInquire(OnGEMRspPPVerificationInquire *callFunction);

	/// <summary>
	///		Map回调 S12
	/// </summary>
	long RegistOnGEMRspMapSetupDataSend(OnGEMRspMapSetupDataSend* callFunction);//S12,F2 Map Set-up Data Acknowledge (MSDA) S,H->E
	long RegistOnGEMRspMapSetupData(OnGEMRspMapSetupData* callFunction);		//S12,F4 Map Set-up Data (MSD) S,H->E
	long RegistOnGEMRspMapTransmit(OnGEMRspMapTransmit* callFunction);			//Map Transmit Grant (MAPTG) S,H->E
	long RegistOnGEMRspMapDataSend2(OnGEMRspMapDataSend2* callFunction);		//Map Data Acknowledge Type 2 (MDA2) S,H->E
	long RegistOnGEMRspMapData2(OnGEMRspMapData2* callFunction);				//Map Data Type 2 (MD2) M,H->E
	long RegistOnGEMReqMapErrorReport(OnGEMReqMapErrorReport* callFunction);	//S12,F19 Map Error Report Send (MERS) S,H<->E
#pragma endregion


private:
	Gem *m_pExGem;
};

