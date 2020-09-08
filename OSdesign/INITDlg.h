#pragma once


// CINITDlg 对话框

class CINITDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CINITDlg)

public:
	CINITDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CINITDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
