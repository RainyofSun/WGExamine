#include "StdAfx.h"
#include "SECSSocket.h"


CSECSSocket::CSECSSocket(HWND wnd)
{
	m_hwnd = wnd;
}


CSECSSocket::~CSECSSocket(void)
{
}


void CSECSSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	TCHAR* buffer = new TCHAR[1024];
	memset(buffer, 0, 1024);

	this->Receive(buffer, 1024);
	SendMessage(m_hwnd, WM_TAIZHI_SOCKET_RECEIVE, 0, (LPARAM)(LPCTSTR)buffer);

	if (buffer != NULL )
	{
		delete[] buffer;
	}

	CSocket::OnReceive(nErrorCode);
}


void CSECSSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	TCHAR* buffer = new TCHAR[1024];
	memset(buffer, 0, 1024);

	this->Receive(buffer, 1024);
	SendMessage(m_hwnd, WM_TAIZHI_SOCKET_CLOSE, 0, (LPARAM)(LPCTSTR)buffer);

	if (buffer != NULL )
	{
		delete[] buffer;
	}
	
	CSocket::OnClose(nErrorCode);
}
