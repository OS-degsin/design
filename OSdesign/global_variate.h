#pragma once
#include "stdafx.h"
#define maxn 10
typedef struct
{
	int allocation[maxn][maxn];	//�������
	int need[maxn][maxn];		//�������
	int max[maxn][maxn];		//����������
	int available[maxn];		//������Դ����
	int resource[maxn];		//����Դ����
	int request[maxn][maxn];		//������󣨸��ã�
	int vis[maxn];		//��ǽ���״̬���� 0��ʾ�������� 1��ʾ���̱����� 2��ʾ���������
}state;
extern state *m_state,safety_state;
extern int pro_num,res_num;