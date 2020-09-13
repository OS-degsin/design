
// OSdesignDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// COSdesignDlg �Ի���
class COSdesignDlg : public CDialogEx
{
// ����
public:
	COSdesignDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OSDESIGN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
