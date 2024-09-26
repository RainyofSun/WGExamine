#pragma once

#include <string>
#include <vector>
using namespace std;

#ifndef CBHANDLE
typedef void *  CBHANDLE;
#endif

#ifndef BYTE
typedef unsigned char  BYTE;
#endif

#ifndef BOOL
typedef int BOOL;
#endif

#ifndef WORD
typedef unsigned short WORD;
#endif

#ifndef USHORT
typedef unsigned short USHORT;
#endif

#ifndef DWORD
typedef unsigned long DWORD;
#endif

#ifndef INT64
typedef long long INT64;
#endif

#ifndef LONGLONG
typedef long long LONGLONG;
#endif

#ifndef UINT64
typedef unsigned long long UINT64;
#endif

#ifndef UINT64
typedef unsigned long long UINT64;
#endif

#ifndef DWORDLONG
typedef unsigned long long DWORDLONG;
#endif


#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

struct cSemion;

struct MapSetupDataSend 
{
	MapSetupDataSend()
	{
		idType = 0;
		fnLocation = 0;
		ffRotation = 0;
		originLocation = 2;
		referPointSelect = 0;
		processAxis = 0;
		dieRowCount = 0;
		dieColumnCount = 0;
		processDieCount = 0;
	}
	WORD	fnLocation;			//扁平边/缺口的旋转角度
	WORD	ffRotation;			//薄膜框架的旋转角度
	BYTE	idType;				//物料类型(0:wafer; 1:wafer cassette; 2:film frame)
	BYTE	originLocation;		//原点位置(0:center; 1:upper right; 2:upper left; 3:lower left; 4:lower right)默认为2
	BYTE	referPointSelect;	//所选参考点个数
	BYTE	processAxis;		//处理轴(0:rows,top,increasing; 1:rows,top,decreasing; 2:rows,bottom,increasing;
								//		3:rows,bottom,decreasing; 4:columns,left,increasing; 5:columns,left,decreasing;
								//		6:columns,right,increasing; 7:columns,right,decreasing)默认为0
	DWORD	dieRowCount;		//芯片行数
	DWORD	dieColumnCount;		//芯片列数
	DWORD	processDieCount;	//待处理/已处理的芯片个数
	std::string	meterialID;		//物料编号
	std::string	nullBinCode;	//空芯片的编码
	std::string	xAxisDieSize;	//芯片在X轴向的尺寸
	std::string	yAxisDieSize;	//芯片在Y轴向的尺寸
	std::string	dieUnitsMeasure;//芯片长度单位
	std::vector<std::string>	referPoint;	//参考点坐标
};
struct MapSetupDataReq
{
	MapSetupDataReq()
	{
		fnLocation = 0;
		ffRotation = 0;
		idType = 0;
		mapFormat = 1;
		processAxis = 0;
		originLocation = 2;
	}
	WORD	fnLocation;			//扁平边/缺口的旋转角度
	WORD	ffRotation;			//薄膜框架的旋转角度
	BYTE	idType;				//物料类型(0:wafer; 1:wafer cassette; 2:film frame)
	BYTE	mapFormat;			//地图类型(0:row; 1:array; 2:coordinate)固定为1
	BYTE	processAxis;		//处理轴(0:rows,top,increasing; 1:rows,top,decreasing; 2:rows,bottom,increasing;
								//		3:rows,bottom,decreasing; 4:columns,left,increasing; 5:columns,left,decreasing;
								//		6:columns,right,increasing; 7:columns,right,decreasing)默认为0
	BYTE	originLocation;		//原点位置(0:center; 1:upper right; 2:upper left; 3:lower left; 4:lower right)默认为2
	std::string	meterialID;		//物料编号
	std::string	nullBinCode;	//空芯片的编码	
	std::string	processBinCode;	//要加工芯片的编码
};
struct MapSetupDataRsp
{
	MapSetupDataRsp()
	{
		idType = 0;
		originLocation = 2;
		referPointSelect = 0;
		fnLocation = 0;
		dieRowCount = 0;
		messageLength = 0;
		dieColumnCount = 0;
		processDieCount = 0;
	}
	BYTE	idType;				//物料类型(0:wafer; 1:wafer cassette; 2:film frame)
	BYTE	originLocation;		//原点位置(0:center; 1:upper right; 2:upper left; 3:lower left; 4:lower right)默认为2
	BYTE	referPointSelect;	//所选参考点个数
	WORD	fnLocation;			//扁平边/缺口的旋转角度
	DWORD	dieRowCount;		//芯片行数
	DWORD	messageLength;		//消息长度(S12F15发送Map的消息)
	DWORD	dieColumnCount;		//芯片列数
	DWORD	processDieCount;	//待处理/已处理的芯片个数
	std::string	meterialID;		//物料编号
	std::string	nullBinCode;	//空芯片的编码
	std::string	xAxisDieSize;	//芯片在X轴向的尺寸
	std::string	yAxisDieSize;	//芯片在Y轴向的尺寸
	std::string	processBinCode;	//要加工芯片的编码
	std::string	dieUnitsMeasure;//芯片长度单位
	std::vector<std::string>	referPoint;	//参考点坐标
};

