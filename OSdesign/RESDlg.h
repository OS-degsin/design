#pragma once
#include "afxwin.h"


// CRESDlg �Ի���

class CRESDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRESDlg)

public:
	CRESDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRESDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
