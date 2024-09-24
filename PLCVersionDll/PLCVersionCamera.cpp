#include "StdAfx.h"
#include "PLCVersionCamera.h"

void __stdcall CPLCVersionCamera::HikMacCallBack(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
{
	CPLCVersionCamera *pVsionProcess = (CPLCVersionCamera*)pUser;
	if (NULL == pData)
	{
		return;
	}
	if (NULL == pFrameInfo)
	{
		return;
	}

	pVsionProcess->m_pRealImageMac = pData;
	pVsionProcess->m_iMacroReal.cameraData = pData;
	if (pVsionProcess->saveHighCameraImage)
	{
		pVsionProcess->saveImage(pData, pFrameInfo, pVsionProcess->m_nBufferSizeForSaveImg, pVsionProcess->m_pBufferForSaveImg, pVsionProcess->highCameraFilePath);
		pVsionProcess->saveHighCameraImage = false;
	}

	if((pVsionProcess->m_iMacroReal.lpDIBBits)&&(pVsionProcess->m_pRealImageMac))
	{
		for(int i=0;i<pVsionProcess->m_iMacroReal.lHeight;i++)
		{
			for(int j=0;j<pVsionProcess->m_iMacroReal.lWidth;j++)
			{
				*(pVsionProcess->m_iMacroReal.lpDIBBits+pVsionProcess->m_lLineWidthMac*i+3*j+0)=
					*(pVsionProcess->m_pRealImageMac+pVsionProcess->m_lLineWidthCard*i+j);
				*(pVsionProcess->m_iMacroReal.lpDIBBits+pVsionProcess->m_lLineWidthMac*i+3*j+1)=
					*(pVsionProcess->m_pRealImageMac+pVsionProcess->m_lLineWidthCard*i+j);
				*(pVsionProcess->m_iMacroReal.lpDIBBits+pVsionProcess->m_lLineWidthMac*i+3*j+2)=
					*(pVsionProcess->m_pRealImageMac+pVsionProcess->m_lLineWidthCard*i+j);
			}
		}
	}

	if (pVsionProcess->outputCameraImage() == true && pVsionProcess->macImgCallback != NULL)
	{
		pVsionProcess->macImgCallback(pVsionProcess->m_iMacroReal, pVsionProcess->getUser1());
	}
}

void __stdcall CPLCVersionCamera::HikMacExcCallBack(unsigned int nMsgType, void* pUser)
{
	CPLCVersionCamera *pVsionProcess = (CPLCVersionCamera *)pUser;	
	CString strTemp;
	if (0 != nMsgType)
	{
		strTemp.Format("%d",nMsgType);
		//LogWriteLog("HIKMACCAM",strTemp);
	}
}

void __stdcall CPLCVersionCamera::HikMicCallBack(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
{
	CPLCVersionCamera *pVsionProcess = (CPLCVersionCamera*)pUser;
	if (NULL == pData)
	{
		return;
	}
	if (NULL == pFrameInfo)
	{
		return;
	}

	pVsionProcess->m_pRealImageMic = pData;
	pVsionProcess->m_iMicroReal.cameraData = pData;

	if (pVsionProcess->saveLowCameraImage)
	{
		pVsionProcess->saveImage(pData, pFrameInfo, pVsionProcess->m_nBufferSizeForSaveImg, pVsionProcess->m_pBufferForSaveImg, pVsionProcess->cameraFilePath);
		pVsionProcess->saveLowCameraImage = false;
	}

	if((pVsionProcess->m_iMicroReal.lpDIBBits)&&(pVsionProcess->m_pRealImageMic))
	{
		for(int i=0;i<pVsionProcess->m_iMicroReal.lHeight;i++)
		{
			for(int j=0;j<pVsionProcess->m_iMicroReal.lWidth;j++)
			{
				*(pVsionProcess->m_iMicroReal.lpDIBBits+pVsionProcess->m_lLineWidthMic*i+3*j+0)=
					*(pVsionProcess->m_pRealImageMic+pVsionProcess->m_lLineWidthCard*i+j);
				*(pVsionProcess->m_iMicroReal.lpDIBBits+pVsionProcess->m_lLineWidthMic*i+3*j+1)=
					*(pVsionProcess->m_pRealImageMic+pVsionProcess->m_lLineWidthCard*i+j);
				*(pVsionProcess->m_iMicroReal.lpDIBBits+pVsionProcess->m_lLineWidthMic*i+3*j+2)=
					*(pVsionProcess->m_pRealImageMic+pVsionProcess->m_lLineWidthCard*i+j);
			}
		}
	}

	if (pVsionProcess->outputCameraImage() == false && pVsionProcess->micImgCallback != NULL)
	{
		pVsionProcess->micImgCallback(pVsionProcess->m_iMicroReal, pVsionProcess->getUser2());
	}
}

void __stdcall CPLCVersionCamera::HikMicExcCallBack(unsigned int nMsgType, void* pUser)
{
	CPLCVersionCamera *pVsionProcess = (CPLCVersionCamera *)pUser;	
	CString strTemp;
	if (0 != nMsgType)
	{
		strTemp.Format("%d",nMsgType);
		//LogWriteLog("HIKMACCAM",strTemp);
	}
}

CPLCVersionCamera::CPLCVersionCamera(void)
{
	m_pRealImageMac = NULL;
	m_pRealImageMic = NULL;
	m_hHikMacHandle = NULL;
	m_hHikMicHandle = NULL;
	m_pBufferForSaveImg = NULL;
	macImgCallback = NULL;
	micImgCallback = NULL;
	pTempUser1 = pTempUser2 = NULL;
	m_nBufferSizeForSaveImg = 0;

	// �߱�
	readCameraConfig(20);
	// �ͱ�
	readCameraConfig(10);

	cameraIsInitialization = false;

	saveHighCameraImage = false;
	saveLowCameraImage = false;
	highCameraFilePath = "";
	cameraFilePath = "";
	outputHighCameraImage = true;
	hasStopCapture = true;

	initImageParams();
}


CPLCVersionCamera::~CPLCVersionCamera(void)
{
}

void CPLCVersionCamera::initImageParams()
{
	memset(&m_stHikDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
	if (NULL == m_pBufferForSaveImg)
	{
		m_nBufferSizeForSaveImg = IMAGE_WIDTH * IMAGE_HEIGHT * 3 + 2048;		
		m_pBufferForSaveImg = (unsigned char*)malloc(m_nBufferSizeForSaveImg);
		if (NULL == m_pBufferForSaveImg)
		{
			return;
		}
	}

	m_hMarcoDIBBits = (HGLOBAL)::GlobalAlloc(GMEM_MOVEABLE, IMAGE_WIDTH * IMAGE_HEIGHT * 3 + 10000);
	m_iMacroReal.lpDIBBits = (unsigned char*)::GlobalLock(m_hMarcoDIBBits);
	m_iMacroReal.lWidth = IMAGE_WIDTH;
	m_iMacroReal.lHeight = IMAGE_HEIGHT;

	m_hMircoDIBBits = (HGLOBAL)::GlobalAlloc(GMEM_MOVEABLE, IMAGE_WIDTH * IMAGE_HEIGHT * 3 + 10000);
	m_iMicroReal.lpDIBBits = (unsigned char*)::GlobalLock(m_hMircoDIBBits);
	m_iMicroReal.lWidth = IMAGE_WIDTH;
	m_iMicroReal.lHeight = IMAGE_HEIGHT;

	m_lLineWidthMac = (m_iMacroReal.lWidth*24+31)/32*4;
	m_lLineWidthMic = (m_iMicroReal.lWidth*24+31)/32*4;
	m_lLineWidthCard = ((m_iMicroReal.lWidth*8)+31)/32*4; 
}

BOOL CPLCVersionCamera::initCamera()
{
	CString strRet;

	// ö�����е�gige �豸
	int nReturn = MV_CC_EnumDevices(MV_GIGE_DEVICE, &m_stHikDevList);
	if (MV_OK != nReturn || 0 == m_stHikDevList.nDeviceNum)
	{
		// û�ҵ��豸���߿����豸Ϊ0
		return FALSE;
	}

	for (auto i = 0; i < m_stHikDevList.nDeviceNum; i++)
	{
		CString strCameName;
		MV_CC_DEVICE_INFO *pDeviceInfo = m_stHikDevList.pDeviceInfo[i];
		if (NULL == pDeviceInfo)
		{
			break;
		}

		strCameName.Format("%s", pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName);

		if ("MACRO" == strCameName)
		{
			m_hHikMacHandle = createCameraHandleAndOpen(pDeviceInfo, HikMacCallBack);
			if (m_hHikMacHandle == NULL)
			{
				// �����ʧ�ܣ������´�һ��
				m_hHikMacHandle = createCameraHandleAndOpen(pDeviceInfo, HikMacCallBack);
				if (m_hHikMacHandle == NULL)
				{
					return FALSE;
				}
			}

			// �����쳣�ص�
			nReturn = MV_CC_RegisterExceptionCallBack(m_hHikMacHandle, HikMacExcCallBack, this);
			if (MV_OK != nReturn)
			{
				CString strLog;
				strLog.Format("���ע���쳣�ص�1ʧ��--- %ld", nReturn);
				AfxMessageBox(strLog);
				return FALSE;
			}

			nReturn = setDeviceParams(m_hHikMacHandle, 600, 1, 30);
			if (MV_OK != nReturn)
			{
				CString strLog;
				strLog.Format("�ͱ����ò���1ʧ��--- %ld %s", nReturn, strCameName);
				AfxMessageBox(strLog);
				return FALSE;
			}
		}
		else if ("MICRO" == strCameName)
		{
			m_hHikMicHandle = createCameraHandleAndOpen(pDeviceInfo, HikMicCallBack);
			if (m_hHikMicHandle == NULL)
			{
				// �����ʧ�ܣ������´�һ��
				m_hHikMicHandle = createCameraHandleAndOpen(pDeviceInfo, HikMicCallBack);
				if (m_hHikMicHandle == NULL)
				{
					return FALSE;
				}
			}

			nReturn = MV_CC_RegisterExceptionCallBack(m_hHikMicHandle, HikMicExcCallBack, this);
			if (MV_OK != nReturn)
			{
				CString strLog;
				strLog.Format("���ע���쳣�ص�2ʧ��--- %ld", nReturn);
				AfxMessageBox(strLog);
				return FALSE;
			}

			nReturn = setDeviceParams(m_hHikMicHandle, 600, 1, 40);
			if (MV_OK != nReturn)
			{
				CString strLog;
				strLog.Format("�ͱ����ò���1ʧ��--- %ld %s", nReturn, strCameName);
				AfxMessageBox(strLog);
				return FALSE;
			}
		}
	}

	cameraIsInitialization = true;

	return TRUE;
}

void CPLCVersionCamera::macCameraStartCapture(void(__stdcall* imageCallback)(ImageInfoStruct imgInfo, void* pUser), void* pUser)
{
	if (!cameraIsInitialization || m_hHikMacHandle == NULL)
	{
		return;
	}

	macImgCallback = imageCallback;
	pTempUser1 = pUser;

	// �����ʼ�ɼ�
	int nReturn = MV_CC_StartGrabbing(m_hHikMacHandle);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("�����ʼ�ɼ�ʧ��");
		return;
	}

	hasStopCapture = false;
}

void CPLCVersionCamera::micCameraStartCapture(void(__stdcall* imageCallback)(ImageInfoStruct imgInfo, void* pUser), void* pUser)
{
	if (!cameraIsInitialization || m_hHikMicHandle == NULL)
	{
		return;
	}

	micImgCallback = imageCallback;
	pTempUser2 = pUser;

	// �ͱ������ʼ�ɼ�
	int nReturn = MV_CC_StartGrabbing(m_hHikMicHandle);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("�����ʼ�ɼ�ʧ��");
		return;
	}

	hasStopCapture = false;
}

void CPLCVersionCamera::stopCapture()
{
	if (!cameraIsInitialization || m_hHikMicHandle == NULL || m_hHikMacHandle == NULL)
	{
		return;
	}
	// �߱����ֹͣ�ɼ�
	int nReturn = MV_CC_StopGrabbing(m_hHikMacHandle);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("���ֹͣ�ɼ�ʧ��");
	}
	// �ͱ����ֹͣ�ɼ�
	nReturn = MV_CC_StopGrabbing(m_hHikMicHandle);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("���ֹͣ�ɼ�ʧ��");
	}

	hasStopCapture = true;
}

