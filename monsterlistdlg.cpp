
#include "stdafx.h"
#include "dqmjse.h"
#include "monsterlistdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

const int CMonsterListDlg::MAXLEVEL_LIST[]		= { 50, 75, 99 };
const LPCTSTR CMonsterListDlg::SEX_LIST[]		= { _T("♂"), _T("♀"), _T("両性具有") };
const LPCTSTR CMonsterListDlg::RANK_LIST[]		= { _T("なし"), _T("F"), _T("E"), _T("D"), _T("C"), _T("B"), _T("A"), _T("S"), _T("SS"), _T("??") };
const LPCTSTR CMonsterListDlg::TYPE_LIST[]		= { _T("なし"), _T("スライム系"), _T("ドラゴン系"), _T("しぜん系"), _T("まじゅう系"), _T("ぶっしつ系"), _T("あくま系"), _T("ゾンビ系"), _T("しんじゅう系") };
const LPCTSTR CMonsterListDlg::STRATEGY_LIST[]	= { _T("ガンガンいこうぜ"), _T("いろいろやろうぜ"), _T("いのちだいじに"), _T("とくぎつかうな") };
const LPCTSTR CMonsterListDlg::SOURCE_LIST[]	= { _T("システム"), _T("ワイヤレス交換(?)"), _T("他国マスタースカウト"), _T("野良モンスタースカウト"), _T("配合"), _T("ゲスト") };
const LPCTSTR CMonsterListDlg::GROWTH_LIST[]	= { _T("ＨＰ"), _T("ＭＰ"), _T("攻撃力"), _T("守備力"), _T("素早さ"), _T("賢さ") };
const LPCTSTR CMonsterListDlg::GUARD_LIST[]		= { _T("弱い"), _T("ふつう"), _T("軽減"), _T("半減"), _T("激減"), _T("無効"), _T("反射"), _T("吸収") };

CList<CMonsterListDlg::IDStrPair> CMonsterListDlg::m_raceIDStrList;
CList<CMonsterListDlg::IDStrPair> CMonsterListDlg::m_skillsetIDStrList;
CList<CMonsterListDlg::IDStrPair> CMonsterListDlg::m_abilityIDStrList;
int CMonsterListDlg::m_raceToCBIndex[];
int CMonsterListDlg::m_skillsetToCBIndex[];
int CMonsterListDlg::m_abilityToCBIndex[];

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CMonsterListDlg, CDialog)

BEGIN_MESSAGE_MAP(CMonsterListDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_NORMALIZE, OnBnClickedCheckNormalize)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_UP, OnBnClickedButtonMonsterUp)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_TOP, OnBnClickedButtonMonsterTop)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_DOWN, OnBnClickedButtonMonsterDown)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_BOTTOM, OnBnClickedButtonMonsterBottom)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_ADD, OnBnClickedButtonMonsterAdd)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_REMOVE, OnBnClickedButtonMonsterRemove)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_MONSTER_LIST, OnLvnItemchangingListMonsterList)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

CMonsterListDlg::CMonsterListDlg(CWnd *pParent) : CDialog(IDD_DQMJSE_MONSTER_LIST, pParent)
{
	m_nLevel = 0;
	m_nCombine = 0;
	m_nBaseHp = 0;
	m_nBaseMp = 0;
	m_nBaseAtk = 0;
	m_nBaseDef = 0;
	m_nBaseAgi = 0;
	m_nBaseInt = 0;
	m_nAtk = 0;
	m_nDef = 0;
	m_nAgi = 0;
	m_nInt = 0;
	m_nCurHp = 0;
	m_nCurMp = 0;
	m_nMaxLevel = 0;
	m_nMaxHp = 0;
	m_nMaxMp = 0;
	m_nExp = 0;
	m_nSkillPoint = 0;
	m_bInterrupt = 0;
	m_bSelectChanging = FALSE;
	m_strName = _T("");
	m_strMaster = _T("");
	m_strParentsName[0] = _T("");
	m_strParentsName[1] = _T("");
	m_strParentsMaster[0] = _T("");
	m_strParentsMaster[1] = _T("");

	::ZeroMemory(m_normalizeFlags, sizeof(m_normalizeFlags));
	::ZeroMemory(m_nGrowthLevel, sizeof(m_nGrowthLevel));
	::ZeroMemory(m_nSkillsetPt, sizeof(m_nSkillsetPt));
	::ZeroMemory(m_masterName, sizeof(m_masterName));
	::ZeroMemory(m_monsterInfo, sizeof(m_monsterInfo));

	InitCBIndex();
}

//////////////////////////////////////////////////////////////////////////

