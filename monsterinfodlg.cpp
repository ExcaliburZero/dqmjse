
#include "stdafx.h"
#include "dqmjse.h"
#include "monsterinfodlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

const int MAXLEVEL_LIST[]			= { 50, 75, 99 };
const LPCTSTR SEX_LIST[]			= { _T("♂"), _T("♀"), _T("両性具有") };
const LPCTSTR RANK_LIST[]			= { _T("なし"), _T("F"), _T("E"), _T("D"), _T("C"), _T("B"), _T("A"), _T("S"), _T("SS"), _T("??") };
const LPCTSTR TYPE_LIST[]			= { _T("なし"), _T("スライム系"), _T("ドラゴン系"), _T("しぜん系"), _T("まじゅう系"), _T("ぶっしつ系"), _T("あくま系"), _T("ゾンビ系"), _T("しんじゅう系") };
const LPCTSTR STRATEGY_LIST[]		= { _T("ガンガンいこうぜ"), _T("いろいろやろうぜ"), _T("いのちだいじに"), _T("とくぎつかうな") };
const LPCTSTR SOURCE_LIST[]			= { _T("システム"), _T("ワイヤレス交換(?)"), _T("他国マスタースカウト"), _T("野良モンスタースカウト"), _T("配合"), _T("ゲスト") };
const LPCTSTR GROWTH_LIST[]			= { _T("ＨＰ"), _T("ＭＰ"), _T("攻撃力"), _T("守備力"), _T("素早さ"), _T("賢さ") };
const LPCTSTR GUARD_LIST[]			= { _T("弱い"), _T("ふつう"), _T("軽減"), _T("半減"), _T("激減"), _T("無効"), _T("反射"), _T("吸収") };

const int IDC_CHECK_SKILLSET_NONE[]				= { IDC_CHECK_SKILLSET_NONE1, IDC_CHECK_SKILLSET_NONE2, IDC_CHECK_SKILLSET_NONE3 };
const int IDC_EDIT_SKILLSET_PT[]				= { IDC_EDIT_SKILLSET_PT1, IDC_EDIT_SKILLSET_PT2, IDC_EDIT_SKILLSET_PT3 };
const int IDC_SPIN_SKILLSET_PT[]				= { IDC_SPIN_SKILLSET_PT1, IDC_SPIN_SKILLSET_PT2, IDC_SPIN_SKILLSET_PT3 };
const int IDC_LABEL_SKILLSET_PT[]				= { IDC_LABEL_SKILLSET_PT1, IDC_LABEL_SKILLSET_PT2, IDC_LABEL_SKILLSET_PT3 };
const int IDC_BUTTON_SKILLSET_MAX[]				= { IDC_BUTTON_SKILLSET_MAX1, IDC_BUTTON_SKILLSET_MAX2, IDC_BUTTON_SKILLSET_MAX3 };
const int IDC_COMBO_SKILLSET[]					= { IDC_COMBO_SKILLSET1, IDC_COMBO_SKILLSET2, IDC_COMBO_SKILLSET3 };

const int IDC_CHECK_ABILITY_NONE[]				= { IDC_CHECK_ABILITY_NONE1, IDC_CHECK_ABILITY_NONE2, IDC_CHECK_ABILITY_NONE3, IDC_CHECK_ABILITY_NONE4, IDC_CHECK_ABILITY_NONE5, IDC_CHECK_ABILITY_NONE6 };
const int IDC_COMBO_ABILITY[]					= { IDC_COMBO_ABILITY1, IDC_COMBO_ABILITY2, IDC_COMBO_ABILITY3, IDC_COMBO_ABILITY4, IDC_COMBO_ABILITY5, IDC_COMBO_ABILITY6 };

const int IDC_GUARD_NAME[]						= { IDC_GUARD_NAME1, IDC_GUARD_NAME2, IDC_GUARD_NAME3, IDC_GUARD_NAME4, IDC_GUARD_NAME5, IDC_GUARD_NAME6, IDC_GUARD_NAME7, IDC_GUARD_NAME8, IDC_GUARD_NAME9, IDC_GUARD_NAME10, IDC_GUARD_NAME11, IDC_GUARD_NAME12, IDC_GUARD_NAME13, IDC_GUARD_NAME14, IDC_GUARD_NAME15, IDC_GUARD_NAME16, IDC_GUARD_NAME17, IDC_GUARD_NAME18, IDC_GUARD_NAME19, IDC_GUARD_NAME20, IDC_GUARD_NAME21, IDC_GUARD_NAME22, IDC_GUARD_NAME23, IDC_GUARD_NAME24, IDC_GUARD_NAME25, IDC_GUARD_NAME26, IDC_GUARD_NAME27 };
const int IDC_COMBO_GUARD_LEVEL[]				= { IDC_COMBO_GUARD_LEVEL1, IDC_COMBO_GUARD_LEVEL2, IDC_COMBO_GUARD_LEVEL3, IDC_COMBO_GUARD_LEVEL4, IDC_COMBO_GUARD_LEVEL5, IDC_COMBO_GUARD_LEVEL6, IDC_COMBO_GUARD_LEVEL7, IDC_COMBO_GUARD_LEVEL8, IDC_COMBO_GUARD_LEVEL9, IDC_COMBO_GUARD_LEVEL10, IDC_COMBO_GUARD_LEVEL11, IDC_COMBO_GUARD_LEVEL12, IDC_COMBO_GUARD_LEVEL13, IDC_COMBO_GUARD_LEVEL14, IDC_COMBO_GUARD_LEVEL15, IDC_COMBO_GUARD_LEVEL16, IDC_COMBO_GUARD_LEVEL17, IDC_COMBO_GUARD_LEVEL18, IDC_COMBO_GUARD_LEVEL19, IDC_COMBO_GUARD_LEVEL20, IDC_COMBO_GUARD_LEVEL21, IDC_COMBO_GUARD_LEVEL22, IDC_COMBO_GUARD_LEVEL23, IDC_COMBO_GUARD_LEVEL24, IDC_COMBO_GUARD_LEVEL25, IDC_COMBO_GUARD_LEVEL26, IDC_COMBO_GUARD_LEVEL27 };

const int IDC_EDIT_PARENT_NAME[]				= { IDC_EDIT_FATHER_NAME, IDC_EDIT_MOTHER_NAME };
const int IDC_EDIT_PARENT_MASTER[]				= { IDC_EDIT_FATHER_MASTER, IDC_EDIT_MOTHER_MASTER };
const int IDC_BUTTON_PARENT_MASTER_ME[]			= { IDC_BUTTON_FATHER_MASTER_ME, IDC_BUTTON_MOTHER_MASTER_ME };
const int IDC_BUTTON_PARENT_MASTER_UNKNOWN[]	= { IDC_BUTTON_FATHER_MASTER_UNKNOWN, IDC_BUTTON_MOTHER_MASTER_UNKNOWN };
const int IDC_CHECK_PARENT_NONE[]				= { IDC_CHECK_FATHER_NONE, IDC_CHECK_MOTHER_NONE };
const int IDC_CHECK_GRANDPARENT_NONE[][2]		= { { IDC_CHECK_FATHER_FATHER_NONE, IDC_CHECK_FATHER_MOTHER_NONE }, { IDC_CHECK_MOTHER_FATHER_NONE, IDC_CHECK_MOTHER_MOTHER_NONE } };

//////////////////////////////////////////////////////////////////////////

