// RESDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OSdesign.h"
#include "RESDlg.h"
#include "afxdialogex.h"

extern int res_num;
// CRESDlg �Ի���

extern int resource[10];

IMPLEMENT_DYNAMIC(CRESDlg, CDialogEx)

CRESDlg::CRESDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRESDlg::IDD, pParent)
	, num1(_T(""))
{

}

CRESDlg::~CRESDlg()
{
}

void CRESDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, cb1);
	DDX_Text(pDX, IDC_EDIT1, num1);
	DDX_Control(pDX, IDC_EDIT2, medit);
}


BEGIN_MESSAGE_MAP(CRESDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CRESDlg::OnBnClickedButton1)
	//ON_EN_CHANGE(IDC_EDIT1, &CRESDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CRESDlg ��Ϣ�������


BOOL CRESDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

//#5312

	//return TRUE;  // return TRUE unless you set the focus to a control
//#5313

//#5312

	//return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	char a[2];
	a[0]='A';
	a[1]='\0';
	for(int i=0;i<res_num;i++){
		CString str(a);
		cb1.InsertString(i,str);
		a[0]++;
	}
	//return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CRESDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int i=cb1.GetCurSel();
	resource[i]=_ttoi(num1);
	char a[2];
	a[0]='A'+i;
	a[1]='\0';
	CString str1(a),str2;
	str2.Format(_T("%d"),resource[1]);
	medit.SetWindowTextW(TEXT("��Դ")+str1+TEXT("��")+str2+TEXT(""));

}