void CMonsterListDlg::DoDataExchange(CDataExchange *pDX)
{
	::DDX_Text(pDX, IDC_EDIT_LEVEL, m_nLevel);
	::DDX_Text(pDX, IDC_EDIT_COMBINE, m_nCombine);
	::DDX_Text(pDX, IDC_EDIT_BASE_HP, m_nBaseHp);
	::DDX_Text(pDX, IDC_EDIT_BASE_MP, m_nBaseMp);
	::DDX_Text(pDX, IDC_EDIT_BASE_ATK, m_nBaseAtk);
	::DDX_Text(pDX, IDC_EDIT_BASE_DEF, m_nBaseDef);
	::DDX_Text(pDX, IDC_EDIT_BASE_AGI, m_nBaseAgi);
	::DDX_Text(pDX, IDC_EDIT_BASE_INT, m_nBaseInt);
	::DDX_Text(pDX, IDC_EDIT_ATK, m_nAtk);
	::DDX_Text(pDX, IDC_EDIT_DEF, m_nDef);
	::DDX_Text(pDX, IDC_EDIT_AGI, m_nAgi);
	::DDX_Text(pDX, IDC_EDIT_INT, m_nInt);
	::DDX_Text(pDX, IDC_EDIT_CUR_HP, m_nCurHp);
	::DDX_Text(pDX, IDC_EDIT_CUR_MP, m_nCurMp);
	::DDX_Text(pDX, IDC_EDIT_MAX_LEVEL, m_nMaxLevel);
	::DDX_Text(pDX, IDC_EDIT_MAX_HP, m_nMaxHp);
	::DDX_Text(pDX, IDC_EDIT_MAX_MP, m_nMaxMp);
	::DDX_Text(pDX, IDC_EDIT_EXP, m_nExp);
	::DDX_Text(pDX, IDC_EDIT_SKILL_POINT, m_nSkillPoint);
	::DDX_Text(pDX, IDC_EDIT_GROWTH_LEVEL_START, m_nGrowthLevel[0]);
	::DDX_Text(pDX, IDC_EDIT_GROWTH_LEVEL_END, m_nGrowthLevel[1]);
	::DDX_Text(pDX, IDC_EDIT_SKILLSET_PT1, m_nSkillsetPt[0]);
	::DDX_Text(pDX, IDC_EDIT_SKILLSET_PT2, m_nSkillsetPt[1]);
	::DDX_Text(pDX, IDC_EDIT_SKILLSET_PT3, m_nSkillsetPt[2]);
	::DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	::DDX_Text(pDX, IDC_EDIT_MASTER, m_strMaster);
	::DDX_Text(pDX, IDC_EDIT_FARTHER_NAME, m_strParentsName[0]);
	::DDX_Text(pDX, IDC_EDIT_FARTHER_MASTER, m_strParentsMaster[0]);
	::DDX_Text(pDX, IDC_EDIT_MOTHER_NAME, m_strParentsName[1]);
	::DDX_Text(pDX, IDC_EDIT_MOTHER_MASTER, m_strParentsMaster[1]);

	::DDX_Control(pDX, IDC_LIST_MONSTER_LIST, m_lstMonster);
	::DDX_Control(pDX, IDC_LIST_SKILL_LIST, m_lstSkill);
	::DDX_Control(pDX, IDC_COMBO_SEX, m_cmbSex);
	::DDX_Control(pDX, IDC_COMBO_RACE, m_cmbRace);
	::DDX_Control(pDX, IDC_COMBO_RANK, m_cmbRank);
	::DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbType);
	::DDX_Control(pDX, IDC_COMBO_STRATEGY, m_cmbStrategy);
	::DDX_Control(pDX, IDC_COMBO_SOURCE, m_cmbSource);
	::DDX_Control(pDX, IDC_COMBO_MAX_LEVEL, m_cmbMaxLevel);
	::DDX_Control(pDX, IDC_COMBO_GROWTH_TYPE, m_cmbGrowthType);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL1, m_cmbGuard[0]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL2, m_cmbGuard[1]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL3, m_cmbGuard[2]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL4, m_cmbGuard[3]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL5, m_cmbGuard[4]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL6, m_cmbGuard[5]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL7, m_cmbGuard[6]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL8, m_cmbGuard[7]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL9, m_cmbGuard[8]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL10, m_cmbGuard[9]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL11, m_cmbGuard[10]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL12, m_cmbGuard[11]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL13, m_cmbGuard[12]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL14, m_cmbGuard[13]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL15, m_cmbGuard[14]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL16, m_cmbGuard[15]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL17, m_cmbGuard[16]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL18, m_cmbGuard[17]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL19, m_cmbGuard[18]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL20, m_cmbGuard[19]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL21, m_cmbGuard[20]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL22, m_cmbGuard[21]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL23, m_cmbGuard[22]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL24, m_cmbGuard[23]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL25, m_cmbGuard[24]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL26, m_cmbGuard[25]);
	::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL27, m_cmbGuard[26]);
	::DDX_Control(pDX, IDC_COMBO_SKILLSET1, m_cmbSkillset[0]);
	::DDX_Control(pDX, IDC_COMBO_SKILLSET2, m_cmbSkillset[1]);
	::DDX_Control(pDX, IDC_COMBO_SKILLSET3, m_cmbSkillset[2]);
	::DDX_Control(pDX, IDC_COMBO_ABILITY1, m_cmbAbility[0]);
	::DDX_Control(pDX, IDC_COMBO_ABILITY2, m_cmbAbility[1]);
	::DDX_Control(pDX, IDC_COMBO_ABILITY3, m_cmbAbility[2]);
	::DDX_Control(pDX, IDC_COMBO_ABILITY4, m_cmbAbility[3]);
	::DDX_Control(pDX, IDC_COMBO_ABILITY5, m_cmbAbility[4]);
	::DDX_Control(pDX, IDC_COMBO_ABILITY6, m_cmbAbility[5]);
	::DDX_Control(pDX, IDC_COMBO_FARTHER_RACE, m_cmbParentsRace[0]);
	::DDX_Control(pDX, IDC_COMBO_FARTHER_FARTHER_RACE, m_cmbGrandparentsRace[0][0]);
	::DDX_Control(pDX, IDC_COMBO_FARTHER_MOTHER_RACE, m_cmbGrandparentsRace[0][1]);
	::DDX_Control(pDX, IDC_COMBO_MOTHER_RACE, m_cmbParentsRace[1]);
	::DDX_Control(pDX, IDC_COMBO_MOTHER_FARTHER_RACE, m_cmbGrandparentsRace[1][0]);
	::DDX_Control(pDX, IDC_COMBO_MOTHER_MOTHER_RACE, m_cmbGrandparentsRace[1][1]);

	::DDX_Text(pDX, IDC_EDIT_LEVEL, m_nLevel);
	::DDX_Text(pDX, IDC_EDIT_COMBINE, m_nCombine);
	::DDX_Text(pDX, IDC_EDIT_BASE_HP, m_nBaseHp);
	::DDX_Text(pDX, IDC_EDIT_BASE_MP, m_nBaseMp);
	::DDX_Text(pDX, IDC_EDIT_BASE_ATK, m_nBaseAtk);
	::DDX_Text(pDX, IDC_EDIT_BASE_DEF, m_nBaseDef);
	::DDX_Text(pDX, IDC_EDIT_BASE_AGI, m_nBaseAgi);
	::DDX_Text(pDX, IDC_EDIT_BASE_INT, m_nBaseInt);
	::DDX_Text(pDX, IDC_EDIT_ATK, m_nAtk);
	::DDX_Text(pDX, IDC_EDIT_DEF, m_nDef);
	::DDX_Text(pDX, IDC_EDIT_AGI, m_nAgi);
	::DDX_Text(pDX, IDC_EDIT_INT, m_nInt);
	::DDX_Text(pDX, IDC_EDIT_CUR_HP, m_nCurHp);
	::DDX_Text(pDX, IDC_EDIT_CUR_MP, m_nCurMp);
	::DDX_Text(pDX, IDC_EDIT_MAX_LEVEL, m_nMaxLevel);
	::DDX_Text(pDX, IDC_EDIT_MAX_HP, m_nMaxHp);
	::DDX_Text(pDX, IDC_EDIT_MAX_MP, m_nMaxMp);
	::DDX_Text(pDX, IDC_EDIT_SKILL_POINT, m_nSkillPoint);
	::DDX_Text(pDX, IDC_EDIT_GROWTH_LEVEL_START, m_nGrowthLevel[0]);
	::DDX_Text(pDX, IDC_EDIT_GROWTH_LEVEL_END, m_nGrowthLevel[1]);

	CDialog::DoDataExchange(pDX);
}

