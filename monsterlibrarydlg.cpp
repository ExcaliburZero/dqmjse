
#include "stdafx.h"
#include "dqmjse.h"
#include "monsterlibrarydlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CMonsterLibraryDlg, CDialog)

BEGIN_MESSAGE_MAP(CMonsterLibraryDlg, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_COMBO_MONSTER_FILTER, OnCbnSelchangeComboMonsterFilter)
	ON_BN_CLICKED(IDC_BUTTON_CHECKALL, &CMonsterLibraryDlg::OnBnClickedButtonCheckall)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

CMonsterLibraryDlg::CMonsterLibraryDlg(CWnd *pParent) : CDialog(IDD_DQMJSE_MONSTER_LIBRARY, pParent)
{

}

//////////////////////////////////////////////////////////////////////////

void CMonsterLibraryDlg::DoDataExchange(CDataExchange *pDX)
{
	::DDX_Control(pDX, IDC_COMBO_MONSTER_FILTER, m_cmbFilter);

	CDialog::DoDataExchange(pDX);
}

BOOL CMonsterLibraryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cmbFilter.SetRedraw(FALSE);
	VERIFY(m_cmbFilter.AddString(_T("すべて")) == CMonsterPanelDlg::FILTER_ALL);
	VERIFY(m_cmbFilter.AddString(_T("スライムけい")) == CMonsterPanelDlg::FILTER_SLIME);
	VERIFY(m_cmbFilter.AddString(_T("ドラゴンけい")) == CMonsterPanelDlg::FILTER_DRAGON);
	VERIFY(m_cmbFilter.AddString(_T("しぜんけい")) == CMonsterPanelDlg::FILTER_NATURE);
	VERIFY(m_cmbFilter.AddString(_T("まじゅうけい")) == CMonsterPanelDlg::FILTER_BEAST);
	VERIFY(m_cmbFilter.AddString(_T("ぶっしつけい")) == CMonsterPanelDlg::FILTER_MATERIAL);
	VERIFY(m_cmbFilter.AddString(_T("あくまけい")) == CMonsterPanelDlg::FILTER_DEMON);
	VERIFY(m_cmbFilter.AddString(_T("ゾンビけい")) == CMonsterPanelDlg::FILTER_ZOMBIE);
	VERIFY(m_cmbFilter.AddString(_T("しんじゅうけい")) == CMonsterPanelDlg::FILTER_INCARNI);
	m_cmbFilter.SetRedraw(TRUE);
	m_cmbFilter.SetCurSel(CMonsterPanelDlg::FILTER_ALL);

	CRect rect;
	GetDlgItem(IDC_STATIC_RECT)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_dlgPanel.Create(IDD_DQMJSE_MONSTER_PANEL, this);
	m_dlgPanel.MoveWindow(&rect, FALSE);
	m_dlgPanel.ShowWindow(SW_SHOW);

	RefreshCollectNum();

	return TRUE;
}

void CMonsterLibraryDlg::OnOK()
{
	UpdateData(TRUE);
}

void CMonsterLibraryDlg::OnCancel()
{
	m_dlgPanel.UpdateData(TRUE);

	DQMJ_SAVE_LIBRARY_INFO libraryinfo;
	VERIFY(::DQMJSaveQueryLibraryInfo(theApp.GetSaveHandle(), &libraryinfo));

	::ZeroMemory(libraryinfo.encounter, sizeof(libraryinfo.encounter));
	::ZeroMemory(libraryinfo.kill, sizeof(libraryinfo.kill));
	::ZeroMemory(libraryinfo.obtain, sizeof(libraryinfo.obtain));
/*

	for (int i = 0; i < m_lstBaggage.GetCount(); i++)
		iteminfo.baggage[i] = m_lstBaggage.GetItemData(i);

	for (int i = 0; i < DQMJ_ITEMLIST_LEN; i++)
		iteminfo.inventory[i] = m_dlgPanel.GetItemNum(i);
*/

	//VERIFY(::DQMJSaveModifyLibraryInfo(theApp.GetSaveHandle(), &libraryinfo));

	CDialog::OnCancel();
}

void CMonsterLibraryDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	CDialog::OnLButtonDown(nFlags, point);
}

void CMonsterLibraryDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	CDialog::OnRButtonDown(nFlags, point);
}

void CMonsterLibraryDlg::OnBnClickedButtonCheckall()
{
	m_dlgPanel.CheckAll();
}

void CMonsterLibraryDlg::OnCbnSelchangeComboMonsterFilter()
{
	int sel = m_cmbFilter.GetCurSel();
	if (sel >= 0)
		m_dlgPanel.SetFilter((CMonsterPanelDlg::FILTER)sel);
}

//////////////////////////////////////////////////////////////////////////

void CMonsterLibraryDlg::RefreshCollectNum()
{
	DQMJ_SAVE_LIBRARY_INFO libraryinfo;
	VERIFY(::DQMJSaveQueryLibraryInfo(theApp.GetSaveHandle(), &libraryinfo));

	int cnt = 0;
	const CIntToStrMap &map = theApp.GetRaceStringMap();

	for (const CIntToStrMap::CPair *pair = map.PGetFirstAssoc(); pair; pair = map.PGetNextAssoc(pair))
	{
		if (libraryinfo.obtain[pair->key])
			cnt++;
	}

	SetDlgItemText(IDC_COLLECT_NUM, theApp.GetDecimalString(cnt, map.GetCount()));
}

//////////////////////////////////////////////////////////////////////////
