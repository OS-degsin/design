#pragma once


// CINITDlg �Ի���

class CINITDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CINITDlg)

public:
	CINITDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CINITDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString pro;
	CString res;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnClose();
};
