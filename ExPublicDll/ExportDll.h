
#pragma once
using namespace std;
#define WM_FAHPMSG (WM_APP+30)//��ʾ�������˳���ť
#define WM_CTVACUUMMSG (WM_APP+31) //����̨��մ򿪷�����Ϣ���ð�ť
void   CreateInterfaceFont(CWnd *pWnd);
bool   OpenFileData(CString strFileName);//true��false �򿪴���
/******************************************************/
int   ReadStringMem(CString strFind,CString *str,CString strFileDirectory);
int   ReadNumDouble(CString strFile,double *Num,CString strFileDirectory);
int   ReadNumFloat(CString strFile,float *Num,CString strFileDirectory);
int   ReadNumLong(CString strFile,long *Num,CString strFileDirectory);
int   WriteStringMem(CString strKey, CString strWrite,CString strFileDirectory);
int   WriteNumFloat(CString strKey, float num,CString strFileDirectory);
int   WriteNumLong(CString strKey,long num,CString strFileDirectory);
int   ReadLongArray(CString strKey,long NumArray[],int nSize,CString strFileDirectory); 
int   ReadDoubleArray(CString strKey,double NumArray[],int nSize,CString strFileDirectory);
int  WriteNumDouble(CString strKey, double num,CString strFileDirectory);
int  WriteLongArray(CString strKey,long NumArray[],int nSize,CString strFileDirectory);
int  WriteDoubleArray(CString strKey,double NumArray[],int nSize,CString strFileDirectory);
/*******************���Ϸ���0��ȷ��-1����**********************************/
void   ReadFileFinish();//�ļ�����ɣ��ͷ�
void   SaveWriteData( );
double VarsMmToInch(int Imm);//����ת��ֵ
double  VarsInchToMm(int Inch );//����ת��ֵ
/****************************************************************/
unsigned int    DeleteTheFile(CString fileDir);
unsigned int    CopyTheFile(CString fileSource,CString fileDes);
unsigned int    MoveTheFile(CString fileSource,CString fileDes);
unsigned int    RenameTheFile(CString fileSource,CString fileRename);
unsigned int    CreateTheDir(CString dirName);
unsigned int    DeleteTheDir(CString dirName);
/*********************���Ϸ���ֵ0��ȷ************************************/
bool   FileIsEmpty(CString strFile);//�ļ��Ƿ�Ϊ��
void   LogWriteLog(CString strEventId, CString strEventData);
/********************************************************************/
HBITMAP GetDLLBmpRes(CString strDllFile, UINT nResID);
HICON GetDLLIconRes(CString strDllFile, UINT nResID);
CString  GetDLLStringRes(CString strDllFile,UINT nResID);
/***********************************************************************/
//////////////////////////////////////////////////////////////////////////
BOOL MyWriteProfileString(const CString strSection, const CString strEntry, 
	const CString strValue, const CString  strIniPath);
BOOL MyGetProfileString( const CString strSection, const CString strEntry,
	CString & strValue, const CString strIniPath );
BOOL MyWriteProfileChar(const CString strSection, const CString strEntry, 
	const char chValue, const CString strIniPath);
BOOL MyGetProfileChar( const CString strSection, const CString strEntry,
	char & chMychar, const CString strIniPath );
BOOL MyWriteProfileBool(const CString strSection, const CString strEntry, 
	const bool bValue, const CString strIniPath);
BOOL MyGetProfileBool( const CString strSection, const CString strEntry,
	bool & bValue, const CString strIniPath );
BOOL MyGetProfileInt( const CString strSection, const CString strEntry,
	int  & nValue, const CString strIniPath );
BOOL MyWriteProfileInt(const CString strSection, const CString strEntry, 
	const int nValue, const CString strIniPath);
BOOL MyWriteProfileDouble(const CString strSection, const CString strEntry, 
	const double dValue, const CString strIniPath);
BOOL MyGetProfileDouble( const CString strSection, const CString strEntry,
	double & dValue, const CString strIniPath );

BOOL MyGetProfileShort( const CString strSection, const CString strEntry,
	short  & nValue, const CString strIniPath );
BOOL MyWriteProfileShort(const CString strSection, const CString strEntry, 
	const int nValue, const CString strIniPath);
BOOL MyWriteProfileFloat(const CString strSection, const CString strEntry, 
	const float dValue, const CString strIniPath);
BOOL MyGetProfileFloat( const CString strSection, const CString strEntry,
	float & dValue, const CString strIniPath );



CString GetProjFilePath();
void WriteCollectData(CString strDescribe, CString strData);