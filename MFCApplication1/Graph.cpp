// Graph.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "Graph.h"
#include "afxdialogex.h"


// CGraph 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGraph, CDialogEx)

CGraph::CGraph(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGraph::IDD, pParent)
	, m_iData_1(0)
	, m_iData_2(0)
	, m_iData_3(0)
	, m_iData_4(0)
	, m_iData_5(0)
	, m_iYAxisIntv(0)
	, m_iDisp_N(0)
	, m_bColorToggle(false)
{

}

CGraph::~CGraph()
{
}

void CGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DATA_N, m_iDisp_N);
}


BEGIN_MESSAGE_MAP(CGraph, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_COLOR, &CGraph::OnBnClickedBtnColor)
	ON_BN_CLICKED(IDC_BTN_CLR, &CGraph::OnBnClickedBtnClr)
END_MESSAGE_MAP()


// CGraph 메시지 처리기입니다.


BOOL CGraph::OnInitDialog()		/* m_LineChartCtrl.Create */
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	if (!m_LineChartCtrl.m_hWnd)
	{
		CRect rcWindow;
		GetClientRect(rcWindow);
		m_LineChartCtrl.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, rcWindow.Width(), rcWindow.Height()), this, 1234);

		CRect rectClear;
		CRect rectClient;	

		GetClientRect(rectClient);
		GetDlgItem(IDOK)->GetWindowRect(rectClear);
		ScreenToClient(rectClear);
		m_iYAxisIntv = rectClient.bottom-rectClear.bottom;
	}

	m_iDisp_N = 1000;
	m_bColorToggle = TRUE;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CGraph::OnSize(UINT nType, int cx, int cy)		// WM_SIZE
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_LineChartCtrl.m_hWnd)
	{
		m_LineChartCtrl.MoveWindow(0, 0, cx, cy - 25, TRUE);		// GUN_MARK : Chart-Position
		//m_LineChartCtrl.MoveWindow(30, 0, cx-30, cy, TRUE);	

		//CButton * pButton = (CButton*)GetDlgItem(IDC_BTN_CLEAR);
		//		pButton->MoveWindow(300, 300, 20, 10, TRUE);
	}

#if (0)
//	if (GetDlgItem(IDC_BTN_CLEAR) != NULL)
	{
		CRect rectClient;
		CRect rectTmp;

		GetClientRect(rectClient);

		GetDlgItem(IDOK)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDOK)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);

		GetDlgItem(IDCANCEL)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDCANCEL)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);

		GetDlgItem(IDC_EDIT_DATA_N)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_EDIT_DATA_N)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);

		GetDlgItem(IDC_BTN_COLOR)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_BTN_COLOR)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);

		GetDlgItem(IDC_BTN_CLR)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_BTN_CLR)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);

//		GetDlgItem(IDC_CHECK_AUTO_CH)->GetWindowRect(rectTmp);
//		ScreenToClient(rectTmp);
//		GetDlgItem(IDC_CHECK_AUTO_CH)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);
//
//		GetDlgItem(IDC_BTN_LOG)->GetWindowRect(rectTmp);
//		ScreenToClient(rectTmp);
//		GetDlgItem(IDC_BTN_LOG)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);
//
//		GetDlgItem(IDC_COMBO_CSCH)->GetWindowRect(rectTmp);
//		ScreenToClient(rectTmp);
//		GetDlgItem(IDC_COMBO_CSCH)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);
//
//		GetDlgItem(IDC_ST_DELTA)->GetWindowRect(rectTmp);
//		ScreenToClient(rectTmp);
//		GetDlgItem(IDC_ST_DELTA)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);
//
//		GetDlgItem(IDC_EDIT_DELTA)->GetWindowRect(rectTmp);
//		ScreenToClient(rectTmp);
//		GetDlgItem(IDC_EDIT_DELTA)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);
//
//		GetDlgItem(IDC_ST_TH)->GetWindowRect(rectTmp);
//		ScreenToClient(rectTmp);
//		GetDlgItem(IDC_ST_TH)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);
//
//		GetDlgItem(IDC_EDIT_TH)->GetWindowRect(rectTmp);
//		ScreenToClient(rectTmp);
//		GetDlgItem(IDC_EDIT_TH)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);
//
//		GetDlgItem(IDC_ST_MAX1)->GetWindowRect(rectTmp);
//		ScreenToClient(rectTmp);
//		GetDlgItem(IDC_ST_MAX1)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);
//
//		GetDlgItem(IDC_EDIT_MMAX)->GetWindowRect(rectTmp);
//		ScreenToClient(rectTmp);
//		GetDlgItem(IDC_EDIT_MMAX)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);
//
//		GetDlgItem(IDC_ST_MAX2)->GetWindowRect(rectTmp);
//		ScreenToClient(rectTmp);
//		GetDlgItem(IDC_ST_MAX2)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);
//
//		GetDlgItem(IDC_EDIT_SMAX)->GetWindowRect(rectTmp);
//		ScreenToClient(rectTmp);
//		GetDlgItem(IDC_EDIT_SMAX)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom - rectTmp.Height() - m_iYAxisIntv, 0, 0, SWP_NOSIZE);
	}
#endif

}


BOOL CGraph::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
			case VK_ESCAPE:
			case VK_RETURN:
				UpdateData(TRUE);
				return TRUE;
			default:
				break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CGraph::OnBnClickedBtnColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bColorToggle == TRUE)
	{
		m_bColorToggle = FALSE;
	}
	else
	{
		m_bColorToggle = TRUE;
	}
	if (m_bColorToggle == TRUE)
	{
		m_LineChartCtrl.m_ChartConfig.crDot = RGB(255, 0, 0);
		m_LineChartCtrl.m_ChartConfig.crBG = RGB(255, 255, 255);	// White
		m_LineChartCtrl.m_ChartConfig.crGuideLine = RGB(128, 128, 128);
		m_LineChartCtrl.m_ChartConfig.crAxis = RGB(0, 0, 0);
		m_LineChartCtrl.m_ChartConfig.crText = RGB(0, 0, 0);
		m_LineChartCtrl.m_ChartConfig.crTextBG = RGB(255, 255, 255);
		//m_LineChartCtrl.m_ChartConfig.crDataLine[0] = RGB(0x00, 0x00, 0x00);
		//m_LineChartCtrl.m_ChartConfig.crDataLine[1] = RGB(0x80, 0x80, 0x80);
	}
	else
	{
		m_LineChartCtrl.m_ChartConfig.crDot = RGB(255, 0, 0);
		m_LineChartCtrl.m_ChartConfig.crBG = RGB(0, 0, 0);			// Black
		m_LineChartCtrl.m_ChartConfig.crGuideLine = RGB(128, 128, 128);
		m_LineChartCtrl.m_ChartConfig.crAxis = RGB(255, 255, 255);
		m_LineChartCtrl.m_ChartConfig.crText = RGB(255, 255, 255);
		m_LineChartCtrl.m_ChartConfig.crTextBG = RGB(0, 0, 0);
		//m_LineChartCtrl.m_ChartConfig.crDataLine[0] = RGB(0xff, 0xff, 0xff);
		//m_LineChartCtrl.m_ChartConfig.crDataLine[1] = RGB(0x80, 0x80, 0x80);
	}
}


void CGraph::OnBnClickedBtnClr()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_LineChartCtrl.m_aData[0].Clear();
	m_LineChartCtrl.m_aData[1].Clear();
}
