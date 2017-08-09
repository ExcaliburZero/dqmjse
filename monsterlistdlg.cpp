
#include "stdafx.h"
#include "dqmjse.h"
#include "monsterlistdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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
	m_nSkillPoint = 0;
	m_uExp = 0;
	m_bInterrupt = 0;
	m_bSelectChanging = FALSE;
	m_strName = _T("");
	m_strMaster = _T("");
	m_strFartherName = _T("");
	m_strFartherMaster = _T("");
	m_strMotherName = _T("");
	m_strMotherMaster = _T("");
	
	::ZeroMemory(m_nNormalizeFlags, sizeof(m_nNormalizeFlags));
	::ZeroMemory(m_nGrowthLevel, sizeof(m_nGrowthLevel));
	::ZeroMemory(m_nSkillsetPt, sizeof(m_nSkillsetPt));
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
	::DDX_Text(pDX, IDC_EDIT_SKILL_POINT, m_nSkillPoint);
	::DDX_Text(pDX, IDC_EDIT_GROWTH_LEVEL_START, m_nGrowthLevel[0]);
	::DDX_Text(pDX, IDC_EDIT_GROWTH_LEVEL_END, m_nGrowthLevel[1]);
	::DDX_Text(pDX, IDC_EDIT_SKILLSET_PT1, m_nSkillsetPt[0]);
	::DDX_Text(pDX, IDC_EDIT_SKILLSET_PT2, m_nSkillsetPt[1]);
	::DDX_Text(pDX, IDC_EDIT_SKILLSET_PT3, m_nSkillsetPt[2]);
	::DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	::DDX_Text(pDX, IDC_EDIT_MASTER, m_strMaster);
	::DDX_Text(pDX, IDC_EDIT_FARTHER_NAME, m_strFartherName);
	::DDX_Text(pDX, IDC_EDIT_FARTHER_MASTER, m_strFartherMaster);
	::DDX_Text(pDX, IDC_EDIT_MOTHER_NAME, m_strMotherName);
	::DDX_Text(pDX, IDC_EDIT_MOTHER_MASTER, m_strMotherMaster);

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
	::DDX_Control(pDX, IDC_COMBO_FARTHER_RACE, m_cmbFartherRace[0]);
	::DDX_Control(pDX, IDC_COMBO_FARTHER_FARTHER_RACE, m_cmbFartherRace[1]);
	::DDX_Control(pDX, IDC_COMBO_FARTHER_MOTHER_RACE, m_cmbFartherRace[2]);
	::DDX_Control(pDX, IDC_COMBO_MOTHER_RACE, m_cmbMotherRace[0]);
	::DDX_Control(pDX, IDC_COMBO_MOTHER_FARTHER_RACE, m_cmbMotherRace[1]);
	::DDX_Control(pDX, IDC_COMBO_MOTHER_MOTHER_RACE, m_cmbMotherRace[2]);

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

	m_bInterrupt = briefing.interrupt;

	DQMJ_SAVE_RANCH_INFO ranchinfo;
	VERIFY(::DQMJSaveQueryRanchInfo(CDqmjSEApp::GetSaveHandle(), &ranchinfo));

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

		DQMJ_SAVE_MONSTER_INFO monsterinfo;
		VERIFY(::DQMJSaveQueryMonsterInfo(CDqmjSEApp::GetSaveHandle(), i, &monsterinfo));

		CString no;
		no.Format(_T("%d"), i + 1);

		m_lstMonster.SetItemText(i, COLUMN_NO, no);
		m_lstMonster.SetItemText(i, COLUMN_NAME, CDqmjSEApp::GetNameString(monsterinfo.name));
		m_lstMonster.SetItemText(i, COLUMN_SEX, GetSexString(monsterinfo.sex));
		m_lstMonster.SetItemText(i, COLUMN_RACE, GetRaceString(monsterinfo.race));
		m_lstMonster.SetItemText(i, COLUMN_RANK, GetRankString(monsterinfo.rank));
		m_lstMonster.SetItemText(i, COLUMN_TYPE, GetTypeString(monsterinfo.type));
	}

	for (int i = 0; i < DQMJ_MEMBER_MAX; i++)
	{
		m_lstMonster.SetItemText(ranchinfo.party_member_idx[i], COLUMN_PLACE, _T("パーティー"));
		m_lstMonster.SetItemText(ranchinfo.standby_idx[i], COLUMN_PLACE, _T("スタンバイ"));
	}

	InitRaceComboBox(m_cmbRace);

	VERIFY(m_cmbSex.AddString(GetSexString(DQMJ_SEX_MALE)) == DQMJ_SEX_MALE);
	VERIFY(m_cmbSex.AddString(GetSexString(DQMJ_SEX_FEMALE)) == DQMJ_SEX_FEMALE);
	VERIFY(m_cmbSex.AddString(GetSexString(DQMJ_SEX_BISEXUAL)) == DQMJ_SEX_BISEXUAL);

	VERIFY(m_cmbRank.AddString(GetRankString(DQMJ_RANK_NONE)) == DQMJ_RANK_NONE);
	VERIFY(m_cmbRank.AddString(GetRankString(DQMJ_RANK_F)) == DQMJ_RANK_F);
	VERIFY(m_cmbRank.AddString(GetRankString(DQMJ_RANK_E)) == DQMJ_RANK_E);
	VERIFY(m_cmbRank.AddString(GetRankString(DQMJ_RANK_D)) == DQMJ_RANK_D);
	VERIFY(m_cmbRank.AddString(GetRankString(DQMJ_RANK_C)) == DQMJ_RANK_C);
	VERIFY(m_cmbRank.AddString(GetRankString(DQMJ_RANK_B)) == DQMJ_RANK_B);
	VERIFY(m_cmbRank.AddString(GetRankString(DQMJ_RANK_A)) == DQMJ_RANK_A);
	VERIFY(m_cmbRank.AddString(GetRankString(DQMJ_RANK_S)) == DQMJ_RANK_S);
	VERIFY(m_cmbRank.AddString(GetRankString(DQMJ_RANK_SS)) == DQMJ_RANK_SS);
	VERIFY(m_cmbRank.AddString(GetRankString(DQMJ_RANK_UNKNOWN)) == DQMJ_RANK_UNKNOWN);

	VERIFY(m_cmbType.AddString(GetTypeString(DQMJ_TYPE_NONE)) == DQMJ_TYPE_NONE);
	VERIFY(m_cmbType.AddString(GetTypeString(DQMJ_TYPE_SLIME)) == DQMJ_TYPE_SLIME);
	VERIFY(m_cmbType.AddString(GetTypeString(DQMJ_TYPE_DRAGON)) == DQMJ_TYPE_DRAGON);
	VERIFY(m_cmbType.AddString(GetTypeString(DQMJ_TYPE_NATURE)) == DQMJ_TYPE_NATURE);
	VERIFY(m_cmbType.AddString(GetTypeString(DQMJ_TYPE_BEAST)) == DQMJ_TYPE_BEAST);
	VERIFY(m_cmbType.AddString(GetTypeString(DQMJ_TYPE_MATERIAL)) == DQMJ_TYPE_MATERIAL);
	VERIFY(m_cmbType.AddString(GetTypeString(DQMJ_TYPE_DEMON)) == DQMJ_TYPE_DEMON);
	VERIFY(m_cmbType.AddString(GetTypeString(DQMJ_TYPE_ZOMBIE)) == DQMJ_TYPE_ZOMBIE);
	VERIFY(m_cmbType.AddString(GetTypeString(DQMJ_TYPE_INCARNI)) == DQMJ_TYPE_INCARNI);

	VERIFY(m_cmbStrategy.AddString(_T("ガンガンいこうぜ")) == DQMJ_STRATEGY_GO_ALL_OUT);
	VERIFY(m_cmbStrategy.AddString(_T("いろいろやろうぜ")) == DQMJ_STRATEGY_TRY_OUT);
	VERIFY(m_cmbStrategy.AddString(_T("いのちだいじに")) == DQMJ_STRATEGY_TAKE_CARE_LIFE);
	VERIFY(m_cmbStrategy.AddString(_T("とくぎつかうな")) == DQMJ_STRATEGY_NO_SKILL);

	VERIFY(m_cmbSource.AddString(_T("システム")) == DQMJ_SOURCE_SYSTEM);
	VERIFY(m_cmbSource.AddString(_T("ワイヤレス交換(?)")) == DQMJ_SOURCE_EXCHANGE);
	VERIFY(m_cmbSource.AddString(_T("他国マスタースカウト")) == DQMJ_SOURCE_MASTER_SCOUT);
	VERIFY(m_cmbSource.AddString(_T("野良モンスタースカウト")) == DQMJ_SOURCE_FEILD_SCOUT);
	VERIFY(m_cmbSource.AddString(_T("配合")) == DQMJ_SOURCE_COMBINE);
	VERIFY(m_cmbSource.AddString(_T("ゲスト")) == DQMJ_SOURCE_GUEST);

	VERIFY(m_cmbMaxLevel.SetItemData(m_cmbMaxLevel.AddString(_T("50")), 50));
	VERIFY(m_cmbMaxLevel.SetItemData(m_cmbMaxLevel.AddString(_T("75")), 75));
	VERIFY(m_cmbMaxLevel.SetItemData(m_cmbMaxLevel.AddString(_T("99")), 99));

	VERIFY(m_cmbGrowthType.AddString(_T("ＨＰ")) == DQMJ_GROWTH_HP);
	VERIFY(m_cmbGrowthType.AddString(_T("ＭＰ")) == DQMJ_GROWTH_MP);
	VERIFY(m_cmbGrowthType.AddString(_T("こうげき力")) == DQMJ_GROWTH_ATK);
	VERIFY(m_cmbGrowthType.AddString(_T("しゅび力")) == DQMJ_GROWTH_DEF);
	VERIFY(m_cmbGrowthType.AddString(_T("すばやさ")) == DQMJ_GROWTH_AGI);
	VERIFY(m_cmbGrowthType.AddString(_T("かしこさ")) == DQMJ_GROWTH_INT);

	for (int i = 0; i < _countof(m_cmbGuard); i++)
	{
		SetDlgItemText(guard_name_id[i], ::DQMJSaveGetGuardName(i));
		VERIFY(m_cmbGuard[i].AddString(_T("弱い")) == DQMJ_GUARD_WEAK);
		VERIFY(m_cmbGuard[i].AddString(_T("ふつう")) == DQMJ_GUARD_NORMAL);
		VERIFY(m_cmbGuard[i].AddString(_T("軽減")) == DQMJ_GUARD_STRONG);
		VERIFY(m_cmbGuard[i].AddString(_T("半減")) == DQMJ_GUARD_HALF);
		VERIFY(m_cmbGuard[i].AddString(_T("激減")) == DQMJ_GUARD_VERY_STRONG);
		VERIFY(m_cmbGuard[i].AddString(_T("無効")) == DQMJ_GUARD_INVALID);
		VERIFY(m_cmbGuard[i].AddString(_T("反射")) == DQMJ_GUARD_REFLECT);
		VERIFY(m_cmbGuard[i].AddString(_T("吸収")) == DQMJ_GUARD_ABSORB);
	}

	for (int i = 0; i < _countof(m_cmbSkillset); i++)
		InitSkillsetComboBox(m_cmbSkillset[i]);

	for (int i = 0; i < _countof(m_cmbAbility); i++)
		InitAbilityComboBox(m_cmbAbility[i]);

	for (int i = 0; i < _countof(m_cmbFartherRace); i++)
		InitRaceComboBox(m_cmbFartherRace[i]);

	for (int i = 0; i < _countof(m_cmbMotherRace); i++)
		InitRaceComboBox(m_cmbMotherRace[i]);

	((CEdit *)GetDlgItem(IDC_EDIT_NAME))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_NAME_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_MASTER))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_NAME_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_FARTHER_NAME))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_NAME_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_FARTHER_MASTER))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_NAME_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_MOTHER_NAME))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_NAME_MAX));
	((CEdit *)GetDlgItem(IDC_EDIT_MOTHER_MASTER))->SetLimitText(CDqmjSEApp::CalcDigit(DQMJ_NAME_MAX));
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
	NormalizeUpdated(FALSE);

	return TRUE;
}

