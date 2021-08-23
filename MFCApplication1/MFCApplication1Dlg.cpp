
// MFCApplication1Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "XLAutomation.h"
#include "XLEzAutomation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��ȭ ����



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
//	, m_iParsPos (0)
//	, m_iParsDigits(0)
, m_iSplitSize(0)
, m_iThread_1(0)
, m_iThread_2(0)
, m_strJob3Path(_T(""))
, m_strJob3Line(_T(""))
, m_bGraphRenewal(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POS_1, m_iParsPos[0]);
	DDX_Text(pDX, IDC_EDIT_POS_2, m_iParsPos[1]);
	DDX_Text(pDX, IDC_EDIT_POS_3, m_iParsPos[2]);
	DDX_Text(pDX, IDC_EDIT_POS_4, m_iParsPos[3]);
	DDX_Text(pDX, IDC_EDIT_POS_5, m_iParsPos[4]);
	DDX_Text(pDX, IDC_EDIT_POS_6, m_iParsPos[5]);
	DDX_Text(pDX, IDC_EDIT_POS_7, m_iParsPos[6]);
	DDX_Text(pDX, IDC_EDIT_POS_8, m_iParsPos[7]);
	DDX_Text(pDX, IDC_EDIT_POS_9, m_iParsPos[8]);
	DDX_Text(pDX, IDC_EDIT_POS_10, m_iParsPos[9]);
	DDX_Text(pDX, IDC_EDIT_DIGITS_1, m_iParsDigits[0]);
	DDX_Text(pDX, IDC_EDIT_DIGITS_2, m_iParsDigits[1]);
	DDX_Text(pDX, IDC_EDIT_DIGITS_3, m_iParsDigits[2]);
	DDX_Text(pDX, IDC_EDIT_DIGITS_4, m_iParsDigits[3]);
	DDX_Text(pDX, IDC_EDIT_DIGITS_5, m_iParsDigits[4]);
	DDX_Text(pDX, IDC_EDIT_DIGITS_6, m_iParsDigits[5]);
	DDX_Text(pDX, IDC_EDIT_DIGITS_7, m_iParsDigits[6]);
	DDX_Text(pDX, IDC_EDIT_DIGITS_8, m_iParsDigits[7]);
	DDX_Text(pDX, IDC_EDIT_DIGITS_9, m_iParsDigits[8]);
	DDX_Text(pDX, IDC_EDIT_DIGITS_10, m_iParsDigits[9]);
	DDX_Text(pDX, IDC_EDIT_SPLIT_N, m_iSplitSize);
	//	DDX_Control(pDX, IDC_EDIT_THREAD_1, m_iThread_3);
	DDX_Text(pDX, IDC_EDIT_THREAD_2, m_iThread_2);
	DDX_Text(pDX, IDC_EDIT_THREAD_1, m_iThread_1);
	DDX_Text(pDX, IDC_EDIT_THREAD_3, m_strJob3Line);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_SPLIT, &CMFCApplication1Dlg::OnBnClickedBtnSplit)
//	ON_BN_CLICKED(IDC_BTN_, &CMFCApplication1Dlg::OnBnClickedBtn)
	ON_BN_CLICKED(IDC_BTN_GRAPH, &CMFCApplication1Dlg::OnBnClickedBtnGraph)
	ON_WM_CREATE()
	
//	ON_MESSAGE(JOB_THREAD_1, &CMFCApplication1Dlg::OnJobThread1)
	ON_MESSAGE(JOB_THREAD_2, &CMFCApplication1Dlg::OnJobThread2)
	ON_BN_CLICKED(IDC_BTN_THREAD_3, &CMFCApplication1Dlg::OnBnClickedBtnThread3)
	ON_MESSAGE(JOB_THREAD_3, &CMFCApplication1Dlg::OnJobThread3)
	ON_MESSAGE(JOB_THREAD_4, &CMFCApplication1Dlg::OnJobThread4)
	ON_MESSAGE(EX_MSG, &CMFCApplication1Dlg::OnExMsg)
END_MESSAGE_MAP()


