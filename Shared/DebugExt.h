// DebugExt.h: interface for the CDebugExt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEBUGEXT_H__FE16F94C_D7D1_4C44_B52F_D8FA2435B04D__INCLUDED_)
#define AFX_DEBUGEXT_H__FE16F94C_D7D1_4C44_B52F_D8FA2435B04D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////////////////////////////////////////////////////////////
// BEGIN : 디버그 관련 매크로
#ifdef _X86_
	#define Dbg_Break() _asm { int 3h }
#else
	#define Dbg_Break() DebugBreak()
#endif

#ifdef _DEBUG
	#define Dbg_Assert(exp) assert(exp)
	#define Dbg_Error(msg)  Dbg_Verify(1, msg)
	#define Dbg_Verify(exp, msg) \
	if (exp) { Dbg_Message(msg, __FILE__, __LINE__); Dbg_Break(); }
	template<bool> struct TCompileTimeError;
	template<> struct TCompileTimeError<true> {};
	#define Dbg_Static(exp, msg) \
	{ TCompileTimeError<((exp) != false)> ERROR_##msg; (void)ERROR_##msg; }
	#define Dbg_Debug(msg) OutputDebugString(msg)
#else
	#define Dbg_Assert(exp) NULL
	#define Dbg_Error(msg) NULL
	#define Dbg_Verify(exp, msg) NULL
	#define Dbg_Static(exp, msg) NULL
	#define Dbg_Debug(msg) NULL
#endif
// END
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// BEGIN : 디버그 관련 매크로
void Dbg_Message(const char* pContext, const char* pFile, unsigned int nLine);
// END
///////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_DEBUGEXT_H__FE16F94C_D7D1_4C44_B52F_D8FA2435B04D__INCLUDED_)