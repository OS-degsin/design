#pragma once
#include "afxwin.h"


// CDLG2 �Ի���

class CDLG2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDLG2)

public:
	CDLG2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLG2();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
private:
	CComboBox cbx_1;
	CString edit_1;
	CEdit edit_2;
public:
	afx_msg void OnBnClickedButton2();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit2();
};