CMonsterInfoDlg::CIDStrList CMonsterInfoDlg::m_raceIDStrList;
CMonsterInfoDlg::CIDStrList CMonsterInfoDlg::m_skillsetIDStrList;
CMonsterInfoDlg::CIDStrList CMonsterInfoDlg::m_abilityIDStrList;
int CMonsterInfoDlg::m_raceToCBIndex[];
int CMonsterInfoDlg::m_skillsetToCBIndex[];
int CMonsterInfoDlg::m_abilityToCBIndex[];

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CMonsterInfoDlg, CDialog)

BEGIN_MESSAGE_MAP(CMonsterInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_NORMALIZE, OnBnClickedCheckNormalize)
	ON_BN_CLICKED(IDC_CHECK_RANK_AUTO, OnBnClickedCheckRankAuto)
	ON_BN_CLICKED(IDC_CHECK_TYPE_AUTO, OnBnClickedCheckTypeAuto)
	ON_BN_CLICKED(IDC_CHECK_DEAD, OnBnClickedCheckDead)
	ON_BN_CLICKED(IDC_CHECK_SKILLSET_NONE1, OnBnClickedCheckSkillsetNone1)
	ON_BN_CLICKED(IDC_CHECK_SKILLSET_NONE2, OnBnClickedCheckSkillsetNone2)
	ON_BN_CLICKED(IDC_CHECK_SKILLSET_NONE3, OnBnClickedCheckSkillsetNone3)
	ON_BN_CLICKED(IDC_CHECK_FATHER_NONE, OnBnClickedCheckFatherNone)
	ON_BN_CLICKED(IDC_CHECK_MOTHER_NONE, OnBnClickedCheckMotherNone)
	ON_BN_CLICKED(IDC_CHECK_FATHER_FATHER_NONE, OnBnClickedCheckFatherFatherNone)
	ON_BN_CLICKED(IDC_CHECK_FATHER_MOTHER_NONE, OnBnClickedCheckFatherMotherNone)
	ON_BN_CLICKED(IDC_CHECK_MOTHER_FATHER_NONE, OnBnClickedCheckMotherFatherNone)
	ON_BN_CLICKED(IDC_CHECK_MOTHER_MOTHER_NONE, OnBnClickedCheckMotherMotherNone)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_UP, OnBnClickedButtonMonsterUp)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_TOP, OnBnClickedButtonMonsterTop)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_DOWN, OnBnClickedButtonMonsterDown)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_BOTTOM, OnBnClickedButtonMonsterBottom)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_ADD, OnBnClickedButtonMonsterAdd)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_REMOVE, OnBnClickedButtonMonsterRemove)
	ON_BN_CLICKED(IDC_BUTTON_STATUS_MAX, OnBnClickedButtonStatusMax)
	ON_BN_CLICKED(IDC_BUTTON_STATUS_MAX_FORCE, OnBnClickedButtonStatusMaxForce)
	ON_BN_CLICKED(IDC_BUTTON_WEAPON_MODIFY, OnBnClickedButtonWeaponModify)
	ON_BN_CLICKED(IDC_BUTTON_WEAPON_REMOVE, OnBnClickedButtonWeaponRemove)
	ON_BN_CLICKED(IDC_BUTTON_GROWTH_RANDOM, OnBnClickedButtonGrowthRandom)
	ON_BN_CLICKED(IDC_BUTTON_SKILLSET_MAX1, OnBnClickedButtonSkillsetMax1)
	ON_BN_CLICKED(IDC_BUTTON_SKILLSET_MAX2, OnBnClickedButtonSkillsetMax2)
	ON_BN_CLICKED(IDC_BUTTON_SKILLSET_MAX3, OnBnClickedButtonSkillsetMax3)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_UP, OnBnClickedButtonSkillUp)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_TOP, OnBnClickedButtonSkillTop)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_DOWN, OnBnClickedButtonSkillDown)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_BOTTOM, OnBnClickedButtonSkillBottom)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_ADD, OnBnClickedButtonSkillAdd)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_MODIFY, OnBnClickedButtonSkillModify)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_REMOVE, OnBnClickedButtonSkillRemove)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_SORT, OnBnClickedButtonSkillSort)
	ON_BN_CLICKED(IDC_BUTTON_MASTER_ME, OnBnClickedButtonMasterMe)
	ON_BN_CLICKED(IDC_BUTTON_MASTER_UNKNOWN, OnBnClickedButtonMasterUnknown)
	ON_BN_CLICKED(IDC_BUTTON_FATHER_MASTER_ME, OnBnClickedButtonFatherMasterMe)
	ON_BN_CLICKED(IDC_BUTTON_FATHER_MASTER_UNKNOWN, OnBnClickedButtonFatherMasterUnknown)
	ON_BN_CLICKED(IDC_BUTTON_MOTHER_MASTER_ME, OnBnClickedButtonMotherMasterMe)
	ON_BN_CLICKED(IDC_BUTTON_MOTHER_MASTER_UNKNOWN, OnBnClickedButtonMotherMasterUnknown)
	ON_LBN_SELCHANGE(IDC_LIST_SKILL_LIST, OnLbnSelchangeListSkillList)
	ON_CBN_SELCHANGE(IDC_COMBO_RACE, OnCbnSelchangeComboRace)
	ON_CBN_SELCHANGE(IDC_COMBO_RANK, OnCbnSelchangeComboRank)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnCbnSelchangeComboType)
	ON_CBN_SELCHANGE(IDC_COMBO_MAX_LEVEL, OnCbnSelchangeComboMaxLevel)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

CMonsterInfoDlg::CMonsterInfoDlg(const DQMJ_SAVE_MONSTER_INFO &monsterinfo, CWnd *pParent) : CDialog(IDD_DQMJSE_MONSTER_INFO, pParent)
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
	m_strParentName[0] = _T("");
	m_strParentName[1] = _T("");
	m_strParentMaster[0] = _T("");
	m_strParentMaster[1] = _T("");
	m_bInterrupt = FALSE;
	m_masterName = _T("");
	m_monsterInfo = monsterinfo;
	m_backupInfo = monsterinfo;

	::ZeroMemory(m_nGrowthLevel, sizeof(m_nGrowthLevel));
	::ZeroMemory(m_nSkillsetPt, sizeof(m_nSkillsetPt));

	StaticInitialize();
}

const DQMJ_SAVE_MONSTER_INFO &CMonsterInfoDlg::GetMonsterInfo() const
{
	return m_monsterInfo;
}

//////////////////////////////////////////////////////////////////////////

