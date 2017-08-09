
#include "stdafx.h"
#include "dqmjse.h"
#include "dqmjsedlg.h"
#include "itemlistdlg.h"
#include "monsterlistdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CDqmjSEDlg, CDialog)

BEGIN_MESSAGE_MAP(CDqmjSEDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_EDIT_ITEM_LIST, OnEditItemList)
	ON_COMMAND(ID_EDIT_MONSTER_LIST, OnEditMonsterList)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

CDqmjSEDlg::CDqmjSEDlg(CWnd *pParent) : CDialog(IDD_DQMJSE_DIALOG, pParent)
{
	m_nGold = 0;
	m_nDeposit = 0;
	m_nVictoryTimes = 0;
	m_nScoutTimes = 0;
	m_nCombineTimes = 0;
	m_nHour = 0;
	m_nMinute = 0;
	m_nSecond = 0;
	m_strPlayerName = _T("");
	m_hIcon = ::AfxGetApp()->LoadIcon(IDR_MAIN_MENU);
	m_hAccel = ::LoadAccelerators(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAIN_MENU));
}

//////////////////////////////////////////////////////////////////////////

BOOL CDqmjSEDlg::OpenFile(LPCTSTR pszFilename)
{
	if (!((CDqmjSEApp *)::AfxGetApp())->OpenSave(pszFilename))
		return FALSE;

	DQMJ_SAVE_BRIEFING briefing;
	if (!::DQMJSaveQueryBriefing(CDqmjSEApp::GetSaveHandle(), &briefing))
		return FALSE;

	DQMJ_SAVE_PLAY_INFO playinfo;
	if (!::DQMJSaveQueryPlayInfo(CDqmjSEApp::GetSaveHandle(), &playinfo))
		return FALSE;

	DQMJ_SAVE_ITEM_INFO iteminfo;
	if (!::DQMJSaveQueryItemInfo(CDqmjSEApp::GetSaveHandle(), &iteminfo))
		return FALSE;

	DQMJ_SAVE_RANCH_INFO ranchinfo;
	if (!::DQMJSaveQueryRanchInfo(CDqmjSEApp::GetSaveHandle(), &ranchinfo))
		return FALSE;

	RefreshBriefing(briefing);
	RefreshPlayInfo(playinfo);
	RefreshItemInfo(iteminfo);
	RefreshRanchInfo(ranchinfo);

	EnableAll(TRUE);
	return TRUE;
}

void CDqmjSEDlg::CloseFile()
{
	((CDqmjSEApp *)::AfxGetApp())->CloseSave();
	EnableAll(FALSE);
}

//////////////////////////////////////////////////////////////////////////

void CDqmjSEDlg::DoDataExchange(CDataExchange *pDX)
{
	::DDX_Text(pDX, IDC_EDIT_PLAYINFO_NAME, m_strPlayerName);
	::DDX_Text(pDX, IDC_EDIT_PLAYINFO_GOLD, m_nGold);
	::DDX_Text(pDX, IDC_EDIT_PLAYINFO_DEPOSIT, m_nDeposit);
	::DDX_Text(pDX, IDC_EDIT_PLAYINFO_VICTORYTIMES, m_nVictoryTimes);
	::DDX_Text(pDX, IDC_EDIT_PLAYINFO_SCOUTTIMES, m_nScoutTimes);
	::DDX_Text(pDX, IDC_EDIT_PLAYINFO_COMBINETIMES, m_nCombineTimes);
	::DDX_Text(pDX, IDC_EDIT_PLAYINFO_HOUR, m_nHour);
	::DDX_Text(pDX, IDC_EDIT_PLAYINFO_MINUTE, m_nMinute);
	::DDX_Text(pDX, IDC_EDIT_PLAYINFO_SECOND, m_nSecond);

	::DDV_MinMaxInt(pDX, m_nGold, 0, DQMJ_GOLD_MAX);
	::DDV_MinMaxInt(pDX, m_nDeposit, 0, DQMJ_GOLD_MAX);
	::DDV_MinMaxInt(pDX, m_nVictoryTimes, 0, DQMJ_RECORD_MAX);
	::DDV_MinMaxInt(pDX, m_nScoutTimes, 0, DQMJ_RECORD_MAX);
	::DDV_MinMaxInt(pDX, m_nCombineTimes, 0, DQMJ_RECORD_MAX);
	::DDV_MinMaxInt(pDX, m_nHour, 0, 99999);
	::DDV_MinMaxInt(pDX, m_nMinute, 0, 59);
	::DDV_MinMaxInt(pDX, m_nSecond, 0, 59);

	CDialog::DoDataExchange(pDX);
}

