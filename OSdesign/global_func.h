#include "stdafx.h"
#include "global_variate.h"
extern void updateNeed(int tempNeed[][maxn], int tempMax[][maxn], int tempAllocation[][maxn]);
extern bool checkSecurity();
extern bool checkDeadlock();
extern bool checkComplete(int i);
extern bool checkRequest(int num, int tempAvailable[], int tempNeed[][maxn]);
extern void updateResource(int num, int tempAvailable[], int tempAllocation[][maxn], int tempNeed[][maxn]);
extern int getMinRequest();
extern int getMaxNeed();
extern bool checkSystemComplete();