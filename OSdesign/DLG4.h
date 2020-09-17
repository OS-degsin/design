#pragma once


// CDLG4 �Ի���

class CDLG4 : public CDialogEx
{
	DECLARE_DYNAMIC(CDLG4)

public:
	CDLG4(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLG4();
	void updateNeed(int tempNeed[][maxn], int tempMax[][maxn], int tempAllocation[][maxn]);
	bool checkSecurity();
	bool checkDeadlock();
	bool checkComplete(int i);
	bool checkRequest(int num, int tempAvailable[], int tempNeed[][maxn]);
	void updateResource(int num, int tempAvailable[], int tempAllocation[][maxn], int tempNeed[][maxn]);
	int getMinRequest();

// �Ի�������
	enum { IDD = IDD_OSDESIGN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
