// DLG3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OSdesign.h"
#include "DLG3.h"
#include "afxdialogex.h"
#include "global.h"


// CDLG3 �Ի���

IMPLEMENT_DYNAMIC(CDLG3, CDialogEx)

CDLG3::CDLG3(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDLG3::IDD, pParent)
{

}

CDLG3::~CDLG3()
{
}

void CDLG3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, cbx_1);
	DDX_Control(pDX, IDC_COMBO2, cbx_2);
	DDX_Text(pDX, IDC_EDIT1, edit_1);
	DDX_Control(pDX, IDC_EDIT3, edit_2);
}


BEGIN_MESSAGE_MAP(CDLG3, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDLG3::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDLG3::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CDLG3::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDLG3 ��Ϣ�������


void CDLG3::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDLG3::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	//�жϽ����Ƿ񶼱�������Դ
	for(int i=0;i<pro_num;i++){
		int sum=0;
		for(int j=0;j<res_num;j++){
			sum+=m_state->max[i][j];
		}
		if(sum==0){
			MessageBox(TEXT("���ڽ���δ��������Դ"));
			return;
		}
		sum=0;
	}
		CDialog::OnCancel();
	
}


void CDLG3::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	// CDialogEx::OnOK();
}


void CDLG3::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	// CDialogEx::OnCancel();
}


void CDLG3::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	// CDialogEx::OnClose();
	exit(0);
}


void CDLG3::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);
	//�ж��Ƿ�����Ϊ��
	if(cbx_1.GetCurSel() == -1||cbx_2.GetCurSel() == -1||edit_1.IsEmpty()){
		MessageBox(TEXT("ѡ����������ݲ���Ϊ��"));
		return;
	}
	//�ж���Դ�����Ƿ�Խ��
	int n=_ttoi(edit_1);
	int i=cbx_1.GetCurSel(),j=cbx_2.GetCurSel();
	if(m_state->resource[j]<n){
		CString str;
		str.Format(_T("%d"),m_state->resource[j]);
		MessageBox(TEXT("�Ƿ����ã�����Դ����Ϊ")+str);
		return;
	}
	//����
	m_state->max[i][j]=n;
	char a[2],b[2];
	a[0]='1'+i;
	b[0]='A'+j;
	b[1]=a[1]='\0';
	CString str1(a),str2(b),str3,str4,str5;
	str3.Format(_T("%d"),m_state->max[i][j]);
	edit_2.GetWindowTextW(str4);
	str5=TEXT("����")+str1+TEXT("��Ҫ")+str2+TEXT("��Դ")+str3+TEXT("��\r\n");
	str4+=str5;
	edit_2.SetWindowTextW(str4);

}


BOOL CDLG3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

//#5312

//	return TRUE;  // return TRUE unless you set the focus to a control
//#5313

//#5312

	//return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ������������
	char a[2];
	a[0]='1';
	a[1]='\0';
	for(int i=0;i<pro_num;i++){
		CString str(a);
		cbx_1.InsertString(i,str);
		a[0]++;
	}
	//��ʼ����Դ������
	char b[2];
	b[0]='A';
	b[1]='\0';
	for(int i=0;i<res_num;i++){
		CString str(b);
		cbx_2.InsertString(i,str);
		b[0]++;
	}

	//return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
	// �쳣: OCX ����ҳӦ���� FALSE
}