void CMonsterListDlg::OnBnClickedCheckNormalize()
{
	if (m_lstMonster.GetSelectedCount() <= 0)
		return;

	int cur_sel = m_lstMonster.GetSelectionMark();
	if (cur_sel <= 0)
		return;

	m_nNormalizeFlags[cur_sel] = IsDlgButtonChecked(IDC_CHECK_NORMALIZE) == BST_CHECKED;
	NormalizeUpdated(TRUE);
	// TODO: Add your control notification handler code here
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
		NormalizeUpdated(FALSE);
		return;
	}

	EnableAll(TRUE);
	CheckDlgButton(IDC_CHECK_NORMALIZE, m_nNormalizeFlags[cur_sel] ? BST_CHECKED : BST_UNCHECKED);
	NormalizeUpdated(TRUE);
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
		m_nSkillPoint = 0;
		m_uExp = 0;
		m_strName = _T("");
		m_strMaster = _T("");
		m_strFartherName = _T("");
		m_strFartherMaster = _T("");
		m_strMotherName = _T("");
		m_strMotherMaster = _T("");

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

		for (int i = 0; i < _countof(m_cmbSkillset); i++)
			m_cmbSkillset[i].SetCurSel(CB_ERR);
		for (int i = 0; i < _countof(m_cmbAbility); i++)
			m_cmbAbility[i].SetCurSel(CB_ERR);
		for (int i = 0; i < _countof(m_cmbGuard); i++)
			m_cmbGuard[i].SetCurSel(CB_ERR);
		for (int i = 0; i < _countof(m_cmbFartherRace); i++)
			m_cmbFartherRace[i].SetCurSel(CB_ERR);
		for (int i = 0; i < _countof(m_cmbMotherRace); i++)
			m_cmbMotherRace[i].SetCurSel(CB_ERR);

		GetDlgItem(IDC_COMBO_RANK)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_TYPE)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_WEAPON_REMOVE)->EnableWindow(FALSE);

		GetDlgItem(IDC_LABEL_GROWTH_LEVEL_RANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROWTH_LEVEL_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROWTH_LEVEL_END)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_GROWTH_LEVEL_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_GROWTH_LEVEL_END)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_GROWTH_TYPE)->EnableWindow(FALSE);

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
		GetDlgItem(IDC_COMBO_SKILLSET1)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_SKILLSET2)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_SKILLSET3)->EnableWindow(FALSE);

		GetDlgItem(IDC_COMBO_ABILITY1)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_ABILITY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_ABILITY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_ABILITY4)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_ABILITY5)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_ABILITY6)->EnableWindow(FALSE);

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
		GetDlgItem(IDC_COMBO_FARTHER_RACE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_FARTHER_FARTHER_RACE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_FARTHER_MOTHER_RACE)->EnableWindow(FALSE);

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
		GetDlgItem(IDC_COMBO_MOTHER_RACE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MOTHER_FARTHER_RACE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MOTHER_MOTHER_RACE)->EnableWindow(FALSE);
	}

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
	GetDlgItem(IDC_COMBO_SEX)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_RACE)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_STRATEGY)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_SOURCE)->EnableWindow(enable);

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
	GetDlgItem(IDC_COMBO_MAX_LEVEL)->EnableWindow(enable);

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
	GetDlgItem(IDC_COMBO_GUARD_LEVEL1)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL2)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL3)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL4)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL5)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL6)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL7)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL8)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL9)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL10)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL11)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL12)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL13)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL14)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL15)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL16)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL17)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL18)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL19)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL20)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL21)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL22)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL23)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL24)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL25)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL26)->EnableWindow(enable);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL27)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_FARTHER)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_FARTHER_NONE)->EnableWindow(enable);

	GetDlgItem(IDC_GROUP_MOTHER)->EnableWindow(enable);
	GetDlgItem(IDC_CHECK_MOTHER_NONE)->EnableWindow(enable);
}