void CMonsterInfoDlg::DoDataExchange(CDataExchange *pDX)
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
	::DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	::DDX_Text(pDX, IDC_EDIT_MASTER, m_strMaster);
	::DDX_Text(pDX, IDC_EDIT_FATHER_NAME, m_strParentName[0]);
	::DDX_Text(pDX, IDC_EDIT_FATHER_MASTER, m_strParentMaster[0]);
	::DDX_Text(pDX, IDC_EDIT_MOTHER_NAME, m_strParentName[1]);
	::DDX_Text(pDX, IDC_EDIT_MOTHER_MASTER, m_strParentMaster[1]);

	::DDX_Control(pDX, IDC_LIST_SKILL_LIST, m_lstSkill);
	::DDX_Control(pDX, IDC_COMBO_SEX, m_cmbSex);
	::DDX_Control(pDX, IDC_COMBO_RACE, m_cmbRace);
	::DDX_Control(pDX, IDC_COMBO_RANK, m_cmbRank);
	::DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbType);
	::DDX_Control(pDX, IDC_COMBO_STRATEGY, m_cmbStrategy);
	::DDX_Control(pDX, IDC_COMBO_SOURCE, m_cmbSource);
	::DDX_Control(pDX, IDC_COMBO_MAX_LEVEL, m_cmbMaxLevel);
	::DDX_Control(pDX, IDC_COMBO_GROWTH_TYPE, m_cmbGrowthType);

	::DDX_Control(pDX, IDC_COMBO_FATHER_RACE, m_cmbParentRace[0]);
	::DDX_Control(pDX, IDC_COMBO_FATHER_FATHER_RACE, m_cmbGrandparentRace[0][0]);
	::DDX_Control(pDX, IDC_COMBO_FATHER_MOTHER_RACE, m_cmbGrandparentRace[0][1]);
	::DDX_Control(pDX, IDC_COMBO_MOTHER_RACE, m_cmbParentRace[1]);
	::DDX_Control(pDX, IDC_COMBO_MOTHER_FATHER_RACE, m_cmbGrandparentRace[1][0]);
	::DDX_Control(pDX, IDC_COMBO_MOTHER_MOTHER_RACE, m_cmbGrandparentRace[1][1]);

	for (int i = 0; i < _countof(IDC_EDIT_SKILLSET_PT); i++)
		::DDX_Text(pDX, IDC_EDIT_SKILLSET_PT[i], m_nSkillsetPt[i]);
	for (int i = 0; i < _countof(IDC_COMBO_GUARD_LEVEL); i++)
		::DDX_Control(pDX, IDC_COMBO_GUARD_LEVEL[i], m_cmbGuard[i]);
	for (int i = 0; i < _countof(IDC_COMBO_SKILLSET); i++)
		::DDX_Control(pDX, IDC_COMBO_SKILLSET[i], m_cmbSkillset[i]);
	for (int i = 0; i < _countof(IDC_COMBO_ABILITY); i++)
		::DDX_Control(pDX, IDC_COMBO_ABILITY[i], m_cmbAbility[i]);

	CDialog::DoDataExchange(pDX);
}

BOOL CMonsterInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	DQMJ_SAVE_BRIEFING briefing;
	VERIFY(::DQMJSaveQueryBriefing(CDqmjSEApp::GetSaveHandle(), &briefing));

	DQMJ_SAVE_PLAY_INFO playerinfo;
	VERIFY(::DQMJSaveQueryPlayInfo(CDqmjSEApp::GetSaveHandle(), &playerinfo));

	m_bInterrupt = briefing.interrupt;
	m_masterName = CDqmjSEApp::GetNameString(playerinfo.player_name);

	InitComboBox(m_cmbSex, SEX_LIST, _countof(SEX_LIST));
	InitComboBox(m_cmbRace, m_raceIDStrList);
	InitComboBox(m_cmbRank, RANK_LIST, _countof(RANK_LIST));
	InitComboBox(m_cmbType, TYPE_LIST, _countof(TYPE_LIST));
	InitComboBox(m_cmbStrategy, STRATEGY_LIST, _countof(STRATEGY_LIST));
	InitComboBox(m_cmbSource, SOURCE_LIST, _countof(SOURCE_LIST));
	InitComboBox(m_cmbGrowthType, GROWTH_LIST, _countof(GROWTH_LIST));
	InitComboBox(m_cmbMaxLevel, MAXLEVEL_LIST, _countof(MAXLEVEL_LIST));
	InitComboBox(m_cmbParentRace[0], m_raceIDStrList);
	InitComboBox(m_cmbParentRace[1], m_raceIDStrList);
	InitComboBox(m_cmbGrandparentRace[0][0], m_raceIDStrList);
	InitComboBox(m_cmbGrandparentRace[0][1], m_raceIDStrList);
	InitComboBox(m_cmbGrandparentRace[1][0], m_raceIDStrList);
	InitComboBox(m_cmbGrandparentRace[1][1], m_raceIDStrList);

	for (int i = 0; i < _countof(m_cmbSkillset); i++)
		InitComboBox(m_cmbSkillset[i], m_skillsetIDStrList);
	for (int i = 0; i < _countof(m_cmbAbility); i++)
		InitComboBox(m_cmbAbility[i], m_abilityIDStrList);
	for (int i = 0; i < _countof(m_cmbGuard); i++)
		InitComboBox(m_cmbGuard[i], GUARD_LIST, _countof(GUARD_LIST));

	for (int i = 0; i < _countof(IDC_GUARD_NAME); i++)
		SetDlgItemText(IDC_GUARD_NAME[i], ::DQMJSaveGetGuardName(i));

	((CEdit *)GetDlgItem(IDC_EDIT_NAME))->SetLimitText(DQMJ_NAME_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT_MASTER))->SetLimitText(DQMJ_NAME_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT_FATHER_NAME))->SetLimitText(DQMJ_NAME_MAX);
	((CEdit *)GetDlgItem(IDC_EDIT_FATHER_MASTER))->SetLimitText(DQMJ_NAME_MAX);
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
	((CEdit *)GetDlgItem(IDC_EDIT_EXP))->SetLimitText(CDqmjSEApp::CalcDigit(INT_MAX));
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
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_EXP))->SetRange32(0, INT_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_GROWTH_LEVEL_START))->SetRange32(0, DQMJ_LEVEL_MAX);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_GROWTH_LEVEL_END))->SetRange32(0, DQMJ_LEVEL_MAX);

	RefreshMonster(LB_ERR);

	return TRUE;
}

void CMonsterInfoDlg::OnOK()
{
/*
	int cur_sel = GetCurSel();
	if (cur_sel < 0)
		return;

	UpdateSaveData(cur_sel);
	RefreshMonsterInfo(cur_sel);*/
}

void CMonsterInfoDlg::OnCancel()
{
/*
	int cur_sel = GetCurSel();
	if (cur_sel >= 0)
		UpdateSaveData(cur_sel);

	// TODO:
*/
	CDialog::OnCancel();
}

void CMonsterInfoDlg::OnBnClickedCheckNormalize()
{
/*
	BOOL normalize = IsDlgButtonChecked(IDC_CHECK_NORMALIZE) == BST_CHECKED;
	int cur_sel = GetCurSel();
	if (cur_sel < 0)
		return;

	UpdateSaveData(cur_sel);
	UpdateStatusSpinRange(normalize);

	if (!normalize)
		return;

	VERIFY(::DQMJSaveModifyMonster(CDqmjSEApp::GetSaveHandle(), cur_sel, &m_monsterInfo, TRUE));
	VERIFY(::DQMJSaveQueryMonsterInfo(CDqmjSEApp::GetSaveHandle(), cur_sel, &m_monsterInfo));

	RefreshMonster(cur_sel);*/
}

void CMonsterInfoDlg::OnBnClickedCheckRankAuto()
{
	DQMJ_SAVE_RACE_SETTING rs;
	if (::DQMJSaveGetRaceSetting(m_monsterInfo.race, &rs))
	{
		m_cmbRank.SetCurSel(GetSafeCBIndex(rs.rank, _countof(RANK_LIST)));
		GetDlgItem(IDC_CHECK_RANK_AUTO)->EnableWindow(FALSE);
	}
	else
	{
		m_cmbRank.SetCurSel(CB_ERR);
	}
}

