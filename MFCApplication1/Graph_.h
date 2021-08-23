#pragma once

#include "MLineChartCtrl.h"
// CGraph 대화 상자입니다.
#include "XLEzAutomation.h"


#define GRAPH_TIMER		21
#define GRAPH_RANDOM	0

#define COLOR_POS_X		305
#define COLOR_POS_Y		295
#define COLOR_REC_SIZE	15
	

class CGraph : public CDialogEx
{
	DECLARE_DYNAMIC(CGraph)

public:
	CGraph(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGraph();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GRAPH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	

	MLineChartCtrl m_LineChartCtrl;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
//	float m_iGraphData;
	int m_iGraphData;

	int m_iDotInterval;
	BOOL m_bGraphStop;
//	afx_msg void OnBnClickedButton2();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnCancel();
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnClear();
	bool m_bGraphStart;
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnCapture();
//	afx_msg void OnBnClickedBtnExcel();
	afx_msg void OnBnClickedBtnStop();

//MLineChartCtrl m_LineChartCtrl2;
//int m_iGraphData2;
	afx_msg void OnEnChangeEdit3();
	int m_iDiffMMax;
	int m_iDiffSMax;
	int m_iDeltaData;
	int m_iThreshold;
	afx_msg void OnCbnSelchangeComboCsch();
	int m_iTSCHSel;
	afx_msg void OnBnClickedBtnLog();
	bool m_bLogState;
	int m_iYAxisIntv;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
//	BOOL m_bAutoCh;
//	afx_msg void OnBnClickedCheck1();
	BOOL m_bAutoCh;
	afx_msg void OnBnClickedCheckAutoCh();
};
