// Graph.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Yubi.h"
#include "Graph.h"
#include "afxdialogex.h"
#include "YubiDlg.h"

// CGraph 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGraph, CDialogEx)

CGraph::CGraph(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGraph::IDD, pParent)
	, m_iGraphData(0)
	, m_bGraphStart(false)
	, m_iDiffMMax(0)
	, m_iDiffSMax(0)
	, m_iDeltaData(0)
	, m_iThreshold(0)
	, m_iTSCHSel(0)
	, m_bLogState(false)
	, m_iYAxisIntv(0)
//	, m_bAutoCh(FALSE)
, m_bAutoCh(FALSE)
{
}

CGraph::~CGraph()
{
}

void CGraph::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MMAX, m_iDiffMMax);
	DDX_Text(pDX, IDC_EDIT_SMAX, m_iDiffSMax);
	DDX_Text(pDX, IDC_EDIT_DELTA, m_iDeltaData);
	DDX_Text(pDX, IDC_EDIT_TH, m_iThreshold);
	DDX_CBIndex(pDX, IDC_COMBO_CSCH, m_iTSCHSel);
	//	DDX_Check(pDX, IDC_CHECK1, m_bAutoCh);
	DDX_Check(pDX, IDC_CHECK_AUTO_CH, m_bAutoCh);
}


BEGIN_MESSAGE_MAP(CGraph, CDialogEx)
	ON_WM_TIMER()
//	ON_BN_CLICKED(IDC_BUTTON2, &CGraph::OnBnClickedButton2)
	ON_WM_SIZE()
//	ON_BN_CLICKED(IDC_BUTTON1, &CGraph::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CGraph::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_START, &CGraph::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_CAPTURE, &CGraph::OnBnClickedBtnCapture)
//	ON_BN_CLICKED(IDC_BTN_EXCEL, &CGraph::OnBnClickedBtnExcel)
	ON_BN_CLICKED(IDC_BTN_STOP, &CGraph::OnBnClickedBtnStop)
//	ON_EN_CHANGE(IDC_EDIT3, &CGraph::OnEnChangeEdit3)
ON_CBN_SELCHANGE(IDC_COMBO_CSCH, &CGraph::OnCbnSelchangeComboCsch)
ON_BN_CLICKED(IDC_BTN_LOG, &CGraph::OnBnClickedBtnLog)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_MOUSEMOVE()
ON_WM_PAINT()
ON_WM_MBUTTONDBLCLK()
ON_WM_MBUTTONDOWN()
ON_WM_LBUTTONDBLCLK()
ON_WM_MOUSEMOVE()
ON_WM_PAINT()
//ON_BN_CLICKED(IDC_CHECK1, &CGraph::OnBnClickedCheck1)
ON_BN_CLICKED(IDC_CHECK_AUTO_CH, &CGraph::OnBnClickedCheckAutoCh)
END_MESSAGE_MAP()


// CGraph 메시지 처리기입니다.


void CGraph::OnTimer(UINT_PTR nIDEvent)
{
#if GRAPH_RANDOM==1
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == GRAPH_TIMER)
	{
//		m_LineChartCtrl.m_ChartData1.Add(m_iGraphData, 0);
		if (m_bGraphStart == TRUE)
		{
			m_LineChartCtrl.m_ChartData1.Add(m_iGraphData, rand()%85+15);
			m_LineChartCtrl.RedrawWindow();
		}
	}
	if(m_bGraphStop == TRUE)
	{
		KillTimer(GRAPH_TIMER);
	}
#endif

	CDialogEx::OnTimer(nIDEvent);
}

BOOL CGraph::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if(!m_LineChartCtrl.m_hWnd)
	{
		CRect rcWindow;
		GetClientRect(rcWindow);
		m_LineChartCtrl.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(30, 0, rcWindow.Width(), rcWindow.Height()), this, 1234);
#if GRAPH_RANDOM==1
		m_bGraphStop = FALSE;
		SetTimer(GRAPH_TIMER, m_iDotInterval, NULL);
#endif


		CRect rectClear;
		CRect rectClient;

		GetClientRect(rectClient);
		GetDlgItem(IDC_BTN_CLEAR)->GetWindowRect(rectClear);
		ScreenToClient(rectClear);
		m_iYAxisIntv = rectClient.bottom-rectClear.bottom;
	}

