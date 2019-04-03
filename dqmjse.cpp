
#include "stdafx.h"
#include "dqmjse.h"
#include "dqmjsedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

static CDqmjSEApp theApp;

//////////////////////////////////////////////////////////////////////////

CDqmjSEApp::CDqmjSEApp()
{
	m_hDqmjSave = NULL;
}

//////////////////////////////////////////////////////////////////////////

BOOL CDqmjSEApp::OpenSave(LPCTSTR pszFilename)
{
	if (m_hDqmjSave != NULL)
		return FALSE;

	m_hDqmjSave = ::DQMJSaveOpenFile(pszFilename);
	if (m_hDqmjSave == NULL)
		return FALSE;

	return TRUE;
}

void CDqmjSEApp::CloseSave()
{
	::DQMJSaveCloseFile(m_hDqmjSave);
	m_hDqmjSave = NULL;
}

BOOL CDqmjSEApp::InitInstance()
{
	INITCOMMONCONTROLSEX initctrls;
	initctrls.dwSize = sizeof(initctrls);
	initctrls.dwICC = ICC_WIN95_CLASSES;
	::InitCommonControlsEx(&initctrls);

	CWinAppEx::InitInstance();

	CDqmjSEDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////

HDQMJSAVE CDqmjSEApp::GetSaveHandle()
{
	return theApp.m_hDqmjSave;
}

int CDqmjSEApp::CalcDigit(int number)
{
	int n = 0;

	while (number != 0)
	{
		n++;
		number /= 10;
	}

	return (n == 0) ? 1 : n;
}

CString CDqmjSEApp::GetDecimalString(int num)
{
	CString str;
	str.Format(_T("%d"), num);

	return str;
}

CString CDqmjSEApp::GetDecimalString2(int num1, int num2)
{
	CString str;
	str.Format(_T("%d/%d"), num1, num2);

	return str;
}

CString CDqmjSEApp::GetNameString(DQMJ_NAME name)
{
	CStringW str;

	UINT len = ::DQMJSaveNameToString(NULL, UINT_MAX, name, L'?');
	VERIFY(::DQMJSaveNameToString(str.GetBuffer(len), len, name, L'?') == len);
	str.ReleaseBuffer();

	return CString(str);
}

CString CDqmjSEApp::GetSexString(int sex)
{
	static const LPCTSTR sex_list[] = { _T("♂"), _T("♀"), _T("♂♀") };

	if ((sex >= 0) && (sex < _countof(sex_list)))
		return sex_list[sex];

	return _T("不明");
}

CString CDqmjSEApp::GetRaceString(int race)
{
	DQMJ_SAVE_RACE_SETTING rs;
	if (::DQMJSaveGetRaceSetting(race, &rs))
		return rs.name;

	return _T("不明");
}

CString CDqmjSEApp::GetRankString(int rank)
{
	static const LPCTSTR rank_list[] = { _T("なし"), _T("F"), _T("E"), _T("D"), _T("C"), _T("B"), _T("A"), _T("S"), _T("SS"), _T("??") };

	if ((rank >= 0) && (rank < _countof(rank_list)))
		return rank_list[rank];

	return _T("不明");
}

CString CDqmjSEApp::GetTypeString(int type)
{
	static const LPCTSTR type_list[] = { _T("なし"), _T("スライム系"), _T("ドラゴン系"), _T("しぜん系"), _T("まじゅう系"), _T("ぶっしつ系"), _T("あくま系"), _T("ゾンビ系"), _T("しんじゅう系") };

	if ((type >= 0) && (type < _countof(type_list)))
		return type_list[type];

	return _T("不明");
}

CString CDqmjSEApp::GetItemNameString(int item)
{
	if (item == 0x00)
		return _T("なし");

	DQMJ_SAVE_ITEM_SETTING is;
	if (::DQMJSaveGetItemSetting(item, &is))
		return is.name;

	return _T("不明");
}

DQMJ_NAME &CDqmjSEApp::GetStringName(DQMJ_NAME &name, LPCTSTR str)
{
	::DQMJSaveStringToName(name, CStringW(str));
	return name;
}

//////////////////////////////////////////////////////////////////////////