// CMFCApplication1Dlg �޽��� ó����

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	for (int i=0; i<10; i++)
	{
		m_iParsPos[i] = 0;
		m_iParsDigits[i] = 0;
	}
	m_iParsPos[0] = 10;
	m_iParsPos[1] = 20;
	m_iParsPos[2] = 30;
	m_iParsPos[3] = 40;
	m_iParsDigits[0] = 4;
	m_iParsDigits[1] = 4;
	m_iParsDigits[2] = 4;
	m_iParsDigits[3] = 4;
	m_iSplitSize = 100000;
	UpdateData(FALSE);



#if (1)	// thread
	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	CWinThread *p1 = NULL;
	CWinThread *p2 = NULL;

	p1 = AfxBeginThread(Thread_1, this);
	if (p1 == NULL)
	{
		AfxMessageBox(_T("Thread_1 Error"));
	}
////CloseHandle(p1);

	p2 = AfxBeginThread(Thread_2, this);
	if (p2 == NULL)
	{
		AfxMessageBox(_T("Thread_2 Error"));
	}
////CloseHandle(p2);
#endif


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString strPathName_R;
	CString strPathName_W;
	CString strTitleName_R;	
	CString strTitleName_W;
	CString strExcelName;

	/* �� File Path ��� */
	char szFilters[] = "Data(*.dat,*.txt) | *.dat;*.txt; | All Files(*.*)|*.*||";
//	char szFilters[] = "All Files(*.*)|*.*||";	
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, this);
	if (fileDlg.DoModal() == IDOK)					// �����ϰ� Ȯ���ϸ� IDOK �� �Ѿ�ɴϴ�
	{
		strPathName_R = fileDlg.GetPathName();		// Ȯ���� ����
		strTitleName_R = fileDlg.GetFileTitle();	// Ȯ���� ����
	}
	else
	{
		return;
	}

	strPathName_W = strPathName_R;
	strPathName_W.Replace(".dat", "_edit.csv");

#if (0)	// Excel
	strExcelName = strPathName_W;
	strExcelName.Replace(".txt", ".xls");
#endif
	/* �� File Open : Write */
	CStdioFile sfWrite;
	if(!sfWrite.Open(strPathName_W, CFile::modeCreate | CFile::modeWrite ))
	{
		AfxMessageBox(_T("File Open Fail !"));
		return;
	}

#if (0)	// Excel
	/* �� Excel Open */	
	CXLAutomation XL(FALSE);			//CXLEzAutomation XL(FALSE); FALSE: ó�� ������ ȭ�鿡 ������ �ʴ´�
	XL.OpenExcelFile(strExcelName);
	XL.CreateWorkSheet();
#endif

	/* �� File Open : Read */
	CStdioFile sfRead;
	CString strLine;
	CString strEdit;
	CString strCell;
	int column = 0;
	int row = 0;
	if (sfRead.Open(strPathName_R, CFile::modeRead|CFile::typeText))
	{
		while(sfRead.ReadString(strLine))	// Read 1-Line
		{ 
			row = 0;
			strEdit = _T("");
			for (int i=0; i<10; i++)
			{				
				if (m_iParsDigits[i] != 0)
				{
					strCell = strLine.Mid(m_iParsPos[i], m_iParsDigits[i]);
#if (0)	// Excel
					XL.SetCellsValueToString(row++, column, strCell);
#endif
					strEdit += strCell;						
					strEdit += _T(',');
				}
				else
				{
					break;
				}
			}
			strEdit += _T("\n");
			sfWrite.WriteString(strEdit);
			column++;
		} 
	}
	else
	{
		AfxMessageBox(_T("File Open Fail !"));
		return;
	}

	sfRead.Close();
	sfWrite.Close();

#if (0)	// Excel
	XL.CreateXYChart(3);
//	XL.UpdatePlotRange(2);
//	XL.UpdatePlotRange(3);
//	XL.SaveFileAs(strExcelName);			
	XL.SaveAs(strExcelName, NULL, NULL, NULL, NULL, NULL);			
	XL.ReleaseExcel();			
