
// OSdesignDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// COSdesignDlg 对话框
class COSdesignDlg : public CDialogEx
{
// 构造
public:
	COSdesignDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_OSDESIGN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedMfcpropertygrid1();
	afx_msg void OnBnClickedButton1();
private:
	CListCtrl allocation_list;
	CListCtrl need_list;
	CListCtrl available_list;
	CComboBox cbx_1;
	CComboBox cbx_2;
	CString edit_1;
	CEdit edit_4;
public:
	afx_msg void OnCbnSelchangeCombo1();
	void updateNeed(int tempNeed[][maxn], int tempMax[][maxn], int tempAllocation[][maxn]);
	bool checkSecurity();
	bool checkDeadlock();
	bool checkRequest(int num, int tempAvailable[], int tempNeed[][maxn]);
	void updateResource(int num, int tempAvailable[], int tempAllocation[][maxn], int tempNeed[][maxn]);
private:
	CEdit edit_2;
	CEdit edit_5;
	CEdit edit_6;
};
