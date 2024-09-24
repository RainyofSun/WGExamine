#pragma once
#include "MVCAPI.h"
#include "MvCameraControl.h"
#include "CameraParams.h"
#include "PLCVersionConfig.h"
#include "ExportDll.h"

#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT CPLCVersionCamera
{
public:
	CPLCVersionCamera(void);
	~CPLCVersionCamera(void);

	static void __stdcall HikMacCallBack(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
	static void __stdcall HikMicCallBack(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
	static void __stdcall HikMacExcCallBack(unsigned int nMsgType, void* pUser);				
	static void __stdcall HikMicExcCallBack(unsigned int nMsgType, void* pUser);
	/**
	 * ���ܣ���ʼ�����
	 */ 
	BOOL initCamera();

	/**
	 * ���ܣ��߱������ʼ�ɼ�ͼ��
	 * ���룺
			param1: ��ImageInfoStruct�������ص�
	 */ 
	void macCameraStartCapture(void(__stdcall* imageCallback)(ImageInfoStruct imgInfo, void* pUser), void* pUser);

	/**
	 * ���ܣ��ͱ������ʼ�ɼ�ͼ��
	 * ���룺
			param1: ��ImageInfoStruct�������ص�
	 */ 
	void micCameraStartCapture(void(__stdcall* imageCallback)(ImageInfoStruct imgInfo, void* pUser), void* pUser);
	
	/**
	 * ���ܣ�ֹͣ�ɼ�
	 */ 
	void stopCapture();

	/**
	 * ���ܣ��ر����
	 */ 
	void closeCamera();

	/**
	 * ���ܣ�ͼƬ����
	 * ���룺
			param1: ��bool������߱���
			param2: ��bool������ͱ���
			param3: ��CString���߱��������·��
			param4: ��CString���ͱ��������·��
			param4: 
	 */ 
	void saveCameraImage(bool saveMacCamera, bool saveMicCamera, CString highCameraPath, CString cameraPath);

	/**
	 * ���ܣ���ȡ��ʱָ��
	 */ 
	void* getUser1();
	void* getUser2();

	/**
	 * ���ܣ��л�����
	 */ 
	void switchCameraImage();
	bool outputCameraImage();

public:

	HGLOBAL m_hMarcoDIBBits;
	HGLOBAL m_hMircoDIBBits;

	ImageInfoStruct m_iMacroReal;
	ImageInfoStruct m_iMicroReal;
	unsigned char* m_pRealImageMac;
	unsigned char* m_pRealImageMic;

	// �߱�������
	void* m_hHikMacHandle;
	// �ͱ�������
	void* m_hHikMicHandle;
	// �߱��������
	CameraConfig m_macCameraConfig;
	// �ͱ��������
	CameraConfig m_micCameraConfig;

	long m_lLineWidthMac;
	long m_lLineWidthMic;
	long m_lLineWidthCard;

	// �豸��Ϣ�б������洢�豸�б�
	MV_CC_DEVICE_INFO_LIST m_stHikDevList;
	// ���ڱ���ͼ��Ļ���
	unsigned char* m_pBufferForSaveImg;
	unsigned int m_nBufferSizeForSaveImg;

	// �洢�߱�ͼƬ/�ͱ�ͼƬ
	bool saveHighCameraImage;
	bool saveLowCameraImage;
	// ͼƬ�洢·��
	CString highCameraFilePath;
	CString cameraFilePath;

	// �߱�ͼƬ�ص�
	void(__stdcall* macImgCallback)(ImageInfoStruct imgInfo, void* pUser);
	// �ͱ�ͼƬ�ص�
	void(__stdcall* micImgCallback)(ImageInfoStruct imgInfo, void* pUser);
private:
	/**
	 * ���ܣ���ʼ���������
	 */ 
	void initImageParams();

	/**
	 * ���ܣ������豸��������豸
	 * ���룺
			param1: ��void*���豸���
			param2: ��void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)���ص�����
	 * �����
			��BOOL���豸����Ƿ񴴽�����
	 */ 
	void* createCameraHandleAndOpen(const MV_CC_DEVICE_INFO* pstDevInfo, void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser));

	/**
	 * ���ܣ����òɼ�����
	 * ���룺
			param1: ��void*���豸���
			param2: ��long���ع�ʱ��
			param3: ��long���������
			param4: ��long��Gamma
	 * �����
			��BOOL�������Ƿ����óɹ�
	 */ 
	BOOL setDeviceParams(void* cameraHandle, long lExpTime, long lGain, long lGamma);

	/**
	 * ���ܣ���ȡ�������
	 * ���룺
		param1: ��int���߱�/�ͱ�����
	 */ 
	void readCameraConfig(int cameraMark);

	/**
	 * ���ܣ�����ͼƬ
	 * ���룺
			param1: ��unsigned char*�� pData
			param2: ��MV_FRAME_OUT_INFO_EX*��ͼƬ��Ϣ
			param3:	��unsigned int��ͼƬ��С
			param4: ��unsigned char*)ͼƬbuffer
			param5: ��CString)�洢·��
	 */ 
	void saveImage(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, unsigned int m_nBufSize, unsigned char* imageBuffer, CString filePath);

private:
	// ����Ƿ���ɳ�ʼ��
	bool cameraIsInitialization;
	// �����һ·����
	bool outputHighCameraImage;
	bool hasStopCapture;
	// ��ʱָ��
	void* pTempUser1;
	void* pTempUser2;
};

