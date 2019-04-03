
#include "stdafx.h"
#include "dqmjse.h"
#include "selectmonsterdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSelectMonsterDlg, CDialog)

BEGIN_MESSAGE_MAP(CSelectMonsterDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MONSTER_LIST, OnNMDblclkListMonsterList)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_MONSTER_LIST, OnLvnItemchangingListMonsterList)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

CSelectMonsterDlg::CSelectMonsterDlg(int monster, BOOL disable_party_member, BOOL disable_standby, CWnd *pParent) : CDialog(IDD_DQMJSE_SELECT_MONSTER, pParent)
{
	m_bDisablePartyMember = disable_party_member;
	m_bDisableStandby = disable_standby;
	m_nSelMonster = monster;
	m_nPartyIndex = -1;
	m_nStandbyIndex = -1;
}

//////////////////////////////////////////////////////////////////////////

int CSelectMonsterDlg::GetSelMonster() const
{
	return m_nSelMonster;
}

BOOL CSelectMonsterDlg::GetPartyIndex() const
{
	return m_nPartyIndex;
}

BOOL CSelectMonsterDlg::GetStandbyIndex() const
{
	return m_nStandbyIndex;
}

//////////////////////////////////////////////////////////////////////////

void CSelectMonsterDlg::DoDataExchange(CDataExchange *pDX)
{
	::DDX_Control(pDX, IDC_LIST_MONSTER_LIST, m_lstMonster);

	CDialog::DoDataExchange(pDX);
}

BOOL CSelectMonsterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lstMonster.SetExtendedStyle(m_lstMonster.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	VERIFY(m_lstMonster.InsertColumn(COLUMN_NO, _T("No."), LVCFMT_LEFT, 28) == COLUMN_NO);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_PARTY, _T("PT"), LVCFMT_LEFT, 25) == COLUMN_PARTY);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_STANDBY, _T("ST"), LVCFMT_LEFT, 25) == COLUMN_STANDBY);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_NAME, _T("名前"), LVCFMT_LEFT, 64) == COLUMN_NAME);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_SEX, _T("性別"), LVCFMT_CENTER, 34) == COLUMN_SEX);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_RACE, _T("種族"), LVCFMT_LEFT, 88) == COLUMN_RACE);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_LEVEL, _T("レベル"), LVCFMT_LEFT, 42) == COLUMN_LEVEL);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_RANK, _T("RANK"), LVCFMT_CENTER, 42) == COLUMN_RANK);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_TYPE, _T("系統"), LVCFMT_LEFT, 62) == COLUMN_TYPE);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_WEAPON, _T("装備"), LVCFMT_CENTER, 90) == COLUMN_WEAPON);

	DQMJ_SAVE_RANCH_INFO ranchinfo;
	VERIFY(::DQMJSaveQueryRanchInfo(CDqmjSEApp::GetSaveHandle(), &ranchinfo));

	m_lstMonster.SetRedraw(FALSE);

	for (int i = 0; i < ranchinfo.monster_num; i++)
	{
		DQMJ_SAVE_MONSTER_INFO monsterinfo;
		VERIFY(m_lstMonster.InsertItem(i, _T("")) == i);
		VERIFY(::DQMJSaveQueryMonsterInfo(CDqmjSEApp::GetSaveHandle(), i, &monsterinfo));

		m_lstMonster.SetItemData(i, MAKELONG(-1, -1));
		m_lstMonster.SetItemText(i, COLUMN_NO, CDqmjSEApp::GetDecimalString(i + 1));
		m_lstMonster.SetItemText(i, COLUMN_NAME, CDqmjSEApp::GetNameString(monsterinfo.name));
		m_lstMonster.SetItemText(i, COLUMN_SEX, CDqmjSEApp::GetSexString(monsterinfo.sex));
		m_lstMonster.SetItemText(i, COLUMN_RACE, CDqmjSEApp::GetRaceString(monsterinfo.race));
		m_lstMonster.SetItemText(i, COLUMN_LEVEL, CDqmjSEApp::GetDecimalString2(monsterinfo.level, monsterinfo.max_level));
		m_lstMonster.SetItemText(i, COLUMN_RANK, CDqmjSEApp::GetRankString(monsterinfo.rank));
		m_lstMonster.SetItemText(i, COLUMN_TYPE, CDqmjSEApp::GetTypeString(monsterinfo.type));
		m_lstMonster.SetItemText(i, COLUMN_WEAPON, CDqmjSEApp::GetItemNameString(monsterinfo.weapon));

		if (i == m_nSelMonster)
		{
			m_lstMonster.SetItemState(i, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			m_lstMonster.SetSelectionMark(i);
		}
	}

	for (int i = 0; i < ranchinfo.party_member_num; i++)
	{
		m_lstMonster.SetItemData(ranchinfo.party_member_idx[i], MAKELONG(i, -1));
		m_lstMonster.SetItemText(ranchinfo.party_member_idx[i], COLUMN_PARTY, CDqmjSEApp::GetDecimalString(i + 1));
	}

	for (int i = 0; i < ranchinfo.standby_num; i++)
	{
		m_lstMonster.SetItemData(ranchinfo.standby_idx[i], MAKELONG(-1, i));
		m_lstMonster.SetItemText(ranchinfo.standby_idx[i], COLUMN_STANDBY, CDqmjSEApp::GetDecimalString(i + 1));
	}

	m_lstMonster.SetRedraw(TRUE);

	if (GetCurSel() < 0)
		m_nSelMonster = LB_ERR;

	GetDlgItem(IDOK)->EnableWindow(CanSelect(m_nSelMonster));

	return TRUE;
}

void CSelectMonsterDlg::OnOK()
{
	int sel = GetCurSel();
	if (!CanSelect(sel))
		return;

	m_nSelMonster = sel;
	m_nPartyIndex = (SHORT)LOWORD(m_lstMonster.GetItemData(sel));
	m_nStandbyIndex = (SHORT)HIWORD(m_lstMonster.GetItemData(sel));

	CDialog::OnOK();
}

void CSelectMonsterDlg::OnNMDblclkListMonsterList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	OnOK();
}

void CSelectMonsterDlg::OnLvnItemchangingListMonsterList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	GetDlgItem(IDOK)->EnableWindow(CanSelect((pNMLV->uNewState & LVIS_SELECTED) ? pNMLV->iItem : LB_ERR));
}

//////////////////////////////////////////////////////////////////////////

int CSelectMonsterDlg::GetCurSel()
{
	int sel = m_lstMonster.GetSelectionMark();
	if (!m_lstMonster.GetItemState(sel, LVIS_SELECTED))
		return LB_ERR;

	return sel;
}

BOOL CSelectMonsterDlg::CanSelect(int sel)
{
	if (sel < 0)
		return FALSE;

	if (sel == m_nSelMonster)
		return TRUE;

	if (m_bDisablePartyMember && ((SHORT)LOWORD(m_lstMonster.GetItemData(sel)) >= 0))
		return FALSE;

	if (m_bDisableStandby && ((SHORT)HIWORD(m_lstMonster.GetItemData(sel)) >= 0))
		return FALSE;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
