
// LockNSleep.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CLockNSleepApp:
// �� Ŭ������ ������ ���ؼ��� LockNSleep.cpp�� �����Ͻʽÿ�.
//

class CLockNSleepApp : public CWinApp
{
public:
	CLockNSleepApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CLockNSleepApp theApp;