
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
	static CString GetDecimalString(int number);
	static CString GetNameString(DQMJ_NAME name);

private:

	HDQMJSAVE	m_hDqmjSave;

};

//////////////////////////////////////////////////////////////////////////