BOOL CDqmjSEDlg::PreTranslateMessage(MSG *pMsg)
{
	if ((m_hAccel != NULL) && ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
		return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDqmjSEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	((CEdit *)GetDlgItem(IDC_EDIT_PLAYINFO_NAME))->SetLimitText(DQMJ_NAME_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT_PLAYINFO_GOLD))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_GOLD_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_PLAYINFO_DEPOSIT))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_GOLD_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_PLAYINFO_VICTORYTIMES))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_RECORD_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_PLAYINFO_SCOUTTIMES))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_RECORD_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_PLAYINFO_COMBINETIMES))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_RECORD_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_PLAYINFO_HOUR))->SetLimitText(5);
	((CEdit *)GetDlgItem(IDC_EDIT_PLAYINFO_MINUTE))->SetLimitText(2);
	((CEdit *)GetDlgItem(IDC_EDIT_PLAYINFO_SECOND))->SetLimitText(2);

	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_PLAYINFO_GOLD))->SetRange32(0, DQMJ_GOLD_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_PLAYINFO_DEPOSIT))->SetRange32(0, DQMJ_GOLD_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_PLAYINFO_VICTORYTIMES))->SetRange32(0, DQMJ_RECORD_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_PLAYINFO_SCOUTTIMES))->SetRange32(0, DQMJ_RECORD_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_PLAYINFO_COMBINETIMES))->SetRange32(0, DQMJ_RECORD_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_PLAYINFO_HOUR))->SetRange32(0, 99999);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_PLAYINFO_MINUTE))->SetRange32(0, 59);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_PLAYINFO_SECOND))->SetRange32(0, 59);

	EnableAll(FALSE);

	return TRUE;
}

void CDqmjSEDlg::OnOK()
{
	UpdateData(TRUE);
}

void CDqmjSEDlg::OnCancel()
{
	EndDialog(IDCANCEL);
}

void CDqmjSEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = ::GetSystemMetrics(SM_CXICON);
		int cyIcon = ::GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CDqmjSEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDqmjSEDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO:
	CDialog::OnDropFiles(hDropInfo);
}

void CDqmjSEDlg::OnFileOpen()
{
	CFileDialog cfd(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T(""), this);
	if (cfd.DoModal() != IDOK)
		return;

	CloseFile();

	if (!OpenFile(cfd.GetPathName()))
		CloseFile();
}

void CDqmjSEDlg::OnFileClose()
{
	CloseFile();
}

void CDqmjSEDlg::OnEditItemList()
{
	CItemListDlg dlg;
	dlg.DoModal();
}

void CDqmjSEDlg::OnEditMonsterList()
{
	CMonsterListDlg dlg;
	dlg.DoModal();
}

//////////////////////////////////////////////////////////////////////////