BOOL CMonsterListDlg::OnInitDialog()
{
	static const int guard_name_id[] =
	{
		IDC_GUARD_NAME1, IDC_GUARD_NAME2, IDC_GUARD_NAME3, IDC_GUARD_NAME4, IDC_GUARD_NAME5, IDC_GUARD_NAME6, IDC_GUARD_NAME7, IDC_GUARD_NAME8, IDC_GUARD_NAME9,
		IDC_GUARD_NAME10, IDC_GUARD_NAME11, IDC_GUARD_NAME12, IDC_GUARD_NAME13, IDC_GUARD_NAME14, IDC_GUARD_NAME15, IDC_GUARD_NAME16, IDC_GUARD_NAME17, IDC_GUARD_NAME18,
		IDC_GUARD_NAME19, IDC_GUARD_NAME20, IDC_GUARD_NAME21, IDC_GUARD_NAME22, IDC_GUARD_NAME23, IDC_GUARD_NAME24, IDC_GUARD_NAME25, IDC_GUARD_NAME26, IDC_GUARD_NAME27, 
	};

	CDialog::OnInitDialog();

	DQMJ_SAVE_BRIEFING briefing;
	VERIFY(::DQMJSaveQueryBriefing(CDqmjSEApp::GetSaveHandle(), &briefing));
	DQMJ_SAVE_PLAY_INFO playerinfo;
	VERIFY(::DQMJSaveQueryPlayInfo(CDqmjSEApp::GetSaveHandle(), &playerinfo));
	DQMJ_SAVE_RANCH_INFO ranchinfo;
	VERIFY(::DQMJSaveQueryRanchInfo(CDqmjSEApp::GetSaveHandle(), &ranchinfo));

	m_bInterrupt = briefing.interrupt;
	::CopyMemory(m_masterName, playerinfo.player_name, sizeof(m_masterName));

	SetDlgItemText(IDC_MONSTER_NUM, GetMonsterNumString(ranchinfo.monster_num));

	m_lstMonster.SetExtendedStyle(m_lstMonster.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	VERIFY(m_lstMonster.InsertColumn(COLUMN_NO, _T("No."), LVCFMT_LEFT, 20) == COLUMN_NO);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_NAME, _T("名前"), LVCFMT_LEFT, 72) == COLUMN_NAME);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_PLACE, _T("場所"), LVCFMT_CENTER, 28) == COLUMN_PLACE);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_SEX, _T("性別"), LVCFMT_CENTER, 28) == COLUMN_SEX);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_RACE, _T("種族"), LVCFMT_LEFT, 88) == COLUMN_RACE);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_RANK, _T("RANK"), LVCFMT_CENTER, 28) == COLUMN_RANK);
	VERIFY(m_lstMonster.InsertColumn(COLUMN_TYPE, _T("系統"), LVCFMT_LEFT, 64) == COLUMN_TYPE);

	for (int i = 0; i < ranchinfo.monster_num; i++)
	{
		VERIFY(m_lstMonster.InsertItem(i, _T("")) == i);
		VERIFY(::DQMJSaveQueryMonsterInfo(CDqmjSEApp::GetSaveHandle(), i, &m_monsterInfo[i]));

		m_lstMonster.SetItemText(i, COLUMN_NO, CDqmjSEApp::GetDecimalString(i + 1));
		m_lstMonster.SetItemText(i, COLUMN_NAME, CDqmjSEApp::GetNameString(m_monsterInfo[i].name));
		m_lstMonster.SetItemText(i, COLUMN_SEX, GetSafeCBString(m_monsterInfo[i].sex, SEX_LIST, _countof(SEX_LIST)));
		m_lstMonster.SetItemText(i, COLUMN_RACE, GetRaceString(m_monsterInfo[i].race));
		m_lstMonster.SetItemText(i, COLUMN_RANK, GetSafeCBString(m_monsterInfo[i].rank, RANK_LIST, _countof(RANK_LIST)));
		m_lstMonster.SetItemText(i, COLUMN_TYPE, GetSafeCBString(m_monsterInfo[i].type, TYPE_LIST, _countof(TYPE_LIST)));
	}

	for (int i = 0; i < DQMJ_MEMBER_MAX; i++)
	{
		m_lstMonster.SetItemText(ranchinfo.party_member_idx[i], COLUMN_PLACE, _T("パーティー"));
		m_lstMonster.SetItemText(ranchinfo.standby_idx[i], COLUMN_PLACE, _T("スタンバイ"));
	}

	InitComboBox(m_cmbRace, m_raceIDStrList);
	InitComboBox(m_cmbParentsRace[0], m_raceIDStrList);
	InitComboBox(m_cmbParentsRace[1], m_raceIDStrList);
	InitComboBox(m_cmbGrandparentsRace[0][0], m_raceIDStrList);
	InitComboBox(m_cmbGrandparentsRace[0][1], m_raceIDStrList);
	InitComboBox(m_cmbGrandparentsRace[1][0], m_raceIDStrList);
	InitComboBox(m_cmbGrandparentsRace[1][1], m_raceIDStrList);

	for (int i = 0; i < _countof(MAXLEVEL_LIST); i++)
		VERIFY(m_cmbMaxLevel.SetItemData(m_cmbMaxLevel.AddString(CDqmjSEApp::GetDecimalString(MAXLEVEL_LIST[i])), MAXLEVEL_LIST[i]) != CB_ERR);
	for (int i = 0; i < _countof(SEX_LIST); i++)
		VERIFY(m_cmbSex.AddString(SEX_LIST[i]) == i);
	for (int i = 0; i < _countof(RANK_LIST); i++)
		VERIFY(m_cmbRank.AddString(RANK_LIST[i]) == i);
	for (int i = 0; i < _countof(TYPE_LIST); i++)
		VERIFY(m_cmbType.AddString(TYPE_LIST[i]) == i);
	for (int i = 0; i < _countof(STRATEGY_LIST); i++)
		VERIFY(m_cmbStrategy.AddString(STRATEGY_LIST[i]) == i);
	for (int i = 0; i < _countof(SOURCE_LIST); i++)
		VERIFY(m_cmbSource.AddString(SOURCE_LIST[i]) == i);
	for (int i = 0; i < _countof(GROWTH_LIST); i++)
		VERIFY(m_cmbGrowthType.AddString(GROWTH_LIST[i]) == i);
	for (int i = 0; i < _countof(m_cmbSkillset); i++)
		InitComboBox(m_cmbSkillset[i], m_skillsetIDStrList);
	for (int i = 0; i < _countof(m_cmbAbility); i++)
		InitComboBox(m_cmbAbility[i], m_abilityIDStrList);

	for (int i = 0; i < _countof(m_cmbGuard); i++)
	{
		SetDlgItemText(guard_name_id[i], ::DQMJSaveGetGuardName(i));
		for (int j = 0; j < _countof(GUARD_LIST); j++)
			VERIFY(m_cmbGuard[i].AddString(GUARD_LIST[j]) == j);
	}

	((CEdit *)GetDlgItem(IDC_EDIT_NAME))->SetLimitText(DQMJ_NAME_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT_MASTER))->SetLimitText(DQMJ_NAME_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT_FARTHER_NAME))->SetLimitText(DQMJ_NAME_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT_FARTHER_MASTER))->SetLimitText(DQMJ_NAME_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT_MOTHER_NAME))->SetLimitText(DQMJ_NAME_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT_MOTHER_MASTER))->SetLimitText(DQMJ_NAME_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT_COMBINE))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_COMBINE_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_LEVEL))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_LEVEL_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_MAX_LEVEL))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_LEVEL_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_BASE_HP))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_BASE_MP))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_BASE_ATK))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_BASE_DEF))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_BASE_AGI))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_BASE_INT))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_ATK))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_DEF))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_AGI))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_INT))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_MAX_HP))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_MAX_MP))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_CUR_HP))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_CUR_MP))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_STATUS_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_SKILL_POINT))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_SKILLPOINT_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_EXP))->SetLimitText(CDqmjSEApp::CalcDigit(UINT_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_GROWTH_LEVEL_START))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_LEVEL_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_GROWTH_LEVEL_END))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_LEVEL_MAX));

	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_COMBINE))->SetRange32(0, DQMJ_COMBINE_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_LEVEL))->SetRange32(0, DQMJ_LEVEL_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_MAX_LEVEL))->SetRange32(0, DQMJ_LEVEL_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_HP))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_MP))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_ATK))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_DEF))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_AGI))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_INT))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_ATK))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_DEF))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_AGI))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_INT))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_MAX_HP))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_MAX_MP))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_CUR_HP))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_CUR_MP))->SetRange32(0, DQMJ_STATUS_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_SKILL_POINT))->SetRange32(0, DQMJ_SKILLPOINT_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_GROWTH_LEVEL_START))->SetRange32(0, DQMJ_LEVEL_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_GROWTH_LEVEL_END))->SetRange32(0, DQMJ_LEVEL_MAX);

	RefreshEnable(-1);
	EnableAll(FALSE);
	NormalizeUpdated();

	return TRUE;
}

