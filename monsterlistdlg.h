
#pragma once

//////////////////////////////////////////////////////////////////////////

class CMonsterListDlg : public CDialog
{
	DECLARE_DYNAMIC(CMonsterListDlg)

public:

	explicit CMonsterListDlg(CWnd *pParent = NULL);

protected:

	CListCtrl	m_lstMonster;

	virtual void DoDataExchange(CDataExchange *pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnBnClickedButtonMonsterUp();
	afx_msg void OnBnClickedButtonMonsterTop();
	afx_msg void OnBnClickedButtonMonsterDown();
	afx_msg void OnBnClickedButtonMonsterBottom();
	afx_msg void OnBnClickedButtonMonsterAdd();
	afx_msg void OnBnClickedButtonMonsterModify();
	afx_msg void OnBnClickedButtonMonsterRemove();
	afx_msg void OnBnClickedButtonMonsterCopy();
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

	int GetCurSel();
	void UpdateMonsterList();
	void RedrawMonsterList(int sel);
	void RefreshMonsterSel(int sel);
	void AddMonster();
	void ModifyMonster(int sel);
	void RemoveMonster(int sel);
	void CopyMonster(int sel);
	void MoveMonster(int sel, int idx);

};

//////////////////////////////////////////////////////////////////////////
