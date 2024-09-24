#include "StdAfx.h"
#include "PLCLeaperVsion.h"
#include "DisplayHelper.h"

CPLCLeaperVsion::CPLCLeaperVsion(void)
{
	m_source_img = m_source_MICimg = NULL;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	m_lmatch.CreateInstance(__uuidof(LMatch));
	m_template_img.CreateInstance(__uuidof(LImage));
	m_source_img.CreateInstance(__uuidof(LImage));
	m_source_MICimg.CreateInstance(__uuidof(LImage));
	m_roi.CreateInstance(__uuidof(LRectRegion));
	_iResultNum = 0;
}


CPLCLeaperVsion::~CPLCLeaperVsion(void)
{
	CoUninitialize();
}

bool CPLCLeaperVsion::Learn(ILImage * img,ILRegion * region)
{
	if (LPVNoError != m_lmatch->Learn(img, region))
	{
		int err = m_lmatch->Learn(img, region);
		CString temperr;
		temperr.Format("err=%d",err);
		AfxMessageBox(temperr);
		return false;

	}
	return true;

}
int CPLCLeaperVsion::Match(ILImage *  img)
{
	m_lmatch->StrictScore  = true;
	if (LPVNoError != (LPVErrorCode)m_lmatch->Match(img, NULL, &m_match_results_temp/*m_match_results*/))
	{
		return 0;
	}

	return m_match_results_temp->Count();
}
MATRES &CPLCLeaperVsion::matchCenterNear(ILImage *  img)
{
	m_mResTemp.SetParaZero();
	_iResultNum = 0;
	if(Match(img))
	{
		ILMatchResultPtr result = m_match_results_temp->Item(0);

		double dCenter_X = img->Width / 2;
		double dCenter_Y = img->Height / 2;
		int nResNum = m_match_results_temp->Count();
		if(nResNum > 0)//有搜索到结果
		{
			// 从搜寻结果中获得与中心点距离最小的点
			double dia = dCenter_X*dCenter_X + (dCenter_Y)*(dCenter_Y);
			double dia2 = 0;
			for(int i=0; i<nResNum; i++)
			{
				result = m_match_results_temp->Item(i);
				int temp11 = result->Score;
				dia2 = (result->Center->X-dCenter_X)*(result->Center->X-dCenter_X)+(result->Center->Y-dCenter_Y)*(result->Center->Y-dCenter_Y);
				if((dia2 < dia) && (result->Score >= _nScore))
				{
					dia = dia2;

					m_mResTemp.dScore = result->Score; 
					m_mResTemp.dPosX = result->Center->X;
					m_mResTemp.dPosY = result->Center->Y;
					m_mResTemp.dSize = result->Scale;
					_iResultNum++;
				}
			}
		}
	}

	return m_mResTemp;											
}
void CPLCLeaperVsion::setScore(int nScore)
{
	_nScore = nScore;
	m_lmatch->AcceptScore = nScore;
	m_lmatch->ScaleTolerance = 10;
}
void CPLCLeaperVsion::setMaxcount(int ncount)
{
	m_lmatch->MaxCount  = ncount;
}
void CPLCLeaperVsion::setDetailLevel(double dLevel)
{
	m_lmatch->DetailLevel = dLevel;
}
void CPLCLeaperVsion::setMatchParam(int nScore,double dLevel,int ncount)
{
	if (0!=nScore)
	{
		m_lmatch->AcceptScore = nScore;
	}
	if (0!=ncount)
	{
		m_lmatch->MaxCount = ncount;
	}
	if (0!=dLevel)
	{
		m_lmatch->DetailLevel = dLevel;
	}
}

