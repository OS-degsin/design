
// OSdesign.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "OSdesign.h"
#include "OSdesignDlg.h"
#include "INITDlg.h"
#include "DLG2.h"
#include "DLG3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int pro_num,res_num,available[maxn],max[maxn][maxn],allocation[maxn][maxn],need[maxn][maxn];

// COSdesignApp

BEGIN_MESSAGE_MAP(COSdesignApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// COSdesignApp 构造

COSdesignApp::COSdesignApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 COSdesignApp 对象

COSdesignApp theApp;


// COSdesignApp 初始化

BOOL COSdesignApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	memset(available,0,sizeof(available));
	memset(max,0,sizeof(max));
	
	CINITDlg D1;
	D1.DoModal();
	res_num=_ttoi(D1.get_res());
	pro_num=_ttoi(D1.get_pro());
	
	CDLG2 D2;
	D2.DoModal();
	

	CDLG3 D3;
	D3.DoModal();
	

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	COSdesignDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
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
bool checkSecurity() {
	//安全序列
	std::queue<int> safetyQueue;

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
		return true;
	else
		return false;
}