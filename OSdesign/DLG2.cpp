// DLG2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OSdesign.h"
#include "DLG2.h"
#include "afxdialogex.h"
#include "INITDlg.h"

extern int res_num,res[10];

// CDLG2 �Ի���

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
END_MESSAGE_MAP()


// CDLG2 ��Ϣ�������




void CDLG2::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(cbx_1.GetCurSel() == -1||edit_1.IsEmpty()){
		MessageBox(TEXT("ѡ����������ݲ���Ϊ��"));
		return;
	}
	for(int i=0;i<res_num;i++){
		if(res[i]==0) {
			MessageBox(TEXT("��Դδ������ȫ"));
			return;
		}
	}
		CDialog::OnCancel();

}


void CDLG2::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	// CDialogEx::OnOK();
}


void CDLG2::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	// CDialogEx::OnCancel();
}


void CDLG2::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��Դ��ʼ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDLG2::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	//�ж������Ƿ�Խ��
	int n=_ttoi(edit_1);
	if(n<0 || n>40 ){
		MessageBox(TEXT("��Դ������ΧӦΪ1-40"));
		return;
	}
	//����
	int i=cbx_1.GetCurSel();
	res[i]=n;
	char a[2];
	a[0]='A'+i;
	a[1]='\0';
	CString str1(a),str2,str3,str4;
	str2.Format(_T("%d"),res[i]);
	edit_2.GetWindowTextW(str3);
	str4=TEXT("��Դ")+str1+TEXT("����Ϊ")+str2+TEXT("��\r\n");
	str3+=str4;
	edit_2.SetWindowTextW(str3);
}
