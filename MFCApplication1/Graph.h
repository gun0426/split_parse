#pragma once


#include "MLineChartCtrl.h"
// CGraph 대화 상자입니다.
#include "XLEzAutomation.h"

// CGraph 대화 상자입니다.

class CGraph : public CDialogEx
{
	DECLARE_DYNAMIC(CGraph)

public:
	CGraph(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGraph();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_GRAPH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