void CDqmjSEDlg::RefreshBriefing(DQMJ_SAVE_BRIEFING &briefing)
{
	SetDlgItemText(IDC_BRIEFING_INTERRUPT, briefing.interrupt ? _T("はい") : _T("いいえ"));
	SetDlgItemText(IDC_BRIEFING_PLACE, MakePlaceString(briefing.place_id));
	SetDlgItemText(IDC_BRIEFING_PLAYERNAME, CDqmjSEApp::GetNameString(briefing.player_name));
	SetDlgItemText(IDC_BRIEFING_STORYPROGRESS, GetStoryString(briefing.story_progress));
	SetDlgItemText(IDC_BRIEFING_PLAYTIME, MakeTimeString(briefing.play_time_hour, briefing.play_time_min, briefing.play_time_sec));
	SetDlgItemText(IDC_BRIEFING_NAME1, CDqmjSEApp::GetNameString(briefing.party_member_name[0]));
	SetDlgItemText(IDC_BRIEFING_NAME2, CDqmjSEApp::GetNameString(briefing.party_member_name[1]));
	SetDlgItemText(IDC_BRIEFING_NAME3, CDqmjSEApp::GetNameString(briefing.party_member_name[2]));
	SetDlgItemText(IDC_BRIEFING_LEVEL1, MakeLevelString(briefing.party_member_level[0]));
	SetDlgItemText(IDC_BRIEFING_LEVEL2, MakeLevelString(briefing.party_member_level[1]));
	SetDlgItemText(IDC_BRIEFING_LEVEL3, MakeLevelString(briefing.party_member_level[2]));
	SetDlgItemText(IDC_BRIEFING_RACE1, MakeRaceString(briefing.party_member_race[0]));
	SetDlgItemText(IDC_BRIEFING_RACE2, MakeRaceString(briefing.party_member_race[1]));
	SetDlgItemText(IDC_BRIEFING_RACE3, MakeRaceString(briefing.party_member_race[2]));
}

void CDqmjSEDlg::RefreshPlayInfo(DQMJ_SAVE_PLAY_INFO &playinfo)
{
	SetDlgItemText(IDC_EDIT_PLAYINFO_NAME, CDqmjSEApp::GetNameString(playinfo.player_name));
	SetDlgItemInt(IDC_EDIT_PLAYINFO_GOLD, playinfo.gold, FALSE);
	SetDlgItemInt(IDC_EDIT_PLAYINFO_DEPOSIT, playinfo.deposit, FALSE);
	SetDlgItemInt(IDC_EDIT_PLAYINFO_VICTORYTIMES, playinfo.victory_times, FALSE);
	SetDlgItemInt(IDC_EDIT_PLAYINFO_SCOUTTIMES, playinfo.scout_times, FALSE);
	SetDlgItemInt(IDC_EDIT_PLAYINFO_COMBINETIMES, playinfo.combine_times, FALSE);
	SetDlgItemInt(IDC_EDIT_PLAYINFO_HOUR, playinfo.play_time_hour, FALSE);
	SetDlgItemInt(IDC_EDIT_PLAYINFO_MINUTE, playinfo.play_time_min, FALSE);
	SetDlgItemInt(IDC_EDIT_PLAYINFO_SECOND, playinfo.play_time_sec, FALSE);

	CheckDlgButton(IDC_CHECK_PLAYERSKILL_ZOOM, playinfo.player_skill[DQMJ_PLAYERSKILL_ZOOM] ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_PLAYERSKILL_EVAC, playinfo.player_skill[DQMJ_PLAYERSKILL_EVAC] ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_PLAYERSKILL_WHISTLE, playinfo.player_skill[DQMJ_PLAYERSKILL_WHISTLE] ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_PLAYERSKILL_STEALTH, playinfo.player_skill[DQMJ_PLAYERSKILL_STEALTH] ? BST_CHECKED : BST_UNCHECKED);
}

void CDqmjSEDlg::RefreshItemInfo(DQMJ_SAVE_ITEM_INFO &iteminfo)
{
	GetDlgItem(IDC_CHECK_SKILLBOOK_WARRIOR)->EnableWindow(iteminfo.bookstore_inited);
	GetDlgItem(IDC_CHECK_SKILLBOOK_MAGE)->EnableWindow(iteminfo.bookstore_inited);
	GetDlgItem(IDC_CHECK_SKILLBOOK_CLERIC)->EnableWindow(iteminfo.bookstore_inited);
	GetDlgItem(IDC_CHECK_SKILLBOOK_FIGHTER)->EnableWindow(iteminfo.bookstore_inited);
	GetDlgItem(IDC_CHECK_SKILLBOOK_SAGE)->EnableWindow(iteminfo.bookstore_inited);
	GetDlgItem(IDC_CHECK_SKILLBOOK_THIEF)->EnableWindow(iteminfo.bookstore_inited);

	CheckDlgButton(IDC_CHECK_SKILLBOOK_INITFLAG, iteminfo.bookstore_inited ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_SKILLBOOK_WARRIOR, iteminfo.bookstore_onsale[DQMJ_SKILLBOOK_WARRIOR] ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_SKILLBOOK_MAGE, iteminfo.bookstore_onsale[DQMJ_SKILLBOOK_MAGE] ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_SKILLBOOK_CLERIC, iteminfo.bookstore_onsale[DQMJ_SKILLBOOK_CLERIC] ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_SKILLBOOK_FIGHTER, iteminfo.bookstore_onsale[DQMJ_SKILLBOOK_FIGHTER] ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_SKILLBOOK_SAGE, iteminfo.bookstore_onsale[DQMJ_SKILLBOOK_SAGE] ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_SKILLBOOK_THIEF, iteminfo.bookstore_onsale[DQMJ_SKILLBOOK_THIEF] ? BST_CHECKED : BST_UNCHECKED);
}

