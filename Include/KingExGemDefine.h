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
	WORD	fnLocation;			//��ƽ��/ȱ�ڵ���ת�Ƕ�
	WORD	ffRotation;			//��Ĥ��ܵ���ת�Ƕ�
	BYTE	idType;				//��������(0:wafer; 1:wafer cassette; 2:film frame)
	BYTE	originLocation;		//ԭ��λ��(0:center; 1:upper right; 2:upper left; 3:lower left; 4:lower right)Ĭ��Ϊ2
	BYTE	referPointSelect;	//��ѡ�ο������
	BYTE	processAxis;		//������(0:rows,top,increasing; 1:rows,top,decreasing; 2:rows,bottom,increasing;
								//		3:rows,bottom,decreasing; 4:columns,left,increasing; 5:columns,left,decreasing;
								//		6:columns,right,increasing; 7:columns,right,decreasing)Ĭ��Ϊ0
	DWORD	dieRowCount;		//оƬ����
	DWORD	dieColumnCount;		//оƬ����
	DWORD	processDieCount;	//������/�Ѵ����оƬ����
	std::string	meterialID;		//���ϱ��
	std::string	nullBinCode;	//��оƬ�ı���
	std::string	xAxisDieSize;	//оƬ��X����ĳߴ�
	std::string	yAxisDieSize;	//оƬ��Y����ĳߴ�
	std::string	dieUnitsMeasure;//оƬ���ȵ�λ
	std::vector<std::string>	referPoint;	//�ο�������
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
	WORD	fnLocation;			//��ƽ��/ȱ�ڵ���ת�Ƕ�
	WORD	ffRotation;			//��Ĥ��ܵ���ת�Ƕ�
	BYTE	idType;				//��������(0:wafer; 1:wafer cassette; 2:film frame)
	BYTE	mapFormat;			//��ͼ����(0:row; 1:array; 2:coordinate)�̶�Ϊ1
	BYTE	processAxis;		//������(0:rows,top,increasing; 1:rows,top,decreasing; 2:rows,bottom,increasing;
								//		3:rows,bottom,decreasing; 4:columns,left,increasing; 5:columns,left,decreasing;
								//		6:columns,right,increasing; 7:columns,right,decreasing)Ĭ��Ϊ0
	BYTE	originLocation;		//ԭ��λ��(0:center; 1:upper right; 2:upper left; 3:lower left; 4:lower right)Ĭ��Ϊ2
	std::string	meterialID;		//���ϱ��
	std::string	nullBinCode;	//��оƬ�ı���	
	std::string	processBinCode;	//Ҫ�ӹ�оƬ�ı���
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
	BYTE	idType;				//��������(0:wafer; 1:wafer cassette; 2:film frame)
	BYTE	originLocation;		//ԭ��λ��(0:center; 1:upper right; 2:upper left; 3:lower left; 4:lower right)Ĭ��Ϊ2
	BYTE	referPointSelect;	//��ѡ�ο������
	WORD	fnLocation;			//��ƽ��/ȱ�ڵ���ת�Ƕ�
	DWORD	dieRowCount;		//оƬ����
	DWORD	messageLength;		//��Ϣ����(S12F15����Map����Ϣ)
	DWORD	dieColumnCount;		//оƬ����
	DWORD	processDieCount;	//������/�Ѵ����оƬ����
	std::string	meterialID;		//���ϱ��
	std::string	nullBinCode;	//��оƬ�ı���
	std::string	xAxisDieSize;	//оƬ��X����ĳߴ�
	std::string	yAxisDieSize;	//оƬ��Y����ĳߴ�
	std::string	processBinCode;	//Ҫ�ӹ�оƬ�ı���
	std::string	dieUnitsMeasure;//оƬ���ȵ�λ
	std::vector<std::string>	referPoint;	//�ο�������
};

//======================================================================================================//
// �ص�ָ��
//======================================================================================================//
#pragma region �ص��ӿ�����

