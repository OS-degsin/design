
// OSdesign.cpp : ����Ӧ�ó��������Ϊ��
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


// COSdesignApp ����

COSdesignApp::COSdesignApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� COSdesignApp ����

COSdesignApp theApp;


// COSdesignApp ��ʼ��

BOOL COSdesignApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
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

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	COSdesignDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
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
bool checkSecurity() {
	//��ȫ����
	std::queue<int> safetyQueue;

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
		return true;
	else
		return false;
}