#if (0)
	CClientDC dc(this);
	CPen myPen;
	CPen* pOldPen;
	CBrush myBrush;
	CBrush* pOldBrush;
	CSize m_sz;
	CPoint m_pt;

	myPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pOldPen = dc.SelectObject(&myPen);
	myBrush.CreateSolidBrush(RGB(255, 0, 0));
	pOldBrush = dc.SelectObject(&myBrush);
	m_pt.x = COLOR_POS_X;
	m_pt.y = COLOR_POS_Y;
	
	m_sz = CSize(COLOR_REC_SIZE, COLOR_REC_SIZE);		
	CRect rect(m_pt, m_sz);
	dc.Rectangle(rect);
	dc.SetBkMode(TRANSPARENT);

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
	DeleteObject(myPen);
	DeleteObject(myBrush);
#endif








	m_bGraphStart = FALSE;
	m_bLogState = FALSE;

	return TRUE;
}

#if (0)
void CGraph::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_LineChartCtrl.m_ChartData1.Clear();
}
#endif

void CGraph::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_LineChartCtrl.m_hWnd)
	{
		m_LineChartCtrl.MoveWindow(0, 0, cx, cy-25, TRUE);		// GUN_MARK : Chart-Position
		//m_LineChartCtrl.MoveWindow(30, 0, cx-30, cy, TRUE);	
	
//CButton * pButton = (CButton*)GetDlgItem(IDC_BTN_CLEAR);
//		pButton->MoveWindow(300, 300, 20, 10, TRUE);
	}


	if (GetDlgItem(IDC_BTN_CLEAR) != NULL)
	{
		CRect rectClient;
		CRect rectTmp;

		GetClientRect(rectClient);

		GetDlgItem(IDC_BTN_CLEAR)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_BTN_CLEAR)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);
		
		GetDlgItem(IDC_BTN_START)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_BTN_START)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);

		GetDlgItem(IDC_BTN_STOP)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_BTN_STOP)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);

//		GetDlgItem(IDC_BTN_EXCEL)->GetWindowRect(rectTmp);
//		ScreenToClient(rectTmp);
//		GetDlgItem(IDC_BTN_EXCEL)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);

		GetDlgItem(IDC_BTN_CAPTURE)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_BTN_CAPTURE)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);

		GetDlgItem(IDC_CHECK_AUTO_CH)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_CHECK_AUTO_CH)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);	

		GetDlgItem(IDC_BTN_LOG)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_BTN_LOG)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);
		
		GetDlgItem(IDC_COMBO_CSCH)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_COMBO_CSCH)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);

		GetDlgItem(IDC_ST_DELTA)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_ST_DELTA)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);

		GetDlgItem(IDC_EDIT_DELTA)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_EDIT_DELTA)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);
		
		GetDlgItem(IDC_ST_TH)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_ST_TH)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);
		
		GetDlgItem(IDC_EDIT_TH)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_EDIT_TH)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);	

		GetDlgItem(IDC_ST_MAX1)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_ST_MAX1)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);
			
		GetDlgItem(IDC_EDIT_MMAX)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_EDIT_MMAX)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);

		GetDlgItem(IDC_ST_MAX2)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_ST_MAX2)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);

		GetDlgItem(IDC_EDIT_SMAX)->GetWindowRect(rectTmp);
		ScreenToClient(rectTmp);
		GetDlgItem(IDC_EDIT_SMAX)->SetWindowPos(NULL, rectTmp.left, rectClient.bottom-rectTmp.Height()-m_iYAxisIntv, 0 , 0, SWP_NOSIZE);			
	}

}


void CGraph::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::OnCancel();
}


#if (0)
void CGraph::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 캡쳐를 하기 위해서 화면에서 현재 프로그램을 감춘다.
//	ShowWindow(SW_HIDE);
	 
	// 스크린 전체를 캡쳐하기 위해서 CWindowDC 형식으로 DC를 얻는다.
	// GetDC의 파라메터에 특정 윈도우 핸들을 넣지 않고 NULL을 넣으면
	// CWindowDC 형식으로 DC를 얻게 된다.
#if (0)
	HDC h_screen_dc = ::GetDC(NULL);
	// 현재 스크린의 해상도를 얻는다.
	int width = ::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = ::GetDeviceCaps(h_screen_dc, VERTRES);