void CMonsterListDlg::NormalizeUpdated(BOOL enable)
{
	BOOL normalize = IsDlgButtonChecked(IDC_CHECK_NORMALIZE);

	GetDlgItem(IDC_COMBO_MAX_LEVEL)->ShowWindow(normalize ? SW_SHOWNOACTIVATE : SW_HIDE);
	GetDlgItem(IDC_EDIT_MAX_LEVEL)->ShowWindow(normalize ? SW_HIDE : SW_SHOWNOACTIVATE);
	GetDlgItem(IDC_SPIN_MAX_LEVEL)->ShowWindow(normalize ? SW_HIDE : SW_SHOWNOACTIVATE);
	GetDlgItem(IDC_CHECK_RANK_AUTO)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_CHECK_TYPE_AUTO)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_EDIT_MAX_HP)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_EDIT_MAX_MP)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_EDIT_ATK)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_EDIT_DEF)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_EDIT_AGI)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_EDIT_INT)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_SPIN_MAX_HP)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_SPIN_MAX_MP)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_SPIN_ATK)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_SPIN_DEF)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_SPIN_AGI)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_SPIN_INT)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_CHECK_DEAD)->EnableWindow(enable && (!normalize || m_bInterrupt));
	GetDlgItem(IDC_CHECK_POISON)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_CHECK_ABILITY_NONE1)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_CHECK_ABILITY_NONE2)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_CHECK_ABILITY_NONE3)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_CHECK_ABILITY_NONE4)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_CHECK_ABILITY_NONE5)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_CHECK_ABILITY_NONE6)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_LIST_SKILL_LIST)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL1)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL2)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL3)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL4)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL5)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL6)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL7)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL8)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL9)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL10)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL11)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL12)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL13)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL14)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL15)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL16)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL17)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL18)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL19)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL20)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL21)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL22)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL23)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL24)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL25)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL26)->EnableWindow(enable && !normalize);
	GetDlgItem(IDC_COMBO_GUARD_LEVEL27)->EnableWindow(enable && !normalize);

	if (normalize)
	{
		CheckDlgButton(IDC_CHECK_RANK_AUTO, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_TYPE_AUTO, BST_CHECKED);
		CheckDlgButton(IDC_CHECK_POISON, BST_UNCHECKED);

		GetDlgItem(IDC_BUTTON_SKILL_UP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_TOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_DOWN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_BOTTOM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_REMOVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILL_SORT)->EnableWindow(FALSE);

		if (!m_bInterrupt)
			CheckDlgButton(IDC_CHECK_DEAD, BST_UNCHECKED);
	}

		

