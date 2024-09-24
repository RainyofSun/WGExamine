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
	 * 功能：初始化相机
	 */ 
	BOOL initCamera();

	/**
	 * 功能：高倍相机开始采集图像
	 * 输入：
			param1: （ImageInfoStruct）函数回调
	 */ 
	void macCameraStartCapture(void(__stdcall* imageCallback)(ImageInfoStruct imgInfo, void* pUser), void* pUser);

	/**
	 * 功能：低倍相机开始采集图像
	 * 输入：
			param1: （ImageInfoStruct）函数回调
	 */ 
	void micCameraStartCapture(void(__stdcall* imageCallback)(ImageInfoStruct imgInfo, void* pUser), void* pUser);
	
	/**
	 * 功能：停止采集
	 */ 
	void stopCapture();

	/**
	 * 功能：关闭相机
	 */ 
	void closeCamera();

	/**
	 * 功能：图片保存
	 * 输入：
			param1: （bool）保存高倍镜
			param2: （bool）保存低倍镜
			param3: （CString）高倍镜保存的路径
			param4: （CString）低倍镜保存的路径
			param4: 
	 */ 
	void saveCameraImage(bool saveMacCamera, bool saveMicCamera, CString highCameraPath, CString cameraPath);

	/**
	 * 功能：获取临时指针
	 */ 
	void* getUser1();
	void* getUser2();

	/**
	 * 功能：切换画面
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

	// 高倍相机句柄
	void* m_hHikMacHandle;
	// 低倍相机句柄
	void* m_hHikMicHandle;
	// 高倍相机参数
	CameraConfig m_macCameraConfig;
	// 低倍相机参数
	CameraConfig m_micCameraConfig;

	long m_lLineWidthMac;
	long m_lLineWidthMic;
	long m_lLineWidthCard;

	// 设备信息列表，用来存储设备列表
	MV_CC_DEVICE_INFO_LIST m_stHikDevList;
	// 用于保存图像的缓存
	unsigned char* m_pBufferForSaveImg;
	unsigned int m_nBufferSizeForSaveImg;

	// 存储高倍图片/低倍图片
	bool saveHighCameraImage;
	bool saveLowCameraImage;
	// 图片存储路径
	CString highCameraFilePath;
	CString cameraFilePath;

	// 高倍图片回调
	void(__stdcall* macImgCallback)(ImageInfoStruct imgInfo, void* pUser);
	// 低倍图片回调
	void(__stdcall* micImgCallback)(ImageInfoStruct imgInfo, void* pUser);
private:
	/**
	 * 功能：初始化相机参数
	 */ 
	void initImageParams();

	/**
	 * 功能：创建设备句柄并打开设备
	 * 输入：
			param1: （void*）设备句柄
			param2: （void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)）回调函数
	 * 输出：
			（BOOL）设备句柄是否创建并打开
	 */ 
	void* createCameraHandleAndOpen(const MV_CC_DEVICE_INFO* pstDevInfo, void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser));

	/**
	 * 功能：设置采集参数
	 * 输入：
			param1: （void*）设备句柄
			param2: （long）曝光时间
			param3: （long）相机增益
			param4: （long）Gamma
	 * 输出：
			（BOOL）参数是否设置成功
	 */ 
	BOOL setDeviceParams(void* cameraHandle, long lExpTime, long lGain, long lGamma);

	/**
	 * 功能：读取相机参数
	 * 输入：
		param1: （int）高倍/低倍区分
	 */ 
	void readCameraConfig(int cameraMark);

	/**
	 * 功能：保存图片
	 * 输入：
			param1: （unsigned char*） pData
			param2: （MV_FRAME_OUT_INFO_EX*）图片信息
			param3:	（unsigned int）图片大小
			param4: （unsigned char*)图片buffer
			param5: （CString)存储路径
	 */ 
	void saveImage(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, unsigned int m_nBufSize, unsigned char* imageBuffer, CString filePath);

private:
	// 相机是否完成初始化
	bool cameraIsInitialization;
	// 输出哪一路画面
	bool outputHighCameraImage;
	bool hasStopCapture;
	// 临时指针
	void* pTempUser1;
	void* pTempUser2;
};

