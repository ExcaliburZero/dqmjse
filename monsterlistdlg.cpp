
#include "stdafx.h"
#include "dqmjse.h"
#include "monsterlistdlg.h"
#include "monsterinfodlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CMonsterListDlg, CDialog)

BEGIN_MESSAGE_MAP(CMonsterListDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_UP, OnBnClickedButtonMonsterUp)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_TOP, OnBnClickedButtonMonsterTop)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_DOWN, OnBnClickedButtonMonsterDown)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_BOTTOM, OnBnClickedButtonMonsterBottom)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_ADD, OnBnClickedButtonMonsterAdd)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_MODIFY, OnBnClickedButtonMonsterModify)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_REMOVE, OnBnClickedButtonMonsterRemove)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_COPY, OnBnClickedButtonMonsterCopy)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MONSTER_LIST, OnNMDblclkListMonsterList)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_MONSTER_LIST, OnLvnItemchangingListMonsterList)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

CMonsterListDlg::CMonsterListDlg(CWnd *pParent) : CDialog(IDD_DQMJSE_MONSTER_LIST, pParent)
{

}

//////////////////////////////////////////////////////////////////////////

void CMonsterListDlg::DoDataExchange(CDataExchange *pDX)
{
	::DDX_Control(pDX, IDC_LIST_MONSTER_LIST, m_lstMonster);

	CDialog::DoDataExchange(pDX);
}

BOOL CMonsterListDlg::OnInitDialog()
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

	UpdateMonsterList();
	RefreshMonsterSel(LB_ERR);

	return TRUE;
}

void CMonsterListDlg::OnOK()
{
	UpdateData(TRUE);
}

void CMonsterListDlg::OnBnClickedButtonMonsterUp()
{
	int cur_sel = GetCurSel();
	if (cur_sel <= 0)
		return;

	MoveMonster(cur_sel, cur_sel - 1);
}

void CMonsterListDlg::OnBnClickedButtonMonsterTop()
{
	int cur_sel = GetCurSel();
	if (cur_sel <= 0)
		return;

	MoveMonster(cur_sel, 0);
}

void CMonsterListDlg::OnBnClickedButtonMonsterDown()
{
	int cur_sel = GetCurSel();
	if ((cur_sel < 0) || (cur_sel >= m_lstMonster.GetItemCount() - 1))
		return;

	MoveMonster(cur_sel, cur_sel + 1);
}

void CMonsterListDlg::OnBnClickedButtonMonsterBottom()
{
	int cur_sel = GetCurSel();
	int bottom_idx = m_lstMonster.GetItemCount() - 1;
	if ((cur_sel < 0) || (cur_sel >= bottom_idx))
		return;

	MoveMonster(cur_sel, bottom_idx);
}

void CMonsterListDlg::OnBnClickedButtonMonsterAdd()
{
	if (m_lstMonster.GetItemCount() >= DQMJ_MONSTER_MAX)
		return;

	AddMonster();
}

void CMonsterListDlg::OnBnClickedButtonMonsterModify()
{
	int cur_sel = GetCurSel();
	if (cur_sel < 0)
		return;

	ModifyMonster(cur_sel);
}

void CMonsterListDlg::OnBnClickedButtonMonsterRemove()
{
	if (m_lstMonster.GetItemCount() <= 1)
		return;

	int cur_sel = GetCurSel();
	if (cur_sel < 0)
		return;

	RemoveMonster(cur_sel);
}

void CMonsterListDlg::OnBnClickedButtonMonsterCopy()
{
	if (m_lstMonster.GetItemCount() >= DQMJ_MONSTER_MAX)
		return;

	int cur_sel = GetCurSel();
	if (cur_sel < 0)
		return;

	CopyMonster(cur_sel);
}

void CMonsterListDlg::OnNMDblclkListMonsterList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	ModifyMonster(pNMItemActivate->iItem);
}

void CMonsterListDlg::OnLvnItemchangingListMonsterList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	RefreshMonsterSel((pNMLV->uNewState & LVIS_SELECTED) ? pNMLV->iItem : LB_ERR);
}

//////////////////////////////////////////////////////////////////////////

int CMonsterListDlg::GetCurSel()
{
	int sel = m_lstMonster.GetSelectionMark();
	if (!m_lstMonster.GetItemState(sel, LVIS_SELECTED))
		return LB_ERR;

	return sel;
}