#endif

	ShellExecute(NULL, "open", strPathName_W, NULL, NULL, SW_SHOW);

	AfxMessageBox(_T("Complete!"));
	
	/* 
		�� CFile::modeCreate		- ������ ������ �� ������ ����ϴ�. ������ �̹� ������ CFileException�� �߻��մϴ�.
		�� CFile::modeNoTruncate	- ������ ������ �� ������ ����ϴ�. ������ �̹� ������ CFile ��ü�� ����˴ϴ�.
		�� CFile::modeRead			- �б� ���Ѹ� ��û�մϴ�.
		�� CFile::modeReadWrite		- �б� �� ���� ������ ��û�մϴ�.
		�� CFile::modeWrite			- ���� ���Ѹ� ��û�մϴ�.
		�� CFile::shareDenyNone		- ���� ������ �����ϴ�.
		�� CFile::shareDenyRead		- �ٸ� ��� ����ڿ� ���� �б� ������ �ź��մϴ�.
		�� CFile::shareDenyWrite	- �ٸ� ��� ����ڿ� ���� ���� ������ �ź��մϴ�.
		�� CFile::shareExclusive	- �ٸ� ��� ����ڿ� ���� �б� �� ���� ������ �ź��մϴ�.
	*/
	/*
		�� CString  Left( int nCount )	: ���� ���� nCount��ŭ ����
		�� CString  Right( int nCount ) : ������ ���� nCount��ŭ ����
		�� CString  Mid( int nFirst, int nCount )	: nFirst���� nCount��ŭ ����
	*/
	
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
#if (0)
		// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFile m_CFileT;
	CString CStrFilePath;
	char filename[100];
	
	GetModuleFileName(NULL, filename, MAX_PATH);					// "F:\tools\mfc\auto_test_ui\Yubi\Debug\Yubi.exe"
	CStrFilePath.Format(_T("%s"), filename);						// 			
	CStrFilePath.Replace(_T("Yubi.exe"),_T("ADC.txt"));				// "F:\tools\mfc\auto_test_ui\Yubi\Debug\ADC.txt"
	if (!m_CFileT.Open(CStrFilePath, CFile::modeCreate|CFile::modeWrite) )
	{
		AfxMessageBox("File open fail !");
	}
	
	int index;	
	char* p_file;
	char buff[100];
	CString CStrTrans;

	UpdateData(TRUE);
	for (int i = 0; i < m_iADCDataN; i++)
	{
		index = 0;		/* start of line */
		while (1)		/* while creating a line */
		{
			sprintf(buff, "%d\t:", i+1);
			index = m_CStrRcv.Find(buff, index);
			/* for line-change */
			if (index == -1)
			{
				m_CFileT.Write("\r\n", 2);
				break;
			}
			index = m_CStrRcv.Find(':', index);	
			index++;	

			/* one-data extract */
			CStrTrans = _T("");		
			while (m_CStrRcv.GetAt(index) != '\r')
			{
				CStrTrans += m_CStrRcv.GetAt(index);
				index++;
			}
			CStrTrans += '\t';

			/* write file */
			p_file = LPSTR(LPCTSTR(CStrTrans));
			m_CFileT.Write(p_file, CStrTrans.GetLength());

			/********************************
				1\t / 11\t / 111\t
				��� 1\t �� �����ϰ� �ִ�. 
			*/
			index = m_CStrRcv.Find("CH1", index);
			if (index == -1)
			{
				m_CFileT.Write("\r\n", 2);
				break;
			}
		}
	}

	/* ���� ���� */
	m_CFileT.Close();
	ShellExecute(NULL, "open", CStrFilePath, NULL, NULL, SW_SHOW);
#endif
}