void CMonsterListDlg::OnBnClickedCheckNormalize()
{
	if (m_lstMonster.GetSelectedCount() <= 0)
		return;

	int cur_sel = m_lstMonster.GetSelectionMark();
	if (cur_sel <= 0)
		return;

	if (IsDlgButtonChecked(IDC_CHECK_NORMALIZE) == BST_CHECKED)
	{
		DQMJ_SAVE_MONSTER_INFO monsterinfo = m_monsterInfo[cur_sel];
		::DQMJSaveNormalizeMonster(m_bInterrupt, IsInPartyOrStandby(cur_sel), m_masterName, &monsterinfo, &m_monsterInfo[cur_sel]);
		m_normalizeFlags[cur_sel] = TRUE;
	}
	else
	{
		m_normalizeFlags[cur_sel] = FALSE;
		EnableAll(TRUE);
	}

	RefreshMonster(m_monsterInfo[cur_sel]);
	NormalizeUpdated();
}

void CMonsterListDlg::OnBnClickedButtonMonsterUp()
{
	if (m_lstMonster.GetSelectedCount() <= 0)
		return;

	int cur_sel = m_lstMonster.GetSelectionMark();
	if (cur_sel <= 0)
		return;
/*
	CString text;
	m_lstMonster.GetText(cur_sel, text);
	DWORD_PTR data = m_lstBaggage.GetItemData(cur_sel);
	m_lstMonster.DeleteString(cur_sel);

	cur_sel--;
	VERIFY(m_lstMonster.InsertString(cur_sel, text) == cur_sel);
	m_lstMonster.SetItemData(cur_sel, data);

	m_lstMonster.SetSel(cur_sel);
	RefreshEnable();*/
}

void CMonsterListDlg::OnBnClickedButtonMonsterTop()
{
	// TODO: Add your control notification handler code here
}

void CMonsterListDlg::OnBnClickedButtonMonsterDown()
{
	// TODO: Add your control notification handler code here
}

void CMonsterListDlg::OnBnClickedButtonMonsterBottom()
{
	// TODO: Add your control notification handler code here
}

void CMonsterListDlg::OnBnClickedButtonMonsterAdd()
{
	// TODO: Add your control notification handler code here
}

void CMonsterListDlg::OnBnClickedButtonMonsterRemove()
{
	// TODO: Add your control notification handler code here
}

void CMonsterListDlg::OnLvnItemchangingListMonsterList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if ((pNMLV->uOldState & LVIS_FOCUSED) && !(pNMLV->uNewState & LVIS_FOCUSED))
		m_bSelectChanging = TRUE;

	if (!((pNMLV->uOldState ^ pNMLV->uNewState) & LVIS_SELECTED))
		return;

	if (m_bSelectChanging && !(pNMLV->uNewState & LVIS_SELECTED))
	{
		m_bSelectChanging = FALSE;
		return;
	}

	int cur_sel = (pNMLV->uNewState & LVIS_SELECTED) ? pNMLV->iItem : -1;
	int prev_sel = (m_lstMonster.GetSelectedCount() > 0) ? m_lstMonster.GetSelectionMark() : -1;
	if (cur_sel == prev_sel)
		return;

	RefreshEnable(cur_sel);

	if (cur_sel < 0)
	{
		EnableAll(FALSE);
		NormalizeUpdated();
		return;
	}

	EnableAll(TRUE);
	CheckDlgButton(IDC_CHECK_NORMALIZE, m_normalizeFlags[cur_sel] ? BST_CHECKED : BST_UNCHECKED);
	RefreshMonster(m_monsterInfo[cur_sel]);
	NormalizeUpdated();
}

//////////////////////////////////////////////////////////////////////////

void CMonsterListDlg::RefreshEnable(int cur_sel)
{
	int item_count = m_lstMonster.GetItemCount();

	GetDlgItem(IDC_BUTTON_MONSTER_UP)->EnableWindow(cur_sel > 0);
	GetDlgItem(IDC_BUTTON_MONSTER_TOP)->EnableWindow(cur_sel > 0);
	GetDlgItem(IDC_BUTTON_MONSTER_DOWN)->EnableWindow((cur_sel >= 0) & (cur_sel < item_count - 1));
	GetDlgItem(IDC_BUTTON_MONSTER_BOTTOM)->EnableWindow((cur_sel >= 0) & (cur_sel < item_count - 1));
	GetDlgItem(IDC_BUTTON_MONSTER_ADD)->EnableWindow(item_count < DQMJ_MONSTER_MAX);
	GetDlgItem(IDC_BUTTON_MONSTER_REMOVE)->EnableWindow(cur_sel >= 0);
}

