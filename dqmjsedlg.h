
#pragma once

//////////////////////////////////////////////////////////////////////////

class CDqmjSEDlg : public CDialog
{
	DECLARE_DYNAMIC(CDqmjSEDlg)

public:

	explicit CDqmjSEDlg(CWnd *pParent = NULL);

	BOOL OpenFile(LPCTSTR pszFilename);
	void CloseFile();

protected:

	int			m_nGold;
	int			m_nDeposit;
	int			m_nVictoryTimes;
	int			m_nScoutTimes;
	int			m_nCombineTimes;
	int			m_nHour;
	int			m_nMinute;
	int			m_nSecond;
	HICON		m_hIcon;
	HACCEL		m_hAccel;
	CString		m_strPlayerName;

	virtual void DoDataExchange(CDataExchange *pDX);
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnFileOpen();
	afx_msg void OnFileClose();
	afx_msg void OnEditItemList();
	afx_msg void OnEditMonsterList();
	afx_msg void OnBnClickedCheckSkillbookInitflag();
	afx_msg void OnBnClickedButtonPartyExchange1() { ExchangeMember(TRUE, 0); }
	afx_msg void OnBnClickedButtonPartyExchange2() { ExchangeMember(TRUE, 1); }
	afx_msg void OnBnClickedButtonPartyExchange3() { ExchangeMember(TRUE, 2); }
	afx_msg void OnBnClickedButtonStandbyExchange1() { ExchangeMember(FALSE, 0); }
	afx_msg void OnBnClickedButtonStandbyExchange2() { ExchangeMember(FALSE, 1); }
	afx_msg void OnBnClickedButtonStandbyExchange3() { ExchangeMember(FALSE, 2); }
	afx_msg void OnBnClickedButtonPartyRemove1() { RemoveMember(TRUE, 0); }
	afx_msg void OnBnClickedButtonPartyRemove2() { RemoveMember(TRUE, 1); }
	afx_msg void OnBnClickedButtonPartyRemove3() { RemoveMember(TRUE, 2); }
	afx_msg void OnBnClickedButtonStandbyRemove1() { RemoveMember(FALSE, 0); }
	afx_msg void OnBnClickedButtonStandbyRemove2() { RemoveMember(FALSE, 1); }
	afx_msg void OnBnClickedButtonStandbyRemove3() { RemoveMember(FALSE, 2); }
	afx_msg void OnBnClickedButtonPartyEdit1() { EditMember(TRUE, 0); }
	afx_msg void OnBnClickedButtonPartyEdit2() { EditMember(TRUE, 1); }
	afx_msg void OnBnClickedButtonPartyEdit3() { EditMember(TRUE, 2); }
	afx_msg void OnBnClickedButtonStandbyEdit1() { EditMember(FALSE, 0); }
	afx_msg void OnBnClickedButtonStandbyEdit2() { EditMember(FALSE, 1); }
	afx_msg void OnBnClickedButtonStandbyEdit3() { EditMember(FALSE, 2); }

	DECLARE_MESSAGE_MAP()

private:

	BOOL RefreshBriefing();
	BOOL RefreshPlayInfo();
	BOOL RefreshBookInfo();
	BOOL RefreshRanchInfo();
	void EnableAll(BOOL enable);
	void UpdateSaveData();
	void ExchangeMember(BOOL party_or_standby, int idx);
	void RemoveMember(BOOL party_or_standby, int idx);
	void EditMember(BOOL party_or_standby, int idx);

	static CString GetStoryString(int story);
	static CString GetPlaceString(int place);
	static CString GetTimeString(int hour, int minute, int second);
	static CString GetLevelString(int level);
	static CString GetRaceString(int race);
	static CString GetMonsterNumString(int monster_num);

};

//////////////////////////////////////////////////////////////////////////
