// Graph.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Yubi.h"
#include "Graph.h"
#include "afxdialogex.h"
#include "YubiDlg.h"

// CGraph ��ȭ �����Դϴ�.

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


// CGraph �޽��� ó�����Դϴ�.


void CGraph::OnTimer(UINT_PTR nIDEvent)
{
#if GRAPH_RANDOM==1
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_LineChartCtrl.m_ChartData1.Clear();
}
#endif

void CGraph::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CDialogEx::OnCancel();
}


#if (0)
void CGraph::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ĸ�ĸ� �ϱ� ���ؼ� ȭ�鿡�� ���� ���α׷��� �����.
//	ShowWindow(SW_HIDE);
	 
	// ��ũ�� ��ü�� ĸ���ϱ� ���ؼ� CWindowDC �������� DC�� ��´�.
	// GetDC�� �Ķ���Ϳ� Ư�� ������ �ڵ��� ���� �ʰ� NULL�� ������
	// CWindowDC �������� DC�� ��� �ȴ�.
#if (0)
	HDC h_screen_dc = ::GetDC(NULL);
	// ���� ��ũ���� �ػ󵵸� ��´�.
	int width = ::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = ::GetDeviceCaps(h_screen_dc, VERTRES);
#else
	CClientDC h_screen_dc(this);
	CRect rect;
	GetClientRect(rect);
	int width = rect.Width();
	int height = rect.Height();
#endif

	// DIB�� ������ �����Ѵ�.
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
	 
	// DIB�� ���� �̹��� ��Ʈ ������ ������ ������ ����
	BYTE *p_image_data = NULL;
	 
	// dib_define�� ���ǵ� �������� DIB�� �����Ѵ�.
	HBITMAP h_bitmap = ::CreateDIBSection(h_screen_dc, &dib_define, DIB_RGB_COLORS, (void **)&p_image_data, 0, 0);
	 
	// �̹����� �����ϱ� ���ؼ� ���� DC�� �����Ѵ�. ���� DC������ ���������� ��Ʈ�ʿ� �����Ͽ�
	// �̹��� ������ ���� �� ���� �����̴�.
	HDC h_memory_dc = ::CreateCompatibleDC(h_screen_dc);
	 
	// ���� DC�� �̹����� ������ ��Ʈ���� �����Ѵ�.
	HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);
	 
	// ���� ��ũ�� ȭ���� ĸ���Ѵ�.
	::BitBlt(h_memory_dc, 0, 0, width, height, h_screen_dc, 0, 0, SRCCOPY);
	 
	// ������ ��Ʈ������ �����Ѵ�.
	::SelectObject(h_memory_dc, h_old_bitmap);
	 
	// ���� DC�� �����Ѵ�.
	DeleteDC(h_memory_dc);
	 
	// DIB ������ ��� ������ �����Ѵ�.
	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = *(WORD*)"BM";
	dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
	dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// DIB ������ �����Ѵ�.
	FILE *p_file = fopen("image.bmp", "wb");
	if(p_file != NULL)
	{
	    fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
	    fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
	    fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
	    fclose(p_file);
	}
	 
	// ����ߴ� ��Ʈ�ʰ� DC �� �����Ѵ�.
	if(NULL != h_bitmap) DeleteObject(h_bitmap);
	if(NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);
	 
	ShellExecute(NULL, "open", "image.bmp", NULL, NULL, SW_SHOW);

	// ĸ�ĸ� �ϱ� ���ؼ� ���� ȭ���� �ٽ� �����ش�.
//	ShowWindow(SW_SHOW);
}
#endif

void CGraph::OnBnClickedBtnClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_LineChartCtrl.m_ChartData1.Clear();
	m_LineChartCtrl.m_ChartData2.Clear();
	m_LineChartCtrl.RedrawWindow();
}


