
// SB_GDB_UPLOAD_TOOL.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSB_GDB_UPLOAD_TOOLApp:
// �йش����ʵ�֣������ SB_GDB_UPLOAD_TOOL.cpp
//

class CSB_GDB_UPLOAD_TOOLApp : public CWinApp
{
public:
	CSB_GDB_UPLOAD_TOOLApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSB_GDB_UPLOAD_TOOLApp theApp;