// INITDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OSdesign.h"
#include "INITDlg.h"
#include "afxdialogex.h"


// CINITDlg �Ի���

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


// CINITDlg ��Ϣ�������


void CINITDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
			UpdateData(TRUE);
		if(pro.IsEmpty()||res.IsEmpty()){
			MessageBox(TEXT("�������ݲ���Ϊ��"));
			return;
		}
		int num1=_ttoi(pro),num2=_ttoi(res);
		if(num1<0 || num1>10 || num2<0 || num2>10){
			MessageBox(TEXT("���뷶ΧӦΪ1-10"));
			return;
		}
		else{
		CDialog::OnCancel();
		}	
}




void CINITDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	// CDialogEx::OnCancel();
}


void CINITDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	// CDialogEx::OnOK();
}


void CINITDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	/// CDialogEx::OnClose();
	exit(0);
}