void CDqmjSEDlg::RefreshRanchInfo(DQMJ_SAVE_RANCH_INFO &ranchinfo)
{
	const int party_name_id[] = { IDC_PARTY_NAME1, IDC_PARTY_NAME2, IDC_PARTY_NAME3 };
	const int party_level_id[] = { IDC_PARTY_LEVEL1, IDC_PARTY_LEVEL2, IDC_PARTY_LEVEL3 };
	const int party_race_id[] = { IDC_PARTY_RACE1, IDC_PARTY_RACE2, IDC_PARTY_RACE3 };
	const int party_remove_id[] = { IDC_BUTTON_PARTY_REMOVE1, IDC_BUTTON_PARTY_REMOVE2, IDC_BUTTON_PARTY_REMOVE3 };
	const int party_edit_id[] = { IDC_BUTTON_PARTY_EDIT1, IDC_BUTTON_PARTY_EDIT2, IDC_BUTTON_PARTY_EDIT3 };

	SetDlgItemText(IDC_PLAYINFO_MONSTER_NUM, GetMonsterNumString(ranchinfo.monster_num));

	for (int i = 0; i < ranchinfo.party_member_num; i++)
	{
		DQMJ_SAVE_MONSTER_INFO monster;

		if (!::DQMJSaveQueryMonsterInfo(CDqmjSEApp::GetSaveHandle(), ranchinfo.party_member_idx[i], &monster))
		{
			SetDlgItemText(party_name_id[i], _T(""));
			SetDlgItemText(party_race_id[i], MakeRaceString(0x00));
		}
		else
		{
			SetDlgItemText(party_name_id[i], CDqmjSEApp::GetNameString(monster.name));
			SetDlgItemText(party_level_id[i], MakeLevelString(monster.level));
			SetDlgItemText(party_race_id[i], MakeRaceString(monster.race));
			GetDlgItem(party_edit_id[i])->EnableWindow(TRUE);
		}

		GetDlgItem(party_remove_id[i])->EnableWindow(TRUE);
	}

	const int standby_name_id[] = { IDC_STANDBY_NAME1, IDC_STANDBY_NAME2, IDC_STANDBY_NAME3 };
	const int standby_level_id[] = { IDC_STANDBY_LEVEL1, IDC_STANDBY_LEVEL2, IDC_STANDBY_LEVEL3 };
	const int standby_race_id[] = { IDC_STANDBY_RACE1, IDC_STANDBY_RACE2, IDC_STANDBY_RACE3 };
	const int standby_remove_id[] = { IDC_BUTTON_STANDBY_REMOVE1, IDC_BUTTON_STANDBY_REMOVE2, IDC_BUTTON_STANDBY_REMOVE3 };
	const int standby_edit_id[] = { IDC_BUTTON_STANDBY_EDIT1, IDC_BUTTON_STANDBY_EDIT2, IDC_BUTTON_STANDBY_EDIT3 };

	for (int i = 0; i < ranchinfo.standby_num; i++)
	{
		DQMJ_SAVE_MONSTER_INFO monster;

		if (!::DQMJSaveQueryMonsterInfo(CDqmjSEApp::GetSaveHandle(), ranchinfo.standby_idx[i], &monster))
		{
			SetDlgItemText(standby_name_id[i], _T(""));
			SetDlgItemText(standby_race_id[i], MakeRaceString(0x00));
		}
		else
		{
			SetDlgItemText(standby_name_id[i], CDqmjSEApp::GetNameString(monster.name));
			SetDlgItemText(standby_level_id[i], MakeLevelString(monster.level));
			SetDlgItemText(standby_race_id[i], MakeRaceString(monster.race));
			GetDlgItem(standby_edit_id[i])->EnableWindow(TRUE);
		}

		GetDlgItem(standby_remove_id[i])->EnableWindow(TRUE);
	}
}