void CMonsterInfoDlg::OnBnClickedCheckTypeAuto()
{
	DQMJ_SAVE_RACE_SETTING rs;
	if (::DQMJSaveGetRaceSetting(m_monsterInfo.race, &rs))
	{
		m_cmbType.SetCurSel(GetSafeCBIndex(rs.type, _countof(TYPE_LIST)));
		GetDlgItem(IDC_CHECK_TYPE_AUTO)->EnableWindow(FALSE);
	}
	else
	{
		m_cmbType.SetCurSel(CB_ERR);
	}
}

void CMonsterInfoDlg::OnBnClickedCheckDead()
{
	if (IsDlgButtonChecked(IDC_CHECK_DEAD) == BST_CHECKED)
	{
		UpdateData(TRUE);
		m_nCurHp = 0;
		UpdateData(FALSE);

		if (IsDlgButtonChecked(IDC_CHECK_NORMALIZE) == BST_CHECKED)
		{
			GetDlgItem(IDC_EDIT_CUR_HP)->EnableWindow(FALSE);
			GetDlgItem(IDC_SPIN_CUR_HP)->EnableWindow(FALSE);
		}
	}
	else
	{
		UpdateData(TRUE);
		m_nCurHp = max(m_nMaxHp, 1);
		UpdateData(FALSE);

		GetDlgItem(IDC_EDIT_CUR_HP)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_CUR_HP)->EnableWindow(TRUE);
	}
}

void CMonsterInfoDlg::OnBnClickedButtonMonsterUp()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonMonsterTop()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonMonsterDown()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonMonsterBottom()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonMonsterAdd()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonMonsterRemove()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonStatusMax()
{
	DQMJ_SAVE_RACE_SETTING rs;
	if (!::DQMJSaveGetRaceSetting(m_monsterInfo.race, &rs))
		return;

//	UpdateSaveData(cur_sel);

	DQMJ_SAVE_MONSTER_INFO monsterinfo = m_monsterInfo;
	monsterinfo.base_hp = rs.limit_hp;
	monsterinfo.base_mp = rs.limit_mp;
	monsterinfo.base_atk = rs.limit_atk;
	monsterinfo.base_def = rs.limit_def;
	monsterinfo.base_agi = rs.limit_agi;
	monsterinfo.base_int = rs.limit_int;

//	VERIFY(::DQMJSaveNormalizeMonster(CDqmjSEApp::GetSaveHandle(), cur_sel, &monsterinfo, &monsterinfo));

	m_monsterInfo.base_hp = monsterinfo.base_hp;
	m_monsterInfo.base_mp = monsterinfo.base_mp;
	m_monsterInfo.base_atk = monsterinfo.base_atk;
	m_monsterInfo.base_def = monsterinfo.base_def;
	m_monsterInfo.base_agi = monsterinfo.base_agi;
	m_monsterInfo.base_int = monsterinfo.base_int;
	m_monsterInfo.actual_hp = monsterinfo.actual_hp;
	m_monsterInfo.actual_mp = monsterinfo.actual_mp;
	m_monsterInfo.actual_atk = monsterinfo.actual_atk;
	m_monsterInfo.actual_def = monsterinfo.actual_def;
	m_monsterInfo.actual_agi = monsterinfo.actual_agi;
	m_monsterInfo.actual_int = monsterinfo.actual_int;
	m_monsterInfo.current_hp = monsterinfo.current_hp;
	m_monsterInfo.current_mp = monsterinfo.current_mp;

//	RefreshMonsterInfo(cur_sel);
}

void CMonsterInfoDlg::OnBnClickedButtonStatusMaxForce()
{
	UpdateData(TRUE);

	m_nBaseHp = DQMJ_STATUS_MAX;
	m_nBaseMp = DQMJ_STATUS_MAX;
	m_nBaseAtk = DQMJ_STATUS_MAX;
	m_nBaseDef = DQMJ_STATUS_MAX;
	m_nBaseAgi = DQMJ_STATUS_MAX;
	m_nBaseInt = DQMJ_STATUS_MAX;

	m_nAtk = DQMJ_STATUS_MAX;
	m_nDef = DQMJ_STATUS_MAX;
	m_nAgi = DQMJ_STATUS_MAX;
	m_nInt = DQMJ_STATUS_MAX;

	m_nCurHp = DQMJ_STATUS_MAX;
	m_nCurMp = DQMJ_STATUS_MAX;
	m_nMaxHp = DQMJ_STATUS_MAX;
	m_nMaxMp = DQMJ_STATUS_MAX;

	UpdateData(FALSE);
}

void CMonsterInfoDlg::OnBnClickedButtonWeaponModify()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonWeaponRemove()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonGrowthRandom()
{
	UpdateData(TRUE);

	DQMJ_SAVE_MONSTER_INFO monsterinfo = m_monsterInfo;
	monsterinfo.growth_type = DQMJ_RAND_GROWTH_TYPE;
	monsterinfo.growth_level[0] = DQMJ_RAND_GROWTH_LEVEL;
	monsterinfo.growth_level[1] = DQMJ_RAND_GROWTH_LEVEL;

//	VERIFY(::DQMJSaveNormalizeMonster(CDqmjSEApp::GetSaveHandle(), cur_sel, &monsterinfo, &monsterinfo));

	m_cmbGrowthType.SetCurSel(monsterinfo.growth_type);
	m_nGrowthLevel[0] = monsterinfo.growth_level[0];
	m_nGrowthLevel[1] = monsterinfo.growth_level[1];

	UpdateData(FALSE);
}

void CMonsterInfoDlg::OnBnClickedButtonSkillsetMax1()
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
}

void CMonsterInfoDlg::OnBnClickedButtonSkillsetMax2()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonSkillsetMax3()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonSkillUp()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonSkillTop()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonSkillDown()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonSkillBottom()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonSkillAdd()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonSkillModify()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonSkillRemove()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonSkillSort()
{
	// TODO: Add your control notification handler code here
}

void CMonsterInfoDlg::OnBnClickedButtonMasterMe()
{
	UpdateData(TRUE);
	m_strMaster = m_masterName;
	UpdateData(FALSE);
}

void CMonsterInfoDlg::OnBnClickedButtonMasterUnknown()
{
	UpdateData(TRUE);
	m_strMaster = _T("ふめい");
	UpdateData(FALSE);
}

void CMonsterInfoDlg::OnBnClickedButtonFatherMasterMe()
{
	UpdateData(TRUE);
	m_strParentMaster[0] = m_masterName;
	UpdateData(FALSE);
}

void CMonsterInfoDlg::OnBnClickedButtonFatherMasterUnknown()
{
	UpdateData(TRUE);
	m_strParentMaster[0] = _T("ふめい");
	UpdateData(FALSE);
}

void CMonsterInfoDlg::OnBnClickedButtonMotherMasterMe()
{
	UpdateData(TRUE);
	m_strParentMaster[1] = m_masterName;
	UpdateData(FALSE);
}

void CMonsterInfoDlg::OnBnClickedButtonMotherMasterUnknown()
{
	UpdateData(TRUE);
	m_strParentMaster[1] = _T("ふめい");
	UpdateData(FALSE);
}

void CMonsterInfoDlg::OnLbnSelchangeListSkillList()
{
	RefreshSkillSel(m_lstSkill.GetCurSel());
}

void CMonsterInfoDlg::OnCbnSelchangeComboRace()
{/*
	int cur_sel = GetCurSel();
	if (cur_sel < 0)
		return;

	UpdateSaveData(cur_sel);
	RefreshMonsterInfo(cur_sel);*/
}

void CMonsterInfoDlg::OnCbnSelchangeComboRank()
{/*
	int cur_sel = GetCurSel();
	if (cur_sel < 0)
		return;

	UpdateSaveData(cur_sel);
	RefreshMonsterInfo(cur_sel);*/
}