/// <summary>
///		ͨ�ûص�
/// </summary>
typedef void (OnGEMMessage)(CBHANDLE hdCB, cSemion *pMessage);												//[�¼�]���յ�������Ϣ
typedef void (OnGEMEvent)(CBHANDLE hdCB, short nEventId, long nParam);										//[�¼�]���յ���ҪͨѶ��ص��¼�
typedef void (OnGEMRemoteEvent)(CBHANDLE hdCB,WORD nPort,short nEventId, long nParam);						//[�¼�]���յ�Զ�̶˿����Ӷ����յ���ҪͨѶ��ص��¼�
typedef void (OnGEMStateEvent)(CBHANDLE hdCB, long nState);													//[�¼�]���յ�KingExGEM��״̬�¼�
typedef void (OnGEMErrorMessage)(CBHANDLE hdCB, long nMsgId, BYTE bFunction, BYTE *pHeader);				//[�¼�]��֪ͨ������Ϣ <S9Fy>
typedef void (OnGEMCommStateChanged)(CBHANDLE hdCB, long nState, long prelState);							//[�¼�]������״̬�ı�
typedef void (OnGEMControlStateChanged)(CBHANDLE hdCB, long nState, long prelState);						//[�¼�]������״̬�ı�
typedef void (OnGEMProcessingStateChanged)(CBHANDLE hdCB, long nState, long prelState);						//[�¼�]������״̬�ı�
typedef void (OnGEMErrorEvent)(CBHANDLE hdCB, string sInterfaceName, string sErrorInfo);					//[�¼�]���յ������¼�
typedef void (OnGEMLogMessage)(CBHANDLE hdCB, const char * sMsg);											//[�¼�]���յ�ͨѶ��־��Ϣ

/// <summary>
///		�豸��Ϣ��ȡ�ص�
/// </summary>
typedef void (OnGEMRspAllSVInfo)(CBHANDLE hdCB, DWORD nCount, long * pnSvid, string *psName, string *psFormat, DWORD *pnlen, string * psMins, string * psMaxs, string * psUnits);								//[�¼�]���յ�����SV��Ϣ
typedef void (OnGEMRspAllDVInfo)(CBHANDLE hdCB, DWORD nCount, long * pnDvid, string *psName, string *psFormat, DWORD *pnlen, string * psMins, string * psMaxs, string * psUnits);								//[�¼�]���յ�����DVVAL��Ϣ
typedef void (OnGEMRspAllEcvInfo)(CBHANDLE hdCB, DWORD nCount, long * pnEcIds, string * psNames, string *psFormat, DWORD *pnlen,string * psDefs, string * psMins, string * psMaxs, string * psUnits);			//[�¼�]���յ�����ECV��Ϣ
typedef void (OnGEMRspAllAlarmInfo)(CBHANDLE hdCB, DWORD nCount, long * pnAlid, long * pnAlcd, string * psAltx,BOOL * pnEnable);																				//[�¼�]���յ�����Alarm��Ϣ
typedef void (OnGEMRspAllEventInfo)(CBHANDLE hdCB, DWORD nCount, long *pnCeid, string *pName, BOOL *pEnable, string *pDescription, DWORD *pnRptidCount, long *pnReportID);										//[�¼�]���յ�����Event��Ϣ
typedef void (OnGEMRspAllReportInfo)(CBHANDLE hdCB, DWORD nCount, long *pnRptid, string *pName, DWORD *vidCount, long *pnVid);																					//[�¼�]���յ�����Report��Ϣ
typedef void (OnGEMRspAllEnabledAlarm)(CBHANDLE hdCB, DWORD nCount, long * pnAlid);																																//[�¼�]���յ��������õĸ澯
typedef void (OnGEMRspAllEnabledEvent)(CBHANDLE hdCB, DWORD nCount, long * pnCeid);																																//[�¼�]���յ��������õ��¼�

