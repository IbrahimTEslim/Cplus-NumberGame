
// NumberGameDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "NumberGame.h"
#include "NumberGameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNumberGameDlg dialog



CNumberGameDlg::CNumberGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NUMBERGAME_DIALOG, pParent)
	, answer(_T(""))
	, firstN(0)


	, secondN(0)
	, op(_T(""))
	, counter(0)
	, timerEdit(_T(""))
	, timeLeft(_T(""))
	, lastTry(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	solved = 0;
	realAnswer = 0;
	secondsLeftSource = 0;
}

void CNumberGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, answer);
	DDX_Text(pDX, IDC_EDIT1, answer);
	DDX_Text(pDX, IDC_FirstN, firstN);
	//  DDX_Text(pDX, IDC_Opt, op);
	DDX_Text(pDX, IDC_SecondN, secondN);
	DDX_Text(pDX, IDC_Opt, op);
	DDX_Text(pDX, IDC_Counter, counter);
	DDX_Text(pDX, IDC_EDIT2, timerEdit);
	DDX_Text(pDX, IDC_EDIT3, timeLeft);
	DDX_Text(pDX, IDC_EDIT4, lastTry);
	DDX_Text(pDX, IDC_EDIT5, highestScore);

}

BEGIN_MESSAGE_MAP(CNumberGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNumberGameDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CNumberGameDlg message handlers

BOOL CNumberGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	leftTimeBrush.CreateSolidBrush(RGB(255, 0, 0));


	CFont font;

	//font.CreatePointFont(1500, L"Garamond");
	font.CreateFont(23, 0, 0, 0, 900, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"Arial");


	setRandomInputs();

	secondsLeftSource = 6;
	highestScore = 0;

	GetDlgItem(IDC_Counter)->SetFont(&font, TRUE);
	GetDlgItem(IDC_EDIT1)->SetFont(&font);
	GetDlgItem(IDC_EDIT2)->SetFont(&font);
	GetDlgItem(IDC_EDIT3)->SetFont(&font);

	font.DeleteObject();

	font.CreatePointFont(1500, L"Arial",NULL);

	GetDlgItem(IDC_FirstN)->SetFont(&font);
	GetDlgItem(IDC_Opt)->SetFont(&font);
	GetDlgItem(IDC_SecondN)->SetFont(&font);


	GetDlgItem(IDC_NAME)->SetFont(&font);

	font.DeleteObject();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNumberGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNumberGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNumberGameDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(1);
	SetTimer(1, 1000, NULL);
	if (isLost) {
		/*lost();*/
		SetTimer(2, 1000, NULL);
		isLost = false;
	}
	if (answerIsRight()) {
		counter = ++solved;

		if (solved % 10 == 0) { secondsLeftSource += 3; }


		SetTimer(2, 1000, NULL);
		SecondsLeft = secondsLeftSource;

		setRandomInputs();

		if (solved > highestScore) {
			highestScore = solved; 
		}
		UpdateData(0);
	}
	else lost();

	GetDlgItem(IDC_EDIT1)->SetWindowText(L"");
}

bool CNumberGameDlg::answerIsRight() {
	UpdateData(1);
	int intAnswer = _ttoi(answer);

	char temp = op.GetAt(0);
	switch (temp)
	{
	case '+':
		realAnswer = firstN + secondN;
		break;
	case '-':
		realAnswer = firstN - secondN;
		break;
	case '*':
		realAnswer = firstN * secondN;
	}

	return realAnswer == intAnswer;
}

void CNumberGameDlg::setRandomInputs() {
	srand(time(0));
	firstN = rand() % ((solved + 1) * 10);
	secondN = rand() % ((solved + 1) * 10);
	switch ((rand() % 4) + 1)
	{
	case 1:
		op = L"+";
		break;
	case 2:
		op = L"-";
		if (firstN < secondN) {
			int temp = firstN;
			firstN = secondN;
			secondN = temp;
		}
		break;
	case 3:
		op = L"*";
		if (firstN < secondN) {
			firstN = (rand() % 10) + 1;
		}
		else secondN = (rand() % 10) + 1;
		SecondsLeft += (solved / 10) + 2;
		break;
	default:
		op = L"+";
	}
	UpdateData(0);

}

int iHours = 0;
int iMinutes = 0;
int iSeconds = 0;
void CNumberGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		iSeconds++;
		if (iSeconds == 60) {
			iSeconds = 0;
			iMinutes++;
		}
		if (iMinutes == 60) {
			iMinutes = 0;
			iHours++;
		}
		CString strHours, strMinutes, strSeconds;

		if (iHours < 10)
			strHours.Format(_T("0%d"), iHours);
		else
			strHours.Format(_T("%d"), iHours);

		if (iMinutes < 10)
			strMinutes.Format(_T("0%d"), iMinutes);
		else
			strMinutes.Format(_T("%d"), iMinutes);

		if (iSeconds < 10)
			strSeconds.Format(_T("0%d"), iSeconds);
		else
			strSeconds.Format(_T("%d"), iSeconds);

		//timerEdit.Format(_T("%s:%s:%s"), strHours, strMinutes, strSeconds);
		CString timerEditStr;
		timerEditStr.Format(_T("%s:%s:%s"), strHours, strMinutes, strSeconds);
		GetDlgItem(IDC_EDIT2)->SetWindowText(timerEditStr);
	}
	if (nIDEvent == 2) {
		if (SecondsLeft <= 0) {
			KillTimer(2);
			OnBnClickedOk();
		}
		
		SecondsLeft--;
		CString timeLeftStr, strSceonds;
		strSceonds.Format(L"%d", SecondsLeft);
		timeLeftStr.Format(L"%s", strSceonds);
		GetDlgItem(IDC_EDIT3)->SetWindowText(timeLeftStr);
	}
	CDialogEx::OnTimer(nIDEvent);
}
void CNumberGameDlg::lost() {
	//if (isLost) { isLost = false; return; }
	
	if (solved > highestScore) { 
		secondHighestScore = highestScore;
		highestScore = solved; 
	}
	KillTimer(1);
	KillTimer(2);
	isLost = true;
	CString lostMsg;
	if (highestScore > secondHighestScore) {
		lostMsg.Format(L"New Record, the Correct Answer is: (%d)\nYour Level (%d)\nNew High Score, Keep going",realAnswer,solved);
		MessageBox(lostMsg, L"Headway", NULL);
		MessageBeep(1);
	}
	else {
		lostMsg.Format(L"Wrong Answer, the Correct is: (%d)\n Your Level: (%d) ", realAnswer, solved);
		MessageBox(lostMsg, L"Faild", NULL);
	}
	secondsLeftSource = 6;
	clear();
 }

void CNumberGameDlg::clear() {
	lastTry = solved;
	solved = 0;
	answer = L"";
	timeLeft = L"";
	timerEdit = L"";
	counter = 0;
	setRandomInputs();
	UpdateData(0);
}

//Not In Use
HBRUSH CNumberGameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
