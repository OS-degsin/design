#pragma once
#include "afxwin.h"


// CDLG3 �Ի���

class CDLG3 : public CDialogEx
{
	DECLARE_DYNAMIC(CDLG3)

public:
	CDLG3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLG3();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox cbx_1;
private:
	CComboBox cbx_2;
public:
	CString edit_1;
private:
	CEdit edit_2;
public:
	afx_msg void OnBnClickedButton2();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
