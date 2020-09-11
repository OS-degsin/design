// DLG3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OSdesign.h"
#include "DLG3.h"
#include "afxdialogex.h"
 
extern int res_num,pro_num,pro[10][10],res[10];
int c_res[10];

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
	//�ж��Ƿ�����Ϊ��
	if(cbx_1.GetCurSel() == -1||cbx_2.GetCurSel() == -1||edit_1.IsEmpty()){
		MessageBox(TEXT("ѡ����������ݲ���Ϊ��"));
		return;
	}
	//�жϽ����Ƿ񶼱�������Դ
	for(int i=0;i<pro_num;i++){
		int sum=0;
		for(int j=0;j<res_num;j++){
			sum+=pro[i][j];
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
	//�ж���Դ�����Ƿ�Խ��
	int n=_ttoi(edit_1);
	if(n<0 || n>40 ){
		MessageBox(TEXT("��Դ������ΧӦΪ1-40"));
		return;
	}
	int i=cbx_1.GetCurSel(),j=cbx_2.GetCurSel();
	//������Ӧ��Դ
	c_res[j]-=n;
	//�ж���Դ�Ƿ񱻺ľ�
	if(c_res[j]<0){
		CString str;
		c_res[j]+=n;
		str.Format(_T("%d"),c_res[j]);
		MessageBox(TEXT("�Ƿ����ã�����Դ����Ϊ")+str);
		return;
	}
	//����
	pro[i][j]=n;
	char a[2],b[2];
	a[0]='1'+i;
	b[0]='A'+j;
	b[1]=a[1]='\0';
	CString str1(a),str2(b),str3,str4,str5;
	str3.Format(_T("%d"),pro[i][j]);
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
	//����res����
	memcpy(c_res,res,10*sizeof(int));
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