void CDqmjSEDlg::EnableAll(BOOL enable)
{
	if (!enable)
	{
		m_strPlayerName = _T("");
		m_nGold = 0;
		m_nDeposit = 0;
		m_nVictoryTimes = 0;
		m_nScoutTimes = 0;
		m_nCombineTimes = 0;
		m_nHour = 0;
		m_nMinute = 0;
		m_nSecond = 0;

		UpdateData(FALSE);

		SetDlgItemText(IDC_BRIEFING_INTERRUPT, _T("--"));
		SetDlgItemText(IDC_BRIEFING_PLACE, _T("--"));
		SetDlgItemText(IDC_BRIEFING_PLAYERNAME, _T("-----"));
		SetDlgItemText(IDC_BRIEFING_STORYPROGRESS, GetStoryString(0));
		SetDlgItemText(IDC_BRIEFING_PLAYTIME, _T("--:--:--"));
		SetDlgItemText(IDC_BRIEFING_NAME1, _T("-----"));
		SetDlgItemText(IDC_BRIEFING_NAME2, _T("-----"));
		SetDlgItemText(IDC_BRIEFING_NAME3, _T("-----"));
		SetDlgItemText(IDC_BRIEFING_LEVEL1, _T("--"));
		SetDlgItemText(IDC_BRIEFING_LEVEL2, _T("--"));
		SetDlgItemText(IDC_BRIEFING_LEVEL3, _T("--"));
		SetDlgItemText(IDC_BRIEFING_RACE1, _T("--"));
		SetDlgItemText(IDC_BRIEFING_RACE2, _T("--"));
		SetDlgItemText(IDC_BRIEFING_RACE3, _T("--"));
		SetDlgItemText(IDC_PLAYINFO_MONSTER_NUM, GetMonsterNumString(0));

		CheckDlgButton(IDC_CHECK_PLAYERSKILL_ZOOM, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_PLAYERSKILL_EVAC, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_PLAYERSKILL_WHISTLE, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_PLAYERSKILL_STEALTH, BST_UNCHECKED);

		SetDlgItemText(IDC_PARTY_NAME1, _T("-----"));
		SetDlgItemText(IDC_PARTY_NAME2, _T("-----"));
		SetDlgItemText(IDC_PARTY_NAME3, _T("-----"));
		SetDlgItemText(IDC_PARTY_LEVEL1, _T("--"));
		SetDlgItemText(IDC_PARTY_LEVEL2, _T("--"));
		SetDlgItemText(IDC_PARTY_LEVEL3, _T("--"));
		SetDlgItemText(IDC_PARTY_RACE1, _T("--"));
		SetDlgItemText(IDC_PARTY_RACE2, _T("--"));
		SetDlgItemText(IDC_PARTY_RACE3, _T("--"));

		SetDlgItemText(IDC_STANDBY_NAME1, _T("-----"));
		SetDlgItemText(IDC_STANDBY_NAME2, _T("-----"));
		SetDlgItemText(IDC_STANDBY_NAME3, _T("-----"));
		SetDlgItemText(IDC_STANDBY_LEVEL1, _T("--"));
		SetDlgItemText(IDC_STANDBY_LEVEL2, _T("--"));
		SetDlgItemText(IDC_STANDBY_LEVEL3, _T("--"));
		SetDlgItemText(IDC_STANDBY_RACE1, _T("--"));
		SetDlgItemText(IDC_STANDBY_RACE2, _T("--"));
		SetDlgItemText(IDC_STANDBY_RACE3, _T("--"));

		CheckDlgButton(IDC_CHECK_SKILLBOOK_INITFLAG, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_SKILLBOOK_WARRIOR, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_SKILLBOOK_MAGE, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_SKILLBOOK_CLERIC, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_SKILLBOOK_FIGHTER, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_SKILLBOOK_SAGE, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_SKILLBOOK_THIEF, BST_UNCHECKED);

		GetDlgItem(IDC_BUTTON_PARTY_REMOVE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PARTY_REMOVE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PARTY_REMOVE3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PARTY_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PARTY_EDIT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PARTY_EDIT3)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_STANDBY_REMOVE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STANDBY_REMOVE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STANDBY_REMOVE3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STANDBY_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STANDBY_EDIT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STANDBY_EDIT3)->EnableWindow(FALSE);
	}

	GetMenu()->EnableMenuItem(ID_FILE_SAVE, enable ? MF_ENABLED : MF_GRAYED);
	GetMenu()->EnableMenuItem(ID_FILE_SAVE_AS, enable ? MF_ENABLED : MF_GRAYED);
	GetMenu()->EnableMenuItem(ID_FILE_CLOSE, enable ? MF_ENABLED : MF_GRAYED);
	GetMenu()->EnableMenuItem(ID_EDIT_ITEM_LIST, enable ? MF_ENABLED : MF_GRAYED);
	GetMenu()->EnableMenuItem(ID_EDIT_MONSTER_LIST, enable ? MF_ENABLED : MF_GRAYED);
	GetMenu()->EnableMenuItem(ID_EDIT_MONSTER_LIBRARY, enable ? MF_ENABLED : MF_GRAYED);
	GetMenu()->EnableMenuItem(ID_EDIT_SKILL_LIBRARY, enable ? MF_ENABLED : MF_GRAYED);

	GetDlgItem(IDC_GROUP_BRIEFING)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_BRIEFING_INTERRUPT)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_BRIEFING_PLAYERNAME)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_BRIEFING_STORYPROGRESS)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_BRIEFING_PLACE)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_BRIEFING_PLAYTIME)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_INTERRUPT)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_PLAYERNAME)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_STORYPROGRESS)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_PLACE)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_PLAYTIME)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_NAME1)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_NAME2)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_NAME3)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_LEVEL1)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_LEVEL2)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_LEVEL3)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_RACE1)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_RACE2)->EnableWindow(enable);
	GetDlgItem(IDC_BRIEFING_RACE3)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_PLAYINFO)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_PLAYINFO_NAME)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_PLAYINFO_GOLD)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_PLAYINFO_DEPOSIT)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_PLAYINFO_VICTORYTIMES)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_PLAYINFO_SCOUTTIMES)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_PLAYINFO_COMBINETIMES)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_PLAYINFO_TIME)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_PLAYINFO_HOUR)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_PLAYINFO_MINUTE)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_PLAYINFO_SECOND)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_PLAYINFO_MONSTER_NUM)->EnableWindow(enable);
	GetDlgItem(IDC_PLAYINFO_MONSTER_NUM)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_PLAYINFO_NAME)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_PLAYINFO_GOLD)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_PLAYINFO_DEPOSIT)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_PLAYINFO_VICTORYTIMES)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_PLAYINFO_SCOUTTIMES)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_PLAYINFO_COMBINETIMES)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_PLAYINFO_HOUR)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_PLAYINFO_MINUTE)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_PLAYINFO_SECOND)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_PLAYINFO_GOLD)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_PLAYINFO_DEPOSIT)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_PLAYINFO_VICTORYTIMES)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_PLAYINFO_SCOUTTIMES)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_PLAYINFO_COMBINETIMES)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_PLAYINFO_HOUR)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_PLAYINFO_MINUTE)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_PLAYINFO_SECOND)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_PLAYERSKILL)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_PLAYERSKILL_ZOOM)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_PLAYERSKILL_EVAC)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_PLAYERSKILL_WHISTLE)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_PLAYERSKILL_STEALTH)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_PARTY)->EnableWindow(enable);
	GetDlgItem(IDC_PARTY_NAME1)->EnableWindow(enable);
	GetDlgItem(IDC_PARTY_NAME2)->EnableWindow(enable);
	GetDlgItem(IDC_PARTY_NAME3)->EnableWindow(enable);
	GetDlgItem(IDC_PARTY_LEVEL1)->EnableWindow(enable);
	GetDlgItem(IDC_PARTY_LEVEL2)->EnableWindow(enable);
	GetDlgItem(IDC_PARTY_LEVEL3)->EnableWindow(enable);
	GetDlgItem(IDC_PARTY_RACE1)->EnableWindow(enable);
	GetDlgItem(IDC_PARTY_RACE2)->EnableWindow(enable);
	GetDlgItem(IDC_PARTY_RACE3)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_PARTY_EXCHANGE1)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_PARTY_EXCHANGE2)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_PARTY_EXCHANGE3)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_STANDBY)->EnableWindow(enable);
	GetDlgItem(IDC_STANDBY_NAME1)->EnableWindow(enable);
	GetDlgItem(IDC_STANDBY_NAME2)->EnableWindow(enable);
	GetDlgItem(IDC_STANDBY_NAME3)->EnableWindow(enable);
	GetDlgItem(IDC_STANDBY_LEVEL1)->EnableWindow(enable);
	GetDlgItem(IDC_STANDBY_LEVEL2)->EnableWindow(enable);
	GetDlgItem(IDC_STANDBY_LEVEL3)->EnableWindow(enable);
	GetDlgItem(IDC_STANDBY_RACE1)->EnableWindow(enable);
	GetDlgItem(IDC_STANDBY_RACE2)->EnableWindow(enable);
	GetDlgItem(IDC_STANDBY_RACE3)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_STANDBY_EXCHANGE1)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_STANDBY_EXCHANGE2)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_STANDBY_EXCHANGE3)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_SKILLBOOK)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_SKILLBOOK_INITFLAG)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_SKILLBOOK_WARRIOR)->EnableWindow(IsDlgButtonChecked(IDC_CHECK_SKILLBOOK_INITFLAG));
	GetDlgItem(IDC_CHECK_SKILLBOOK_MAGE)->EnableWindow(IsDlgButtonChecked(IDC_CHECK_SKILLBOOK_INITFLAG));
	GetDlgItem(IDC_CHECK_SKILLBOOK_CLERIC)->EnableWindow(IsDlgButtonChecked(IDC_CHECK_SKILLBOOK_INITFLAG));
	GetDlgItem(IDC_CHECK_SKILLBOOK_FIGHTER)->EnableWindow(IsDlgButtonChecked(IDC_CHECK_SKILLBOOK_INITFLAG));
	GetDlgItem(IDC_CHECK_SKILLBOOK_SAGE)->EnableWindow(IsDlgButtonChecked(IDC_CHECK_SKILLBOOK_INITFLAG));
	GetDlgItem(IDC_CHECK_SKILLBOOK_THIEF)->EnableWindow(IsDlgButtonChecked(IDC_CHECK_SKILLBOOK_INITFLAG));
}

