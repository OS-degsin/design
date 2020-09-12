
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
	DDX_Control(pDX, IDC_EDIT2, edit_2);
	DDX_Control(pDX, IDC_EDIT5, edit_5);
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
	CString str,res,pro;
	allocation_list.InsertColumn(0,TEXT(""),LVCFMT_LEFT,50);
	for (int i=1;i<=pro_num;i++)
	{
		str.Format(_T("%d"),i);
		allocation_list.InsertColumn(i,TEXT("����")+str,LVCFMT_LEFT,50);
	}
	for(int i=0;i<res_num;i++){
		res.Format(_T("%c"),65+i);
		allocation_list.InsertItem(i,res);
		for(int j=1;j<=pro_num;j++){
			str.Format(_T("%d"),allocation[j-1][i]);
			allocation_list.SetItemText(i,j,str);
		}	
	}
	// need������ʾ
	need_list.InsertColumn(0,TEXT(""),LVCFMT_LEFT,50);
	for (int i=1;i<=pro_num;i++)
	{
		str.Format(_T("%d"),i);
		need_list.InsertColumn(i,TEXT("����")+str,LVCFMT_LEFT,50);
	}
	for(int i=0;i<res_num;i++){
		res.Format(_T("%c"),65+i);
		need_list.InsertItem(i,res);
		for(int j=1;j<=pro_num;j++){
			str.Format(_T("%d"),max[j-1][i]);
			need_list.SetItemText(i,j,str);
		}	
	}
	// available����չʾ
	for (int i=0;i<res_num;i++)
	{
		str.Format(_T("%c"),65+i);
		available_list.InsertColumn(i,TEXT("��Դ")+str,LVCFMT_LEFT,60);
	}
	str.Format(_T("%d"),available[0]);
	available_list.InsertItem(0,str);
	for(int i=1;i<res_num;i++){
		str.Format(_T("%d"),available[i]);
		available_list.SetItemText(0,i,str);
	}
	//��ʼ������������
	char a[2];
	a[0]='1';
	a[1]='\0';
	for(int i=0;i<pro_num;i++){
		str=a;
		cbx_1.InsertString(i,str);
		a[0]++;
	}
	//��ʼ����Դ������
	char b[2];
	b[0]='A';
	b[1]='\0';
	for(int i=0;i<res_num;i++){
		str=b;
		cbx_2.InsertString(i,str);
		b[0]++;
	}
	//��ʼ����ȫ��״̬�밲ȫ����
	edit_2.SetWindowTextW(TEXT("��ȫ"));
	str="";
	for(int i=1;i<=pro_num;i++){
		if(i==pro_num){
			pro.Format(_T(" ����%d"),i);
			str+=pro;
		}
		else {
			pro.Format(_T("����%d ->"),i);
			str+=pro;
		}
	}
	edit_5.SetWindowTextW(str);

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


//�ú��������а�ȫ��⣬ȷ�Ͽ��Ը����ٵ���
void updateNeed(int tempNeed[][maxn], int tempMax[][maxn], int tempAllocation[][maxn]) {
	for (int i = 0; i < pro_num; i++) {
		for (int j = 0; j < res_num; j++) {
			tempNeed[i][j] = tempMax[i][j] - tempAllocation[i][j];
		}
	}
}

//����˵���������±꣬available������need����
bool checkRequest(int num, int tempAvailable[], int tempNeed[][maxn]) {
	for (int j = 0; j < res_num; j++) {
		if (tempAvailable[j] >= tempNeed[num][j])
			continue;
		else
			return false;
	}
	return true;
}

//����checkSecurity()����
void updateResource(int num, int tempAvailable[], int tempAllocation[][maxn], int tempNeed[][maxn]) {
	for (int j = 0; j < res_num; j++) 
		tempAvailable[j] += tempAllocation[num][j];

	for (int j = 0; j < res_num; j++) 
		tempNeed[num][j] = 0;

	for (int j = 0; j < res_num; j++)
		tempAllocation[num][j] = 0;
}

//�ú���������鵱ǰ״̬�Ƿ�ȫ������Դ�����޹أ�
	//��ȫ����
	std::queue<int> safetyQueue;
	CString safetystr;
bool checkSecurity() {
	//��ȫ�������
	bool safetyMark[maxn]; 
	memset(safetyMark, false, sizeof(safetyMark));
	//���Ƶ�ǰ����Դ��Ϣ����ʱ����
	int tempNeed[maxn][maxn], tempMax[maxn][maxn], tempAllocation[maxn][maxn], tempAvailable[maxn];
	memset(tempNeed, 0, sizeof(tempNeed)), memset(tempMax, 0, sizeof(tempMax));
	memset(tempAllocation, 0, sizeof(tempAllocation)), memset(tempAvailable, 0, sizeof(tempAvailable));
	memcpy(tempNeed, need, sizeof(need)), memcpy(tempMax, max, sizeof(max));
	memcpy(tempAllocation, allocation, sizeof(allocation)), memcpy(tempAvailable, available, sizeof(available));

	//��ĳ���̿��Լ��밲ȫ���У��������밲ȫ���У���ǰ������Ժ������ţ�
	for (int i = 0; i < pro_num; i++) {
		for (int j = 0; j < pro_num; j++) {
			if (true == safetyMark[j])
				continue;

			if (checkRequest(j, tempAvailable, tempNeed)) {
				safetyQueue.push(j);
				safetyMark[j] = true;
				updateResource(j, tempAvailable, tempAllocation, tempNeed);
			}
		}
	}

	//�������Ҫ��ӡ��ȫ���У���ȫ���о���safetyQueue�
	if (safetyQueue.size() == pro_num)
	{
		CString pro;
		while (!safetyQueue.empty())
		{
			int i=safetyQueue.front();
			safetyQueue.pop();
			if(safetyQueue.size()==0){
				pro.Format(_T("����%d"),i+1);
				safetystr+=pro;
			}
			else{
				pro.Format(_T("����%d ->"),i+1);
				safetystr+=pro;
			}
		}
		return true;
	}
	else
		return false;
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
	/*  if(available[j]<n){
		CString str;
		str.Format(_T("%d"),available[j]);
		MessageBox(TEXT("�Ƿ����ã�����Դ����Ϊ")+str);
		return;
	}*/

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

	//��ȫ�Լ��
	if(checkSecurity()){
		edit_2.SetWindowTextW(TEXT("��ȫ"));
		edit_5.SetWindowTextW(safetystr);
	}
	else{
		MessageBox(TEXT("ϵͳ�����벻��ȫ״̬��"));
		edit_2.SetWindowTextW(TEXT("����ȫ"));
		edit_5.SetWindowTextW(TEXT(""));
	}
}


void COSdesignDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
