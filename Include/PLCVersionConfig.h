#pragma once
#include <stdint.h>

// ͼ���
#define IMAGE_WIDTH		580
// ͼ���
#define IMAGE_HEIGHT	480

// ͼ����Ϣ����
struct ImageInfoStruct
{
	long lWidth;
	long lHeight;
	unsigned char* lpDIBBits;
	// �洢������ص�ͼ������
	unsigned char* cameraData;

	ImageInfoStruct()
	{
		lWidth = lHeight = 0;
		lpDIBBits = NULL;
		cameraData = NULL;
	}

	ImageInfoStruct operator=(const ImageInfoStruct &other)
	{
		lWidth = other.lWidth;
		lHeight = other.lHeight;
		lpDIBBits = other.lpDIBBits;
		cameraData = other.cameraData;
		return *this;
	}
};
// �Ҷ�ƥ����ز���
struct PatternSearchParam
{
	int _iAccuracy;										// ����
	int _iCoarsescale;									// �ٶ�
	double _dAngleLow;									// ��ת���ɶ�Low
	double _dAngleHigh;									// ��ת���ɶ�High
	double _dAngleDup;									// ��ת���ɶ�Dup

	int _nAcceptNum;
	double _dAcceptThre;
	double _dConfusionThre;
	double _dOverlapThre;

	PatternSearchParam()
	{
		InitParam();
	}

	void InitParam()
	{
		_iAccuracy = 0;
		_iCoarsescale = 2;
		_dAngleLow = -15.0;
		_dAngleHigh = 15.0;
		_dAngleDup = 360.0;
		_nAcceptNum = 10;
		_dAcceptThre = 0.4;
		_dConfusionThre = 0.8;
		_dOverlapThre = 0.1;
	}

	PatternSearchParam operator= (PatternSearchParam &other)
	{
		_iAccuracy = other._iAccuracy;
		_iCoarsescale = other._iCoarsescale;
		_dAngleLow = other._dAngleLow;
		_dAngleHigh = other._dAngleHigh;
		_dAngleDup = other._dAngleDup;
		_nAcceptNum = other._nAcceptNum;
		_dAcceptThre = other._dAcceptThre;
		_dConfusionThre = other._dConfusionThre;
		_dOverlapThre = other._dOverlapThre;
		return *this;
	}
};

// ͼ�������������ݶ���
struct ImageSearchParam
{
	int maxNumToFind;									// ���������
	double fRotate;										// �Ƕȷ�Χ
	double dContrastThr;								// �Աȶ���ֵ
	double dOverThr;									// �ص���ֵ
	double dScale;										// ����ϵ��

	double dGranuFine;									// ������
	double dgranularity ;								// ����ϸ��	
	unsigned char ucnoiseThre ;							// ������ֵ
	double ltotalGradMagThre;							// �ݶȷ�ֵ����ֵ

	double dScore;										// ���ƶ���ֵ
	bool bIgnPol;										// �Ƿ���Լ���
	PatternSearchParam _Pattern;						// Pattersearch����

	ImageSearchParam()
	{
		InitParam();
	}

	void InitParam()
	{
		maxNumToFind = 10;
		fRotate = 5.0;
		dScale = 0.2;
		dContrastThr = 10.0;
		dOverThr = 0.8;

		dGranuFine = 1.0;
		dgranularity = 4.0;
		ucnoiseThre = 30;
		ltotalGradMagThre = 750;

		dScore = 0.9;
		bIgnPol = false;
	}

	ImageSearchParam operator= (ImageSearchParam &other)
	{
		maxNumToFind = other.maxNumToFind;
		fRotate = other.fRotate;
		dScale = other.dScale;
		dContrastThr = other.dContrastThr;
		dOverThr = other.dOverThr;

		dGranuFine = other.dGranuFine;
		dgranularity = other.dgranularity;
		ucnoiseThre = other.ucnoiseThre;
		ltotalGradMagThre = other.ltotalGradMagThre;

		dScore = other.dScore;
		bIgnPol = other.bIgnPol;

		_Pattern = other._Pattern;

		return *this;
	}
};

// ʶ�������ݶ���
struct MATRES{
	double dScore;                     //���۷���		
	double dPosX;					   //X����ƽ��		
	double dPosY;                      //Y����ƽ��		
	double dRotate;                    //��ת�Ƕ�		
	double dSize;                      //һ������		
	double dSizeX;                     //X��������		
	double dSizeY;                     //Y��������

	MATRES()
	{
		SetParaZero();
	}

	void SetParaZero()
	{
		dScore = 0;                     		
		dPosX = 0;                 		
		dPosY = 0;                    		
		dRotate = 0;                   		
		dSize = 0;                       		
		dSizeX = 0;                     		
		dSizeY = 0;                     
	}
	MATRES operator= (MATRES &other)
	{
		dScore = other.dScore;
		dPosX = other.dPosX;
		dPosY = other.dPosY;
		dRotate = other.dRotate;
		dSize = other.dSize;
		dSizeX = other.dSizeX;
		dSizeY = other.dSizeY;

		return *this;
	}
};

// �������
struct CameraConfig 
{
	long lMacroExpTime;//�ع�ʱ��
	long lMacroGain0;//����
	long lMacroGain1;
	long lMacroGain2;
	long lBinaryThreshold;
	double dScaleFactor;//����ϵ��

	CameraConfig()
	{
		InitParam();
	}

	void InitParam()
	{
		lMacroExpTime = 100;//�ع�ʱ��
		lMacroGain0 = 100;//����
		lMacroGain1 = 0;
		lMacroGain2 = 0;
		lBinaryThreshold = 0;
		dScaleFactor = 1;//����ϵ��
	}
};