#else
	CClientDC h_screen_dc(this);
	CRect rect;
	GetClientRect(rect);
	int width = rect.Width();
	int height = rect.Height();
#endif

	// DIB의 형식을 정의한다.
	BITMAPINFO dib_define;
	dib_define.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	dib_define.bmiHeader.biWidth = width;
	dib_define.bmiHeader.biHeight = height;
	dib_define.bmiHeader.biPlanes = 1;
	dib_define.bmiHeader.biBitCount = 24;
	dib_define.bmiHeader.biCompression = BI_RGB;
	dib_define.bmiHeader.biSizeImage = (((width * 24 + 31) & ~31) >> 3) * height;
	dib_define.bmiHeader.biXPelsPerMeter = 0;
	dib_define.bmiHeader.biYPelsPerMeter = 0;
	dib_define.bmiHeader.biClrImportant = 0;
	dib_define.bmiHeader.biClrUsed = 0;
	 
	// DIB의 내부 이미지 비트 패턴을 참조할 포인터 변수
	BYTE *p_image_data = NULL;
	 
	// dib_define에 정의된 내용으로 DIB를 생성한다.
	HBITMAP h_bitmap = ::CreateDIBSection(h_screen_dc, &dib_define, DIB_RGB_COLORS, (void **)&p_image_data, 0, 0);
	 
	// 이미지를 추출하기 위해서 가상 DC를 생성한다. 메인 DC에서는 직접적으로 비트맵에 접근하여
	// 이미지 패턴을 얻을 수 없기 때문이다.
	HDC h_memory_dc = ::CreateCompatibleDC(h_screen_dc);
	 
	// 가상 DC에 이미지를 추출할 비트맵을 연결한다.
	HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);
	 
	// 현재 스크린 화면을 캡쳐한다.
	::BitBlt(h_memory_dc, 0, 0, width, height, h_screen_dc, 0, 0, SRCCOPY);
	 
	// 본래의 비트맵으로 복구한다.
	::SelectObject(h_memory_dc, h_old_bitmap);
	 
	// 가상 DC를 제거한다.
	DeleteDC(h_memory_dc);
	 
	// DIB 파일의 헤더 내용을 구성한다.
	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = *(WORD*)"BM";
	dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
	dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// DIB 파일을 생성한다.
	FILE *p_file = fopen("image.bmp", "wb");
	if(p_file != NULL)
	{
	    fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
	    fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
	    fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
	    fclose(p_file);
	}
	 
	// 사용했던 비트맵과 DC 를 해제한다.
	if(NULL != h_bitmap) DeleteObject(h_bitmap);
	if(NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);
	 
	ShellExecute(NULL, "open", "image.bmp", NULL, NULL, SW_SHOW);

	// 캡쳐를 하기 위해서 감춘 화면을 다시 보여준다.
//	ShowWindow(SW_SHOW);
}
#endif

void CGraph::OnBnClickedBtnClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_LineChartCtrl.m_ChartData1.Clear();
	m_LineChartCtrl.m_ChartData2.Clear();
	m_LineChartCtrl.RedrawWindow();
}


void CGraph::OnBnClickedBtnStart()
{
#if (0)
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bGraphStart == TRUE)
	{
		m_bGraphStart = FALSE;
		CButton * pButton = (CButton*)GetDlgItem(IDC_BTN_START);
		if (pButton && ::IsWindow( pButton->GetSafeHwnd() ))
		{
			pButton->SetWindowText(_T("Start"));
		}
	}
	else
	{
		m_bGraphStart = TRUE;
		CButton * pButton = (CButton*)GetDlgItem(IDC_BTN_START);
		if (pButton && ::IsWindow( pButton->GetSafeHwnd() ))
		{
			pButton->SetWindowText(_T("Stop"));
		}
	}
#endif
	m_iDiffMMax = 0;
	m_iDiffSMax = 0;
	m_bGraphStart = TRUE;
	UpdateData(FALSE);
//	GetDlgItem(IDC_EDIT_SEND)->EnableWindow(TRUE);   
}


void CGraph::OnBnClickedBtnCapture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 캡쳐를 하기 위해서 화면에서 현재 프로그램을 감춘다.
//	ShowWindow(SW_HIDE);
	 
	// 스크린 전체를 캡쳐하기 위해서 CWindowDC 형식으로 DC를 얻는다.
	// GetDC의 파라메터에 특정 윈도우 핸들을 넣지 않고 NULL을 넣으면
	// CWindowDC 형식으로 DC를 얻게 된다.