void CPLCVersionCamera::closeCamera()
{
	if (!hasStopCapture)
	{
		stopCapture();
	}

	// �رո߱����
	MV_CC_CloseDevice(m_hHikMacHandle);
	MV_CC_DestroyHandle(m_hHikMacHandle);

	// �رյͱ����
	MV_CC_CloseDevice(m_hHikMicHandle);
	MV_CC_DestroyHandle(m_hHikMicHandle);

	if (m_pBufferForSaveImg)
	{
		free(m_pBufferForSaveImg);
		m_pBufferForSaveImg = NULL;
	}
	m_nBufferSizeForSaveImg = 0;

	if(m_hMarcoDIBBits)
	{
		::GlobalUnlock(m_hMarcoDIBBits);
		::GlobalFree(m_hMarcoDIBBits);
	}

	if(m_hMircoDIBBits)
	{
		::GlobalUnlock(m_hMircoDIBBits);
		::GlobalFree(m_hMircoDIBBits);
	}

	m_hHikMacHandle = NULL;
	m_hHikMicHandle = NULL;
	m_pRealImageMac = NULL;
	m_pRealImageMic = NULL;
	pTempUser1 = NULL;
	pTempUser2 = NULL;
}

void CPLCVersionCamera::saveCameraImage(bool saveMacCamera, bool saveMicCamera, CString highCameraPath, CString cameraPath)
{
	saveHighCameraImage = saveMacCamera;
	saveLowCameraImage = saveMicCamera;
	highCameraFilePath = highCameraPath;
	cameraFilePath = cameraPath;
}