void CMonsterInfoDlg::OnCbnSelchangeComboType()
{/*
	int cur_sel = GetCurSel();
	if (cur_sel < 0)
		return;

	UpdateSaveData(cur_sel);
	RefreshMonsterInfo(cur_sel);*/
}

void CMonsterInfoDlg::OnCbnSelchangeComboMaxLevel()
{
	UpdateData(TRUE);
	m_nMaxLevel = MAXLEVEL_LIST[m_cmbMaxLevel.GetCurSel()];
	UpdateData(FALSE);
}

//////////////////////////////////////////////////////////////////////////
/*

void CMonsterInfoDlg::ClearMonsterInfo()
{
	::ZeroMemory(&m_monsterInfo, sizeof(m_monsterInfo));

	*m_monsterInfo.name = 0xFF;
	*m_monsterInfo.master = 0xFF;
	m_monsterInfo.sex = -1;
	m_monsterInfo.rank = DQMJ_AUTO_RANK;
	m_monsterInfo.type = DQMJ_AUTO_TYPE;
	m_monsterInfo.strategy = -1;
	m_monsterInfo.source = -1;
	m_monsterInfo.growth_type = DQMJ_RAND_GROWTH_TYPE;
	m_monsterInfo.growth_level[0] = DQMJ_RAND_GROWTH_LEVEL;
	m_monsterInfo.growth_level[1] = DQMJ_RAND_GROWTH_LEVEL;
}
*/

void CMonsterInfoDlg::UpdateSaveData(int sel)
{
	if (sel < 0)
		return;

	UpdateData(TRUE);

	m_monsterInfo.cheat = IsDlgButtonChecked(IDC_CHECK_CHEAT) == BST_CHECKED;
	m_monsterInfo.dead = IsDlgButtonChecked(IDC_CHECK_DEAD) == BST_CHECKED;
	m_monsterInfo.poison = IsDlgButtonChecked(IDC_CHECK_POISON) == BST_CHECKED;

	CDqmjSEApp::GetStringName(m_monsterInfo.name, m_strName);
	CDqmjSEApp::GetStringName(m_monsterInfo.master, m_strMaster);

	m_monsterInfo.race = m_cmbRace.GetItemData(m_cmbRace.GetCurSel());
	m_monsterInfo.sex = m_cmbSex.GetCurSel();
	m_monsterInfo.rank = m_cmbRank.GetCurSel();
	m_monsterInfo.type = m_cmbType.GetCurSel();
	m_monsterInfo.combine = m_nCombine;
	m_monsterInfo.source = m_cmbSource.GetCurSel();
	m_monsterInfo.level = m_nLevel;
	m_monsterInfo.max_level = m_nMaxLevel;
	m_monsterInfo.base_hp = m_nBaseHp;
	m_monsterInfo.base_mp = m_nBaseMp;
	m_monsterInfo.base_atk = m_nBaseAtk;
	m_monsterInfo.base_def = m_nBaseDef;
	m_monsterInfo.base_agi = m_nBaseAgi;
	m_monsterInfo.base_int = m_nBaseInt;
	m_monsterInfo.current_hp = m_nCurHp;
	m_monsterInfo.current_mp = m_nCurMp;
	m_monsterInfo.actual_hp = m_nMaxHp;
	m_monsterInfo.actual_mp = m_nMaxMp;
	m_monsterInfo.actual_atk = m_nAtk;
	m_monsterInfo.actual_def = m_nDef;
	m_monsterInfo.actual_agi = m_nAgi;
	m_monsterInfo.actual_int = m_nInt;
	m_monsterInfo.remaining_sp = m_nSkillPoint;
	m_monsterInfo.exp = m_nExp;
	m_monsterInfo.strategy = m_cmbStrategy.GetCurSel();
	m_monsterInfo.growth_type = m_cmbGrowthType.GetCurSel();
	m_monsterInfo.growth_level[0] = m_nGrowthLevel[0];
	m_monsterInfo.growth_level[1] = m_nGrowthLevel[1];

//int					weapon;									/* 装備している武器 */

	for (int i = 0; i < _countof(IDC_CHECK_SKILLSET_NONE); i++)
	{
		if ((IsDlgButtonChecked(IDC_CHECK_SKILLSET_NONE[i]) == BST_CHECKED) || (m_cmbSkillset[i].GetCurSel() < 0))
		{
			m_monsterInfo.skillset[i] = 0x00;
			m_monsterInfo.assigned_sp[i] = 0;
		}
		else
		{
			m_monsterInfo.skillset[i] = m_cmbSkillset[i].GetItemData(m_cmbSkillset[i].GetCurSel());
			m_monsterInfo.assigned_sp[i] = m_nSkillsetPt[i];
		}
	}

#if 0
	int					skill_active_num[DQMJ_SKILLSET_MAX];	/* 各スキルの開放特技数（restrict時は無視される） */
	int					guard_info[DQMJ_GUARD_MAX];				/* ガード情報（restrict時は無視される） */
	int					skill_list[DQMJ_SKILL_MAX];				/* 習得特技リスト（restrict時は無視される） */
	int					ability_list[DQMJ_ABILITY_MAX];			/* 特性リスト（restrict時は無視される） */
#endif

	for (int i = 0; i < _countof(IDC_CHECK_PARENT_NONE); i++)
	{
		if ((IsDlgButtonChecked(IDC_CHECK_PARENT_NONE[i]) == BST_CHECKED) || (m_cmbParentRace[i].GetCurSel() < 0))
		{
			m_monsterInfo.parent_race[i] = 0x00;
			::ZeroMemory(m_monsterInfo.parent_name[i], sizeof(m_monsterInfo.parent_name[i]));
			::ZeroMemory(m_monsterInfo.parent_master[i], sizeof(m_monsterInfo.parent_master[i]));
		}
		else
		{
			m_monsterInfo.parent_race[i] = m_cmbParentRace[i].GetItemData(m_cmbParentRace[i].GetCurSel());

			CDqmjSEApp::GetStringName(m_monsterInfo.parent_name[i], m_strParentName[i]);
			CDqmjSEApp::GetStringName(m_monsterInfo.parent_master[i], m_strParentMaster[i]);
		}

		for (int j = 0; j < _countof(IDC_CHECK_GRANDPARENT_NONE[i]); j++)
		{
			if ((IsDlgButtonChecked(IDC_CHECK_PARENT_NONE[i]) == BST_CHECKED) || (IsDlgButtonChecked(IDC_CHECK_GRANDPARENT_NONE[i][j]) == BST_CHECKED) || (m_cmbGrandparentRace[i][j].GetCurSel() < 0))
				m_monsterInfo.grandparent_race[i][j] = 0x00;
			else
				m_monsterInfo.grandparent_race[i][j] = m_cmbGrandparentRace[i][j].GetItemData(m_cmbGrandparentRace[i][j].GetCurSel());
		}
	}

	VERIFY(::DQMJSaveModifyMonster(CDqmjSEApp::GetSaveHandle(), sel, &m_monsterInfo, IsDlgButtonChecked(IDC_CHECK_NORMALIZE) == BST_CHECKED));
	VERIFY(::DQMJSaveQueryMonsterInfo(CDqmjSEApp::GetSaveHandle(), sel, &m_monsterInfo));
}

