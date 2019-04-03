
#pragma once

//////////////////////////////////////////////////////////////////////////

class CSelectMonsterDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectMonsterDlg)

public:

	explicit CSelectMonsterDlg(int monster = LB_ERR, BOOL disable_party_member = FALSE, BOOL disable_standby = FALSE, CWnd *pParent = NULL);

	int GetSelMonster() const;
	int GetPartyIndex() const;
	int GetStandbyIndex() const;

protected:

	CListCtrl	m_lstMonster;

	virtual void DoDataExchange(CDataExchange *pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnNMDblclkListMonsterList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangingListMonsterList(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:

	enum COLUMN
	{
		COLUMN_NO,
		COLUMN_PARTY,
		COLUMN_STANDBY,
		COLUMN_NAME,
		COLUMN_SEX,
		COLUMN_RACE,
		COLUMN_LEVEL,
		COLUMN_RANK,
		COLUMN_TYPE,
		COLUMN_WEAPON,
	};

	BOOL		m_bDisablePartyMember;
	BOOL		m_bDisableStandby;
	int			m_nSelMonster;
	int			m_nPartyIndex;
	int			m_nStandbyIndex;

	int GetCurSel();
	BOOL CanSelect(int sel);

};

//////////////////////////////////////////////////////////////////////////