void* CPLCVersionCamera::getUser1() 
{
	return pTempUser1;	
}

void* CPLCVersionCamera::getUser2()
{
	return pTempUser2;
}

void CPLCVersionCamera::switchCameraImage()
{
	outputHighCameraImage = !outputHighCameraImage;
}

bool CPLCVersionCamera::outputCameraImage()
{
	return outputHighCameraImage;
}

void* CPLCVersionCamera::createCameraHandleAndOpen(const MV_CC_DEVICE_INFO* pstDevInfo, void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser))
{
	void* cameraHandle = NULL;
	int nReturn = MV_CC_CreateHandle(&cameraHandle, pstDevInfo);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("δ�ɹ��������");
		MV_CC_DestroyHandle(cameraHandle);
		cameraHandle = NULL;
	}

	nReturn = MV_CC_RegisterImageCallBackEx(cameraHandle, cbOutput, this);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("���ע��ʧ�� ---");
		MV_CC_DestroyHandle(cameraHandle);
		cameraHandle = NULL;
	}

	nReturn = MV_CC_OpenDevice(cameraHandle, MV_ACCESS_Exclusive, 0);
	if (MV_OK != nReturn)
	{
		MV_CC_DestroyHandle(cameraHandle);
		cameraHandle = NULL;
	}
	
	return cameraHandle;
}