/*
	if (enable)
	{
		if (m_cmbType.GetItemData(m_cmbType.GetCurSel()) == DQMJ_TYPE_INCARNI)
		{
			m_cmbSex.SetCurSel(DQMJ_SEX_BISEXUAL);
			m_cmbSex.EnableWindow(FALSE);
		}
	}*/
}

//////////////////////////////////////////////////////////////////////////

void CMonsterListDlg::InitRaceComboBox(CComboBox &combo)
{
	static BOOL flag = FALSE;
	static CList<DQMJ_SAVE_RACE_SETTING> list[DQMJ_TYPE_NUM];

	if (!flag)
	{
		for (int i = 0; i < DQMJ_MONSTERLIST_LEN; i++)
		{
			DQMJ_SAVE_RACE_SETTING rs;
			if (::DQMJSaveGetRaceSetting(i, &rs))
				list[rs.type].AddTail(rs);
		}

		flag = TRUE;
	}

	for (int i = 0; i < DQMJ_TYPE_NUM; i++)
	{
		POSITION pos = list[i].GetHeadPosition();
		while (pos != NULL)
		{
			const DQMJ_SAVE_RACE_SETTING &rs = list[i].GetNext(pos);
			VERIFY(combo.SetItemData(combo.AddString(rs.name), rs.race) != CB_ERR);
		}
	}
}

