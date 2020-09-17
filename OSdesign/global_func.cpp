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
queue<int> safetyQueue;
CString safetystr;
bool checkSecurity() {
	//安全标记数组
	bool safetyMark[maxn]; 
	memset(safetyMark, false, sizeof(safetyMark));
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
				pro.Format(_T("进程%d "),i+1);
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
CString deadlockstr;
int flag[maxn];
/*
//解锁序列（若非死锁状态，可按次序列顺序解锁）
queue<int> unlockQueue;


int checkDeadlock() {
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
	{
		deadlockstr=TEXT("死锁：\r\n");
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
				str.Format(_T("进程%d \r\n"),i+1);
				deadlockstr+=str;
			}
		}
		return false;
	}
	return unlockQueue.size();

}
*/
vector<int> deadlock[bound];

// Edge作为邻接表存图
vector<int> edge[bound];

// 标记某进程节点是否被访问过
bool visNode[bound];

// 用于存储dfs的路径
vector<int> path;

int inDegree[bound];
int father[bound];

// Union-Find algorithm, 并查集的find函数，找一个节点祖先用的
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

// 0~99号节点是进程节点，100~199号节点是资源节点。
bool checkDeadlock() {
	bool ret = false;

	// 初始化并查集的father数组
	for (int i = 0; i < bound; i++)
		father[i] = i;

	// 清空visNode数组, inDegree数组, path，deadlock二维向量, edge邻接表
	memset(visNode, false, sizeof(visNode));
	memset(inDegree, 0, sizeof(inDegree));
	for (int i = 0; i < pro_num; i++)
		deadlock[i].clear();
	for (int i = 0; i < bound; i++)
		edge[i].clear();
	path.clear();

	// 根据资源分配 和 被搁置的请求 进行加边
	for (int pro = 0; pro < pro_num; pro++) {
		for (int res = 0; res < res_num; res++) {

			// 分配的资源：从资源向进程加边 并 记录每个节点的入度
			if (m_state->allocation[pro][res]) {
				addEdge(getResourceIndex(res), pro);
				inDegree[pro] ++;
			}

			// 搁置的请求：从进程向资源加边 并 记录每个节点的入度
			if (m_state->request[pro][res]) {
				addEdge(pro, getResourceIndex(res));
				inDegree[getResourceIndex(res)] ++;
			}
		}
	}

	// 2020-9-17 15:04 注释：不需要优先搜索入度为0的节点
	//for(int i=0;i<pro_num;i++){
		//if(inDegree[i] == 0){
			//path.push_back(i);
			//visNode[i] = true;
			//dfs(i);
		//}
	//}


	// 有可能存在多个连通块，所以从没有访问过的点再次dfs
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
			str1.Format(_T("死锁%d:\r\n"),k);
			k++;
			deadlockstr+=str1;
			 for(int j=0;j<deadlock[i].size();j++){
				 CString str2;
				 str2.Format(_T("进程%d\r\n"),deadlock[i][j]+1);

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