BOOL CPLCVersionCamera::setDeviceParams(void* cameraHandle, long lExpTime, long lGain, long lGamma)
{
	int nReturn = MV_OK;
	CString strRet = "";

	// ����֡��
	nReturn = MV_CC_SetBoolValue(cameraHandle, "AcquisitionFrameRateEnable", true);
	if (nReturn != MV_OK)
	{
		strRet.Format("nRet = %d m_hHikHandle = %d",nReturn, cameraHandle);

		AfxMessageBox("ZhenLv--Gongnengʧ��" + strRet);
		return nReturn;
	}

	// �͹�Դ��˸Ƶ��һ��
	nReturn = MV_CC_SetFloatValue(cameraHandle, "AcquisitionFrameRate", 30);
	if (nReturn != MV_OK)
	{
		AfxMessageBox("�������֡��ʧ��");
		return nReturn;
	}

	// �����ڴ���ģʽ
	nReturn = MV_CC_SetEnumValue(cameraHandle, "TriggerMode", MV_TRIGGER_MODE_OFF);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("��������ڴ���ģʽʧ��");
		return nReturn;
	}

	// ���������ɼ�ģʽ
	nReturn = MV_CC_SetEnumValue(cameraHandle, "AcquisitionMode", MV_ACQ_MODE_CONTINUOUS);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("������������ɼ�ģʽʧ��");
		return nReturn;
	}

	// ����ͼƬ��С
	nReturn = MV_CC_SetIntValue(cameraHandle, "Width", IMAGE_WIDTH);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("ͼ��������ʧ��");
		return nReturn;
	}

	nReturn = MV_CC_SetIntValue(cameraHandle, "Height", IMAGE_HEIGHT);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("ͼ��߶�����ʧ��");
		return nReturn;
	}

	// ����OffsetX��OffsetX���Ϊ32
	nReturn = MV_CC_SetIntValue(cameraHandle, "OffsetX", 0);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("ͼ��OffsetX����ʧ��");
		return nReturn;
	}

	// �����ع�ģʽ
	nReturn = MV_CC_SetEnumValue(cameraHandle, "ExposureMode", MV_EXPOSURE_MODE_TIMED); // �Զ��ع�ģʽ��timed
	if (MV_OK != nReturn)
	{
		AfxMessageBox("��������ع�ģʽʧ��");
		return nReturn;
	}

	nReturn = MV_CC_SetEnumValue(cameraHandle, "ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("��������Զ��ع�ģʽʧ��");
		return nReturn;
	}

	nReturn = MV_CC_SetFloatValue(cameraHandle, "ExposureTime", lExpTime);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("��������ع�ʱ��ʧ��");
		return nReturn;
	}

	// ��������ģʽ -- ��������ǰ�Ȱ��Զ�����رգ�ʧ�����践��
	nReturn = MV_CC_SetEnumValue(cameraHandle, "GainAuto", MV_GAIN_MODE_OFF);
	nReturn = MV_CC_SetFloatValue(cameraHandle, "Gain", lGain);
	if (MV_OK != nReturn)//
	{
		AfxMessageBox("�����������ʧ��");
		return nReturn;
	}

	// ���ý�ħGmma ģʽ
	nReturn = MV_CC_SetBoolValue(cameraHandle, "GammaEnable", true);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("GammaEnableʹ�����ô���");
		return nReturn;
	}

	nReturn = MV_CC_SetFloatValue(cameraHandle, "Gamma", (float)lGamma/10);
	if (MV_OK != nReturn)
	{
		AfxMessageBox("�������Gammaʧ��");
		return nReturn;
	}

	return nReturn;
}