void CGraph::OnBnClickedBtnStart()
{
#if (0)
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ĸ�ĸ� �ϱ� ���ؼ� ȭ�鿡�� ���� ���α׷��� �����.
//	ShowWindow(SW_HIDE);
	 
	// ��ũ�� ��ü�� ĸ���ϱ� ���ؼ� CWindowDC �������� DC�� ��´�.
	// GetDC�� �Ķ���Ϳ� Ư�� ������ �ڵ��� ���� �ʰ� NULL�� ������
	// CWindowDC �������� DC�� ��� �ȴ�.
#if (0)
	HDC h_screen_dc = ::GetDC(NULL);
	// ���� ��ũ���� �ػ󵵸� ��´�.
	int width = ::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = ::GetDeviceCaps(h_screen_dc, VERTRES);
#else
	CClientDC h_screen_dc(this);
	CRect rect;
	GetClientRect(rect);
	int width = rect.Width();
	int height = rect.Height();
#endif

	// DIB�� ������ �����Ѵ�.
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
	 
	// DIB�� ���� �̹��� ��Ʈ ������ ������ ������ ����
	BYTE *p_image_data = NULL;
	 
	// dib_define�� ���ǵ� �������� DIB�� �����Ѵ�.
	HBITMAP h_bitmap = ::CreateDIBSection(h_screen_dc, &dib_define, DIB_RGB_COLORS, (void **)&p_image_data, 0, 0);
	 
	// �̹����� �����ϱ� ���ؼ� ���� DC�� �����Ѵ�. ���� DC������ ���������� ��Ʈ�ʿ� �����Ͽ�
	// �̹��� ������ ���� �� ���� �����̴�.
	HDC h_memory_dc = ::CreateCompatibleDC(h_screen_dc);
	 
	// ���� DC�� �̹����� ������ ��Ʈ���� �����Ѵ�.
	HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);
	 
	// ���� ��ũ�� ȭ���� ĸ���Ѵ�.
	::BitBlt(h_memory_dc, 0, 0, width, height, h_screen_dc, 0, 0, SRCCOPY);
	 
	// ������ ��Ʈ������ �����Ѵ�.
	::SelectObject(h_memory_dc, h_old_bitmap);
	 
	// ���� DC�� �����Ѵ�.
	DeleteDC(h_memory_dc);
	 
	// DIB ������ ��� ������ �����Ѵ�.
	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = *(WORD*)"BM";
	dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
	dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// DIB ������ �����Ѵ�.
	FILE *p_file = fopen("image.bmp", "wb");
	if(p_file != NULL)
	{
	    fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
	    fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
	    fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
	    fclose(p_file);
	}
	 
	// ����ߴ� ��Ʈ�ʰ� DC �� �����Ѵ�.
	if(NULL != h_bitmap) DeleteObject(h_bitmap);
	if(NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);
	 
	ShellExecute(NULL, "open", "image.bmp", NULL, NULL, SW_SHOW);

	// ĸ�ĸ� �ϱ� ���ؼ� ���� ȭ���� �ٽ� �����ش�.
//	ShowWindow(SW_SHOW);
}

#if (0)
void CGraph::OnBnClickedBtnExcel()
{

#if (1)	/////
	/* �⺻������ �ʿ��� ������ */
	TCHAR chThisPath[256];
	CString strThisPath;
//	CXLEzAutomation XL(FALSE);				// FALSE: ó�� ������ ȭ�鿡 ������ �ʴ´�
	CXLAutomation XL(FALSE);

	/* �⺻ ���� */
	GetCurrentDirectory(256, chThisPath);	// ���� ���丮 ��ġ�� ����
	strThisPath.Format(_T("%s\\%s.xlsx"), chThisPath, _T("Diff"));	// ���丮 ��ġ�� ���������� ����
	GetModuleFileName(NULL, chThisPath, 256);

	/* ���� ���� ���� */
	XL.OpenExcelFile(strThisPath);
	XL.CreateWorkSheet();

	UpdateData(TRUE);
	int pos, len, row, column;
	CString strLine = _T("");
	CString strCell = _T("");
#endif

#if (1)		// File �б� �׽�Ʈ
	CStdioFile stdFile;
	CString strTmp = _T("");
	CString strTotal = _T("");
	CString filename = _T("test2.log");	// ������Ʈ ����(�ڵ尡 �ִ�)�� test.txt�� �����Ѵ�. 

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
	/* �⺻������ �ʿ��� ������ */
	TCHAR chThisPath[256];
	CString strThisPath;
//	CXLEzAutomation XL(FALSE);				// FALSE: ó�� ������ ȭ�鿡 ������ �ʴ´�
	CXLAutomation XL(FALSE);

	/* �⺻ ���� */
	GetCurrentDirectory(256, chThisPath);	// ���� ���丮 ��ġ�� ����
	strThisPath.Format(_T("%s\\%s.xlsx"), chThisPath, _T("Diff"));	// ���丮 ��ġ�� ���������� ����
	GetModuleFileName(NULL, chThisPath, 256);

	/* ���� ���� ���� */
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

//	XL.SaveFileAs(strThisPath);				// ���� ���� ���� 
	XL.SaveAs(strThisPath, NULL, NULL, NULL, NULL, NULL);				// ���� ���� ���� 
	XL.ReleaseExcel();						// ���� ���� ����
#endif
}
#endif


void CGraph::OnBnClickedBtnStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_bGraphStart = FALSE;
}


void CGraph::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CGraph::OnCbnSelchangeComboCsch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nID == SC_CLOSE)
	{
		CYubiDlg* pDlg = (CYubiDlg*)AfxGetApp()->m_pMainWnd;
		pDlg->Close_Graph();
	}

	CDialogEx::OnSysCommand(nID, lParam);
}

void CGraph::OnLButtonDblClk(UINT nFlags, CPoint point)
{
#if (0)	// GUN_MARK : ���򺯰� ����� �ʿ���� ���Ƴ���.
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
//			strTmp.Format(_T("RGB ���: (%u, %u, %u) "), GetRValue(color), GetGValue(color), GetBValue(color));
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

#if (0)	// GUN_MARK : ���򺯰� ����� �ʿ���� ���Ƴ���.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
