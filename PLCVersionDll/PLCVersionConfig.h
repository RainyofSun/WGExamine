#pragma once
#include <stdint.h>

// 图像宽
#define IMAGE_WIDTH		580
// 图像高
#define IMAGE_HEIGHT	480

// 图像信息数据
struct ImageInfoStruct
{
	long lWidth;
	long lHeight;
	unsigned char* lpDIBBits;
	// 存储相机返回的图像数据
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
// 灰度匹配相关参数
struct PatternSearchParam
{
	int _iAccuracy;										// 精度
	int _iCoarsescale;									// 速度
	double _dAngleLow;									// 旋转自由度Low
	double _dAngleHigh;									// 旋转自由度High
	double _dAngleDup;									// 旋转自由度Dup

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

// 图像搜索参数数据对象
struct ImageSearchParam
{
	int maxNumToFind;									// 最大搜索数
	double fRotate;										// 角度范围
	double dContrastThr;								// 对比度阈值
	double dOverThr;									// 重叠阈值
	double dScale;										// 缩放系数

	double dGranuFine;									// 颗粒度
	double dgranularity ;								// 颗粒细度	
	unsigned char ucnoiseThre ;							// 噪声阈值
	double ltotalGradMagThre;							// 梯度幅值和阈值

	double dScore;										// 相似度阈值
	bool bIgnPol;										// 是否忽略极性
	PatternSearchParam _Pattern;						// Pattersearch参数

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

// 识别结果数据对象
struct MATRES{
	double dScore;                     //评价分数		
	double dPosX;					   //X方向平移		
	double dPosY;                      //Y方向平移		
	double dRotate;                    //旋转角度		
	double dSize;                      //一致缩放		
	double dSizeX;                     //X方向缩放		
	double dSizeY;                     //Y方向缩放

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

// 相机参数
struct CameraConfig 
{
	long lMacroExpTime;//曝光时间
	long lMacroGain0;//增益
	long lMacroGain1;
	long lMacroGain2;
	long lBinaryThreshold;
	double dScaleFactor;//缩放系数

	CameraConfig()
	{
		InitParam();
	}

	void InitParam()
	{
		lMacroExpTime = 100;//曝光时间
		lMacroGain0 = 100;//增益
		lMacroGain1 = 0;
		lMacroGain2 = 0;
		lBinaryThreshold = 0;
		dScaleFactor = 1;//缩放系数
	}
};