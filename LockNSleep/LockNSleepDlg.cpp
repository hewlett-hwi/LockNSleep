
// LockNSleepDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "LockNSleep.h"
#include "LockNSleepDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TITLE _T("LockNSleep ver 1.1")
//////////////////////////////////////////////////////////////////////////
// Global 변수
//////////////////////////////////////////////////////////////////////////
BOOL				g_bExit = FALSE; // 스레드 종료
BOOL				g_bCountThread = TRUE; // 스레드 작동 여부.
UINT				CountThread(LPVOID lparam); // 카운트 스레드
int					nSelectCMD=0; // 명령어 FLAG


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLockNSleepDlg 대화 상자




CLockNSleepDlg::CLockNSleepDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLockNSleepDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLockNSleepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLockNSleepDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_STATIC_Sav, &CLockNSleepDlg::OnBnClicked_Saver)
	ON_BN_CLICKED(IDC_STATIC_Login, &CLockNSleepDlg::OnBnClicked_Login)
	ON_BN_CLICKED(IDC_STATIC_Turnoff, &CLockNSleepDlg::OnBnClicked_Turnoff)
	ON_BN_CLICKED(IDC_STATIC_LockNSleep, &CLockNSleepDlg::OnBnClicked_Locknsleep)
END_MESSAGE_MAP()


// CLockNSleepDlg 메시지 처리기

BOOL CLockNSleepDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	SetWindowText(TITLE);
	m_background.CreateSolidBrush(RGB(255, 255, 255)); // 배경변경
	static_font_edit(); // static 폰트 및 크기, 색상 변경
	MakeThread(); // 스레드 생성
	g_bCountThread=TRUE; // 스레드 플레그
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CLockNSleepDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CLockNSleepDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CLockNSleepDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
/* ENTER, ESC 종료방지 */
//////////////////////////////////////////////////////////////////////////
BOOL CLockNSleepDlg::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
		// 키가 눌렸을때
	case WM_KEYDOWN:
		switch(pMsg->wParam)
		{
			// 리턴키\tab
		case VK_RETURN:
			return TRUE;
			// ESC키
		case VK_ESCAPE:
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


//////////////////////////////////////////////////////////////////////////
/* 색변경 */
//////////////////////////////////////////////////////////////////////////
HBRUSH CLockNSleepDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	hbr = (HBRUSH)m_background; // 배경 변경


	// STATIC TEXT 변경
	if(pWnd->GetDlgCtrlID() == IDC_STATIC_TEXT_1)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);;
	}

	if(pWnd->GetDlgCtrlID() == IDC_STATIC_TEXT_2)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);;
	}

	if(pWnd->GetDlgCtrlID() == IDC_STATIC_TEXT_3)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);;
	}

	if(pWnd->GetDlgCtrlID() == IDC_STATIC_TEXT_4)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);;
	}

	if(pWnd->GetDlgCtrlID() == IDC_STATIC_TITLE)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);;
	}

	return hbr;
}

//////////////////////////////////////////////////////////////////////////
/* static 폰트 및 크기, 색상 변경 */
//////////////////////////////////////////////////////////////////////////
void CLockNSleepDlg::static_font_edit(void)
{
	CFont fnt;
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 14;
	lf.lfWeight = FW_BOLD;
	::lstrcpy(lf.lfFaceName, (LPCWSTR)"Tahoma");
	fnt.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&fnt);
	fnt.Detach();
}


//////////////////////////////////////////////////////////////////////////
/* 스크린세이버 보이기 */
//////////////////////////////////////////////////////////////////////////
void CLockNSleepDlg::OnBnClicked_Saver(void)
{
	nSelectCMD=1;
//	::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_SCREENSAVE, 0); // 스크린 세이버
	Sleep(2000);
	::PostQuitMessage(0); // 프로그램 종료
}


//////////////////////////////////////////////////////////////////////////
/* 잠금하기 */
//////////////////////////////////////////////////////////////////////////
void CLockNSleepDlg::OnBnClicked_Login(void)
{
	nSelectCMD=2;
//	if(LockWorkStation()==0) // 잠금 API
//		AfxMessageBox(_T("LockWorkStation Failed"));
	Sleep(2000);
	::PostQuitMessage(0); // 프로그램 종료
}


//////////////////////////////////////////////////////////////////////////
/* 모니터끄기 */
//////////////////////////////////////////////////////////////////////////
void CLockNSleepDlg::OnBnClicked_Turnoff(void)
{
	nSelectCMD=3;
//	::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2); // 모니터 끄기
	Sleep(2000);
	::PostQuitMessage(0); // 프로그램 종료
}


//////////////////////////////////////////////////////////////////////////
/* 잠금하고 모니터 끄기 */
//////////////////////////////////////////////////////////////////////////
void CLockNSleepDlg::OnBnClicked_Locknsleep(void)
{
	nSelectCMD=4;
// 	::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2); // 모니터 끄기
// 	if(LockWorkStation()==0) // 잠금 API
// 		AfxMessageBox(_T("LockWorkStation Failed"));
	Sleep(2000);
	::PostQuitMessage(0); // 프로그램 종료
}


void CLockNSleepDlg::MakeThread(void)
{
	g_bCountThread=FALSE; // 처음엔 시작 안함
	CWinThread * pThread = NULL;

	if( !(pThread=AfxBeginThread(CountThread,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED)) )
	{		
		//		AfxMessageBox(_T("스레드 생성 실패"));
	}						
	VERIFY(pThread->SetThreadPriority(THREAD_PRIORITY_NORMAL));
	pThread->ResumeThread();
}

UINT CountThread(LPVOID lparam)
{
	CLockNSleepDlg* lpDlg = (CLockNSleepDlg*)AfxGetApp()->GetMainWnd();
	DWORD           dwExitCode = 0L,dwTime=0L;

	while(!g_bExit)
	{

		if( g_bCountThread == FALSE ) //Thread 안함.
		{
			Sleep(100);
			continue;
		}

//		lpDlg->ShowLog(_T("Thread 시작!"));
		lpDlg->Core_Thread();

	}

	::GetExitCodeThread(AfxGetThread()->m_hThread, &dwExitCode );
	AfxEndThread(dwExitCode );
	return dwExitCode ;
}


void CLockNSleepDlg::Core_Thread(void)
{
	if(nSelectCMD==1)
	{
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_SCREENSAVE, 0); // 스크린 세이버
	}
	else if(nSelectCMD==2)
	{
		if(LockWorkStation()==0) // 잠금 API
			AfxMessageBox(_T("LockWorkStation Failed"));
	}
	else if(nSelectCMD==3)
	{
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2); // 모니터 끄기
	}
	else if(nSelectCMD==4)
	{
		if(LockWorkStation()==0) // 잠금 API
			AfxMessageBox(_T("LockWorkStation Failed"));
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2); // 모니터 끄기
	}
/*
	if(nSelectCMD!=0) // 종료
	{
		nSelectCMD=0;
		g_bExit=TRUE;
	}
*/
}
