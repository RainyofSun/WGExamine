// PLCVersionDll.h : PLCVersionDll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPLCVersionDllApp
// �йش���ʵ�ֵ���Ϣ������� PLCVersionDll.cpp
//

class CPLCVersionDllApp : public CWinApp
{
public:
	CPLCVersionDllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