/*
// Type
// 0: ���� ��θ� ����
// 1: ���� �̸��� ����
// 2: ���� Ȯ���� ����
// 3: Ȯ���ڸ� �� ���ϸ� ����
// 4: 2�����̽��� ���� Ȯ���ڿ��� .�� ��.
CString strClip(CString str, int nType)
{
 //���� Full Path�� ����
 TCHAR szTmp[4096];
 StrCpy(szTmp, str);
 CString strTmp;

 CString strResult = _T("");

 switch(nType)
 {
	case 0:		// ������ ��θ� ����.	
		PathRemoveFileSpec(szTmp);
		strResult = szTmp;
		break;
	case 1:		// ���� �̸��� ����
		strResult = PathFindFileName(szTmp);
		break;
	case 2:		// ���� Ȯ���� ����
		strResult = PathFindExtension(szTmp);
		break;
	case 3:		// Ȯ���ڸ� �� ���ϸ� ����
		strTmp = PathFindFileName(szTmp);
		ZeroMemory(szTmp, 4096);
		StrCpy(szTmp, strTmp);
		PathRemoveExtension(szTmp); 
		strResult = szTmp;
		break;
	case 4:		// 4: 2�����̽��� ���� Ȯ���ڿ��� .�� ��.
		strResult = PathFindExtension(szTmp);
		strResult = strResult.Right(strResult.GetLength()-1);
		break;
 }


 return strResult;
}
*/
void CMFCApplication1Dlg::OnBnClickedBtnSplit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CStdioFile sfWrite;
	CStdioFile sfRead;
	CString str_folder_path;
	CString str_path_name;	
	CString str_file_title;
	CString str_file_ext;
	CString str_file_name;
	CString str_core_name;	
	CString str_full_path;
	int split_indx = 0;

	/* �� File Path ��� */
	char szFilters[] = "Data(*.dat,*.txt) | *.dat;*.txt; | All Files(*.*)|*.*||";
//	char szFilters[] = "All Files(*.*)|*.*||";	
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, this);
	if (fileDlg.DoModal() == IDOK)					// �����ϰ� Ȯ���ϸ� IDOK �� �Ѿ�ɴϴ�
	{
		str_folder_path	= fileDlg.GetFolderPath();	// ���丮
		str_path_name	= fileDlg.GetPathName();	// ���丮+�����̸�+Ȯ����
		str_file_title	= fileDlg.GetFileTitle();	// �����̸�
		str_file_ext	= fileDlg.GetFileExt();		// Ȯ����
		str_file_name	= fileDlg.GetFileName();	// �����̸�+Ȯ����
	}
	else
	{
		return;
	}

	str_core_name = str_path_name;
	str_core_name.Replace(".dat", "_split_");
	str_full_path.Format("%s_%03d", (TCHAR*)((LPCSTR)str_core_name), split_indx++); 
	if(!sfWrite.Open(str_full_path, CFile::modeCreate | CFile::modeWrite ))
	{
		AfxMessageBox(_T("File Open Fail !"));
		return;
	}

	CString strLine = _T("");
	CString strPack = _T("");
	int nLine = 0;
	if (sfRead.Open(str_path_name, CFile::modeRead|CFile::typeText))
	{
		while(sfRead.ReadString(strLine))	// Read 1-Line
		{ 		
			strLine += _T('\n');
			sfWrite.WriteString(strLine);
			nLine++;
			if (nLine == m_iSplitSize)
			{
				nLine = 0;
				sfWrite.Close();
				str_full_path.Format("%s_%03d", (TCHAR*)((LPCSTR)str_core_name), split_indx++); 
				if(!sfWrite.Open(str_full_path, CFile::modeCreate | CFile::modeWrite ))
				{
					AfxMessageBox(_T("File Open Fail !"));
					return;
				}
			}
		}
	}

	sfRead.Close();
	sfWrite.Close();



#if (0)
	CStdioFile sfWrite;
	int Line_N = 0;
	CStdioFile sfRead;
	CString strLine = _T("");
	CString strPack = _T("");

	if(!sfWrite.Open(strPathName_W, CFile::modeCreate | CFile::modeWrite ))
	{
		AfxMessageBox(_T("File Open Fail !"));
		return;
	}

	if (sfRead.Open(strPathName_R, CFile::modeRead|CFile::typeText))
	{
		while(sfRead.ReadString(strLine))	// Read 1-Line
		{ 
			strPack += strLine;
			strPack += _T("\n");
			Line_N++;
			if (Line_N == 100)
			{
				Line_N = 0;
				sfWrite.Close();
				strPathName_W.Format("%s%s",


					strThisPath.Format(_T("%s\\%s.xlsx"), chThisPath, _T("ADC"));




				/* �� File Open : Write */
				if(!sfWrite.Open(strPathName_W, CFile::modeCreate | CFile::modeWrite ))
				{
					AfxMessageBox(_T("File Open Fail !"));
					return;
				}
			}
		} 
	}
	else
	{
		AfxMessageBox(_T("File Open Fail !"));
		return;
	}
#endif


}


