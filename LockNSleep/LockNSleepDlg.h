
// LockNSleepDlg.h : 헤더 파일
//

#pragma once


// CLockNSleepDlg 대화 상자
class CLockNSleepDlg : public CDialogEx
{
// 생성입니다.
public:
	CLockNSleepDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg); // esc enter 종료방지때문에 추가
	CBrush   m_background; // 다이얼로그 배경색 바꾸기 위하여

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOCKNSLEEP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void static_font_edit(void);
	afx_msg void OnBnClicked_Saver(void);
	afx_msg void OnBnClicked_Login(void);
	afx_msg void OnBnClicked_Turnoff(void);
	afx_msg void OnBnClicked_Locknsleep(void);
	void MakeThread(void);
	void Core_Thread(void);
};
