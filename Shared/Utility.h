// Utility.h: interface for the Utillity.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTILITY_H__EA4D690A_DFDE_4BEF_903E_DE97DC98FD0F__INCLUDED_)
#define AFX_UTILITY_H__EA4D690A_DFDE_4BEF_903E_DE97DC98FD0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////////////////////////////////////////////////////////////
// BEGIN : 문자열 관련 매크로
#define VA Str_Format
#define CS(str) #str
#define SA(a) (sizeof(a)/sizeof((a)[0]))

#define BEGIN_SELECT(e) switch (e) {
#define CASE_SELECT(e)  case(e): return CS(e);
#define END_SELECT(e)   } return CS(e);

#ifdef _DEBUG
	#define COMMENT
#else
	#define COMMENT /##/
#endif

#define SAFE_DELETE(p) { if (p) { delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p) = NULL; } }
#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p) = NULL; } }
#define SAFE_FCLOSE(p) { if (p) { ::fclose(p); (p) = NULL; } }
// END
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// BEGIN
char* Str_Format(char* pFormat, ...);
// END
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// BEGIN
struct TDelete
{
	template<typename T> void operator()(T* pT) const
	{
		delete pT;
		pT = NULL;		//060521_kch null 초기화 
	}
};
// END
///////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_UTILITY_H__EA4D690A_DFDE_4BEF_903E_DE97DC98FD0F__INCLUDED_)