void CMonsterListDlg::RefreshMonster(DQMJ_SAVE_MONSTER_INFO &monster)
{
	static const int skillset_ctrl_id[][5] =
	{
		{ IDC_CHECK_SKILLSET_NONE1, IDC_LABEL_SKILLSET_PT1, IDC_EDIT_SKILLSET_PT1, IDC_SPIN_SKILLSET_PT1, IDC_BUTTON_SKILLSET_MAX1 },
		{ IDC_CHECK_SKILLSET_NONE2, IDC_LABEL_SKILLSET_PT2, IDC_EDIT_SKILLSET_PT2, IDC_SPIN_SKILLSET_PT2, IDC_BUTTON_SKILLSET_MAX2 },
		{ IDC_CHECK_SKILLSET_NONE3, IDC_LABEL_SKILLSET_PT3, IDC_EDIT_SKILLSET_PT3, IDC_SPIN_SKILLSET_PT3, IDC_BUTTON_SKILLSET_MAX3 },
	};

	static const int ability_none_id[] =
	{
		IDC_CHECK_ABILITY_NONE1, IDC_CHECK_ABILITY_NONE2, IDC_CHECK_ABILITY_NONE3, IDC_CHECK_ABILITY_NONE4, IDC_CHECK_ABILITY_NONE5, IDC_CHECK_ABILITY_NONE6,
	};

	static const int parents_ctrl_id[][12] =
	{
		{
			IDC_CHECK_FARTHER_NONE, IDC_CHECK_FARTHER_FARTHER_NONE, IDC_CHECK_FARTHER_MOTHER_NONE,
			IDC_LABEL_FARTHER_NAME, IDC_LABEL_FARTHER_MASTER, IDC_LABEL_FARTHER_RACE, IDC_LABEL_FARTHER_FARTHER_RACE, IDC_LABEL_FARTHER_MOTHER_RACE,
			IDC_EDIT_FARTHER_NAME, IDC_EDIT_FARTHER_MASTER, IDC_BUTTON_FARTHER_MASTER_ME, IDC_BUTTON_FARTHER_MASTER_UNKNOWN,
		},
		{
			IDC_CHECK_MOTHER_NONE, IDC_CHECK_MOTHER_FARTHER_NONE, IDC_CHECK_MOTHER_MOTHER_NONE,
			IDC_LABEL_MOTHER_NAME, IDC_LABEL_MOTHER_MASTER, IDC_LABEL_MOTHER_RACE, IDC_LABEL_MOTHER_FARTHER_RACE, IDC_LABEL_MOTHER_MOTHER_RACE,
			IDC_EDIT_MOTHER_NAME, IDC_EDIT_MOTHER_MASTER, IDC_BUTTON_MOTHER_MASTER_ME, IDC_BUTTON_MOTHER_MASTER_UNKNOWN,
		},
	};

	m_nCombine = monster.combine;
	m_nLevel = monster.level;
	m_nMaxLevel = monster.max_level;
	m_nBaseHp = monster.base_hp;
	m_nBaseMp = monster.base_mp;
	m_nBaseAtk = monster.base_atk;
	m_nBaseDef = monster.base_def;
	m_nBaseInt = monster.base_agi;
	m_nCurHp = monster.current_hp;
	m_nCurMp = monster.current_mp;
	m_nMaxHp = monster.actual_hp;
	m_nMaxMp = monster.actual_mp;
	m_nAtk = monster.actual_atk;
	m_nDef = monster.actual_def;
	m_nAgi = monster.actual_agi;
	m_nInt = monster.actual_int;
	m_nExp = monster.exp;
	m_nSkillPoint = monster.remaining_sp;

	m_strName = CDqmjSEApp::GetNameString(monster.name);
	m_strMaster = CDqmjSEApp::GetNameString(monster.master);

	CheckDlgButton(IDC_CHECK_CHEAT, monster.cheat ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_DEAD, monster.dead ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_POISON, monster.poison ? BST_CHECKED : BST_UNCHECKED);

	SetDlgItemText(IDC_WEAPON_NAME, GetEquipmentNameString(monster.weapon));
	GetDlgItem(IDC_BUTTON_WEAPON_REMOVE)->EnableWindow(monster.weapon != 0x00);

	m_cmbRace.SetCurSel(GetSafeCBIndex(monster.race, m_raceToCBIndex, _countof(m_raceToCBIndex)));
	m_cmbSex.SetCurSel(GetSafeCBIndex(monster.sex, _countof(SEX_LIST)));
	m_cmbStrategy.SetCurSel(GetSafeCBIndex(monster.strategy, _countof(STRATEGY_LIST)));
	m_cmbSource.SetCurSel(GetSafeCBIndex(monster.source, _countof(SOURCE_LIST)));
	m_cmbMaxLevel.SetCurSel(CB_ERR);
	m_lstSkill.ResetContent();

	if (monster.rank == DQMJ_AUTO_RANK)
	{
		CheckDlgButton(IDC_CHECK_RANK_AUTO, BST_CHECKED);
		m_cmbRank.EnableWindow(FALSE);
		m_cmbRank.SetCurSel(CB_ERR);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_RANK_AUTO, BST_UNCHECKED);
		m_cmbRank.EnableWindow(TRUE);
		m_cmbRank.SetCurSel(GetSafeCBIndex(monster.rank, _countof(RANK_LIST)));
	}

	if (monster.type == DQMJ_AUTO_TYPE)
	{
		CheckDlgButton(IDC_CHECK_TYPE_AUTO, BST_CHECKED);
		m_cmbType.EnableWindow(FALSE);
		m_cmbType.SetCurSel(CB_ERR);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_TYPE_AUTO, BST_UNCHECKED);
		m_cmbType.EnableWindow(TRUE);
		m_cmbType.SetCurSel(GetSafeCBIndex(monster.type, _countof(TYPE_LIST)));
	}

	if (monster.growth_type == DQMJ_RAND_GROWTH_TYPE)
	{
		CheckDlgButton(IDC_CHECK_GROWTH_TYPE_RANDOM, BST_CHECKED);
		m_cmbGrowthType.EnableWindow(FALSE);
		m_cmbGrowthType.SetCurSel(CB_ERR);
	}
	else
	{
		CheckDlgButton(IDC_CHECK_GROWTH_TYPE_RANDOM, BST_UNCHECKED);
		m_cmbGrowthType.EnableWindow(TRUE);
		m_cmbGrowthType.SetCurSel(GetSafeCBIndex(monster.growth_type, _countof(GROWTH_LIST)));
	}

	if ((monster.growth_level[0] == DQMJ_RAND_GROWTH_LEVEL) || (monster.growth_level[1] == DQMJ_RAND_GROWTH_LEVEL))
	{
		m_nGrowthLevel[0] = 0;
		m_nGrowthLevel[1] = 0;
		CheckDlgButton(IDC_CHECK_GROWTH_LEVEL_RANDOM, BST_CHECKED);
		GetDlgItem(IDC_LABEL_GROWTH_LEVEL_RANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROWTH_LEVEL_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROWTH_LEVEL_END)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_GROWTH_LEVEL_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_GROWTH_LEVEL_END)->EnableWindow(FALSE);
	}
	else
	{
		m_nGrowthLevel[0] = monster.growth_level[0];
		m_nGrowthLevel[1] = monster.growth_level[1];
		CheckDlgButton(IDC_CHECK_GROWTH_LEVEL_RANDOM, BST_UNCHECKED);
		GetDlgItem(IDC_LABEL_GROWTH_LEVEL_RANGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_GROWTH_LEVEL_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_GROWTH_LEVEL_END)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_GROWTH_LEVEL_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_GROWTH_LEVEL_END)->EnableWindow(TRUE);
	}

	for (int i = 0; i < _countof(m_cmbGuard); i++)
		m_cmbGuard[i].SetCurSel(GetSafeCBIndex(monster.guard_info[i], _countof(GUARD_LIST)));

	for (int i = 0; i < _countof(MAXLEVEL_LIST); i++)
	{
		if (MAXLEVEL_LIST[i] == monster.max_level)
		{
			m_cmbMaxLevel.SetCurSel(i);
			break;
		}
	}

	for (int i = 0; i < _countof(m_cmbSkillset); i++)
	{
		m_nSkillsetPt[i] = monster.assigned_sp[i];

		if (monster.skillset[i] == 0x00)
		{
			CheckDlgButton(skillset_ctrl_id[i][0], BST_CHECKED);
			GetDlgItem(skillset_ctrl_id[i][1])->EnableWindow(FALSE);
			GetDlgItem(skillset_ctrl_id[i][2])->EnableWindow(FALSE);
			GetDlgItem(skillset_ctrl_id[i][3])->EnableWindow(FALSE);
			GetDlgItem(skillset_ctrl_id[i][4])->EnableWindow(FALSE);
			m_cmbSkillset[i].EnableWindow(FALSE);
			m_cmbSkillset[i].SetCurSel(CB_ERR);
		}
		else
		{
			CheckDlgButton(skillset_ctrl_id[i][0], BST_UNCHECKED);
			GetDlgItem(skillset_ctrl_id[i][1])->EnableWindow(TRUE);
			GetDlgItem(skillset_ctrl_id[i][2])->EnableWindow(TRUE);
			GetDlgItem(skillset_ctrl_id[i][3])->EnableWindow(TRUE);
			GetDlgItem(skillset_ctrl_id[i][4])->EnableWindow(TRUE);
			m_cmbSkillset[i].EnableWindow(TRUE);
			m_cmbSkillset[i].SetCurSel(GetSafeCBIndex(monster.skillset[i], m_skillsetToCBIndex, _countof(m_skillsetToCBIndex)));
		}
	}

	for (int i = 0; i < _countof(m_cmbAbility); i++)
	{
		if (monster.ability_list[i] == 0x00)
		{
			CheckDlgButton(ability_none_id[i], BST_CHECKED);
			m_cmbAbility[i].EnableWindow(FALSE);
			m_cmbAbility[i].SetCurSel(CB_ERR);
		}
		else
		{
			CheckDlgButton(ability_none_id[i], BST_UNCHECKED);
			m_cmbAbility[i].EnableWindow(TRUE);
			m_cmbAbility[i].SetCurSel(GetSafeCBIndex(monster.ability_list[i], m_abilityToCBIndex, _countof(m_abilityToCBIndex)));
		}
	}

	for (int i = 0; i < DQMJ_SKILL_MAX; i++)
	{
		LPCTSTR str = ::DQMJSaveGetSkillName(monster.skill_list[i]);
		if (str != NULL)
			VERIFY(m_lstSkill.SetItemData(m_lstSkill.AddString(str), monster.skill_list[i]) != LB_ERR);
	}

	SetDlgItemText(IDC_SKILL_NUM, GetSkillNumString(m_lstSkill.GetCount()));

	for (int i = 0; i < _countof(m_cmbParentsRace); i++)
	{
		if (monster.parents_race[i] == 0x00)
		{
			m_strParentsName[i] = _T("");
			m_strParentsMaster[i] = _T("");

			CheckDlgButton(parents_ctrl_id[i][0], BST_CHECKED);
			CheckDlgButton(parents_ctrl_id[i][1], BST_CHECKED);
			CheckDlgButton(parents_ctrl_id[i][2], BST_CHECKED);

			GetDlgItem(parents_ctrl_id[i][1])->EnableWindow(FALSE);
			GetDlgItem(parents_ctrl_id[i][2])->EnableWindow(FALSE);
			GetDlgItem(parents_ctrl_id[i][3])->EnableWindow(FALSE);
			GetDlgItem(parents_ctrl_id[i][4])->EnableWindow(FALSE);
			GetDlgItem(parents_ctrl_id[i][5])->EnableWindow(FALSE);
			GetDlgItem(parents_ctrl_id[i][6])->EnableWindow(FALSE);
			GetDlgItem(parents_ctrl_id[i][7])->EnableWindow(FALSE);
			GetDlgItem(parents_ctrl_id[i][8])->EnableWindow(FALSE);
			GetDlgItem(parents_ctrl_id[i][9])->EnableWindow(FALSE);
			GetDlgItem(parents_ctrl_id[i][10])->EnableWindow(FALSE);
			GetDlgItem(parents_ctrl_id[i][11])->EnableWindow(FALSE);

			m_cmbParentsRace[i].EnableWindow(FALSE);
			m_cmbParentsRace[i].SetCurSel(CB_ERR);
			m_cmbGrandparentsRace[i][0].EnableWindow(FALSE);
			m_cmbGrandparentsRace[i][0].SetCurSel(CB_ERR);
			m_cmbGrandparentsRace[i][1].EnableWindow(FALSE);
			m_cmbGrandparentsRace[i][1].SetCurSel(CB_ERR);
		}
		else
		{
			m_strParentsName[i] = CDqmjSEApp::GetNameString(monster.parents_name[i]);
			m_strParentsMaster[i] = CDqmjSEApp::GetNameString(monster.parents_master[i]);

			CheckDlgButton(parents_ctrl_id[i][0], BST_UNCHECKED);

			GetDlgItem(parents_ctrl_id[i][1])->EnableWindow(TRUE);
			GetDlgItem(parents_ctrl_id[i][2])->EnableWindow(TRUE);
			GetDlgItem(parents_ctrl_id[i][3])->EnableWindow(TRUE);
			GetDlgItem(parents_ctrl_id[i][4])->EnableWindow(TRUE);
			GetDlgItem(parents_ctrl_id[i][5])->EnableWindow(TRUE);
			GetDlgItem(parents_ctrl_id[i][6])->EnableWindow(TRUE);
			GetDlgItem(parents_ctrl_id[i][7])->EnableWindow(TRUE);
			GetDlgItem(parents_ctrl_id[i][8])->EnableWindow(TRUE);
			GetDlgItem(parents_ctrl_id[i][9])->EnableWindow(TRUE);
			GetDlgItem(parents_ctrl_id[i][10])->EnableWindow(TRUE);
			GetDlgItem(parents_ctrl_id[i][11])->EnableWindow(TRUE);

			m_cmbParentsRace[i].EnableWindow(TRUE);
			m_cmbParentsRace[i].SetCurSel(GetSafeCBIndex(monster.parents_race[i], m_raceToCBIndex, _countof(m_raceToCBIndex)));

			if (monster.grandparents_race[i][0] == 0x00)
			{
				CheckDlgButton(parents_ctrl_id[i][1], BST_CHECKED);
				m_cmbGrandparentsRace[i][0].EnableWindow(FALSE);
				m_cmbGrandparentsRace[i][0].SetCurSel(CB_ERR);
			}
			else
			{
				CheckDlgButton(parents_ctrl_id[i][1], BST_UNCHECKED);
				m_cmbGrandparentsRace[i][0].EnableWindow(TRUE);
				m_cmbGrandparentsRace[i][0].SetCurSel(GetSafeCBIndex(monster.grandparents_race[i][0], m_raceToCBIndex, _countof(m_raceToCBIndex)));
			}

			if (monster.grandparents_race[i][1] == 0x00)
			{
				CheckDlgButton(parents_ctrl_id[i][2], BST_CHECKED);
				m_cmbGrandparentsRace[i][1].EnableWindow(FALSE);
				m_cmbGrandparentsRace[i][1].SetCurSel(CB_ERR);
			}
			else
			{
				CheckDlgButton(parents_ctrl_id[i][2], BST_UNCHECKED);
				m_cmbGrandparentsRace[i][1].EnableWindow(TRUE);
				m_cmbGrandparentsRace[i][1].SetCurSel(GetSafeCBIndex(monster.grandparents_race[i][1], m_raceToCBIndex, _countof(m_raceToCBIndex)));
			}
		}
	}

	UpdateData(FALSE);
}