//////////////////////////////////////////////////////////////////////////

CString CDqmjSEDlg::GetStoryString(int story)
{
	WCHAR str[] = L"☆☆☆☆☆☆☆☆☆☆";
	for (int i = 0; i < story; i++)
		str[i] = L'★';

	USES_CONVERSION;
	return W2T(str);
}

CString CDqmjSEDlg::MakePlaceString(int place)
{
	LPCTSTR str = ::DQMJSaveGetPlaceName(place);
	return (str == NULL) ? _T("不明") : str;
}

CString CDqmjSEDlg::MakeTimeString(int hour, int minute, int second)
{
	CString str;
	str.Format(_T("%d:%02d:%02d"), hour, minute, second);

	return str;
}

CString CDqmjSEDlg::MakeLevelString(int level)
{
	CString str;
	str.Format(_T("Lv.%d"), level);

	return str;
}

CString CDqmjSEDlg::MakeRaceString(int race)
{
	CString str;

	DQMJ_SAVE_RACE_SETTING rs;
	if ((race != 0x00) && ::DQMJSaveGetRaceSetting(race, &rs))
		str.Format(_T("[%s]"), rs.name);
	else
		str = _T("[不明]");

	return str;
}

CString CDqmjSEDlg::GetMonsterNumString(int monster_num)
{
	CString str;
	str.Format(_T("%d 匹"), monster_num);

	return str;
}

//////////////////////////////////////////////////////////////////////////
