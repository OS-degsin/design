#pragma once
#include "stdafx.h"
#define maxn 10
typedef struct
{
	int allocation[maxn][maxn];	//分配矩阵
	int need[maxn][maxn];		//需求矩阵
	int max[maxn][maxn];		//最大需求矩阵
	int available[maxn];		//可用资源向量
	int resource[maxn];		//总资源向量
	int request[maxn][maxn];		//请求矩阵（搁置）
	int vis[maxn];		//标记进程状态矩阵 0表示仍在运行 1表示进程被撤销 2表示进程已完成
}state;
extern state *m_state,safety_state;
extern int pro_num,res_num;