/// <summary>
///		�豸һ��ص�
/// </summary>
typedef void (OnGEMECVChanged)(CBHANDLE hdCB, DWORD nCount, long* plEcIds, string* psVals);																				//[�¼�]���յ�ECV�ı���¼�
typedef void (OnGEMReqChangeECV)(CBHANDLE hdCB, long nMsgId, DWORD nCount, long* plEcIds, string* psVals);																//[��Ϣ]������ECV�ı����Ϣ <S2F15>
typedef void (OnGEMReqDateTimeSend)(CBHANDLE hdCB, long nMsgId, string sSystemTime);																					//[��Ϣ]��������������ʱ��  <S2F31>
typedef void (OnGEMReqDateTime)(CBHANDLE hdCB, long nMsgId);																											//[��Ϣ]����������ʱ��  <S2F17>
typedef void (OnGEMRspDateTime)(CBHANDLE hdCB, string sSystemTime);																										//[��Ϣ]���ظ�����ʱ��  <S2F18>
typedef void (OnGEMReqSimpleRemoteCommand)(CBHANDLE hdCB, long nMsgId, string sRcmd);																					//[��Ϣ]������ִ�м�Զ��ָ��  <S2F21>
typedef void (OnGEMReqOffline)(CBHANDLE hdCB, long nMsgId, long nFromState, long nToState);																				//[��Ϣ]����������  <S1F15>
typedef void (OnGEMReqOnline)(CBHANDLE hdCB, long nMsgId, long nFromState, long nToState);																				//[��Ϣ]����������  <S1F17>
typedef void (OnGEMReqRemoteCommand)(CBHANDLE hdCB, long nMsgId, string sRcmd, DWORD nCount, string* psNames, string* psVals);											//[��Ϣ]������ִ��Զ��ָ��  <S241>
typedef void (OnGEMReqEnhancedRemoteCommand)(CBHANDLE hdCB, long nMsgId, string sObjspec, string sRcmd, DWORD nCount, string* psNames, string* psVals);					//[��Ϣ]������ִ����ǿԶ��ָ��  <S2F49>
typedef void (OnGEMSecondaryMsgReceived)(CBHANDLE hdCB, long nS, long nF, long nSysbyte, string sParam1, string sParam2, string sParam3);								//[��Ϣ]���յ��ظ�������Ϣ  <SxF2n>
typedef void (OnGEMTerminalMessage)(CBHANDLE hdCB, long nMsgId,long nTid, string sMsg);																					//[��Ϣ]���յ��ն���Ϣ-��  <S10F3>
typedef void (OnGEMTerminalMultiMessage)(CBHANDLE hdCB, long nMsgId,long nTid, DWORD nCount, string* psMsg);															//[��Ϣ]���յ��ն���Ϣ-��  <S10F5>
typedef void (OnGEMBroadcast)(CBHANDLE hdCB, long nMsgId, string sMsg);																					//[��Ϣ]���յ��ն���Ϣ-��  <S10F3>
typedef void (OnGEMRspLoopback)(CBHANDLE hdCB, DWORD nCount, BYTE* pbAbs);																								//[��Ϣ]���ظ���·���     <S2F26>
typedef void (OnGEMAlarmEnableStateChanged)(CBHANDLE hdCB, BYTE bAled, DWORD nCount, long *pnAlid);																		//[�¼�]���յ�Alarm����״̬�ı��¼�
typedef void (OnGEMEventEnableStateChanged)(CBHANDLE hdCB, BYTE bCeed, DWORD nCount, long *pnCeid);																		//[�¼�]���յ�Event����״̬�ı��¼�
typedef void (OnGEMEventSend)(CBHANDLE hdCB, long nCeid, long nSysbyte);																								//[�¼�]���յ�Event�����¼�

