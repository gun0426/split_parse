
// MFCApplication1Dlg.h : 헤더 파일
//

#define JOB_THREAD_1	WM_USER+0
#define JOB_THREAD_2	WM_USER+1
#define JOB_THREAD_3	WM_USER+2
#define JOB_THREAD_4	WM_USER+3
#define EX_MSG			WM_USER+10

#pragma once
#include "afxwin.h"
#include "Graph.h"

// CMFCApplication1Dlg 대화 상자
class CMFCApplication1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	int m_iParsPos[10];
	int m_iParsDigits[10];
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnSplit();
	int m_iSplitSize;
	afx_msg void OnBnClickedBtn();
	afx_msg void OnBnClickedBtnGraph();
	static UINT Thread_1(LPVOID pParam);
	static UINT Thread_2(LPVOID pParam);
	static UINT Thread_3(LPVOID pParam);
	static UINT Thread_4(LPVOID pParam);
	int m_iThread_2;
	int m_iThread_1;
protected:	
	afx_msg LRESULT OnJobThread1(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnJobThread2(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnJobThread3(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnJobThread4(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedBtnThread3();
	
public:
	CString m_strJob3Path;
	CStdioFile m_sfRead;
	CString m_strJob3Line;
	CGraph m_CGraph;
	bool m_bGraphRenewal;
	
protected:
	afx_msg LRESULT OnExMsg(WPARAM wParam, LPARAM lParam);
};