void CMFCApplication1Dlg::OnBnClickedBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
#if (0)
	UpdateData(TRUE);

	m_CGraph.m_iDiffMMax = 0;
	m_CGraph.m_iDiffSMax = 0;

	m_bGraphEn = TRUE;
	UpdateData(FALSE);

	m_CGraph.m_bGraphStart = TRUE;
	m_CGraph.m_iDotInterval = 50;
	m_CGraph.DestroyWindow();
	m_CGraph.Create(IDD_GRAPH_DLG, this);
	m_CGraph.ShowWindow(SW_SHOW);
#if (SPREAD_TEST == 1)
	m_strSAddr = _T("84");
	GetDlgItem(IDC_EDIT_SADDR)->SetWindowTextA(m_strSAddr);
	Do_I2CConfig(0x84);
#else
	m_strSAddr = _T("40");
	GetDlgItem(IDC_EDIT_SADDR)->SetWindowTextA(m_strSAddr);
	Do_I2CConfig(0x40);
#endif
	Wait(100);
	SetTimer(GET_DATA_TIMER, 70, NULL);
	////SetTimer(GET_DATA_TIMER, 50, NULL);
#endif
}


void CMFCApplication1Dlg::OnBnClickedBtnGraph()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	m_CGraph.DestroyWindow();
	m_CGraph.Create(IDD_DIALOG_GRAPH, this);
	m_CGraph.ShowWindow(SW_SHOW);

	/* �� Thread 4 ���� */
	CWinThread *p1 = NULL;
	p1 = AfxBeginThread(Thread_4, this);
	if (p1 == NULL)
	{
		AfxMessageBox(_T("Thread_4 Error"));
	}
	////CloseHandle(p1);


////static int i = 0;
//
//	CGraph* pGraph = new CGraph;
//	pGraph->Create(IDD_DIALOG_GRAPH, this);
//	pGraph->ShowWindow(SW_SHOW);
//
//	/* �� Thread 4 ���� */
//	CWinThread *p1 = NULL;
//	p1 = AfxBeginThread(Thread_4, this);
////	i++;
//	if (p1 == NULL)
//	{
//		AfxMessageBox(_T("Thread_4 Error"));
//	}
}
void CMFCApplication1Dlg::OnBnClickedBtnThread3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	/* �� File Path ��� */
	char szFilters[] = "Data(*.dat,*.txt) | *.dat;*.txt; | All Files(*.*)|*.*||";
	//	char szFilters[] = "All Files(*.*)|*.*||";	
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, this);
	if (fileDlg.DoModal() == IDOK)					// �����ϰ� Ȯ���ϸ� IDOK �� �Ѿ�ɴϴ�
	{
		m_strJob3Path = fileDlg.GetPathName();		// ���丮+�����̸�+Ȯ����
	}
	else
	{
		return;
	}
	if (m_sfRead.Open(m_strJob3Path, CFile::modeRead | CFile::typeText | CFile::shareDenyNone))
	{
	}
	else
	{
	}

	/* �� Thread 3 ���� */
	CWinThread *p1 = NULL;
	p1 = AfxBeginThread(Thread_3, this);
	if (p1 == NULL)
	{
		AfxMessageBox(_T("Thread_3 Error"));
	}
	////CloseHandle(p1);
}