void CMonsterInfoDlg::RefreshMonster(int sel)
{
	BOOL enable = sel >= 0;
	BOOL normalize = IsDlgButtonChecked(IDC_CHECK_NORMALIZE) == BST_CHECKED;
	BOOL freeModeOnly = enable && !normalize;
	BOOL interruptOnly = enable && (!normalize || m_bInterrupt);

	m_cmbMaxLevel.ShowWindow(normalize ? SW_SHOWNOACTIVATE : SW_HIDE);
	GetDlgItem(IDC_EDIT_MAX_LEVEL)->ShowWindow(normalize ? SW_HIDE : SW_SHOWNOACTIVATE);
	GetDlgItem(IDC_SPIN_MAX_LEVEL)->ShowWindow(normalize ? SW_HIDE : SW_SHOWNOACTIVATE);

	m_lstSkill.EnableWindow(freeModeOnly);

	for (int i = 0; i < _countof(m_cmbGuard); i++)
		m_cmbGuard[i].EnableWindow(freeModeOnly);

	GetDlgItem(IDC_EDIT_MASTER)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_BUTTON_MASTER_ME)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_BUTTON_MASTER_UNKNOWN)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_CHECK_RANK_AUTO)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_CHECK_TYPE_AUTO)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_CHECK_CHEAT)->EnableWindow(freeModeOnly);

	GetDlgItem(IDC_EDIT_MAX_HP)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_EDIT_MAX_MP)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_EDIT_ATK)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_EDIT_DEF)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_EDIT_AGI)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_EDIT_INT)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_EDIT_CUR_HP)->EnableWindow(interruptOnly);
	GetDlgItem(IDC_EDIT_CUR_MP)->EnableWindow(interruptOnly);
	GetDlgItem(IDC_SPIN_MAX_HP)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_SPIN_MAX_MP)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_SPIN_ATK)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_SPIN_DEF)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_SPIN_AGI)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_SPIN_INT)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_SPIN_CUR_HP)->EnableWindow(interruptOnly);
	GetDlgItem(IDC_SPIN_CUR_MP)->EnableWindow(interruptOnly);
	GetDlgItem(IDC_BUTTON_STATUS_MAX_FORCE)->EnableWindow(freeModeOnly);
	GetDlgItem(IDC_CHECK_DEAD)->EnableWindow(interruptOnly);
	GetDlgItem(IDC_CHECK_POISON)->EnableWindow(freeModeOnly);

	for (int i = 0; i < _countof(IDC_CHECK_ABILITY_NONE); i++)
		GetDlgItem(IDC_CHECK_ABILITY_NONE[i])->EnableWindow(freeModeOnly);

	RefreshMonsterInfo(sel);

	RefreshSkillSel(LB_ERR, !enable || normalize);
}