void CPLCLeaperVsion::GetPatImage(ILImage *  img )
{
	m_lmatch->GetPatImage(img );
}
void CPLCLeaperVsion::GetPatMask ( ILImage *  mask ) 
{
	m_lmatch->GetPatMask (mask ); 
}
bool CPLCLeaperVsion::LoadImage( CString filename ) 
{
	if (LPVNoError != (LPVErrorCode)m_source_img->Load ( filename.GetString() ))
	{
		return false;
	}
	return true;
}
bool CPLCLeaperVsion::SaveMatch ( CString  filename )
{
	if (LPVNoError != (LPVErrorCode)m_lmatch->Save(filename.GetString()))
	{
		return false;
	}
	return true;
	//return (LPVErrorCode)m_lmatch->Save(filename.GetString());
}
bool CPLCLeaperVsion::LoadMatch ( CString  filename )
{
	if (LPVNoError != (LPVErrorCode)m_lmatch->Load(filename.GetString()))
	{
		return false;
	}
	return true;

}
void CPLCLeaperVsion::displayImage(ILImagePtr img, CStatic* pic_item,
	ILRectRegionPtr roi, ILMatchResultsPtr match_results, int cur_result_index)
{
	if (img->Void()) return;

	DisplayHelper dh(img->Width, img->Height, pic_item);

	// 1.3 draw image to bitmap
	img->Draw(dh.hdc, dh.zoomx, dh.zoomy, 0, 0);

	// 1.4 draw roi
	if (roi) {
		roi->Draw(dh.hdc, true, dh.zoomx, dh.zoomy, 0, 0);
	}

	// 1.5 draw match result
	if (match_results) {
		// green for all result
		((ILDrawablePtr)match_results)->SetPenColor(LPVGreen);
		match_results->DrawAll(dh.hdc,
			(LPVPatDrawFlags)(LPVPatDrawFlags::LPVPatDrawBoundingRect + LPVPatDrawFlags::LPVPatDrawCenter),
			dh.zoomx, dh.zoomy, 0, 0);
	}

	// 1.6 current match result
	if (cur_result_index >= 0) {
		// red for selected result
		((ILDrawablePtr)match_results)->SetPenColor(LPVRed);
		((ILDrawablePtr)match_results)->SetFontColor(LPVRed);
		match_results->Draw(dh.hdc, cur_result_index,
			LPVPatDrawFlags::LPVPatDrawAll,
			dh.zoomx, dh.zoomy, 0, 0);
	}
}

void CPLCLeaperVsion::displayTemplate(CStatic* pic_item)
{
	if (!m_lmatch->IsLearnt())
		return; // skip, it's not learn

	// get template image
	GetPatImage(m_template_img);

	//CStatic* pic_item = (CStatic*)GetDlgItem(IDC_STATIC_TRAIN);
	DisplayHelper dh(m_template_img->Width, m_template_img->Height, pic_item);

	// draw the template image
	m_template_img->Draw(dh.hdc, dh.zoomx, dh.zoomy, 0, 0);

	// draw the mask
	ILImagePtr template_mask(__uuidof(LImage));
	GetPatMask(template_mask);
	if (!template_mask->Void()) {
		template_mask->DrawAsMask(dh.hdc, dh.zoomx, dh.zoomy, 0, 0);
	}

	// draw the position and the template center of features
	double patX, patY, patAngle;
	m_lmatch->GetPatCenter(&patX, &patY, &patAngle);
	ILMatchResultPtr templatePat(__uuidof(LMatchResult));
	templatePat->Set(m_lmatch, patX, patY, patAngle, 1, 100);
	templatePat->Draw(dh.hdc,
		(LPVPatDrawFlags)(LPVPatDrawFlags::LPVPatDrawFeature + LPVPatDrawFlags::LPVPatDrawCenter),
		dh.zoomx, dh.zoomy, 0, 0);

	// refresh the center setting on ui
	//LPVPatCenterMode cenMode = m_lmatch->GetPatCenterMode();
	//((CComboBox*)GetDlgItem(IDC_COMBO_CENTER))->SetCurSel((int)cenMode);
	//setValueF(IDC_X, patX);
	//setValueF(IDC_Y, patY);
	//setValueF(IDC_A, patAngle);
}