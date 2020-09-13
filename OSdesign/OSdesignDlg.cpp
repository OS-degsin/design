
// OSdesignDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OSdesign.h"
#include "OSdesignDlg.h"
#include "afxdialogex.h"
#include "global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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
	DDX_Control(pDX, IDC_EDIT6, edit_6);
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
	memset(m_state->allocation,0,sizeof(m_state->allocation));
	memcpy(m_state->need,m_state->max,sizeof(m_state->max));
	memcpy(m_state->available,m_state->resource,sizeof(m_state->resource));
	// allocation矩阵显示
	CString str,res,pro;
	allocation_list.InsertColumn(0,TEXT(""),LVCFMT_LEFT,60);
	for (int i=0;i<res_num;i++)
	{
		str.Format(_T("%c"),i+65);
		allocation_list.InsertColumn(i+1,TEXT("资源")+str,LVCFMT_LEFT,60);
	}
	for(int i=0;i<pro_num;i++){
		pro.Format(_T("进程%d"),i+1);
		allocation_list.InsertItem(i,pro);
		for(int j=0;j<res_num;j++){
			str.Format(_T("%d"),m_state->allocation[i][j]);
			allocation_list.SetItemText(i,j+1,str);
		}	
	}
	// need矩阵显示
	need_list.InsertColumn(0,TEXT(""),LVCFMT_LEFT,60);
	for (int i=0;i<res_num;i++)
	{
		str.Format(_T("%c"),i+65);
		need_list.InsertColumn(i+1,TEXT("资源")+str,LVCFMT_LEFT,60);
	}
	for(int i=0;i<pro_num;i++){
		res.Format(_T("进程%d"),1+i);
		need_list.InsertItem(i,res);
		for(int j=0;j<res_num;j++){
			str.Format(_T("%d"),m_state->need[i][j]);
			need_list.SetItemText(i,j+1,str);
		}
	}
	// available矩阵展示
	for (int i=0;i<res_num;i++)
	{
		str.Format(_T("%c"),65+i);
		available_list.InsertColumn(i,TEXT("资源")+str,LVCFMT_LEFT,60);
	}
		str.Format(_T("%d"),m_state->available[0]);
	available_list.InsertItem(0,str);
	for(int i=1;i<res_num;i++){
		str.Format(_T("%d"),m_state->available[i]);
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
void COSdesignDlg::updateNeed(int tempNeed[][maxn], int tempMax[][maxn], int tempAllocation[][maxn]) {
	for (int i = 0; i < pro_num; i++) {
		for (int j = 0; j < res_num; j++) {
			tempNeed[i][j] = tempMax[i][j] - tempAllocation[i][j];
		}
	}
}

//参数说明：进程下标，available向量，need矩阵
bool COSdesignDlg::checkRequest(int num, int tempAvailable[], int tempNeed[][maxn]) {
	for (int j = 0; j < res_num; j++) {
		if (tempAvailable[j] >= tempNeed[num][j])
			continue;
		else
			return false;
	}
	return true;
}

//仅供checkSecurity()和checkDeadlock()调用
void COSdesignDlg::updateResource(int num, int tempAvailable[], int tempAllocation[][maxn], int tempNeed[][maxn]) {
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

bool COSdesignDlg::checkSecurity() {
	//安全标记数组
	bool safetyMark[maxn]; 
	memset(safetyMark, false, sizeof(safetyMark));

	//清空safetyQueue
	while (safetyQueue.size()) {
		safetyQueue.pop();
	}

	//复制当前的资源信息到临时数组
	int tempNeed[maxn][maxn], tempMax[maxn][maxn], tempAllocation[maxn][maxn], tempAvailable[maxn];
	memset(tempNeed, 0, sizeof(tempNeed)), memset(tempMax, 0, sizeof(tempMax));
	memset(tempAllocation, 0, sizeof(tempAllocation)), memset(tempAvailable, 0, sizeof(tempAvailable));
	memcpy(tempNeed, m_state->need, sizeof(m_state->need)), memcpy(tempMax,m_state->max, sizeof(m_state->max));
	memcpy(tempAllocation, m_state->allocation, sizeof(m_state->allocation)), memcpy(tempAvailable, m_state->available, sizeof(m_state->available));

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
	safetystr="";
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


bool COSdesignDlg::checkDeadlock() {
	//解锁序列（若非死锁状态，可按次序列顺序解锁）
	std::queue<int> unlockQueue;

	//安全标记数组
	bool safetyMark[maxn];
	memset(safetyMark, false, sizeof(safetyMark));

	//清空unlockQueue
	while (unlockQueue.size()) {
		unlockQueue.pop();
	}

	//复制当前的资源信息到临时数组
	int tempRequest[maxn][maxn], tempMax[maxn][maxn], tempAllocation[maxn][maxn], tempAvailable[maxn];
	memset(tempRequest, 0, sizeof(tempRequest)), memset(tempMax, 0, sizeof(tempMax));
	memset(tempAllocation, 0, sizeof(tempAllocation)), memset(tempAvailable, 0, sizeof(tempAvailable));
	memcpy(tempRequest, m_state->request, sizeof(m_state->request)), memcpy(tempMax, m_state->max, sizeof(m_state->max));
	memcpy(tempAllocation, m_state->allocation, sizeof(m_state->allocation)), memcpy(tempAvailable, m_state->available, sizeof(m_state->available));

	//若某进程可以加入安全序列，立即加入安全序列（当前加入比以后加入更优）
	for (int i = 0; i < pro_num; i++) {
		for (int j = 0; j < pro_num; j++) {
			if (true == safetyMark[j])
				continue;
			if (checkRequest(j, tempAvailable, tempRequest)) {
				unlockQueue.push(j);
				safetyMark[j] = true;
				updateResource(j, tempAvailable, tempAllocation, tempRequest);
			}
		}
	}

	if (unlockQueue.size() == pro_num)
		return true;
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
	//判断资源数量是否足够
	int n=_ttoi(edit_1);
	int i=cbx_1.GetCurSel(),j=cbx_2.GetCurSel();
	 if(m_state->available[j]<n){
		//搁置申请，放入request数组
		 MessageBox(TEXT("可用资源不足！"));
		m_state->request[i][j]=n;
		char a[2],b[2];
		a[0]='1'+i;
		b[0]='A'+j;
		b[1]=a[1]='\0';
		CString str1(a),str2(b),str3,str4,str5;
		str3.Format(_T("%d"),n);
		edit_6.GetWindowTextW(str4);
		str5=TEXT("搁置：进程")+str1+TEXT("申请")+str2+TEXT("资源数量为")+str3+TEXT("个\r\n");
		str4+=str5;
		edit_6.SetWindowTextW(str4);
		return;
	}
	else{
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
		m_state->allocation[i][j]+=n;
		str6.Format(_T("%d"),m_state->allocation[i][j]);
		allocation_list.SetItemText(i,j+1,str6);

		//更新need矩阵
		CString str7;
		m_state->need[i][j]-=n;
		str7.Format(_T("%d"),m_state->need[i][j]);
		need_list.SetItemText(i,j+1,str7);
	
		//更新available资源
		CString str8;
		m_state->available[j]-=n;
		str8.Format(_T("%d"),m_state->available[j]);
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
			CString str9;
			edit_4.GetWindowTextW(str9);
			edit_4.SetWindowTextW(str9+TEXT("系统进入不安全状态!\r\n"));
		}
	}
}



void COSdesignDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}