#if (0)
	HDC h_screen_dc = ::GetDC(NULL);
	// 현재 스크린의 해상도를 얻는다.
	int width = ::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = ::GetDeviceCaps(h_screen_dc, VERTRES);
#else
	CClientDC h_screen_dc(this);
	CRect rect;
	GetClientRect(rect);
	int width = rect.Width();
	int height = rect.Height();
#endif

	// DIB의 형식을 정의한다.
	BITMAPINFO dib_define;
	dib_define.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	dib_define.bmiHeader.biWidth = width;
	dib_define.bmiHeader.biHeight = height;
	dib_define.bmiHeader.biPlanes = 1;
	dib_define.bmiHeader.biBitCount = 24;
	dib_define.bmiHeader.biCompression = BI_RGB;
	dib_define.bmiHeader.biSizeImage = (((width * 24 + 31) & ~31) >> 3) * height;
	dib_define.bmiHeader.biXPelsPerMeter = 0;
	dib_define.bmiHeader.biYPelsPerMeter = 0;
	dib_define.bmiHeader.biClrImportant = 0;
	dib_define.bmiHeader.biClrUsed = 0;
	 
	// DIB의 내부 이미지 비트 패턴을 참조할 포인터 변수
	BYTE *p_image_data = NULL;
	 
	// dib_define에 정의된 내용으로 DIB를 생성한다.
	HBITMAP h_bitmap = ::CreateDIBSection(h_screen_dc, &dib_define, DIB_RGB_COLORS, (void **)&p_image_data, 0, 0);
	 
	// 이미지를 추출하기 위해서 가상 DC를 생성한다. 메인 DC에서는 직접적으로 비트맵에 접근하여
	// 이미지 패턴을 얻을 수 없기 때문이다.
	HDC h_memory_dc = ::CreateCompatibleDC(h_screen_dc);
	 
	// 가상 DC에 이미지를 추출할 비트맵을 연결한다.
	HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);
	 
	// 현재 스크린 화면을 캡쳐한다.
	::BitBlt(h_memory_dc, 0, 0, width, height, h_screen_dc, 0, 0, SRCCOPY);
	 
	// 본래의 비트맵으로 복구한다.
	::SelectObject(h_memory_dc, h_old_bitmap);
	 
	// 가상 DC를 제거한다.
	DeleteDC(h_memory_dc);
	 
	// DIB 파일의 헤더 내용을 구성한다.
	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = *(WORD*)"BM";
	dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
	dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// DIB 파일을 생성한다.
	FILE *p_file = fopen("image.bmp", "wb");
	if(p_file != NULL)
	{
	    fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
	    fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
	    fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
	    fclose(p_file);
	}
	 
	// 사용했던 비트맵과 DC 를 해제한다.
	if(NULL != h_bitmap) DeleteObject(h_bitmap);
	if(NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);
	 
	ShellExecute(NULL, "open", "image.bmp", NULL, NULL, SW_SHOW);

	// 캡쳐를 하기 위해서 감춘 화면을 다시 보여준다.
//	ShowWindow(SW_SHOW);
}