void CMonsterListDlg::EnableAll(BOOL enable)
{
	if (!enable)
	{
		m_nLevel = 0;
		m_nCombine = 0;
		m_nBaseHp = 0;
		m_nBaseMp = 0;
		m_nBaseAtk = 0;
		m_nBaseDef = 0;
		m_nBaseAgi = 0;
		m_nBaseInt = 0;
		m_nAtk = 0;
		m_nDef = 0;
		m_nAgi = 0;
		m_nInt = 0;
		m_nCurHp = 0;
		m_nCurMp = 0;
		m_nMaxLevel = 0;
		m_nMaxHp = 0;
		m_nMaxMp = 0;
		m_nExp = 0;
		m_nSkillPoint = 0;
		m_strName = _T("");
		m_strMaster = _T("");
		m_strParentsName[0] = _T("");
		m_strParentsName[1] = _T("");
		m_strParentsMaster[0] = _T("");
		m_strParentsMaster[1] = _T("");

		::ZeroMemory(m_nGrowthLevel, sizeof(m_nGrowthLevel));
		::ZeroMemory(m_nSkillsetPt, sizeof(m_nSkillsetPt));

		UpdateData(FALSE);

		SetDlgItemText(IDC_WEAPON_NAME, GetEquipmentNameString(0x00));
		SetDlgItemText(IDC_SKILL_NUM, _T("--/--"));

		CheckDlgButton(IDC_CHECK_NORMALIZE, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_RANK_AUTO, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_TYPE_AUTO, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_CHEAT, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_DEAD, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_POISON, BST_UNCHECKED);
		CheckDlgButton(IDC_CHECK_GROWTH_TYPE_RANDOM, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_GROWTH_LEVEL_RANDOM, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_SKILLSET_NONE1, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_SKILLSET_NONE2, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_SKILLSET_NONE3, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_ABILITY_NONE1, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_ABILITY_NONE2, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_ABILITY_NONE3, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_ABILITY_NONE4, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_ABILITY_NONE5, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_ABILITY_NONE6, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_FARTHER_NONE, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_FARTHER_FARTHER_NONE, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_FARTHER_MOTHER_NONE, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_MOTHER_NONE, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_MOTHER_FARTHER_NONE, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_MOTHER_MOTHER_NONE, BST_CHECKED);

		m_lstSkill.ResetContent();

		m_cmbSex.SetCurSel(CB_ERR);
		m_cmbRace.SetCurSel(CB_ERR);
		m_cmbRank.SetCurSel(CB_ERR);
		m_cmbType.SetCurSel(CB_ERR);
		m_cmbStrategy.SetCurSel(CB_ERR);
		m_cmbSource.SetCurSel(CB_ERR);
		m_cmbMaxLevel.SetCurSel(CB_ERR);
		m_cmbGrowthType.SetCurSel(CB_ERR);
		m_cmbParentsRace[0].SetCurSel(CB_ERR);
		m_cmbParentsRace[1].SetCurSel(CB_ERR);
		m_cmbGrandparentsRace[0][0].SetCurSel(CB_ERR);
		m_cmbGrandparentsRace[0][1].SetCurSel(CB_ERR);
		m_cmbGrandparentsRace[1][0].SetCurSel(CB_ERR);
		m_cmbGrandparentsRace[1][1].SetCurSel(CB_ERR);

		for (int i = 0; i < _countof(m_cmbSkillset); i++)
			m_cmbSkillset[i].SetCurSel(CB_ERR);
		for (int i = 0; i < _countof(m_cmbAbility); i++)
			m_cmbAbility[i].SetCurSel(CB_ERR);
		for (int i = 0; i < _countof(m_cmbGuard); i++)
			m_cmbGuard[i].SetCurSel(CB_ERR);

		m_cmbRank.EnableWindow(FALSE);
		m_cmbType.EnableWindow(FALSE);
		m_cmbGrowthType.EnableWindow(FALSE);
		m_cmbParentsRace[0].EnableWindow(FALSE);
		m_cmbParentsRace[1].EnableWindow(FALSE);
		m_cmbGrandparentsRace[0][0].EnableWindow(FALSE);
		m_cmbGrandparentsRace[0][1].EnableWindow(FALSE);
		m_cmbGrandparentsRace[1][0].EnableWindow(FALSE);
		m_cmbGrandparentsRace[1][1].EnableWindow(FALSE);

		for (int i = 0; i < _countof(m_cmbSkillset); i++)
			m_cmbSkillset[i].EnableWindow(FALSE);
		for (int i = 0; i < _countof(m_cmbAbility); i++)
			m_cmbAbility[i].EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_WEAPON_REMOVE)->EnableWindow(FALSE);

		GetDlgItem(IDC_LABEL_GROWTH_LEVEL_RANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROWTH_LEVEL_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROWTH_LEVEL_END)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_GROWTH_LEVEL_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_GROWTH_LEVEL_END)->EnableWindow(FALSE);

		GetDlgItem(IDC_LABEL_SKILLSET_PT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_LABEL_SKILLSET_PT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_LABEL_SKILLSET_PT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SKILLSET_PT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SKILLSET_PT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SKILLSET_PT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_SKILLSET_PT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_SKILLSET_PT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_SKILLSET_PT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILLSET_MAX1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILLSET_MAX2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILLSET_MAX3)->EnableWindow(FALSE);


		GetDlgItem(IDC_BUTTON_SKILL_UP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_TOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_DOWN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_BOTTOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_REMOVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_SORT)->EnableWindow(FALSE);

		GetDlgItem(IDC_LABEL_FARTHER_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_LABEL_FARTHER_MASTER)->EnableWindow(FALSE);
		GetDlgItem(IDC_LABEL_FARTHER_RACE)->EnableWindow(FALSE);
		GetDlgItem(IDC_LABEL_FARTHER_FARTHER_RACE)->EnableWindow(FALSE);
		GetDlgItem(IDC_LABEL_FARTHER_MOTHER_RACE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FARTHER_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FARTHER_MASTER)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_FARTHER_MASTER_ME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_FARTHER_MASTER_UNKNOWN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FARTHER_FARTHER_NONE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_FARTHER_MOTHER_NONE)->EnableWindow(FALSE);

		GetDlgItem(IDC_LABEL_MOTHER_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_LABEL_MOTHER_MASTER)->EnableWindow(FALSE);
		GetDlgItem(IDC_LABEL_MOTHER_RACE)->EnableWindow(FALSE);
		GetDlgItem(IDC_LABEL_MOTHER_FARTHER_RACE)->EnableWindow(FALSE);
		GetDlgItem(IDC_LABEL_MOTHER_MOTHER_RACE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MOTHER_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MOTHER_MASTER)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_MOTHER_MASTER_ME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_MOTHER_MASTER_UNKNOWN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_MOTHER_FARTHER_NONE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_MOTHER_MOTHER_NONE)->EnableWindow(FALSE);
	}

	m_cmbSex.EnableWindow(enable);
	m_cmbRace.EnableWindow(enable);
	m_cmbStrategy.EnableWindow(enable);
	m_cmbSource.EnableWindow(enable);
	m_cmbMaxLevel.EnableWindow(enable);

	for (int i = 0; i < _countof(m_cmbGuard); i++)
		m_cmbGuard[i].EnableWindow(enable);

	GetDlgItem(IDC_CHECK_NORMALIZE)->EnableWindow(enable);
	GetDlgItem(IDC_GROUP_INFORMATION)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_BASIC)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_NAME)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_SEX)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_MASTER)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_RACE)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_RANK)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_TYPE)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_STRATEGY)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_SOURCE)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_NAME)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_MASTER)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_MASTER_ME)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_MASTER_UNKNOWN)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_RANK_AUTO)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_TYPE_AUTO)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_CHEAT)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_STATUS)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_LEVEL)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_COMBINE)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_BASE_HP)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_BASE_MP)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_BASE_ATK)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_BASE_DEF)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_BASE_AGI)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_BASE_INT)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_MAX_LEVEL)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_MAX_HP)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_MAX_MP)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_ATK)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_DEF)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_AGI)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_INT)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_CUR_HP)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_CUR_MP)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_SKILL_POINT)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_EXP)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_LEVEL)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_COMBINE)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_BASE_HP)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_BASE_MP)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_BASE_ATK)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_BASE_DEF)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_BASE_AGI)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_BASE_INT)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_MAX_LEVEL)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_MAX_HP)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_MAX_MP)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_ATK)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_DEF)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_AGI)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_INT)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_CUR_HP)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_CUR_MP)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_SKILL_POINT)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_EXP)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_LEVEL)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_COMBINE)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_BASE_HP)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_BASE_MP)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_BASE_ATK)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_BASE_DEF)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_BASE_AGI)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_BASE_INT)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_MAX_LEVEL)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_MAX_HP)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_MAX_MP)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_ATK)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_DEF)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_AGI)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_INT)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_CUR_HP)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_CUR_MP)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_SKILL_POINT)->EnableWindow(enable);
	GetDlgItem(IDC_SPIN_EXP)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_STATUS_MAX)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_STATUS_MAX_FORCE)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_DEAD)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_POISON)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_WEAPON)->EnableWindow(enable);
	GetDlgItem(IDC_WEAPON_NAME)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_WEAPON_MODIFY)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_GROWTH)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_GROWTH_TYPE)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_GROWTH_LEVEL)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_GROWTH_TYPE_RANDOM)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_GROWTH_LEVEL_RANDOM)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_SKILLSET)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_SKILLSET_NONE1)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_SKILLSET_NONE2)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_SKILLSET_NONE3)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_ABILITY)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_ABILITY_NONE1)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_ABILITY_NONE2)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_ABILITY_NONE3)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_ABILITY_NONE4)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_ABILITY_NONE5)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_ABILITY_NONE6)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_SKILL)->EnableWindow(enable);
	GetDlgItem(IDC_LABEL_SKILL_NUM)->EnableWindow(enable);
	GetDlgItem(IDC_SKILL_NUM)->EnableWindow(enable);
	GetDlgItem(IDC_LIST_SKILL_LIST)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_GUARD)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME1)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME2)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME3)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME4)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME5)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME6)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME7)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME8)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME9)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME10)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME11)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME12)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME13)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME14)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME15)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME16)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME17)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME18)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME19)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME20)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME21)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME22)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME23)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME24)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME25)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME26)->EnableWindow(enable);
	GetDlgItem(IDC_GUARD_NAME27)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_FARTHER)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_FARTHER_NONE)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_MOTHER)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_MOTHER_NONE)->EnableWindow(enable);
}