void CMonsterListDlg::InitSkillsetComboBox(CComboBox &combo)
{
	for (int i = 0; i < DQMJ_SKILLSETLIST_LEN; i++)
	{
		LPCTSTR str = ::DQMJSaveGetSkillsetName(i);
		if (str != NULL)
			VERIFY(combo.SetItemData(combo.AddString(str), i) != CB_ERR);
	}
}

void CMonsterListDlg::InitAbilityComboBox(CComboBox &combo)
{
	for (int i = 0; i < DQMJ_ABILITYLIST_LEN; i++)
	{
		LPCTSTR str = ::DQMJSaveGetAbilityName(i);
		if (str != NULL)
			VERIFY(combo.SetItemData(combo.AddString(str), i) != CB_ERR);
	}
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

LPCTSTR CMonsterListDlg::GetSexString(int sex)
{
	switch (sex)
	{
	case DQMJ_SEX_MALE:
		return _T("♂");
	case DQMJ_SEX_FEMALE:
		return _T("♀");
	case DQMJ_SEX_BISEXUAL:
		return _T("両性具有");
	}

	return _T("不明");
}

LPCTSTR CMonsterListDlg::GetRaceString(int race)
{
	DQMJ_SAVE_RACE_SETTING rs;
	if (::DQMJSaveGetRaceSetting(race, &rs))
		return rs.name;

	return _T("不明");
}

LPCTSTR CMonsterListDlg::GetRankString(int rank)
{
	switch (rank)
	{
	case DQMJ_RANK_NONE:
		return _T("なし");
	case DQMJ_RANK_F:
		return _T("F");
	case DQMJ_RANK_E:
		return _T("E");
	case DQMJ_RANK_D:
		return _T("D");
	case DQMJ_RANK_C:
		return _T("C");
	case DQMJ_RANK_B:
		return _T("B");
	case DQMJ_RANK_A:
		return _T("A");
	case DQMJ_RANK_S:
		return _T("S");
	case DQMJ_RANK_SS:
		return _T("SS");
	case DQMJ_RANK_UNKNOWN:
		return _T("??");
	}

	return _T("不明");
}

LPCTSTR CMonsterListDlg::GetTypeString(int type)
{
	switch (type)
	{
	case DQMJ_TYPE_NONE:
		return _T("なし");
	case DQMJ_TYPE_SLIME:
		return _T("スライム系");
	case DQMJ_TYPE_DRAGON:
		return _T("ドラゴン系");
	case DQMJ_TYPE_NATURE:
		return _T("しぜん系");
	case DQMJ_TYPE_BEAST:
		return _T("まじゅう系");
	case DQMJ_TYPE_MATERIAL:
		return _T("ぶっしつ系");
	case DQMJ_TYPE_DEMON:
		return _T("あくま系");
	case DQMJ_TYPE_ZOMBIE:
		return _T("ゾンビ系");
	case DQMJ_TYPE_INCARNI:
		return _T("しんじゅう系");
	}

	return _T("不明");
}

LPCTSTR CMonsterListDlg::GetEquipmentNameString(int equipment)
{
	if (equipment == 0x00)
		return _T("装備なし");

	DQMJ_SAVE_ITEM_SETTING is;
	if (::DQMJSaveGetItemSetting(equipment, &is))
		return is.name;

	return _T("不明");
}

//////////////////////////////////////////////////////////////////////////
