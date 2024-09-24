#include "StdAfx.h"
#include "SECSConnectBase.h"


CSECSConnectBase::CSECSConnectBase(void)
{
	m_pEventSocketThread = nullptr;
	bExitEventSocketThread = true;
}


CSECSConnectBase::~CSECSConnectBase(void)
{
	if(m_pEventSocketThread != NULL)
	{
		bExitEventSocketThread = true;
		::WaitForSingleObject(m_pEventSocketThread->m_hThread,INFINITE);
		delete m_pEventSocketThread;
		m_pEventSocketThread = NULL;
	}
}

void CSECSConnectBase::resumeSECSThread()
{
	if (m_pEventSocketThread != nullptr)
	{
		return;
	}

	m_pEventSocketThread = AfxBeginThread(EventSocketThread, this, 0, 0, CREATE_SUSPENDED);
	if (m_pEventSocketThread == nullptr)
	{
		return;
	}

	bExitEventSocketThread = false;
	m_pEventSocketThread->m_bAutoDelete = FALSE;
	m_pEventSocketThread->ResumeThread();
}