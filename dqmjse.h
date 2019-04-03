
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"
#include "dqmjsav.h"

//////////////////////////////////////////////////////////////////////////

class CDqmjSEApp : public CWinAppEx
{

public:

	CDqmjSEApp();

	BOOL OpenSave(LPCTSTR pszFilename);
	void CloseSave();

	virtual BOOL InitInstance();

	static HDQMJSAVE GetSaveHandle();
	static int CalcDigit(int number);
	static CString GetDecimalString(int num);
	static CString GetDecimalString2(int num1, int num2);
	static CString GetNameString(DQMJ_NAME name);
	static CString GetSexString(int sex);
	static CString GetRaceString(int race);
	static CString GetRankString(int rank);
	static CString GetTypeString(int type);
	static CString GetItemNameString(int item);
	static DQMJ_NAME &GetStringName(DQMJ_NAME &name, LPCTSTR str);

private:

	HDQMJSAVE	m_hDqmjSave;

};

//////////////////////////////////////////////////////////////////////////