void CMonsterInfoDlg::RefreshMonsterInfo(int sel)
{
	BOOL normalize = IsDlgButtonChecked(IDC_CHECK_NORMALIZE) == BST_CHECKED;

	m_nLevel = m_monsterInfo.level;
	m_nCombine = m_monsterInfo.combine;
	m_nBaseHp = m_monsterInfo.base_hp;
	m_nBaseMp = m_monsterInfo.base_mp;
	m_nBaseAtk = m_monsterInfo.base_atk;
	m_nBaseDef = m_monsterInfo.base_def;
	m_nBaseAgi = m_monsterInfo.base_agi;
	m_nBaseInt = m_monsterInfo.base_int;
	m_nAtk = m_monsterInfo.actual_atk;
	m_nDef = m_monsterInfo.actual_def;
	m_nAgi = m_monsterInfo.actual_agi;
	m_nInt = m_monsterInfo.actual_int;
	m_nMaxLevel = m_monsterInfo.max_level;
	m_nMaxHp = m_monsterInfo.actual_hp;
	m_nMaxMp = m_monsterInfo.actual_mp;
	m_nCurHp = m_monsterInfo.current_hp;
	m_nCurMp = m_monsterInfo.current_mp;
	m_nExp = m_monsterInfo.exp;
	m_nSkillPoint = m_monsterInfo.remaining_sp;

	m_strName = CDqmjSEApp::GetNameString(m_monsterInfo.name);
	m_strMaster = CDqmjSEApp::GetNameString(m_monsterInfo.master);

	CheckDlgButton(IDC_CHECK_CHEAT, m_monsterInfo.cheat ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_DEAD, m_monsterInfo.dead ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_POISON, m_monsterInfo.poison ? BST_CHECKED : BST_UNCHECKED);

	SetDlgItemText(IDC_WEAPON_NAME, CDqmjSEApp::GetItemNameString(m_monsterInfo.weapon));
	GetDlgItem(IDC_BUTTON_WEAPON_REMOVE)->EnableWindow(m_monsterInfo.weapon != 0x00);

	m_cmbSex.SetCurSel(GetSafeCBIndex(m_monsterInfo.sex, _countof(SEX_LIST)));
	m_cmbRace.SetCurSel(GetSafeCBIndex(m_monsterInfo.race, m_raceToCBIndex, _countof(m_raceToCBIndex)));
	m_cmbStrategy.SetCurSel(GetSafeCBIndex(m_monsterInfo.strategy, _countof(STRATEGY_LIST)));
	m_cmbSource.SetCurSel(GetSafeCBIndex(m_monsterInfo.source, _countof(SOURCE_LIST)));
	m_cmbMaxLevel.SetCurSel(CB_ERR);
	m_lstSkill.ResetContent();

	DQMJ_SAVE_RACE_SETTING rs;
	if (::DQMJSaveGetRaceSetting(m_monsterInfo.race, &rs))
	{
		GetDlgItem(IDC_CHECK_RANK_AUTO)->EnableWindow(!normalize);
		GetDlgItem(IDC_CHECK_TYPE_AUTO)->EnableWindow(!normalize);

		m_cmbRank.EnableWindow(!normalize);
		m_cmbType.EnableWindow(!normalize);
	}
	else
	{
		rs.rank = DQMJ_RANK_NONE;
		rs.type = DQMJ_TYPE_NONE;

		GetDlgItem(IDC_CHECK_RANK_AUTO)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_TYPE_AUTO)->EnableWindow(FALSE);

		m_cmbRank.EnableWindow(FALSE);
		m_cmbType.EnableWindow(FALSE);
	}

	if (normalize && m_monsterInfo.dead)
	{
		GetDlgItem(IDC_EDIT_CUR_HP)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_CUR_HP)->EnableWindow(FALSE);
	}

	if (m_monsterInfo.rank == DQMJ_AUTO_RANK)
	{
		CheckDlgButton(IDC_CHECK_RANK_AUTO, BST_CHECKED);
		GetDlgItem(IDC_CHECK_RANK_AUTO)->EnableWindow(FALSE);

		m_cmbRank.SetCurSel(GetSafeCBIndex(rs.rank, _countof(RANK_LIST)));
	}
	else
	{
		if (m_monsterInfo.rank == rs.rank)
		{
			CheckDlgButton(IDC_CHECK_RANK_AUTO, BST_CHECKED);
			GetDlgItem(IDC_CHECK_RANK_AUTO)->EnableWindow(FALSE);
		}
		else
		{
			CheckDlgButton(IDC_CHECK_RANK_AUTO, BST_UNCHECKED);
		}

		m_cmbRank.SetCurSel(GetSafeCBIndex(m_monsterInfo.rank, _countof(RANK_LIST)));
	}

	if (m_monsterInfo.type == DQMJ_AUTO_TYPE)
	{
		CheckDlgButton(IDC_CHECK_TYPE_AUTO, BST_CHECKED);
		GetDlgItem(IDC_CHECK_TYPE_AUTO)->EnableWindow(FALSE);

		m_cmbType.SetCurSel(GetSafeCBIndex(rs.type, _countof(TYPE_LIST)));
	}
	else
	{
		if (m_monsterInfo.type == rs.type)
		{
			CheckDlgButton(IDC_CHECK_TYPE_AUTO, BST_CHECKED);
			GetDlgItem(IDC_CHECK_TYPE_AUTO)->EnableWindow(FALSE);
		}
		else
		{
			CheckDlgButton(IDC_CHECK_TYPE_AUTO, BST_UNCHECKED);
		}

		m_cmbType.SetCurSel(GetSafeCBIndex(m_monsterInfo.type, _countof(TYPE_LIST)));
	}

	if (m_monsterInfo.growth_type == DQMJ_RAND_GROWTH_TYPE)
	{
		m_cmbGrowthType.EnableWindow(FALSE);
		m_cmbGrowthType.SetCurSel(CB_ERR);
	}
	else
	{
		m_cmbGrowthType.EnableWindow(TRUE);
		m_cmbGrowthType.SetCurSel(GetSafeCBIndex(m_monsterInfo.growth_type, _countof(GROWTH_LIST)));
	}

	if ((m_monsterInfo.growth_level[0] == DQMJ_RAND_GROWTH_LEVEL) || (m_monsterInfo.growth_level[1] == DQMJ_RAND_GROWTH_LEVEL))
	{
		m_nGrowthLevel[0] = 0;
		m_nGrowthLevel[1] = 0;

		GetDlgItem(IDC_EDIT_GROWTH_LEVEL_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_GROWTH_LEVEL_END)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_GROWTH_LEVEL_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_GROWTH_LEVEL_END)->EnableWindow(FALSE);
	}
	else
	{
		m_nGrowthLevel[0] = m_monsterInfo.growth_level[0];
		m_nGrowthLevel[1] = m_monsterInfo.growth_level[1];

		GetDlgItem(IDC_EDIT_GROWTH_LEVEL_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_GROWTH_LEVEL_END)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_GROWTH_LEVEL_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_GROWTH_LEVEL_END)->EnableWindow(TRUE);
	}

	for (int i = 0; i < _countof(m_cmbGuard); i++)
		m_cmbGuard[i].SetCurSel(GetSafeCBIndex(m_monsterInfo.guard_info[i], _countof(GUARD_LIST)));

	for (int i = 0; i < _countof(MAXLEVEL_LIST); i++)
	{
		if (MAXLEVEL_LIST[i] == m_monsterInfo.max_level)
		{
			m_cmbMaxLevel.SetCurSel(i);
			break;
		}
	}

	for (int i = 0; i < _countof(m_cmbSkillset); i++)
	{
		m_nSkillsetPt[i] = m_monsterInfo.assigned_sp[i];

		if (m_monsterInfo.skillset[i] == 0x00)
		{
			CheckDlgButton(IDC_CHECK_SKILLSET_NONE[i], BST_CHECKED);

			GetDlgItem(IDC_LABEL_SKILLSET_PT[i])->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SKILLSET_PT[i])->EnableWindow(FALSE);
			GetDlgItem(IDC_SPIN_SKILLSET_PT[i])->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SKILLSET_MAX[i])->EnableWindow(FALSE);

			m_cmbSkillset[i].EnableWindow(FALSE);
			m_cmbSkillset[i].SetCurSel(CB_ERR);
		}
		else
		{
			CheckDlgButton(IDC_CHECK_SKILLSET_NONE[i], BST_UNCHECKED);

			GetDlgItem(IDC_LABEL_SKILLSET_PT[i])->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_SKILLSET_PT[i])->EnableWindow(TRUE);
			GetDlgItem(IDC_SPIN_SKILLSET_PT[i])->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_SKILLSET_MAX[i])->EnableWindow(TRUE);

			m_cmbSkillset[i].EnableWindow(TRUE);
			m_cmbSkillset[i].SetCurSel(GetSafeCBIndex(m_monsterInfo.skillset[i], m_skillsetToCBIndex, _countof(m_skillsetToCBIndex)));
		}
	}

	for (int i = 0; i < _countof(m_cmbAbility); i++)
	{
		if (m_monsterInfo.ability_list[i] == 0x00)
		{
			CheckDlgButton(IDC_CHECK_ABILITY_NONE[i], BST_CHECKED);

			m_cmbAbility[i].EnableWindow(FALSE);
			m_cmbAbility[i].SetCurSel(CB_ERR);
		}
		else
		{
			CheckDlgButton(IDC_CHECK_ABILITY_NONE[i], BST_UNCHECKED);

			m_cmbAbility[i].EnableWindow(!normalize);
			m_cmbAbility[i].SetCurSel(GetSafeCBIndex(m_monsterInfo.ability_list[i], m_abilityToCBIndex, _countof(m_abilityToCBIndex)));
		}
	}

	for (int i = 0; i < DQMJ_SKILL_MAX; i++)
	{
		LPCTSTR str = ::DQMJSaveGetSkillName(m_monsterInfo.skill_list[i]);
		if (str != NULL)
			VERIFY(m_lstSkill.SetItemData(m_lstSkill.AddString(str), m_monsterInfo.skill_list[i]) != LB_ERR);
	}

	SetDlgItemText(IDC_SKILL_NUM, CDqmjSEApp::GetDecimalString2(m_lstSkill.GetCount(), DQMJ_SKILL_MAX));

	for (int i = 0; i < _countof(m_cmbParentRace); i++)
	{
		BOOL enable = m_monsterInfo.parent_race[i] != 0x00;

		CheckDlgButton(IDC_CHECK_PARENT_NONE[i], enable ? BST_UNCHECKED : BST_CHECKED);

		if (enable)
		{
			m_strParentName[i] = CDqmjSEApp::GetNameString(m_monsterInfo.parent_name[i]);
			m_strParentMaster[i] = CDqmjSEApp::GetNameString(m_monsterInfo.parent_master[i]);
			m_cmbParentRace[i].SetCurSel(GetSafeCBIndex(m_monsterInfo.parent_race[i], m_raceToCBIndex, _countof(m_raceToCBIndex)));
		}
		else
		{
			m_strParentName[i] = _T("");
			m_strParentMaster[i] = _T("");
			m_cmbParentRace[i].SetCurSel(CB_ERR);
		}

		GetDlgItem(IDC_EDIT_PARENT_NAME[i])->EnableWindow(enable);
		GetDlgItem(IDC_EDIT_PARENT_MASTER[i])->EnableWindow(enable);
		GetDlgItem(IDC_BUTTON_PARENT_MASTER_ME[i])->EnableWindow(enable);
		GetDlgItem(IDC_BUTTON_PARENT_MASTER_UNKNOWN[i])->EnableWindow(enable);

		m_cmbParentRace[i].EnableWindow(enable);

		for (int j = 0; j <= _countof(m_monsterInfo.grandparent_race[i]); j++)
		{
			GetDlgItem(IDC_CHECK_GRANDPARENT_NONE[i][j])->EnableWindow(enable);

			if (m_monsterInfo.grandparent_race[i][j] == 0x00)
			{
				CheckDlgButton(IDC_CHECK_GRANDPARENT_NONE[i][j], BST_CHECKED);
				m_cmbGrandparentRace[i][j].EnableWindow(FALSE);
				m_cmbGrandparentRace[i][j].SetCurSel(CB_ERR);
			}
			else
			{
				CheckDlgButton(IDC_CHECK_GRANDPARENT_NONE[i][j], BST_UNCHECKED);
				m_cmbGrandparentRace[i][j].EnableWindow(enable);
				m_cmbGrandparentRace[i][j].SetCurSel(GetSafeCBIndex(m_monsterInfo.grandparent_race[i][j], m_raceToCBIndex, _countof(m_raceToCBIndex)));
			}
		}
	}

	UpdateData(FALSE);
}

