
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

	DECLARE_MESSAGE_MAP()

private:

	void RefreshBriefing(DQMJ_SAVE_BRIEFING &briefing);
	void RefreshPlayInfo(DQMJ_SAVE_PLAY_INFO &playinfo);
	void RefreshItemInfo(DQMJ_SAVE_ITEM_INFO &iteminfo);
	void RefreshRanchInfo(DQMJ_SAVE_RANCH_INFO &ranchinfo);
	void EnableAll(BOOL enable);
	void UpdateSaveData();

	static CString GetStoryString(int story);
	static CString GetPlaceString(int place);
	static CString GetTimeString(int hour, int minute, int second);
	static CString GetLevelString(int level);
	static CString GetRaceString(int race);
	static CString GetMonsterNumString(int monster_num);

};

//////////////////////////////////////////////////////////////////////////