void CMonsterListDlg::NormalizeUpdated()
{
	BOOL normalize = IsDlgButtonChecked(IDC_CHECK_NORMALIZE);
	if (!normalize)
	{
		m_cmbMaxLevel.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MAX_LEVEL)->ShowWindow(SW_SHOWNOACTIVATE);
		GetDlgItem(IDC_SPIN_MAX_LEVEL)->ShowWindow(SW_SHOWNOACTIVATE);
		return;
	}

	m_cmbMaxLevel.ShowWindow(SW_SHOWNOACTIVATE);
	GetDlgItem(IDC_EDIT_MAX_LEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_SPIN_MAX_LEVEL)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_CHECK_CHEAT)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_RANK_AUTO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_TYPE_AUTO)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MAX_HP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MAX_MP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ATK)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DEF)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_AGI)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_INT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_MAX_HP)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_MAX_MP)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_ATK)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_DEF)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_AGI)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_INT)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_POISON)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STATUS_MAX_FORCE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_ABILITY_NONE1)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_ABILITY_NONE2)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_ABILITY_NONE3)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_ABILITY_NONE4)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_ABILITY_NONE5)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_ABILITY_NONE6)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST_SKILL_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SKILL_UP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SKILL_TOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SKILL_DOWN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SKILL_BOTTOM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SKILL_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SKILL_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SKILL_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SKILL_SORT)->EnableWindow(FALSE);

	m_cmbRank.EnableWindow(FALSE);
	m_cmbType.EnableWindow(FALSE);

	if (!m_bInterrupt)
		GetDlgItem(IDC_CHECK_DEAD)->EnableWindow(FALSE);

	for (int i = 0; i < _countof(m_cmbAbility); i++)
		m_cmbAbility[i].EnableWindow(FALSE);
	for (int i = 0; i < _countof(m_cmbGuard); i++)
		m_cmbGuard[i].EnableWindow(FALSE);
}