//======================================================================================================//
// 回调指针
//======================================================================================================//
#pragma region 回调接口声明

/// <summary>
///		通用回调
/// </summary>
typedef void (OnGEMMessage)(CBHANDLE hdCB, cSemion *pMessage);												//[事件]：收到定制消息
typedef void (OnGEMEvent)(CBHANDLE hdCB, short nEventId, long nParam);										//[事件]：收到重要通讯相关的事件
typedef void (OnGEMRemoteEvent)(CBHANDLE hdCB,WORD nPort,short nEventId, long nParam);						//[事件]：收到远程端口连接对象收到重要通讯相关的事件
typedef void (OnGEMStateEvent)(CBHANDLE hdCB, long nState);													//[事件]：收到KingExGEM的状态事件
typedef void (OnGEMErrorMessage)(CBHANDLE hdCB, long nMsgId, BYTE bFunction, BYTE *pHeader);				//[事件]：通知错误消息 <S9Fy>
typedef void (OnGEMCommStateChanged)(CBHANDLE hdCB, long nState, long prelState);							//[事件]：连接状态改变
typedef void (OnGEMControlStateChanged)(CBHANDLE hdCB, long nState, long prelState);						//[事件]：控制状态改变
typedef void (OnGEMProcessingStateChanged)(CBHANDLE hdCB, long nState, long prelState);						//[事件]：处理状态改变
typedef void (OnGEMErrorEvent)(CBHANDLE hdCB, string sInterfaceName, string sErrorInfo);					//[事件]：收到错误事件
typedef void (OnGEMLogMessage)(CBHANDLE hdCB, const char * sMsg);											//[事件]：收到通讯日志消息

/// <summary>
///		设备信息获取回调
/// </summary>
typedef void (OnGEMRspAllSVInfo)(CBHANDLE hdCB, DWORD nCount, long * pnSvid, string *psName, string *psFormat, DWORD *pnlen, string * psMins, string * psMaxs, string * psUnits);								//[事件]：收到所有SV信息
typedef void (OnGEMRspAllDVInfo)(CBHANDLE hdCB, DWORD nCount, long * pnDvid, string *psName, string *psFormat, DWORD *pnlen, string * psMins, string * psMaxs, string * psUnits);								//[事件]：收到所有DVVAL信息
typedef void (OnGEMRspAllEcvInfo)(CBHANDLE hdCB, DWORD nCount, long * pnEcIds, string * psNames, string *psFormat, DWORD *pnlen,string * psDefs, string * psMins, string * psMaxs, string * psUnits);			//[事件]：收到所有ECV信息
typedef void (OnGEMRspAllAlarmInfo)(CBHANDLE hdCB, DWORD nCount, long * pnAlid, long * pnAlcd, string * psAltx,BOOL * pnEnable);																				//[事件]：收到所有Alarm信息
typedef void (OnGEMRspAllEventInfo)(CBHANDLE hdCB, DWORD nCount, long *pnCeid, string *pName, BOOL *pEnable, string *pDescription, DWORD *pnRptidCount, long *pnReportID);										//[事件]：收到所有Event信息
typedef void (OnGEMRspAllReportInfo)(CBHANDLE hdCB, DWORD nCount, long *pnRptid, string *pName, DWORD *vidCount, long *pnVid);																					//[事件]：收到所有Report信息
typedef void (OnGEMRspAllEnabledAlarm)(CBHANDLE hdCB, DWORD nCount, long * pnAlid);																																//[事件]：收到所有启用的告警
typedef void (OnGEMRspAllEnabledEvent)(CBHANDLE hdCB, DWORD nCount, long * pnCeid);																																//[事件]：收到所有启用的事件

