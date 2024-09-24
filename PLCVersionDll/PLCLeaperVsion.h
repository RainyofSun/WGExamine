/*----------------------------------------------------------------
 * 版权所有 (c) 北京中电科电子装备有限公司 保留所有权利。
 * 公司名称：北京中电科电子装备有限公司
 * 
 * 创建者：刘冉
 * 创建时间：2024-8-20
 * 版本：V1.0.0
 * 描述：封装LPW识别库
 *
 * ----------------------------------------------------------------
 * 修改人：
 * 时间：
 * 修改说明：
 *
 * 版本：
 *----------------------------------------------------------------*/
#pragma once

#include "LPVCore.h"
#include "LPVGeom.h"
#include "LPVPat.h"
#include "PLCVersionConfig.h"

#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT CPLCLeaperVsion
{
public:
	CPLCLeaperVsion(void);
	~CPLCLeaperVsion(void);

public:
	ILMatchPtr m_lmatch;//后期私有化
	ILImagePtr m_source_img;
	ILImagePtr m_source_MICimg;
	
public:
	void displayImage(ILImagePtr img, CStatic* pic_item,
		ILRectRegionPtr roi = NULL, ILMatchResultsPtr match_results = NULL,
		int cur_result_index = -1);

	bool Learn(ILImage * img,ILRegion * region);
	void setScore(int nScore);
	void setMaxcount(int ncount);
	int Match(ILImage *  img);
	void setDetailLevel(double dLevel);
	void setMatchParam(int nScore,double dLevel,int ncount);
	//ILImagePtr m_source_img;
	ILRectRegionPtr m_roi;
	ILImagePtr m_template_img;
	ILMatchResultsPtr m_match_results;
	ILMatchResultsPtr m_match_results_temp;
	void GetPatImage(ILImage *  img );
	void GetPatMask ( ILImage *  mask ); 
	void displayTemplate(CStatic* pic_item);//显示模版
	bool LoadImage ( CString  filename ); 
	bool SaveMatch ( CString  filename ); 
	bool LoadMatch ( CString  filename );

	MATRES &matchCenterNear(ILImage *  img);
	
private:
	MATRES m_mResTemp;											// 临时保存搜索结果
	int _nScore;
	int _iResultNum;
};

