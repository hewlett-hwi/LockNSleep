
// LockNSleepDlg.h : ��� ����
//

#pragma once


// CLockNSleepDlg ��ȭ ����
class CLockNSleepDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CLockNSleepDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	virtual BOOL PreTranslateMessage(MSG* pMsg); // esc enter ������������� �߰�
	CBrush   m_background; // ���̾�α� ���� �ٲٱ� ���Ͽ�

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOCKNSLEEP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