//////////////////////////////////////////////////////////////////////////

void CMonsterListDlg::InitCBIndex()
{
	static BOOL flag = FALSE;
	if (flag)
		return;

	for (int i = 0; i < _countof(m_raceToCBIndex); i++)
		m_raceToCBIndex[i] = CB_ERR;
	for (int i = 0; i < _countof(m_skillsetToCBIndex); i++)
		m_skillsetToCBIndex[i] = CB_ERR;
	for (int i = 0; i < _countof(m_abilityToCBIndex); i++)
		m_abilityToCBIndex[i] = CB_ERR;

	CList<DQMJ_SAVE_RACE_SETTING> list[DQMJ_TYPE_NUM];

	for (int i = 0; i < DQMJ_MONSTERLIST_LEN; i++)
	{
		DQMJ_SAVE_RACE_SETTING rs;
		if (::DQMJSaveGetRaceSetting(i, &rs))
			list[rs.type].AddTail(rs);
	}

	for (int i = 0; i < DQMJ_TYPE_NUM; i++)
	{
		POSITION pos = list[i].GetHeadPosition();
		while (pos != NULL)
		{
			const DQMJ_SAVE_RACE_SETTING &rs = list[i].GetNext(pos);
			IDStrPair pair = { rs.race, rs.name };
			m_raceToCBIndex[pair.id] = m_raceIDStrList.GetCount();
			m_raceIDStrList.AddTail(pair);
		}
	}

	for (int i = 0; i < DQMJ_SKILLSETLIST_LEN; i++)
	{
		LPCTSTR str = ::DQMJSaveGetSkillsetName(i);
		if (str != NULL)
		{
			IDStrPair pair = { i, str };
			m_skillsetToCBIndex[pair.id] = m_skillsetIDStrList.GetCount();
			m_skillsetIDStrList.AddTail(pair);
		}
	}

	for (int i = 0; i < DQMJ_ABILITYLIST_LEN; i++)
	{
		LPCTSTR str = ::DQMJSaveGetAbilityName(i);
		if (str != NULL)
		{
			IDStrPair pair = { i, str };
			m_abilityToCBIndex[pair.id] = m_abilityIDStrList.GetCount();
			m_abilityIDStrList.AddTail(pair);
		}
	}

	flag = TRUE;
}

int CMonsterListDlg::GetSafeCBIndex(int idx, int len)
{
	return ((idx >= 0) && (idx < len)) ? idx : CB_ERR;
}

int CMonsterListDlg::GetSafeCBIndex(int idx, const int *list, int len)
{
	return ((idx >= 0) && (idx < len)) ? list[idx] : CB_ERR;
}

LPCTSTR CMonsterListDlg::GetSafeCBString(int idx, const LPCTSTR *list, int len)
{
	return ((idx > 0) && (idx < len)) ? list[idx] : _T("不明");
}

void CMonsterListDlg::InitComboBox(CComboBox &combo, const CList<IDStrPair> &list)
{
	POSITION pos = list.GetHeadPosition();
	while (pos != NULL)
	{
		const IDStrPair &pair = list.GetNext(pos);
		VERIFY(combo.SetItemData(combo.AddString(pair.str), pair.id) != CB_ERR);
	}
}

LPCTSTR CMonsterListDlg::GetRaceString(int race)
{
	DQMJ_SAVE_RACE_SETTING rs;
	if (::DQMJSaveGetRaceSetting(race, &rs))
		return rs.name;

	return _T("不明");
}

LPCTSTR CMonsterListDlg::GetEquipmentNameString(int equipment)
{
	if (equipment == 0x00)
		return _T("なし");

	DQMJ_SAVE_ITEM_SETTING is;
	if (::DQMJSaveGetItemSetting(equipment, &is))
		return is.name;

	return _T("不明");
}

CString CMonsterListDlg::GetMonsterNumString(int num)
{
	CString str;
	str.Format(_T("%d/%d"), num, DQMJ_MONSTER_MAX);

	return str;
}

CString CMonsterListDlg::GetSkillNumString(int num)
{
	CString str;
	str.Format(_T("%d/%d"), num, DQMJ_SKILL_MAX);

	return str;
}

BOOL CMonsterListDlg::IsInPartyOrStandby(int monster_idx)
{
	DQMJ_SAVE_RANCH_INFO ranchinfo;
	VERIFY(::DQMJSaveQueryRanchInfo(CDqmjSEApp::GetSaveHandle(), &ranchinfo));

	for (int i = 0; i < DQMJ_MEMBER_MAX; i++)
	{
		if (monster_idx == ranchinfo.party_member_idx[i])
			return TRUE;

		if (monster_idx == ranchinfo.standby_idx[i])
			return TRUE;
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
