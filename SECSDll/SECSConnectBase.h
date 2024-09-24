/*----------------------------------------------------------------
 * 版权所有 (c) 北京中电科电子装备有限公司 保留所有权利。
 * 公司名称：北京中电科电子装备有限公司
 * 
 * 创建者：刘冉
 * 创建时间：2024-9-20
 * 版本：V1.0.0
 * 描述：SECS 连接基类
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
#include <map>

using namespace std;

UINT EventSocketThread(LPVOID lpParameter);

#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT CSECSConnectBase
{
public:
	CSECSConnectBase(void);
	~CSECSConnectBase(void);

	/**
	 * 功能：配置连接信息
	 * 输入：
			param1: (SECSCommandParameters) 配置信息
	 */ 
	virtual void SECS_SetCommandParameters(SECSCommandParameters parameters){m_parameters = parameters;};

	/**
	 * 功能：开始连接SECS
	 */ 
	virtual void SECS_Connect(){};

	/**
	 * 功能：断开连接SECS
	 */ 
	virtual void SECS_Disconnect(){};
	/**
	 * 功能：事件上报
	 * 输入：
			param1: evID 事件ID
			param2: stringMap 事件绑定的ReportID 及 ReportID 绑定的对应的常量值
	 */ 
	virtual void SECS_EventReport(int evID, std::map<CString, CString> stringMap){};

	/**
	 * 功能：报警上报
	 */ 
	virtual void SECS_AlarmReport(int alID){};

	/**
	 * 功能：消警事件上报
	 */ 
	virtual void SECS_ClearAlarmReport(int alID){};

protected:
	/**
	 * 功能：开启事件线程
	 */ 
	void resumeSECSThread();

public:
	SECSCommandParameters m_parameters;
	bool bExitEventSocketThread;

protected:
	CWinThread *m_pEventSocketThread;
};

