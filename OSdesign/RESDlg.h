#pragma once
#include "afxwin.h"


// CRESDlg 对话框

class CRESDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRESDlg)

public:
	CRESDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRESDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox cb1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	CString num1;
private:
	CEdit medit;
};
