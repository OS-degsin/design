#include "stdafx.h"
#define maxn 10
typedef struct
{
	int allocation[maxn][maxn];
	int need[maxn][maxn];
	int max[maxn][maxn];
	int available[maxn];
	int resource[maxn];
	int request[maxn][maxn];
}state;
extern state *m_state;
extern int pro_num,res_num;