void CMonsterInfoDlg::RefreshSkillSel(int sel, BOOL disable)
{
	int item_count = m_lstSkill.GetCount();

	GetDlgItem(IDC_BUTTON_SKILL_UP)->EnableWindow(!disable && (sel > 0));
	GetDlgItem(IDC_BUTTON_SKILL_TOP)->EnableWindow(!disable && (sel > 0));
	GetDlgItem(IDC_BUTTON_SKILL_DOWN)->EnableWindow(!disable && (sel >= 0) && (sel < item_count - 1));
	GetDlgItem(IDC_BUTTON_SKILL_BOTTOM)->EnableWindow(!disable && (sel >= 0) && (sel < item_count - 1));
	GetDlgItem(IDC_BUTTON_SKILL_ADD)->EnableWindow(!disable && (item_count < DQMJ_SKILL_MAX));
	GetDlgItem(IDC_BUTTON_SKILL_MODIFY)->EnableWindow(!disable && (sel >= 0));
	GetDlgItem(IDC_BUTTON_SKILL_REMOVE)->EnableWindow(!disable && (sel >= 0));
	GetDlgItem(IDC_BUTTON_SKILL_SORT)->EnableWindow(!disable && (item_count > 0));
}

void CMonsterInfoDlg::UpdateStatusSpinRange(BOOL normalize)
{
	if (normalize)
	{
		DQMJ_SAVE_RACE_SETTING rs;
		VERIFY(::DQMJSaveGetRaceSetting(m_monsterInfo.race, &rs));

		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_HP))->SetRange32(0, rs.limit_hp);
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_MP))->SetRange32(0, rs.limit_mp);
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_ATK))->SetRange32(0, rs.limit_atk);
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_DEF))->SetRange32(0, rs.limit_def);
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_AGI))->SetRange32(0, rs.limit_agi);
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_INT))->SetRange32(0, rs.limit_int);

		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_CUR_HP))->SetRange32(1, m_monsterInfo.actual_hp);
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_CUR_MP))->SetRange32(0, m_monsterInfo.actual_mp);
	}
	else
	{
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_HP))->SetRange32(0, DQMJ_STATUS_MAX);
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_MP))->SetRange32(0, DQMJ_STATUS_MAX);
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_ATK))->SetRange32(0, DQMJ_STATUS_MAX);
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_DEF))->SetRange32(0, DQMJ_STATUS_MAX);
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_AGI))->SetRange32(0, DQMJ_STATUS_MAX);
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_BASE_INT))->SetRange32(0, DQMJ_STATUS_MAX);

		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_CUR_HP))->SetRange32(0, DQMJ_STATUS_MAX);
		((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_CUR_MP))->SetRange32(0, DQMJ_STATUS_MAX);
	}
}

void CMonsterInfoDlg::CheckSkillsetNone(int idx)
{
	UpdateData(TRUE);

	if (IsDlgButtonChecked(IDC_CHECK_SKILLSET_NONE[idx]) == BST_CHECKED)
	{
		m_nSkillsetPt[idx] = 0;
		m_cmbSkillset[idx].SetCurSel(CB_ERR);
		m_cmbSkillset[idx].EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SKILLSET_PT[idx])->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_SKILLSET_PT[idx])->EnableWindow(FALSE);
		GetDlgItem(IDC_LABEL_SKILLSET_PT[idx])->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SKILLSET_MAX[idx])->EnableWindow(FALSE);
	}
	else
	{
		m_cmbSkillset[idx].SetCurSel(0);
		m_cmbSkillset[idx].EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SKILLSET_PT[idx])->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_SKILLSET_PT[idx])->EnableWindow(TRUE);
		GetDlgItem(IDC_LABEL_SKILLSET_PT[idx])->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SKILLSET_MAX[idx])->EnableWindow(TRUE);
	}

	UpdateData(FALSE);
}

void CMonsterInfoDlg::CheckParentNone(BOOL father_or_mother)
{
	int idx = father_or_mother ? 0 : 1;

	if (IsDlgButtonChecked(IDC_CHECK_PARENT_NONE[idx]) != BST_CHECKED)
	{
		m_cmbParentRace[idx].SetCurSel(0);
		UpdateData(TRUE);
		m_strParentName[idx] = _T("ふめい");
		m_strParentMaster[idx] = _T("ふめい");
		UpdateData(FALSE);
	}
/*

	UpdateSaveData(cur_sel);
	RefreshMonsterInfo(cur_sel);*/
}

void CMonsterInfoDlg::CheckGrandparentNone(BOOL father_or_mother, BOOL grandfather_or_grandmother)
{
	int i = father_or_mother ? 0 : 1;
	int j = grandfather_or_grandmother ? 0 : 1;

	if (IsDlgButtonChecked(IDC_CHECK_GRANDPARENT_NONE[i][j]) != BST_CHECKED)
		m_cmbGrandparentRace[i][j].SetCurSel(0);
	
/*
	UpdateSaveData(cur_sel);
	RefreshMonsterInfo(cur_sel);*/
}

//////////////////////////////////////////////////////////////////////////

void CMonsterInfoDlg::StaticInitialize()
{
	static BOOL flag = FALSE;
	if (flag)
		return;

	flag = TRUE;
	InitCBIndex();
}

void CMonsterInfoDlg::InitCBIndex()
{
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
}

void CMonsterInfoDlg::InitComboBox(CComboBox &combo, const int *list, int len)
{
	combo.SetRedraw(FALSE);

	for (int i = 0; i < len; i++)
		VERIFY(combo.AddString(CDqmjSEApp::GetDecimalString(list[i])) == i);

	combo.SetRedraw(TRUE);
}

void CMonsterInfoDlg::InitComboBox(CComboBox &combo, const LPCTSTR *list, int len)
{
	combo.SetRedraw(FALSE);

	for (int i = 0; i < len; i++)
		VERIFY(combo.AddString(list[i]) == i);

	combo.SetRedraw(TRUE);
}

void CMonsterInfoDlg::InitComboBox(CComboBox &combo, const CIDStrList &list)
{
	combo.SetRedraw(FALSE);

	POSITION pos = list.GetHeadPosition();
	while (pos != NULL)
	{
		const IDStrPair &pair = list.GetNext(pos);
		VERIFY(combo.SetItemData(combo.AddString(pair.str), pair.id) != CB_ERR);
	}

	combo.SetRedraw(TRUE);
}

int CMonsterInfoDlg::GetSafeCBIndex(int idx, int len)
{
	return ((idx >= 0) && (idx < len)) ? idx : CB_ERR;
}

int CMonsterInfoDlg::GetSafeCBIndex(int idx, const int *list, int len)
{
	return ((idx >= 0) && (idx < len)) ? list[idx] : CB_ERR;
}

LPCTSTR CMonsterInfoDlg::GetSafeCBString(int idx, const LPCTSTR *list, int len)
{
	return ((idx >= 0) && (idx < len)) ? list[idx] : _T("不明");
}

//////////////////////////////////////////////////////////////////////////
