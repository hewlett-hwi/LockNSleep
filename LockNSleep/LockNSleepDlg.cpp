
// LockNSleepDlg.cpp : ���� ����
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
// Global ����
//////////////////////////////////////////////////////////////////////////
BOOL				g_bExit = FALSE; // ������ ����
BOOL				g_bCountThread = TRUE; // ������ �۵� ����.
UINT				CountThread(LPVOID lparam); // ī��Ʈ ������
int					nSelectCMD=0; // ��ɾ� FLAG


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CLockNSleepDlg ��ȭ ����




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


// CLockNSleepDlg �޽��� ó����

BOOL CLockNSleepDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	SetWindowText(TITLE);
	m_background.CreateSolidBrush(RGB(255, 255, 255)); // ��溯��
	static_font_edit(); // static ��Ʈ �� ũ��, ���� ����
	MakeThread(); // ������ ����
	g_bCountThread=TRUE; // ������ �÷���
	

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CLockNSleepDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CLockNSleepDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
/* ENTER, ESC ������� */
//////////////////////////////////////////////////////////////////////////
BOOL CLockNSleepDlg::PreTranslateMessage(MSG* pMsg)
{
	switch(pMsg->message)
	{
		// Ű�� ��������
	case WM_KEYDOWN:
		switch(pMsg->wParam)
		{
			// ����Ű\tab
		case VK_RETURN:
			return TRUE;
			// ESCŰ
		case VK_ESCAPE:
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


//////////////////////////////////////////////////////////////////////////
/* ������ */
//////////////////////////////////////////////////////////////////////////
HBRUSH CLockNSleepDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	hbr = (HBRUSH)m_background; // ��� ����


	// STATIC TEXT ����
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
/* static ��Ʈ �� ũ��, ���� ���� */
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
/* ��ũ�����̹� ���̱� */
//////////////////////////////////////////////////////////////////////////
void CLockNSleepDlg::OnBnClicked_Saver(void)
{
	nSelectCMD=1;
//	::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_SCREENSAVE, 0); // ��ũ�� ���̹�
	Sleep(2000);
	::PostQuitMessage(0); // ���α׷� ����
}


//////////////////////////////////////////////////////////////////////////
/* ����ϱ� */
//////////////////////////////////////////////////////////////////////////
void CLockNSleepDlg::OnBnClicked_Login(void)
{
	nSelectCMD=2;
//	if(LockWorkStation()==0) // ��� API
//		AfxMessageBox(_T("LockWorkStation Failed"));
	Sleep(2000);
	::PostQuitMessage(0); // ���α׷� ����
}


//////////////////////////////////////////////////////////////////////////
/* ����Ͳ��� */
//////////////////////////////////////////////////////////////////////////
void CLockNSleepDlg::OnBnClicked_Turnoff(void)
{
	nSelectCMD=3;
//	::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2); // ����� ����
	Sleep(2000);
	::PostQuitMessage(0); // ���α׷� ����
}


//////////////////////////////////////////////////////////////////////////
/* ����ϰ� ����� ���� */
//////////////////////////////////////////////////////////////////////////
void CLockNSleepDlg::OnBnClicked_Locknsleep(void)
{
	nSelectCMD=4;
// 	::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2); // ����� ����
// 	if(LockWorkStation()==0) // ��� API
// 		AfxMessageBox(_T("LockWorkStation Failed"));
	Sleep(2000);
	::PostQuitMessage(0); // ���α׷� ����
}


void CLockNSleepDlg::MakeThread(void)
{
	g_bCountThread=FALSE; // ó���� ���� ����
	CWinThread * pThread = NULL;

	if( !(pThread=AfxBeginThread(CountThread,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED)) )
	{		
		//		AfxMessageBox(_T("������ ���� ����"));
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

		if( g_bCountThread == FALSE ) //Thread ����.
		{
			Sleep(100);
			continue;
		}

//		lpDlg->ShowLog(_T("Thread ����!"));
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
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_SCREENSAVE, 0); // ��ũ�� ���̹�
	}
	else if(nSelectCMD==2)
	{
		if(LockWorkStation()==0) // ��� API
			AfxMessageBox(_T("LockWorkStation Failed"));
	}
	else if(nSelectCMD==3)
	{
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2); // ����� ����
	}
	else if(nSelectCMD==4)
	{
		if(LockWorkStation()==0) // ��� API
			AfxMessageBox(_T("LockWorkStation Failed"));
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2); // ����� ����
	}
/*
	if(nSelectCMD!=0) // ����
	{
		nSelectCMD=0;
		g_bExit=TRUE;
	}
*/
}