/// <summary>
///		�豸�䷽����ص�
/// </summary>
typedef void (OnGEMReqPPLoadInquire)(CBHANDLE hdCB, long nMsgId, string sPpid, DWORD nLength);																													//[��Ϣ]�������䷽���� <S7F1>
typedef void (OnGEMRspPPLoadInquire)(CBHANDLE hdCB, long nResult);																																				//[��Ϣ]���ظ��䷽���� <S7F2>
typedef void (OnGEMReqPP)(CBHANDLE hdCB, long nMsgId, string sPpid);																																			//[��Ϣ]�������䷽     <S7F5
typedef void (OnGEMRspPP)(CBHANDLE hdCB, string sPpid, DWORD nLength, unsigned char* pbBody);																													//[��Ϣ]���ظ��䷽     <S7F6>
typedef void (OnGEMReqPPEx)(CBHANDLE hdCB, long nMsgId, string sPpid, string sRecipePath);																														//[��Ϣ]�������䷽�ļ�  <S7F5>
typedef void (OnGEMRspPPEx)(CBHANDLE hdCB, string sPpid, string sRecipePath);																																	//[��Ϣ]���ظ��䷽�ļ�  <S7F6>
typedef void (OnGEMReqPPSend)(CBHANDLE hdCB, long nMsgId, string sPpid, DWORD nLength, unsigned char* pbBody);																									//[��Ϣ]�������䷽����  <S7F3>	
typedef void (OnGEMRspPPSend)(CBHANDLE hdCB, long nResult);																																						//[��Ϣ]���ظ��䷽����  <S7F4>
typedef void (OnGEMReqPPSendEx)(CBHANDLE hdCB, long nMsgId, string sPpid, string sRecipePath);																													//[��Ϣ]�������䷽�ļ�����  <S7F3>
typedef void (OnGEMRspPPSendEx)(CBHANDLE hdCB, long nResult);																																					//[��Ϣ]���ظ��䷽�ļ�����  <S7F4>
typedef void (OnGEMReqPPFmt)(CBHANDLE hdCB, long nMsgId, string sPpid);																																			//[��Ϣ]�������׼�䷽     <S7F25>
typedef void (OnGEMRspPPFmt)(CBHANDLE hdCB, string sPpid, string sMdln, string sSoftRev, DWORD nCount, string* psCCode, DWORD* plParamCount, string* psParamNames);												//[��Ϣ]���ظ���׼�䷽     <S7F26>
typedef void (OnGEMReqPPFmtSend)(CBHANDLE hdCB, long nMsgId, string sPpid, string sMdln, string sSoftRev, DWORD nCount, string* psCCode, DWORD* plParamCount, string* psParamNames);							//[��Ϣ]�������׼�䷽����  <S7F23>
typedef void (OnGEMRspPPFmtSend)(CBHANDLE hdCB, long nResult);																																					//[��Ϣ]���ظ���׼�䷽����  <S7F24>
typedef void (OnGEMRspPPVerification)(CBHANDLE hdCB);																																							//[��Ϣ]���ظ��䷽��֤      <S7F28>
typedef void (OnGEMRspPPVerificationInquire)(CBHANDLE hdCB, long nResult);																																		//[��Ϣ]���ظ��䷽��֤����  <S7F30>
typedef void (OnGEMReqPPList)(CBHANDLE hdCB, long nMsgId);																																						//[��Ϣ]�������䷽�б�      <S7F19>
typedef void (OnGEMReqPPDelete)(CBHANDLE hdCB, long nMsgId, DWORD nCount, string* psPpid);																														//[��Ϣ]�������䷽ɾ��      <S7F17>

/// <summary>
///		Map�ص� S12
/// </summary>
typedef void (OnGEMRspMapSetupDataSend)(CBHANDLE hdCB, long nAck);
typedef void (OnGEMRspMapSetupData)(CBHANDLE hdCB, MapSetupDataRsp& mapDataRsp);
typedef void (OnGEMRspMapTransmit)(CBHANDLE hdCB, long nAck);
typedef void (OnGEMRspMapDataSend2)(CBHANDLE hdCB, long nAck);
typedef void (OnGEMRspMapData2)(CBHANDLE hdCB, string sMaterialID, BYTE bIDType, string sStartPosition, vector<string> vBinCodeList);
typedef void (OnGEMReqMapErrorReport)(CBHANDLE hdCB, BYTE bMapError, BYTE bDataLocation);
#pragma endregion