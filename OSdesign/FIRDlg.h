#pragma once
#include "afxwin.h"


// CFIRDlg �Ի���

class CFIRDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFIRDlg)

public:
	CFIRDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFIRDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	int pro_num,res_num;
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox cbx1;
	virtual BOOL OnInitDialog();
};
