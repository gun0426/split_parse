#pragma once


#include "MLineChartCtrl.h"
// CGraph ��ȭ �����Դϴ�.
#include "XLEzAutomation.h"

// CGraph ��ȭ �����Դϴ�.

class CGraph : public CDialogEx
{
	DECLARE_DYNAMIC(CGraph)

public:
	CGraph(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGraph();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_GRAPH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:

	int m_iData_1;
	int m_iData_2;
	int m_iData_3;
	int m_iData_4;
	int m_iData_5;
	MLineChartCtrl m_LineChartCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int m_iYAxisIntv;
	int m_iDisp_N;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool m_bColorToggle;
	afx_msg void OnBnClickedBtnColor();
	afx_msg void OnBnClickedBtnClr();
};
