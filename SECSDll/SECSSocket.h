/*----------------------------------------------------------------
 * ��Ȩ���� (c) �����е�Ƶ���װ�����޹�˾ ��������Ȩ����
 * ��˾���ƣ������е�Ƶ���װ�����޹�˾
 * 
 * �����ߣ���Ƚ
 * ����ʱ�䣺2024-9-20
 * �汾��V1.0.0
 * ������Socket�ķ�װ��
 *
 * ----------------------------------------------------------------
 * �޸��ˣ�
 * ʱ�䣺
 * �޸�˵����
 *
 * �汾��
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

