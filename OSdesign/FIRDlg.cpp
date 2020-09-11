// FIRDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OSdesign.h"
#include "FIRDlg.h"
#include "afxdialogex.h"
#include "INITDlg.h"

extern CString pro,res;

// CFIRDlg 对话框

IMPLEMENT_DYNAMIC(CFIRDlg, CDialogEx)

CFIRDlg::CFIRDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFIRDlg::IDD, pParent)
{

}

CFIRDlg::~CFIRDlg()
{
}

void CFIRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, cbx1);
}


BEGIN_MESSAGE_MAP(CFIRDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CFIRDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CFIRDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CFIRDlg 消息处理程序


void CFIRDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	/*CString s;
	s.Format(_T("整数是：%d"),pro_num);
	MessageBox(s);*/
	UpdateWindow();
}





/*BOOL CFIRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

//#5312

	return TRUE;  // return TRUE unless you set the focus to a control
//#5313

//#5312

	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	// TODO:  在此添加额外的初始化
	CString st("A");
	for(int i=0;i<res_num;i++){
		cbx1.InsertString(i,st);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	// 异常: OCX 属性页应返回 FALSE
}*/
