// DLG4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OSdesign.h"
#include "DLG4.h"
#include "afxdialogex.h"
#include "global.h"
#define INF 0x3f3f3f3f
// CDLG4 �Ի���

IMPLEMENT_DYNAMIC(CDLG4, CDialogEx)

CDLG4::CDLG4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDLG4::IDD, pParent)
{

}

CDLG4::~CDLG4()
{
}

void CDLG4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


// CDLG4 ��Ϣ�������

//�ú��������а�ȫ��⣬ȷ�Ͽ��Ը����ٵ���
void CDLG4::updateNeed(int tempNeed[][maxn], int tempMax[][maxn], int tempAllocation[][maxn]) {
	for (int i = 0; i < pro_num; i++) {
		for (int j = 0; j < res_num; j++) {
			tempNeed[i][j] = tempMax[i][j] - tempAllocation[i][j];
		}
	}
}

//����˵���������±꣬available������need����
bool CDLG4::checkRequest(int num, int tempAvailable[], int tempNeed[][maxn]) {
	for (int j = 0; j < res_num; j++) {
		if (tempAvailable[j] >= tempNeed[num][j])
			continue;
		else
			return false;
	}
	return true;
}

//����checkSecurity()����
void CDLG4::updateResource(int num, int tempAvailable[], int tempAllocation[][maxn], int tempNeed[][maxn]) {
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
bool CDLG4::checkSecurity() {
	//��ȫ�������
	bool safetyMark[maxn]; 
	memset(safetyMark, false, sizeof(safetyMark));
	//���Ƶ�ǰ����Դ��Ϣ����ʱ����
	int tempNeed[maxn][maxn], tempMax[maxn][maxn], tempAllocation[maxn][maxn], tempAvailable[maxn];
	memset(tempNeed, 0, sizeof(tempNeed)), memset(tempMax, 0, sizeof(tempMax));
	memset(tempAllocation, 0, sizeof(tempAllocation)), memset(tempAvailable, 0, sizeof(tempAvailable));
	memcpy(tempNeed, m_state->need, sizeof(m_state->need)), memcpy(tempMax,m_state->max, sizeof(m_state->max));
	memcpy(tempAllocation, m_state->allocation, sizeof(m_state->allocation)), memcpy(tempAvailable, m_state->available, sizeof(m_state->available));
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
	safetystr="";
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
//�������У���������״̬���ɰ�������˳�������
std::queue<int> unlockQueue;
CString deadlockstr;
int CDLG4::checkDeadlock() {
	//��ȫ�������
	bool safetyMark[maxn];
	memset(safetyMark, false, sizeof(safetyMark));

	//���unlockQueue
	while (unlockQueue.size()) {
		unlockQueue.pop();
	}

	//���Ƶ�ǰ����Դ��Ϣ����ʱ����
	int tempRequest[maxn][maxn], tempMax[maxn][maxn], tempAllocation[maxn][maxn], tempAvailable[maxn];
	memset(tempRequest, 0, sizeof(tempRequest)), memset(tempMax, 0, sizeof(tempMax));
	memset(tempAllocation, 0, sizeof(tempAllocation)), memset(tempAvailable, 0, sizeof(tempAvailable));
	memcpy(tempRequest, m_state->request, sizeof(m_state->request)), memcpy(tempMax, m_state->max, sizeof(m_state->max));
	memcpy(tempAllocation, m_state->allocation, sizeof(m_state->allocation)), memcpy(tempAvailable, m_state->available, sizeof(m_state->available));

	//��ĳ���̿��Լ��밲ȫ���У��������밲ȫ���У���ǰ������Ժ������ţ�
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
	{
		deadlockstr=TEXT("������\r\n");
		int vis[maxn];
		memset(vis,0,sizeof(vis));
		while(!unlockQueue.empty()){
			int temp=unlockQueue.front();
			unlockQueue.pop();
			vis[temp]=1;
		}
		for(int i=0;i<pro_num;i++){
			if(vis[i]==0) {
				CString str;
				str.Format(_T("����%d \r\n"),i+1);
				deadlockstr+=str;
			}
		}
		return false;
	}
	return unlockQueue.size();
	
}
bool CDLG4::checkComplete(int i){
	int tempSum=0;
	for(int j=0;j<res_num;j++){
		tempSum+=m_state->need[i][j];
	}
	if(tempSum==0)  return true;
	else return false;
}
int CDLG4::getMinRequest(){
	int tempMin= INF,tempindex=-1;
	for(int i=0;i<pro_num;i++){
		int tempSum=0;
		for(int j=0;j<res_num;j++){
			if(m_state->request[i][j]<=m_state->available[j]){
				tempSum+=m_state->request[i][j];
			}
		}
		if(tempSum !=0 && tempSum<tempMin){
			tempMin=tempSum;
			tempindex=i;
		}
	}
	return tempindex;
}

int getMaxNeed(){
	int tempMax= 0,tempindex=-1;
	for(int i=0;i<pro_num;i++){
		int tempSum=0;
		for(int j=0;j<res_num;j++){
				tempSum+=m_state->need[i][j];
		}
		if(tempSum !=0 && tempSum>tempMax){
			tempMax=tempSum;
			tempindex=i;
		}
	}
	return tempindex;
}