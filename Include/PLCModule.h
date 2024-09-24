/*----------------------------------------------------------------
 * ��Ȩ���� (c) �����е�Ƶ���װ�����޹�˾ ��������Ȩ����
 * ��˾���ƣ������е�Ƶ���װ�����޹�˾
 * 
 * �����ߣ���Ƚ
 * ����ʱ�䣺2024-7-30
 * �汾��V1.0.0
 * ������������ ֻ����PLC�Ľ��������ݸ���
 *
 * ----------------------------------------------------------------
 * �޸��ˣ�
 * ʱ�䣺
 * �޸�˵����
 *
 * �汾��V1.0.0
 *----------------------------------------------------------------*/
#pragma once
#include <afxmt.h>
#include <vector>
#include "PLCModuleDefine.h"

#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT CPLCModule
{
public:
	/**
	 * ���ܣ���ȡΨһʵ��
	 * �����
			��CPLCModule*��ʵ��
	 */ 
	static CPLCModule *getInstance();

	/**
	 * ���ܣ�����������Ϣ
	 * ���룺
			param1: connectInfo PLC���յ�IP��Port ��, UDP ��һλ Ϊ����IP��Port���ڶ���Ϊ����IP��Port
			param2: type		PLCЭ��(Ĭ��ΪUDPЭ��)
	 * �����
			��bool���Ƿ����óɹ�
	 */ 
	bool setPLCCommunicationInfo(std::vector<PLCConnectInfo> connectInfos, PLCProtocolType type = PLC_UDP);

	/**
	 * ���ܣ���������ˢ���߳�
	 */ 
	void startThread();

	/**
	 * ���ܣ��Ƿ��ʼ���ɹ� 
	 * �����
			��bool���Ƿ��ʼ���ɹ�
	 */ 
	bool isInitialized() const;

	/**
	 * ���ܣ��ͷ���Դ
	 */ 
	static void release();
	
	/**
	 * ���ܣ��������ݰ�д������
	 * ���룺
			param1: ��id������id
			param2����int��д�������
	 * �����
			��bool���Ƿ�д��ɹ�
	 */
	bool orderPacketSetValue(int dataId, int writeValue) const;

	/**
	 * ���ܣ��������ݰ���ȡ����
	 * ���룺
			param1: ��id������id
			parma2����int����ȡ��ֵ
	 * �����
			��BOOL���Ƿ��ȡ�ɹ�
	 */ 
	bool orderPacketGetValue(int dataId, int readValue) const;

	/**
	 * ���ܣ��������ݰ�д������
	 * ���룺
			param1: ��int�����ݰ�ID
			param2: ��id������id
			param3����int��д�������
	 * �����
			��bool���Ƿ�д��ɹ�
	 */
	bool writePacketSetValue(int nPacketId, int dataId, int writeValue) const;

	/**
	 * ���ܣ��������ݰ���ȡ����
	 * ���룺
			param1: ��int�����ݰ�ID
			param2: ��id������id
			parma3����int����ȡ��ֵ
	 * �����
			��bool���Ƿ��ȡ�ɹ�
	 */ 
	bool writePacketGetValue(int nPacketId, int dataId, int readValue) const;

	/**
	 * ���ܣ���ȡ�������ݰ�����ֵ
	 * ���룺
			param1: ��int������ID
			parma2����int����ȡ��ֵ
	 * �����
			��bool���Ƿ��ȡ�ɹ�
	 */
	bool readPacketGetValue(int dataId, int readValue) const;

	////////////////////////////////// Modbus �ӿ� ////////////////////////////////////////
	/**
	 * ���ܣ���ȡboolֵ
	 * ���룺
			param1: ��CString����ַ "PLC0$M$102"
			param2: ��bool*����ȡֵ
	 * �����
			��bool���Ƿ��ȡ�ɹ�
	 */ 
	bool readBoolValue(CString address, bool *bValue);

	/**
	 * ���ܣ�д��Boolֵ
	 * ���룺
			param1: ��CString����ַ "PLC0$M$102"
			param2: ��bool��д��ֵ
	 * �����
			��bool���Ƿ�д��ɹ�
	 */ 
	bool writeBoolValue(CString address, bool bValue);

	/**
	 * ���ܣ���ȡShortֵ
	 * ���룺
			param1: ��CString����ַ "PLC0$M$102"
			param2: ��short*����ȡֵ
	 * �����
			��bool���Ƿ��ȡ�ɹ�
	 */ 
	bool readShortValue(CString address, short *shValue);

	/**
	 * ���ܣ�д��Shortֵ
	 * ���룺
			param1: ��CString����ַ "PLC0$M$102"
			param2: ��short��д��ֵ
	 * �����
			��bool���Ƿ�д��ɹ�
	 */ 
	bool writeShortValue(CString address, short shValue);
	
	/**
	 * ���ܣ���ȡIntֵ
	 * ���룺
			param1: ��CString����ַ "PLC0$M$102"
			param2: ��int*����ȡֵ
	 * �����
			��bool���Ƿ��ȡ�ɹ�
	 */ 
	bool readIntValue(CString address, int *iValue);

	/**
	 * ���ܣ�д��Intֵ
	 * ���룺
			param1: ��CString����ַ "PLC0$M$102"
			param2: ��int��д��ֵ
	 * �����
			��bool���Ƿ�д��ɹ�
	 */ 
	bool writeIntValue(CString address, int iValue);

	/**
	 * ���ܣ���ȡFloatֵ
	 * ���룺
			param1: ��CString����ַ "PLC0$M$102"
			param2: ��float*����ȡֵ
	 * �����
			��bool���Ƿ��ȡ�ɹ�
	 */ 
	bool readFloatValue(CString address, float *fValue);

	/**
	 * ���ܣ�д��Floatֵ
	 * ���룺
			param1: ��CString����ַ "PLC0$M$102"
			param2: ��float��д��ֵ
	 * �����
			��bool���Ƿ�д��ɹ�
	 */ 
	bool writeFloatValue(CString address, float fValue);

private:
	CPLCModule(void);
	CPLCModule(const CPLCModule &);
	CPLCModule & operator=(const CPLCModule &);
	~CPLCModule(void);

	static CPLCModule *m_instance;
	static CMutex m_mutex;

	class PLCModuleGarbo
	{
	public:
		~PLCModuleGarbo()
		{
			release();
		}
	};

	static PLCModuleGarbo garbo;

private:// �߳�
	static DWORD __stdcall ThreadUpdate(LPVOID lpParameter);

	static bool m_bIsCloseThread;							// �Ƿ�ر��߳�(��������ʱʹ��)
	static HANDLE m_hThread;								// ״̬�߳̾��
	static int m_sleepTime;									// PLCģ���̼߳��ʱ�䣨��λ��ms��
	static bool m_bIsStartThread;							// �Ƿ�ʼ�߳�
};

