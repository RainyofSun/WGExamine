#pragma once

#include <string>
#include <vector>
#include <string.h>

using namespace std;


//  XGem state
enum _eExGemState{
	ExGemState_Unknown = -1,
	ExGemState_Initialized = 0,
	ExGemState_Started,
	ExGemState_Stopped,
	ExGemState_Closed
};

//	Communication state
enum _eCommState
{
	Comm_None = 0,
	Comm_Disabled = 1,
	Comm_WaitCRFromHost,
	Comm_WaitDelay,
	Comm_WaitCRA,
	Comm_Communicating
};

//	Control state
enum _eControlState
{
	Control_None = 0,
	Control_EqOffline = 1,
	Control_AttemptOnline,
	Control_HostOffline,
	Control_Local,
	Control_Remote
};

//	Processing state
enum ProcessingState
{
	Processing_None = 0,
	Processing_Init = 1,
	Processing_Idle,
	Processing_SetUp,
	Processing_Ready,
	Processing_Execuing,
	Processing_Paused
};

//	Processing Reason
enum _eProcessingReason
{
	ProcReason_None = 0,
	ProcReason_Stop = 1,
	ProcReason_Abort,
	ProcReason_AlarmPause,
	ProcReason_CommandPause,
	ProcReason_Resume
};


extern CString toCString(string str) ;
extern DWORDLONG KvGetTickCount();
extern string getSTime(byte timeFormat);
extern void SplitString(const string& s, vector<string>& v, const string& c);
