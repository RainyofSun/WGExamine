#include "StdAfx.h"
#include "Helper.h"


CString toCString(string str) 
{
#ifdef _UNICODE		
	//如果是unicode工程	
	USES_CONVERSION;
	CString s(str.c_str());	
	CString ans(str.c_str());		
	return ans;
#else		
	//如果是多字节工程	
	CString ans;		
	ans.Format("%s", str.c_str());
	return ans;
#endif 	
}

DWORDLONG KvGetTickCount()
{
	FILETIME ft;
	SYSTEMTIME st;
	GetLocalTime(&st);
	SystemTimeToFileTime(&st, &ft); // converts to file time format
	DWORDLONG uTimeCount =((((DWORDLONG) ft.dwHighDateTime) << 32) + ft.dwLowDateTime)/10000;

	return uTimeCount;
}

string getSTime(byte timeFormat)
{
	char time[20]={0};
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	if(timeFormat==1)
		sprintf_s(time,"%4d%02d%02d%02d%02d%02d%02d",systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute, systime.wSecond,systime.wMilliseconds/10);
	else
		sprintf_s(time,"%2d%02d%02d%02d%02d%02d",systime.wYear%100,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute, systime.wSecond);
	string StrSystime = time;

	return StrSystime;
}

void SplitString(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while(string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2-pos1));
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if(pos1 != s.length())
		v.push_back(s.substr(pos1));
}