void CPLCVersionCamera::readCameraConfig(int cameraMark)
{
	CString m_strConfigFile = "..\\Data\\Machine\\Config.dat";
	CString strTemp = "";

	if (cameraMark == 10)
	{
		strTemp = "CAMMiC";
		if (OpenFileData(m_strConfigFile))
		{
			ReadNumLong(strTemp+"_EXPTIME",&(m_micCameraConfig.lMacroExpTime),m_strConfigFile);
			ReadNumLong(strTemp+"_GAIN0",&(m_micCameraConfig.lMacroGain0),m_strConfigFile);
			ReadNumLong(strTemp+"_GAIN1",&(m_micCameraConfig.lMacroGain1),m_strConfigFile);
			ReadNumLong(strTemp+"_GAIN2",&(m_micCameraConfig.lMacroGain2),m_strConfigFile);
			ReadNumLong(strTemp+"_BINTHR",&(m_micCameraConfig.lBinaryThreshold),m_strConfigFile);
			ReadNumDouble(strTemp+"_SCALE",&(m_micCameraConfig.dScaleFactor),m_strConfigFile);
		}
	}

	if (cameraMark == 20)
	{
		strTemp = "CAMMAC";
		if (OpenFileData(m_strConfigFile))
		{
			ReadNumLong(strTemp+"_EXPTIME",&(m_macCameraConfig.lMacroExpTime),m_strConfigFile);
			ReadNumLong(strTemp+"_GAIN0",&(m_macCameraConfig.lMacroGain0),m_strConfigFile);
			ReadNumLong(strTemp+"_GAIN1",&(m_macCameraConfig.lMacroGain1),m_strConfigFile);
			ReadNumLong(strTemp+"_GAIN2",&(m_macCameraConfig.lMacroGain2),m_strConfigFile);
			ReadNumLong(strTemp+"_BINTHR",&(m_macCameraConfig.lBinaryThreshold),m_strConfigFile);
			ReadNumDouble(strTemp+"_SCALE",&(m_macCameraConfig.dScaleFactor),m_strConfigFile);
		}
	}
}

void CPLCVersionCamera::saveImage(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, unsigned int m_nBufSize, unsigned char* imageBuffer, CString filePath)
{
	MV_SAVE_IMAGE_PARAM_EX strParam = {0};
	strParam.enImageType = MV_Image_Bmp;
	strParam.enPixelType = pFrameInfo->enPixelType;
	strParam.nBufferSize = m_nBufSize;
	strParam.nWidth = pFrameInfo->nWidth;
	strParam.nHeight = pFrameInfo->nHeight;
	strParam.nDataLen = pFrameInfo->nFrameLen;
	strParam.pData = pData;
	strParam.pImageBuffer = imageBuffer;
	strParam.nJpgQuality = 80;
	
	int nReturn = MV_CC_SaveImageEx(&strParam);
	FILE* fp = fopen(filePath,"wb");
	fwrite(imageBuffer, 1, strParam.nImageLen, fp);
	fclose(fp);
}