/*===============================================
		THREAD 1
================================================*/
UINT CMFCApplication1Dlg::Thread_1(LPVOID pParam)
{
	CMFCApplication1Dlg *aa = (CMFCApplication1Dlg*)pParam;

	CMFCApplication1Dlg *pDlg = (CMFCApplication1Dlg*)AfxGetApp()->m_pMainWnd;
	while (1)
	{			
		Sleep(100);
		pDlg->PostMessage(JOB_THREAD_1, 0, 0);
	}

	return 0;
}
afx_msg LRESULT CMFCApplication1Dlg::OnJobThread1(WPARAM wParam, LPARAM lParam)
{
	m_iThread_1++;
	m_iThread_1 %= 100;
m_bGraphRenewal = TRUE;
	UpdateData(FALSE);
	return 0;
}
/*===============================================
		THREAD 2
================================================*/
UINT CMFCApplication1Dlg::Thread_2(LPVOID pParam)
{
	CMFCApplication1Dlg *aa = (CMFCApplication1Dlg*)pParam;

	CMFCApplication1Dlg *pDlg = (CMFCApplication1Dlg*)AfxGetApp()->m_pMainWnd;
	while (1)
	{
		Sleep(200);
		pDlg->PostMessage(JOB_THREAD_2, 0, 0);
	}

	return 0;
}
afx_msg LRESULT CMFCApplication1Dlg::OnJobThread2(WPARAM wParam, LPARAM lParam)
{
	m_iThread_2++;
	m_iThread_2 %= 100;
	UpdateData(FALSE);
	return 0;
}
/*===============================================
		THREAD 3
================================================*/
UINT CMFCApplication1Dlg::Thread_3(LPVOID pParam)
{
	CMFCApplication1Dlg *aa = (CMFCApplication1Dlg*)pParam;

	CMFCApplication1Dlg *pDlg = (CMFCApplication1Dlg*)AfxGetApp()->m_pMainWnd;
	while (1)
	{
		Sleep(1000);
		pDlg->PostMessage(JOB_THREAD_3, 0, 0);
	}

	return 0;
}
afx_msg LRESULT CMFCApplication1Dlg::OnJobThread3(WPARAM wParam, LPARAM lParam)
{
	//	int nLine = 0;
	m_strJob3Line = _T("");
	//	if (m_sfRead.Open(m_strJob3Path, CFile::modeRead | CFile::typeText))
	{
		//		while (m_sfRead.ReadString(m_strJob3Line))	// Read 1-Line
		//		{
		//			m_strJob3Line += _T('\n');
		//		}
		m_sfRead.ReadString(m_strJob3Line);
	}
	UpdateData(FALSE);
	return 0;
}
/*===============================================
		THREAD 4
================================================*/
UINT CMFCApplication1Dlg::Thread_4(LPVOID pParam)
{
	CMFCApplication1Dlg *aa = (CMFCApplication1Dlg*)pParam;
	CMFCApplication1Dlg *pDlg = (CMFCApplication1Dlg*)AfxGetApp()->m_pMainWnd;

	while (1)
	{
		Sleep(0);
		if (aa->m_bGraphRenewal == TRUE)
		{
			aa->m_bGraphRenewal = FALSE;
			pDlg->PostMessage(JOB_THREAD_4, 0, 0);
		}		
	}

	return 0;
}
afx_msg LRESULT CMFCApplication1Dlg::OnJobThread4(WPARAM wParam, LPARAM lParam)
{
	m_CGraph.m_LineChartCtrl.m_aData[0].Add((float)m_iThread_1, 0, 0);
	m_CGraph.m_LineChartCtrl.m_aData[1].Add((float)m_iThread_2, 0, 0);	
	if (m_CGraph.m_LineChartCtrl.m_aData[0].lstData.GetSize() > m_CGraph.m_iDisp_N)
	{
		m_CGraph.m_LineChartCtrl.m_aData[0].lstData.RemoveAt(0);
		m_CGraph.m_LineChartCtrl.m_aData[1].lstData.RemoveAt(0);
	}
	m_CGraph.m_LineChartCtrl.RedrawWindow();
	return 0;
}



afx_msg LRESULT CMFCApplication1Dlg::OnExMsg(WPARAM wParam, LPARAM lParam)
{
	int i=0;

	i++;

	return 0;
}