void CMonsterListDlg::UpdateMonsterList()
{
	DQMJ_SAVE_RANCH_INFO ranchinfo;
	VERIFY(::DQMJSaveQueryRanchInfo(CDqmjSEApp::GetSaveHandle(), &ranchinfo));

	for (int i = 0; i < ranchinfo.monster_num; i++)
	{
		DQMJ_SAVE_MONSTER_INFO monsterinfo;
		VERIFY(m_lstMonster.InsertItem(i, _T("")) == i);
		VERIFY(::DQMJSaveQueryMonsterInfo(CDqmjSEApp::GetSaveHandle(), i, &monsterinfo));

		m_lstMonster.SetItemText(i, COLUMN_NO, CDqmjSEApp::GetDecimalString(i + 1));
		m_lstMonster.SetItemText(i, COLUMN_NAME, CDqmjSEApp::GetNameString(monsterinfo.name));
		m_lstMonster.SetItemText(i, COLUMN_SEX, CDqmjSEApp::GetSexString(monsterinfo.sex));
		m_lstMonster.SetItemText(i, COLUMN_RACE, CDqmjSEApp::GetRaceString(monsterinfo.race));
		m_lstMonster.SetItemText(i, COLUMN_LEVEL, CDqmjSEApp::GetDecimalString2(monsterinfo.level, monsterinfo.max_level));
		m_lstMonster.SetItemText(i, COLUMN_RANK, CDqmjSEApp::GetRankString(monsterinfo.rank));
		m_lstMonster.SetItemText(i, COLUMN_TYPE, CDqmjSEApp::GetTypeString(monsterinfo.type));
		m_lstMonster.SetItemText(i, COLUMN_WEAPON, CDqmjSEApp::GetItemNameString(monsterinfo.weapon));
	}

	for (int i = 0; i < ranchinfo.party_member_num; i++)
		m_lstMonster.SetItemText(ranchinfo.party_member_idx[i], COLUMN_PARTY, CDqmjSEApp::GetDecimalString(i + 1));

	for (int i = 0; i < ranchinfo.standby_num; i++)
		m_lstMonster.SetItemText(ranchinfo.standby_idx[i], COLUMN_STANDBY, CDqmjSEApp::GetDecimalString(i + 1));

	SetDlgItemText(IDC_MONSTER_NUM, CDqmjSEApp::GetDecimalString2(m_lstMonster.GetItemCount(), DQMJ_MONSTER_MAX));
}

void CMonsterListDlg::RedrawMonsterList(int sel)
{
	m_lstMonster.SetRedraw(FALSE);
	m_lstMonster.DeleteAllItems();
	UpdateMonsterList();

	if (sel >= m_lstMonster.GetItemCount())
		sel = LB_ERR;
	else
		m_lstMonster.SetItemState(sel, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	m_lstMonster.SetSelectionMark(sel);
	m_lstMonster.SetRedraw(TRUE);

	m_lstMonster.SetFocus();
	RefreshMonsterSel(sel);
}

void CMonsterListDlg::RefreshMonsterSel(int sel)
{
	int item_count = m_lstMonster.GetItemCount();

	GetDlgItem(IDC_BUTTON_MONSTER_UP)->EnableWindow(sel > 0);
	GetDlgItem(IDC_BUTTON_MONSTER_TOP)->EnableWindow(sel > 0);
	GetDlgItem(IDC_BUTTON_MONSTER_DOWN)->EnableWindow((sel >= 0) && (sel < item_count - 1));
	GetDlgItem(IDC_BUTTON_MONSTER_BOTTOM)->EnableWindow((sel >= 0) && (sel < item_count - 1));
	GetDlgItem(IDC_BUTTON_MONSTER_ADD)->EnableWindow(item_count < DQMJ_MONSTER_MAX);
	GetDlgItem(IDC_BUTTON_MONSTER_MODIFY)->EnableWindow(sel >= 0);
	GetDlgItem(IDC_BUTTON_MONSTER_REMOVE)->EnableWindow((sel >= 0) && (item_count > 1));
	GetDlgItem(IDC_BUTTON_MONSTER_COPY)->EnableWindow((sel >= 0) && (item_count < DQMJ_MONSTER_MAX));
}

void CMonsterListDlg::AddMonster()
{
	DQMJ_SAVE_MONSTER_INFO monsterinfo;
	::ZeroMemory(&monsterinfo, sizeof(monsterinfo));

	CMonsterInfoDlg dlg(monsterinfo, this);
	dlg.DoModal();
	monsterinfo = dlg.GetMonsterInfo();

	VERIFY(::DQMJSaveNewMonster(CDqmjSEApp::GetSaveHandle(), &monsterinfo, FALSE));
	RedrawMonsterList(0);
}

void CMonsterListDlg::ModifyMonster(int sel)
{
	if (sel < 0)
		return;

	DQMJ_SAVE_MONSTER_INFO monsterinfo;
	VERIFY(::DQMJSaveQueryMonsterInfo(CDqmjSEApp::GetSaveHandle(), sel, &monsterinfo));

	CMonsterInfoDlg dlg(monsterinfo, this);
	dlg.DoModal();
	monsterinfo = dlg.GetMonsterInfo();

	m_lstMonster.SetFocus();
	RefreshMonsterSel(sel);
}

void CMonsterListDlg::RemoveMonster(int sel)
{
	if (sel < 0)
		return;

	VERIFY(::DQMJSaveRemoveMonster(CDqmjSEApp::GetSaveHandle(), sel));
	RedrawMonsterList(sel);
}

void CMonsterListDlg::CopyMonster(int sel)
{
	if (sel < 0)
		return;

	VERIFY(::DQMJSaveCopyMonster(CDqmjSEApp::GetSaveHandle(), sel));
	RedrawMonsterList(0);
}

void CMonsterListDlg::MoveMonster(int sel, int idx)
{
	if (sel < 0)
		return;

	VERIFY(::DQMJSaveMoveMonster(CDqmjSEApp::GetSaveHandle(), sel, idx));
	RedrawMonsterList(idx);
}

//////////////////////////////////////////////////////////////////////////
