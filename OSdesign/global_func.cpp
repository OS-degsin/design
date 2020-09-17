#include "stdafx.h"
#include "global_func.h"
#include "global_variate.h"
#include <queue>
#include <functional>
#include <vector>
#define INF 0x3f3f3f3f
#define bound 200
using namespace std;

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
queue<int> safetyQueue;
CString safetystr;
bool checkSecurity() {
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
				pro.Format(_T("����%d "),i+1);
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
CString deadlockstr;
int flag[maxn];
/*
//�������У���������״̬���ɰ�������˳�������
queue<int> unlockQueue;


int checkDeadlock() {
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
				flag[i]=1;
				CString str;
				str.Format(_T("����%d \r\n"),i+1);
				deadlockstr+=str;
			}
		}
		return false;
	}
	return unlockQueue.size();

}
*/
vector<int> deadlock[bound];

// Edge��Ϊ�ڽӱ��ͼ
vector<int> edge[bound];

// ���ĳ���̽ڵ��Ƿ񱻷��ʹ�
bool visNode[bound];

// ���ڴ洢dfs��·��
vector<int> path;

int inDegree[bound];
int father[bound];

// Union-Find algorithm, ���鼯��find��������һ���ڵ������õ�
int findAncestor(int node) {
	if (node != father[node])
		father[node] = findAncestor(father[node]);
	return father[node];
}

void dfs(int nowNode) {
	//for(int toNode : edge[nowNode]){
	for (int i = 0; i < edge[nowNode].size(); i++) {
		int toNode = edge[nowNode][i];
		if (false == visNode[toNode]) {
			visNode[toNode] = true;;
			path.push_back(toNode);

			dfs(toNode);
		}
		else {
			int lastAncestor = findAncestor(toNode);
			for (int i = path.size() - 1; i >= 0 && path[i] != toNode; i--) {
				int temp = path[i];
				int pa = findAncestor(temp);
				father[pa] = lastAncestor;
			}
			return;
		}
	}
}

int getResourceIndex(int x) {
	return x + 100;
}

void addEdge(int from, int to) {
	edge[from].push_back(to);
}

// 0~99�Žڵ��ǽ��̽ڵ㣬100~199�Žڵ�����Դ�ڵ㡣
bool checkDeadlock() {
	bool ret = false;

	// ��ʼ�����鼯��father����
	for (int i = 0; i < bound; i++)
		father[i] = i;

	// ���visNode����, inDegree����, path��deadlock��ά����, edge�ڽӱ�
	memset(visNode, false, sizeof(visNode));
	memset(inDegree, 0, sizeof(inDegree));
	for (int i = 0; i < pro_num; i++)
		deadlock[i].clear();
	for (int i = 0; i < bound; i++)
		edge[i].clear();
	path.clear();

	// ������Դ���� �� �����õ����� ���мӱ�
	for (int pro = 0; pro < pro_num; pro++) {
		for (int res = 0; res < res_num; res++) {

			// �������Դ������Դ����̼ӱ� �� ��¼ÿ���ڵ�����
			if (m_state->allocation[pro][res]) {
				addEdge(getResourceIndex(res), pro);
				inDegree[pro] ++;
			}

			// ���õ����󣺴ӽ�������Դ�ӱ� �� ��¼ÿ���ڵ�����
			if (m_state->request[pro][res]) {
				addEdge(pro, getResourceIndex(res));
				inDegree[getResourceIndex(res)] ++;
			}
		}
	}

	// 2020-9-17 15:04 ע�ͣ�����Ҫ�����������Ϊ0�Ľڵ�
	//for(int i=0;i<pro_num;i++){
		//if(inDegree[i] == 0){
			//path.push_back(i);
			//visNode[i] = true;
			//dfs(i);
		//}
	//}


	// �п��ܴ��ڶ����ͨ�飬���Դ�û�з��ʹ��ĵ��ٴ�dfs
	for (int i = 0; i < pro_num; i++) {
		if (inDegree[i] == 0)
			continue;
		if (true == visNode[i])
			continue;
		path.push_back(i);
		visNode[i] = true;
		dfs(i);
	}

	for (int i = 0; i < pro_num; i++) {
		int pa = findAncestor(i);
		deadlock[i].push_back(i);
		if (i == pa) {
			continue;
		}
		else {
			ret = true;
			deadlock[pa].push_back(i);
		}
	}

	int k=1;
	deadlockstr.Empty();
	for (int i=0;i<pro_num;i++)
	{
		if(deadlock[i].size()>1){
			CString str1;
			str1.Format(_T("����%d:\r\n"),k);
			k++;
			deadlockstr+=str1;
			 for(int j=0;j<deadlock[i].size();j++){
				 CString str2;
				 str2.Format(_T("����%d\r\n"),deadlock[i][j]+1);

				 deadlockstr+=str2;
				 flag[deadlock[i][j]]=1;
				 /*CString ii,jj,kk;
				 ii.Format(_T("i:%d "),i);
				 jj.Format(_T("j:%d "),j);
				 kk.Format(_T("deadlock[i][j]:%d "),deadlock[i][j]);
				 AfxMessageBox(ii+jj+kk);*/
			 }
		}
	}
	
	return ret;
}
bool checkComplete(int i){
	int tempSum=0;
	for(int j=0;j<res_num;j++){
		tempSum+=m_state->need[i][j];
	}
	if(tempSum==0)  return true;
	else return false;
}

int getMinRequest(){
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
		if(flag[i]!=1) continue;
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
bool checkSystemComplete(){
	for(int i=0;i<pro_num;i++){
		if(m_state->vis[i]==0)
			return false;
	}
	return true;
}