// DebugExt.cpp: implementation of the CDebugExt class.
//
//////////////////////////////////////////////////////////////////////

#include "DebugExt.h"
#include "SharedDefine.h"

///////////////////////////////////////////////////////////////////////////////
// Debug Function
///////////////////////////////////////////////////////////////////////////////

void Dbg_Message(const char* pContext, const char* pFile, unsigned int nLine)
{	// 원도우 메세지 박스 출력
	static char szBuffer[MAX_BUFFER_LINE][MAX_PATH];
	sprintf(szBuffer[0], "%s", pContext);
	sprintf(szBuffer[1], "%s(%d Line)", pFile, nLine);
	MessageBox(NULL, szBuffer[0], szBuffer[1], MB_OK|MB_ICONERROR);
}