#if (0)
void CGraph::OnBnClickedBtnExcel()
{

#if (1)	/////
	/* 기본적으로 필요한 변수들 */
	TCHAR chThisPath[256];
	CString strThisPath;
//	CXLEzAutomation XL(FALSE);				// FALSE: 처리 과정을 화면에 보이지 않는다
	CXLAutomation XL(FALSE);

	/* 기본 세팅 */
	GetCurrentDirectory(256, chThisPath);	// 현재 디렉토리 위치를 구함
	strThisPath.Format(_T("%s\\%s.xlsx"), chThisPath, _T("Diff"));	// 디렉토리 위치에 엑셀파일을 지정
	GetModuleFileName(NULL, chThisPath, 256);

	/* 엑셀 파일 오픈 */
	XL.OpenExcelFile(strThisPath);
	XL.CreateWorkSheet();

	UpdateData(TRUE);
	int pos, len, row, column;
	CString strLine = _T("");
	CString strCell = _T("");
#endif

#if (1)		// File 읽기 테스트
	CStdioFile stdFile;
	CString strTmp = _T("");
	CString strTotal = _T("");
	CString filename = _T("test2.log");	// 프로젝트 폴더(코드가 있는)에 test.txt를 생성한다. 

	if (!stdFile.Open(filename, CFile::modeRead, NULL))
	{
		return;
	}
	while (stdFile.ReadString(strTmp))
	{
		strTotal += strTmp;
	}
	stdFile.Close();
#endif

#if (1)
//	int pos, len, row, column;
//	CString strLine = _T("");
//	CString strCell = _T("");

	len = strTotal.GetLength();
	pos = strTotal.Find(_T("FD"), 0);

	while (pos < len)
	{
		strLine = _T("");
		while (strTotal.GetAt(pos) != '\n')
		{
			strLine += strTotal.GetAt(pos++);
			strLine.Replace(_T("\t\t"), _T("\t"));
		}
		for (column = 0; column < 16; column++)
		{
			AfxExtractSubString(strCell, strLine, column, '\t');
			//XL.SetCellValue(column+1, row+1, strCell);
			XL.SetCellsValueToString(column+1, row+1, strCell);
		}
		row++;
		pos++;
//		pos++;	// "\r\n"
	}
#endif



#if (0)	/////
	/* 기본적으로 필요한 변수들 */
	TCHAR chThisPath[256];
	CString strThisPath;
//	CXLEzAutomation XL(FALSE);				// FALSE: 처리 과정을 화면에 보이지 않는다
	CXLAutomation XL(FALSE);

	/* 기본 세팅 */
	GetCurrentDirectory(256, chThisPath);	// 현재 디렉토리 위치를 구함
	strThisPath.Format(_T("%s\\%s.xlsx"), chThisPath, _T("Diff"));	// 디렉토리 위치에 엑셀파일을 지정
	GetModuleFileName(NULL, chThisPath, 256);

	/* 엑셀 파일 오픈 */
	XL.OpenExcelFile(strThisPath);
	XL.CreateWorkSheet();

	UpdateData(TRUE);
	int pos, len, row, column;
	CString strLine = _T("");
	CString strCell = _T("");
#endif


#if (0)
	/* Cell Clear */
	for (row = 0; row < 300; row++)
	{
		XL.DeleteRow(row+1);
	}
#endif



#if (0)
CStdioFile * filePtr;
CYubiDlg* pDlg = (CYubiDlg*)AfxGetApp()->m_pMainWnd;
filePtr = pDlg->m_pCLogManager->logFile;
if (filePtr == NULL)
{
	return;
}

CString cStr;
CString tmp;

while (filePtr->ReadString(tmp))
{
	cStr += tmp + _T("\n");
}

cStr += tmp + _T("\n");
#endif
	



#if (0)
	pos = 0;
	row = 0;
	
	len = m_CStrRichEditRx.GetLength();
	pos = m_CStrRichEditRx.Find(_T("TEMP"), 0);

	while (pos < len)
	{
		strLine = _T("");
		while (m_CStrRichEditRx.GetAt(pos) != '\n')
		{
			strLine += m_CStrRichEditRx.GetAt(pos++);
			strLine.Replace(_T("\t\t"), _T("\t"));
		}
		for (column = 0; column < m_iExcelColumn_N; column++)
		{
			AfxExtractSubString(strCell, strLine, column, '\t');
//			XL.SetCellValue(column+1, row+1, strCell);
			XL.SetCellsValueToString(column+1, row+1, strCell);
		}
		row++;
		pos++;
//		pos++;	// "\r\n"
	}
#endif


#if (1)	//////
////	XL.CreateXYChart(3);
//	XL.UpdatePlotRange(2);
//	XL.UpdatePlotRange(3);

//	XL.SaveFileAs(strThisPath);				// 엑셀 파일 저장 
	XL.SaveAs(strThisPath, NULL, NULL, NULL, NULL, NULL);				// 엑셀 파일 저장 
	XL.ReleaseExcel();						// 엑셀 파일 해제
#endif
}
#endif


void CGraph::OnBnClickedBtnStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bGraphStart = FALSE;
}


void CGraph::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CGraph::OnCbnSelchangeComboCsch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

//	int temp;
	static int preCH = 0;

	m_iDiffMMax = 0;
	m_iDiffSMax = 0;

	if (preCH == m_iTSCHSel)
	{
		return;
	}
}


