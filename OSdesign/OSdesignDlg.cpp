
// OSdesignDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OSdesign.h"
#include "OSdesignDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int pro_num,res_num,available[10],max[10][10],allocation[10][10],need[10][10];

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COSdesignDlg �Ի���



COSdesignDlg::COSdesignDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COSdesignDlg::IDD, pParent)
	, edit_1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void COSdesignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST8, allocation_list);
	DDX_Control(pDX, IDC_LIST11, need_list);
	DDX_Control(pDX, IDC_LIST9, available_list);
	DDX_Control(pDX, IDC_COMBO1, cbx_1);
	DDX_Control(pDX, IDC_COMBO2, cbx_2);
	DDX_Text(pDX, IDC_EDIT1, edit_1);
	DDX_Control(pDX, IDC_EDIT4, edit_4);
}

BEGIN_MESSAGE_MAP(COSdesignDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_STN_CLICKED(IDC_MFCPROPERTYGRID1, &COSdesignDlg::OnStnClickedMfcpropertygrid1)
	ON_BN_CLICKED(IDC_BUTTON1, &COSdesignDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &COSdesignDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// COSdesignDlg ��Ϣ�������

BOOL COSdesignDlg::OnInitDialog()
{
	SetWindowText(_T("���������ָ�"));
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// allocation�����ʼ��
	memset(allocation,0,sizeof(allocation));
	memcpy(need,max,sizeof(max));
	// allocation������ʾ
	allocation_list.InsertColumn(0,TEXT(""),LVCFMT_LEFT,50);
	for (int i=1;i<=pro_num;i++)
	{
		CString str;
		str.Format(_T("%d"),i);
		allocation_list.InsertColumn(i,TEXT("����")+str,LVCFMT_LEFT,50);
	}
	for(int i=0;i<res_num;i++){
		CString res1,str1;
		res1.Format(_T("%c"),65+i);
		allocation_list.InsertItem(i,res1);
		for(int j=1;j<=pro_num;j++){
			str1.Format(_T("%d"),allocation[j-1][i]);
			allocation_list.SetItemText(i,j,str1);
		}	
	}
	// need������ʾ
	need_list.InsertColumn(0,TEXT(""),LVCFMT_LEFT,50);
	for (int i=1;i<=pro_num;i++)
	{
		CString str;
		str.Format(_T("%d"),i);
		need_list.InsertColumn(i,TEXT("����")+str,LVCFMT_LEFT,50);
	}
	for(int i=0;i<res_num;i++){
		CString res2,str2;
		res2.Format(_T("%c"),65+i);
		need_list.InsertItem(i,res2);
		for(int j=1;j<=pro_num;j++){
			str2.Format(_T("%d"),max[j-1][i]);
			need_list.SetItemText(i,j,str2);
		}	
	}
	// available����չʾ
	for (int i=0;i<res_num;i++)
	{
		CString str;
		str.Format(_T("%c"),65+i);
		available_list.InsertColumn(i,TEXT("��Դ")+str,LVCFMT_LEFT,60);
	}
	CString str3;
	str3.Format(_T("%d"),available[0]);
	available_list.InsertItem(0,str3);
	for(int i=1;i<res_num;i++){
		
		str3.Format(_T("%d"),available[i]);
		available_list.SetItemText(0,i,str3);
	}
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void COSdesignDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COSdesignDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COSdesignDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void COSdesignDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(cbx_1.GetCurSel() == -1||cbx_2.GetCurSel() == -1||edit_1.IsEmpty()){
		MessageBox(TEXT("ѡ����������ݲ���Ϊ��"));
		return;
	}
	//�ж���Դ�����Ƿ�Խ��
	int n=_ttoi(edit_1);
	int i=cbx_1.GetCurSel(),j=cbx_2.GetCurSel();
		if(available[j]<n){
		CString str;
		str.Format(_T("%d"),available[j]);
		MessageBox(TEXT("�Ƿ����ã�����Դ����Ϊ")+str);
		return;
	}

	char a[2],b[2];
	a[0]='1'+i;
	b[0]='A'+j;
	b[1]=a[1]='\0';
	CString str1(a),str2(b),str3,str4,str5;
	str3.Format(_T("%d"),n);
	edit_4.GetWindowTextW(str4);
	str5=TEXT("����")+str1+TEXT("����")+str2+TEXT("��Դ����Ϊ")+str3+TEXT("��\r\n");
	str4+=str5;
	edit_4.SetWindowTextW(str4);


	//����allocation����
	CString str6;
	allocation[i][j]+=n;
	str6.Format(_T("%d"),allocation[i][j]);
	allocation_list.SetItemText(j,i+1,str6);

	//����need����
	CString str7;
	need[i][j]=max[i][j]-allocation[i][j];
	str7.Format(_T("%d"),need[i][j]);
	need_list.SetItemText(j,i+1,str7);
	
	//����available��Դ
	CString str8;
	available[j]-=n;
	str8.Format(_T("%d"),available[j]);
	available_list.SetItemText(0,j,str8);
}


void COSdesignDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
