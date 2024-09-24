/*----------------------------------------------------------------
 * ��Ȩ���� (c) �����е�Ƶ���װ�����޹�˾ ��������Ȩ����
 * ��˾���ƣ������е�Ƶ���װ�����޹�˾
 * 
 * �����ߣ���Ƚ
 * ����ʱ�䣺2024-8-20
 * �汾��V1.0.0
 * ��������װLPWʶ���
 *
 * ----------------------------------------------------------------
 * �޸��ˣ�
 * ʱ�䣺
 * �޸�˵����
 *
 * �汾��
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
	ILMatchPtr m_lmatch;//����˽�л�
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
	void displayTemplate(CStatic* pic_item);//��ʾģ��
	bool LoadImage ( CString  filename ); 
	bool SaveMatch ( CString  filename ); 
	bool LoadMatch ( CString  filename );

	MATRES &matchCenterNear(ILImage *  img);
	
private:
	MATRES m_mResTemp;											// ��ʱ�����������
	int _nScore;
	int _iResultNum;
};

