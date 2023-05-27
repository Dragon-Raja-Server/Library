// Utility.cpp: implementation of the Utility.
//
//////////////////////////////////////////////////////////////////////

#include "Utility.h"
#include "SharedDefine.h"

///////////////////////////////////////////////////////////////////////////////
// Debug Function
///////////////////////////////////////////////////////////////////////////////

char* Str_Format(char* pFormat, ...)
{	// 문자열 형식 만들기 함수
	static char szBuffer[MAX_BUFFER_LINE][MAX_PATH];
	static int nIndex = 0;
	// 두개의 버퍼를 만들어 교대로 사용
	char* pBuffer = szBuffer[nIndex++&1];
	// 가변인자값을 버퍼에 저장
	va_list vaList;
	va_start(vaList, pFormat);
	vsprintf(pBuffer, pFormat, vaList);
	va_end(vaList);
	return pBuffer;
}
