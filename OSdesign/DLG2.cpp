// DLG2.cpp : 实现文件
//

#include "stdafx.h"
#include "OSdesign.h"
#include "DLG2.h"
#include "afxdialogex.h"
#include "INITDlg.h"
#include "afxwin.h"
extern int res_num,available[10];

// CDLG2 对话框

IMPLEMENT_DYNAMIC(CDLG2, CDialogEx)

CDLG2::CDLG2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDLG2::IDD, pParent)
	, edit_1(_T(""))
{

}

CDLG2::~CDLG2()
{
}

void CDLG2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, cbx_1);
	DDX_Text(pDX, IDC_EDIT1, edit_1);
	DDX_Control(pDX, IDC_EDIT2, edit_2);
}


BEGIN_MESSAGE_MAP(CDLG2, CDialogEx)
	// ON_BN_CLICKED(IDC_BUTTON3, &CDLG2::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDLG2::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CDLG2::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CDLG2::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CDLG2 消息处理程序




void CDLG2::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	for(int i=0;i<res_num;i++){
		if(available[i]==0) {
			MessageBox(TEXT("资源未设置完全"));
			return;
		}
	}
	/*
	//判断输入是否越界
	int n=_ttoi(edit_1);
	//更新
	int i=cbx_1.GetCurSel();
	available[i]=n;
	char a[2];
	a[0]='A'+i;
	a[1]='\0';
	CString str,str1(a),str2,str3,str4;
	str2.Format(_T("%d"),available[i]);
	edit_2.GetWindowTextW(str3);
	str4=TEXT("资源")+str1+TEXT("设置为")+str2+TEXT("个\r\n");
	//str3+=str4;
	//edit_2.SetWindowTextW(str3);
	
	if(IDOK ==MessageBox(NULL,str3,MB_OKCANCEL))
	{*/
		CDialog::OnCancel();
	//}

}


void CDLG2::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	// CDialogEx::OnOK();
}


void CDLG2::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	// CDialogEx::OnCancel();
}


void CDLG2::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// CDialogEx::OnClose();
	exit(0);
}


BOOL CDLG2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

//#5312

//	return TRUE;  // return TRUE unless you set the focus to a control
//#5313

//#5312

	//return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	// TODO:  在此添加额外的初始化
	//资源初始化
	char a[2];
	a[0]='A';
	a[1]='\0';
	for(int i=0;i<res_num;i++){
		CString str(a);
		cbx_1.InsertString(i,str);
		a[0]++;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	// 异常: OCX 属性页应返回 FALSE
}


void CDLG2::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(cbx_1.GetCurSel() == -1||edit_1.IsEmpty()){
		MessageBox(TEXT("选项或输入内容不能为空"));
		return;
	}
	//判断输入是否越界
	int n=_ttoi(edit_1);
	if(n<0 || n>40 ){
		MessageBox(TEXT("资源数量范围应为1-40"));
		return;
	}
	//更新
	int i=cbx_1.GetCurSel();
	available[i]=n;
	char a[2];
	a[0]='A'+i;
	a[1]='\0';
	CString str1(a),str2,str3,str4;
	str2.Format(_T("%d"),available[i]);
	edit_2.GetWindowTextW(str3);
	str4=TEXT("资源")+str1+TEXT("设置为")+str2+TEXT("个\r\n");
	str3+=str4;
	edit_2.SetWindowTextW(str3);

	
}


void CDLG2::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
}
