
// OSdesign.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <algorithm>
#include <iterator>
#include <iostream>
#include <queue>
#include <stack>
#define  maxn 10

// COSdesignApp:
// �йش����ʵ�֣������ OSdesign.cpp
//

class COSdesignApp : public CWinApp
{
public:
	COSdesignApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern COSdesignApp theApp;