void CGraph::OnBnClickedBtnLog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bLogState == TRUE)
	{
		m_bLogState = FALSE;
		CButton * pButton = (CButton*)GetDlgItem(IDC_BTN_LOG);
		if (pButton && ::IsWindow( pButton->GetSafeHwnd() ))
		{
			pButton->SetWindowText(_T("Log-On"));
		}	
		CYubiDlg* pDlg = (CYubiDlg*)AfxGetApp()->m_pMainWnd;
		pDlg->m_pCLogManager->Close();
	}
	else
	{
		m_bLogState = TRUE;
		CButton * pButton = (CButton*)GetDlgItem(IDC_BTN_LOG);
		if (pButton && ::IsWindow( pButton->GetSafeHwnd() ))
		{
			pButton->SetWindowText(_T("Log-Off"));
		}
	
		CYubiDlg* pDlg = (CYubiDlg*)AfxGetApp()->m_pMainWnd;
		pDlg->m_pCLogManager->Open();
	}
}


void CGraph::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nID == SC_CLOSE)
	{
		CYubiDlg* pDlg = (CYubiDlg*)AfxGetApp()->m_pMainWnd;
		pDlg->Close_Graph();
	}

	CDialogEx::OnSysCommand(nID, lParam);
}

void CGraph::OnLButtonDblClk(UINT nFlags, CPoint point)
{
#if (0)	// GUN_MARK : 색깔변경 기능이 필요없어 막아놓음.
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if ((point.x>=COLOR_POS_X) && (point.x<COLOR_POS_X+COLOR_REC_SIZE) && (point.y>=COLOR_POS_Y) && (point.y<COLOR_POS_Y+COLOR_REC_SIZE))
	{
	//	CColorDialog dlg;	// default : RGB(0,0,0)
	//	CColorDialog dlg(RGB(255, 0, 0));
		CColorDialog dlg(RGB(255, 0, 0), CC_FULLOPEN);	// CC_ANYCOLOR/CC_FULLOPEN/CC_PREVENTFULL/CC_RGBINIT/CC_SOLIDCOLOR
	//	CColorDialog dlg(RGB(255, 0, 0), CC_FULLOPEN, this);
	//	dlg.DoModal() ;  
		if (dlg.DoModal() == IDOK)
		{
			COLORREF color = dlg.GetColor();
//			CString strTmp;
//			strTmp.Format(_T("RGB 출력: (%u, %u, %u) "), GetRValue(color), GetGValue(color), GetBValue(color));
//			AfxMessageBox(strTmp);
			m_LineChartCtrl.m_ChartConfig.crDot = RGB((GetRValue(color)+5)%256,(GetGValue(color)+5)%256, (GetBValue(color)+5)%256);
			m_LineChartCtrl.m_ChartConfig.crDataLine1 = color;//RGB(30, 144, 255);
		}
	}
#endif
	CDialogEx::OnLButtonDblClk(nFlags, point);
}



void CGraph::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

#if (0)	// GUN_MARK : 색깔변경 기능이 필요없어 막아놓음.
//	CClientDC dc(this);
	CPen myPen;
	CPen* pOldPen;
	CBrush myBrush;
	CBrush* pOldBrush;
	CSize m_sz;
	CPoint m_pt;

	myPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pOldPen = dc.SelectObject(&myPen);
	myBrush.CreateSolidBrush(RGB(255, 0, 0));
	pOldBrush = dc.SelectObject(&myBrush);
	m_pt.x = COLOR_POS_X;
	m_pt.y = COLOR_POS_Y;
	
	m_sz = CSize(COLOR_REC_SIZE, COLOR_REC_SIZE);		
	CRect rect(m_pt, m_sz);
	dc.Rectangle(rect);
	dc.SetBkMode(TRANSPARENT);

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
	DeleteObject(myPen);
	DeleteObject(myBrush);
#endif
}


#if (0)
void CGraph::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_bAutoCh == TRUE)
	{
		GetDlgItem(IDC_COMBO_CSCH)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_CSCH)->EnableWindow(TRUE);
	}
}
#endif


void CGraph::OnBnClickedCheckAutoCh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_bAutoCh == TRUE)
	{
		GetDlgItem(IDC_COMBO_CSCH)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_CSCH)->EnableWindow(TRUE);
	}
}