/// <summary>
///		设备一般回调
/// </summary>
typedef void (OnGEMECVChanged)(CBHANDLE hdCB, DWORD nCount, long* plEcIds, string* psVals);																				//[事件]：收到ECV改变的事件
typedef void (OnGEMReqChangeECV)(CBHANDLE hdCB, long nMsgId, DWORD nCount, long* plEcIds, string* psVals);																//[消息]：请求ECV改变的消息 <S2F15>
typedef void (OnGEMReqDateTimeSend)(CBHANDLE hdCB, long nMsgId, string sSystemTime);																					//[消息]：请求设置日期时间  <S2F31>
typedef void (OnGEMReqDateTime)(CBHANDLE hdCB, long nMsgId);																											//[消息]：请求日期时间  <S2F17>
typedef void (OnGEMRspDateTime)(CBHANDLE hdCB, string sSystemTime);																										//[消息]：回复日期时间  <S2F18>
typedef void (OnGEMReqSimpleRemoteCommand)(CBHANDLE hdCB, long nMsgId, string sRcmd);																					//[消息]：请求执行简单远程指令  <S2F21>
typedef void (OnGEMReqOffline)(CBHANDLE hdCB, long nMsgId, long nFromState, long nToState);																				//[消息]：请求离线  <S1F15>
typedef void (OnGEMReqOnline)(CBHANDLE hdCB, long nMsgId, long nFromState, long nToState);																				//[消息]：请求在线  <S1F17>
typedef void (OnGEMReqRemoteCommand)(CBHANDLE hdCB, long nMsgId, string sRcmd, DWORD nCount, string* psNames, string* psVals);											//[消息]：请求执行远程指令  <S241>
typedef void (OnGEMReqEnhancedRemoteCommand)(CBHANDLE hdCB, long nMsgId, string sObjspec, string sRcmd, DWORD nCount, string* psNames, string* psVals);					//[消息]：请求执行增强远程指令  <S2F49>
typedef void (OnGEMSecondaryMsgReceived)(CBHANDLE hdCB, long nS, long nF, long nSysbyte, string sParam1, string sParam2, string sParam3);								//[消息]：收到回复类型消息  <SxF2n>
typedef void (OnGEMTerminalMessage)(CBHANDLE hdCB, long nMsgId,long nTid, string sMsg);																					//[消息]：收到终端消息-单  <S10F3>
typedef void (OnGEMTerminalMultiMessage)(CBHANDLE hdCB, long nMsgId,long nTid, DWORD nCount, string* psMsg);															//[消息]：收到终端消息-多  <S10F5>
typedef void (OnGEMBroadcast)(CBHANDLE hdCB, long nMsgId, string sMsg);																					//[消息]：收到终端消息-单  <S10F3>
typedef void (OnGEMRspLoopback)(CBHANDLE hdCB, DWORD nCount, BYTE* pbAbs);																								//[消息]：回复回路诊断     <S2F26>
typedef void (OnGEMAlarmEnableStateChanged)(CBHANDLE hdCB, BYTE bAled, DWORD nCount, long *pnAlid);																		//[事件]：收到Alarm启用状态改变事件
typedef void (OnGEMEventEnableStateChanged)(CBHANDLE hdCB, BYTE bCeed, DWORD nCount, long *pnCeid);																		//[事件]：收到Event启用状态改变事件
typedef void (OnGEMEventSend)(CBHANDLE hdCB, long nCeid, long nSysbyte);																								//[事件]：收到Event发送事件

