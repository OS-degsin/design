// FIRDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OSdesign.h"
#include "FIRDlg.h"
#include "afxdialogex.h"
#include "INITDlg.h"

extern CString pro,res;

// CFIRDlg �Ի���

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


// CFIRDlg ��Ϣ�������


void CFIRDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/*CString s;
	s.Format(_T("�����ǣ�%d"),pro_num);
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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString st("A");
	for(int i=0;i<res_num;i++){
		cbx1.InsertString(i,st);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	// �쳣: OCX ����ҳӦ���� FALSE
}*/
