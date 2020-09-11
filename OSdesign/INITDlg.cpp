// INITDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OSdesign.h"
#include "INITDlg.h"
#include "afxdialogex.h"


// CINITDlg 对话框

IMPLEMENT_DYNAMIC(CINITDlg, CDialogEx)

CINITDlg::CINITDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CINITDlg::IDD, pParent)
	, pro(_T(""))
	, res(_T(""))
{

}

CINITDlg::~CINITDlg()
{
}

void CINITDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, pro);
	DDX_Text(pDX, IDC_EDIT2, res);
}


BEGIN_MESSAGE_MAP(CINITDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CINITDlg::OnBnClickedButton1)
	// ON_BN_CLICKED(IDC_BUTTON2, &CINITDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CINITDlg 消息处理程序


void CINITDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
		UpdateData(TRUE);

		if(pro.IsEmpty()||res.IsEmpty()){
			MessageBox(TEXT("输入内容不能为空"));
			return;
		}
		int num_pro=_ttoi(pro),num_res=_ttoi(res);
		if(num_pro<0 || num_pro>10 || num_res<0 || num_res>10){
			MessageBox(TEXT("输入范围应为1-10"));
			return;
		}
		else{
		CDialog::OnCancel();
		}	
}




void CINITDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	// CDialogEx::OnCancel();
}


void CINITDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	// CDialogEx::OnOK();
}


void CINITDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	/// CDialogEx::OnClose();
	exit(0);
}