/// <summary>
///		设备配方管理回调
/// </summary>
typedef void (OnGEMReqPPLoadInquire)(CBHANDLE hdCB, long nMsgId, string sPpid, DWORD nLength);																													//[消息]：请求配方加载 <S7F1>
typedef void (OnGEMRspPPLoadInquire)(CBHANDLE hdCB, long nResult);																																				//[消息]：回复配方加载 <S7F2>
typedef void (OnGEMReqPP)(CBHANDLE hdCB, long nMsgId, string sPpid);																																			//[消息]：请求配方     <S7F5
typedef void (OnGEMRspPP)(CBHANDLE hdCB, string sPpid, DWORD nLength, unsigned char* pbBody);																													//[消息]：回复配方     <S7F6>
typedef void (OnGEMReqPPEx)(CBHANDLE hdCB, long nMsgId, string sPpid, string sRecipePath);																														//[消息]：请求配方文件  <S7F5>
typedef void (OnGEMRspPPEx)(CBHANDLE hdCB, string sPpid, string sRecipePath);																																	//[消息]：回复配方文件  <S7F6>
typedef void (OnGEMReqPPSend)(CBHANDLE hdCB, long nMsgId, string sPpid, DWORD nLength, unsigned char* pbBody);																									//[消息]：请求配方发送  <S7F3>	
typedef void (OnGEMRspPPSend)(CBHANDLE hdCB, long nResult);																																						//[消息]：回复配方发送  <S7F4>
typedef void (OnGEMReqPPSendEx)(CBHANDLE hdCB, long nMsgId, string sPpid, string sRecipePath);																													//[消息]：请求配方文件发送  <S7F3>
typedef void (OnGEMRspPPSendEx)(CBHANDLE hdCB, long nResult);																																					//[消息]：回复配方文件发送  <S7F4>
typedef void (OnGEMReqPPFmt)(CBHANDLE hdCB, long nMsgId, string sPpid);																																			//[消息]：请求标准配方     <S7F25>
typedef void (OnGEMRspPPFmt)(CBHANDLE hdCB, string sPpid, string sMdln, string sSoftRev, DWORD nCount, string* psCCode, DWORD* plParamCount, string* psParamNames);												//[消息]：回复标准配方     <S7F26>
typedef void (OnGEMReqPPFmtSend)(CBHANDLE hdCB, long nMsgId, string sPpid, string sMdln, string sSoftRev, DWORD nCount, string* psCCode, DWORD* plParamCount, string* psParamNames);							//[消息]：请求标准配方发送  <S7F23>
typedef void (OnGEMRspPPFmtSend)(CBHANDLE hdCB, long nResult);																																					//[消息]：回复标准配方发送  <S7F24>
typedef void (OnGEMRspPPVerification)(CBHANDLE hdCB);																																							//[消息]：回复配方验证      <S7F28>
typedef void (OnGEMRspPPVerificationInquire)(CBHANDLE hdCB, long nResult);																																		//[消息]：回复配方验证加载  <S7F30>
typedef void (OnGEMReqPPList)(CBHANDLE hdCB, long nMsgId);																																						//[消息]：请求配方列表      <S7F19>
typedef void (OnGEMReqPPDelete)(CBHANDLE hdCB, long nMsgId, DWORD nCount, string* psPpid);																														//[消息]：请求配方删除      <S7F17>

/// <summary>
///		Map回调 S12
/// </summary>
typedef void (OnGEMRspMapSetupDataSend)(CBHANDLE hdCB, long nAck);
typedef void (OnGEMRspMapSetupData)(CBHANDLE hdCB, MapSetupDataRsp& mapDataRsp);
typedef void (OnGEMRspMapTransmit)(CBHANDLE hdCB, long nAck);
typedef void (OnGEMRspMapDataSend2)(CBHANDLE hdCB, long nAck);
typedef void (OnGEMRspMapData2)(CBHANDLE hdCB, string sMaterialID, BYTE bIDType, string sStartPosition, vector<string> vBinCodeList);
typedef void (OnGEMReqMapErrorReport)(CBHANDLE hdCB, BYTE bMapError, BYTE bDataLocation);
#pragma endregion