
// NumberGameDlg.h : header file
//

#pragma once


// CNumberGameDlg dialog
class CNumberGameDlg : public CDialogEx
{
// Construction
public:
	CNumberGameDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NUMBERGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	enum operators
	{
		add = 1, sub = 2, mul = 3
	};
	bool answerIsRight();
	void setRandomInputs();
	int solved;
//	CString answer;
	CString answer;
	int firstN;
//	CString op;
//	CString op;
	int secondN;
	int realAnswer;
	CString op;
	int counter;
	int SecondsLeft = 6;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void lost();
	void clear();
	CString timerEdit;
	CString timeLeft;
	int lastTry = 0;
	bool isLost = false;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush leftTimeBrush;
	bool closeToLose = false;
	int secondsLeftSource;
	int highestScore;
	int secondHighestScore;
};
