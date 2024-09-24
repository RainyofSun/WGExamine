/*----------------------------------------------------------------
 * 版权所有 (c) 北京中电科电子装备有限公司 保留所有权利。
 * 公司名称：北京中电科电子装备有限公司
 * 
 * 创建者：刘冉
 * 创建时间：2024-9-20
 * 版本：V1.0.0
 * 描述：Socket的封装类
 *
 * ----------------------------------------------------------------
 * 修改人：
 * 时间：
 * 修改说明：
 *
 * 版本：
 *----------------------------------------------------------------*/
#pragma once
#include "afxsock.h"
#include "SECSConfig.h"

class CSECSSocket: public CSocket
{
public:
	CSECSSocket(HWND wnd);
	~CSECSSocket(void);


	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

private:
	HWND m_hwnd;
};

