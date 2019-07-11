
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"
#include "dqmjsav.h"

//////////////////////////////////////////////////////////////////////////

typedef CList<int, int>						CIntList;
typedef CMap<int, int, int, int>			CIntToIntMap;
typedef CMap<int, int, CString, LPCTSTR>	CIntToStrMap;

//////////////////////////////////////////////////////////////////////////

class CDqmjSEApp : public CWinAppEx
{

public:

	CDqmjSEApp();

	HDQMJSAVE GetSaveHandle() const { return m_hDqmjSave; }
	const CIntList &GetWeaponList() const { return m_weaponList; }
	const CStringArray &GetSexStringList() const { return m_sexList; }
	const CStringArray &GetRankStringList() const { return m_rankList; }
	const CStringArray &GetTypeStringList() const { return m_typeList; }
	const CStringArray &GetSkillsetStringList() const { return m_skillsetList; }
	const CStringArray &GetAbilityStringList() const { return m_abilityList; }
	const CStringArray &GetStrategyStringList() const { return m_strategyList; }
	const CStringArray &GetSourceStringList() const { return m_sourceList; }
	const CStringArray &GetGrowthStringList() const { return m_growthList; }
	const CStringArray &GetGuardStringList() const { return m_guardList; }
	const CIntToStrMap &GetRaceStringMap() const { return m_raceMap; }
	const CIntToStrMap &GetItemStringMap() const { return m_itemMap; }

	int CalcDigit(int number) const;
	CString GetDecimalString(int num) const;
	CString GetDecimalString(int num1, int num2) const;
	CString GetNameString(const DQMJ_NAME &name) const;
	CString GetSexString(int sex) const;
	CString GetRaceString(int race) const;
	CString GetRankString(int rank) const;
	CString GetTypeString(int type) const;
	CString GetItemString(int item) const;
	DQMJ_NAME GetStringName(LPCTSTR str) const;

	BOOL OpenSave(LPCTSTR pszFilename);
	void CloseSave();

	virtual BOOL InitInstance();

private:

	HDQMJSAVE		m_hDqmjSave;
	CIntList		m_weaponList;
	CStringArray	m_sexList;
	CStringArray	m_rankList;
	CStringArray	m_typeList;
	CStringArray	m_skillsetList;
	CStringArray	m_abilityList;
	CStringArray	m_strategyList;
	CStringArray	m_sourceList;
	CStringArray	m_growthList;
	CStringArray	m_guardList;
	CIntToStrMap	m_raceMap;
	CIntToStrMap	m_itemMap;

	static void InitStringList(CStringArray &arr, const LPCTSTR *list, int len);
	static void InitStringList(CStringArray &arr, LPCTSTR (*func)(int), int len);
	static CString GetSafeString(const CStringArray &arr, int idx);
	static CString GetSafeString(const CIntToStrMap &map, int id);

};

//////////////////////////////////////////////////////////////////////////

extern CDqmjSEApp theApp;

//////////////////////////////////////////////////////////////////////////
