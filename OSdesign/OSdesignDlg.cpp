
// OSdesignDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OSdesign.h"
#include "OSdesignDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int pro_num,res_num,available[10],max[10][10],allocation[10][10],need[10][10];

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// COSdesignDlg 对话框



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


// COSdesignDlg 消息处理程序

BOOL COSdesignDlg::OnInitDialog()
{
	SetWindowText(_T("死锁检测与恢复"));
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// allocation矩阵初始化
	memset(allocation,0,sizeof(allocation));
	memcpy(need,max,sizeof(max));
	// allocation矩阵显示
	CString str,res,pro;
	allocation_list.InsertColumn(0,TEXT(""),LVCFMT_LEFT,50);
	for (int i=1;i<=pro_num;i++)
	{
		str.Format(_T("%d"),i);
		allocation_list.InsertColumn(i,TEXT("进程")+str,LVCFMT_LEFT,50);
	}
	for(int i=0;i<res_num;i++){
		res.Format(_T("%c"),65+i);
		allocation_list.InsertItem(i,res);
		for(int j=1;j<=pro_num;j++){
			str.Format(_T("%d"),allocation[j-1][i]);
			allocation_list.SetItemText(i,j,str);
		}	
	}
	// need矩阵显示
	need_list.InsertColumn(0,TEXT(""),LVCFMT_LEFT,50);
	for (int i=1;i<=pro_num;i++)
	{
		str.Format(_T("%d"),i);
		need_list.InsertColumn(i,TEXT("进程")+str,LVCFMT_LEFT,50);
	}
	for(int i=0;i<res_num;i++){
		res.Format(_T("%c"),65+i);
		need_list.InsertItem(i,res);
		for(int j=1;j<=pro_num;j++){
			str.Format(_T("%d"),max[j-1][i]);
			need_list.SetItemText(i,j,str);
		}	
	}
	// available矩阵展示
	for (int i=0;i<res_num;i++)
	{
		str.Format(_T("%c"),65+i);
		available_list.InsertColumn(i,TEXT("资源")+str,LVCFMT_LEFT,60);
	}
	str.Format(_T("%d"),available[0]);
	available_list.InsertItem(0,str);
	for(int i=1;i<res_num;i++){
		str.Format(_T("%d"),available[i]);
		available_list.SetItemText(0,i,str);
	}
	//初始化进程下拉框
	char a[2];
	a[0]='1';
	a[1]='\0';
	for(int i=0;i<pro_num;i++){
		str=a;
		cbx_1.InsertString(i,str);
		a[0]++;
	}
	//初始化资源下拉框
	char b[2];
	b[0]='A';
	b[1]='\0';
	for(int i=0;i<res_num;i++){
		str=b;
		cbx_2.InsertString(i,str);
		b[0]++;
	}
	//初始化安全性状态与安全序列
	edit_2.SetWindowTextW(TEXT("安全"));
	str="";
	for(int i=1;i<=pro_num;i++){
		if(i==pro_num){
			pro.Format(_T(" 进程%d"),i);
			str+=pro;
		}
		else {
			pro.Format(_T("进程%d ->"),i);
			str+=pro;
		}
	}
	edit_5.SetWindowTextW(str);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COSdesignDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COSdesignDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//该函数不进行安全检测，确认可以更新再调用
void updateNeed(int tempNeed[][maxn], int tempMax[][maxn], int tempAllocation[][maxn]) {
	for (int i = 0; i < pro_num; i++) {
		for (int j = 0; j < res_num; j++) {
			tempNeed[i][j] = tempMax[i][j] - tempAllocation[i][j];
		}
	}
}

//参数说明：进程下标，available向量，need矩阵
bool checkRequest(int num, int tempAvailable[], int tempNeed[][maxn]) {
	for (int j = 0; j < res_num; j++) {
		if (tempAvailable[j] >= tempNeed[num][j])
			continue;
		else
			return false;
	}
	return true;
}

//仅供checkSecurity()调用
void updateResource(int num, int tempAvailable[], int tempAllocation[][maxn], int tempNeed[][maxn]) {
	for (int j = 0; j < res_num; j++) 
		tempAvailable[j] += tempAllocation[num][j];

	for (int j = 0; j < res_num; j++) 
		tempNeed[num][j] = 0;

	for (int j = 0; j < res_num; j++)
		tempAllocation[num][j] = 0;
}

//该函数仅仅检查当前状态是否安全，和资源分配无关！
	//安全序列
	std::queue<int> safetyQueue;
	CString safetystr;
bool checkSecurity() {
	//安全标记数组
	bool safetyMark[maxn]; 
	memset(safetyMark, false, sizeof(safetyMark));
	//复制当前的资源信息到临时数组
	int tempNeed[maxn][maxn], tempMax[maxn][maxn], tempAllocation[maxn][maxn], tempAvailable[maxn];
	memset(tempNeed, 0, sizeof(tempNeed)), memset(tempMax, 0, sizeof(tempMax));
	memset(tempAllocation, 0, sizeof(tempAllocation)), memset(tempAvailable, 0, sizeof(tempAvailable));
	memcpy(tempNeed, need, sizeof(need)), memcpy(tempMax, max, sizeof(max));
	memcpy(tempAllocation, allocation, sizeof(allocation)), memcpy(tempAvailable, available, sizeof(available));

	//若某进程可以加入安全序列，立即加入安全序列（当前加入比以后加入更优）
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

	//如果有需要打印安全序列，安全序列就在safetyQueue里。
	if (safetyQueue.size() == pro_num)
	{
		CString pro;
		while (!safetyQueue.empty())
		{
			int i=safetyQueue.front();
			safetyQueue.pop();
			if(safetyQueue.size()==0){
				pro.Format(_T("进程%d"),i+1);
				safetystr+=pro;
			}
			else{
				pro.Format(_T("进程%d ->"),i+1);
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(cbx_1.GetCurSel() == -1||cbx_2.GetCurSel() == -1||edit_1.IsEmpty()){
		MessageBox(TEXT("选项或输入内容不能为空"));
		return;
	}
	//判断资源数量是否越界
	int n=_ttoi(edit_1);
	int i=cbx_1.GetCurSel(),j=cbx_2.GetCurSel();
	/*  if(available[j]<n){
		CString str;
		str.Format(_T("%d"),available[j]);
		MessageBox(TEXT("非法设置，该资源余量为")+str);
		return;
	}*/

	char a[2],b[2];
	a[0]='1'+i;
	b[0]='A'+j;
	b[1]=a[1]='\0';
	CString str1(a),str2(b),str3,str4,str5;
	str3.Format(_T("%d"),n);
	edit_4.GetWindowTextW(str4);
	str5=TEXT("进程")+str1+TEXT("申请")+str2+TEXT("资源数量为")+str3+TEXT("个\r\n");
	str4+=str5;
	edit_4.SetWindowTextW(str4);


	//更新allocation矩阵
	CString str6;
	allocation[i][j]+=n;
	str6.Format(_T("%d"),allocation[i][j]);
	allocation_list.SetItemText(j,i+1,str6);

	//更新need矩阵
	CString str7;
	need[i][j]=max[i][j]-allocation[i][j];
	str7.Format(_T("%d"),need[i][j]);
	need_list.SetItemText(j,i+1,str7);
	
	//更新available资源
	CString str8;
	available[j]-=n;
	str8.Format(_T("%d"),available[j]);
	available_list.SetItemText(0,j,str8);

	//安全性检测
	if(checkSecurity()){
		edit_2.SetWindowTextW(TEXT("安全"));
		edit_5.SetWindowTextW(safetystr);
	}
	else{
		MessageBox(TEXT("系统将进入不安全状态！"));
		edit_2.SetWindowTextW(TEXT("不安全"));
		edit_5.SetWindowTextW(TEXT(""));
	}
}


void COSdesignDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
