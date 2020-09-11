#pragma once
#include "afxwin.h"


// CFIRDlg 对话框

class CFIRDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFIRDlg)

public:
	CFIRDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFIRDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	int pro_num,res_num;
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox cbx1;
	virtual BOOL OnInitDialog();
};
