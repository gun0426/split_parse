// MLineChartCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MLineChartCtrl.h"

// MLineChartCtrl

IMPLEMENT_DYNAMIC(MLineChartCtrl, CWnd)

MLineChartCtrl::MLineChartCtrl()
{
	m_hMemBitmap = NULL;
	m_hMemDC = NULL;
}

MLineChartCtrl::~MLineChartCtrl()
{
}


BEGIN_MESSAGE_MAP(MLineChartCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// MLineChartCtrl 메시지 처리기입니다.



void MLineChartCtrl::OnPaint()	// GUN_MARK
{
	CPaintDC dc(this); // device context for painting
	HDC hDC = dc.m_hDC;

	GetClientRect(rcWindow);
	DrawChart(m_hMemDC);	
	BitBlt(hDC, 0, 0, rcWindow.Width(), rcWindow.Height(), m_hMemDC, 0, 0, SRCCOPY);	// DC간의 영역끼리 고속 복사를 수행한다. 


#if (1)	// Cursor 위치 데이타값 표시
	if ((m_posChart.x >= rcData.left+5) && (m_posChart.x <= rcData.right-5) && (m_posChart.y >= rcData.top+5) && (m_posChart.y <= rcData.bottom-5))		// 표시영역 설정
	{
		CFont font,*pOldFont;	
		font.CreatePointFont(110, _T("Consolas"));	// 10point(x/10), _T("Consolas Bold")
		pOldFont = (CFont*)dc.SelectObject(&font);
		dc.SetTextColor(RGB(0x00,0x00,0xff));		// Blue
		//dc.SetBkColor(RGB(50,50,50));
		SelectObject(hDC, pOldFont);
		DeleteObject(font);

		int y_posTotal = rcData.top-rcData.bottom;
		int y_posTemp = m_posChart.y-rcData.bottom;
		int y_datTotal = (int)(dblYMax-dblYMin);
		int y_datTemp = (int)dblYMin+((y_posTemp*y_datTotal)/y_posTotal);

		CString str;
		str.Format("%d", (int)y_datTemp);
	//	str.Format("%d, %d", m_posChart.x, m_posChart.y);	// 좌표출력
		dc.TextOut(m_posChart.x, m_posChart.y-20, str);	
	//	HPEN hDotPen	= CreatePen(PS_DOT, 1, RGB(0xff,0x00,0xff));
		HPEN hDotPen	= CreatePen(PS_DOT, 1, RGB(0x00,0x00,0xff));
		HPEN hOldPen	= (HPEN)SelectObject(hDC, hDotPen);
		MoveToEx(hDC, 50, m_posChart.y, NULL);
		LineTo(hDC, rcData.right, m_posChart.y);

		SelectObject(hDC, hOldPen);
		DeleteObject(hDotPen);
	}
#endif


}

void MLineChartCtrl::DrawChart(HDC hDC)
{
	CalcDataRect();
	CalcAxis();
	DrawBG(hDC);
	DrawAxisX(hDC);
	DrawAxisY(hDC);
	DrawAxisLine(hDC);
	DrawData(hDC);
}

void MLineChartCtrl::CalcDataRect()
{
	// CALC DATA RECT
	{
		rcData.left		= rcWindow.left		+ m_ChartConfig.nMarginLeft;
		rcData.right	= rcWindow.right	- m_ChartConfig.nMarginRight;
		rcData.top		= rcWindow.top		+ m_ChartConfig.nMarginTop;
		rcData.bottom	= rcWindow.bottom	- m_ChartConfig.nMarginBottom;
	}
}

void MLineChartCtrl::CalcAxis()
{
	// X축 계산
	{
		if(m_aData[0].lstData.GetSize()>m_ChartConfig.nInitWidth)
		{
			nXDataSize = m_ChartConfig.nInitWidth + (int)(((double)(m_aData[0].lstData.GetSize()-m_ChartConfig.nInitWidth)/(double)m_ChartConfig.nWidthExtent)*(double)m_ChartConfig.nWidthExtent);
			nXDataSize = m_ChartConfig.nInitWidth + (int)(((double)(m_aData[0].lstData.GetSize()-m_ChartConfig.nInitWidth)/(double)m_ChartConfig.nWidthExtent)*(double)m_ChartConfig.nWidthExtent);
		}
		else
		{
			nXDataSize = m_ChartConfig.nInitWidth;
		}

		dblXIntv = rcData.Width()/(double)nXDataSize;
	}

	// Y축 계산
	{
		dblYCenter = (m_aData[0].nYMax+m_aData[0].nYMin)/2;

		if(m_aData[0].nYMax-m_aData[0].nYMin<1)
		{
			dblYMin = m_aData[0].nYMin - 1;
			dblYMax = m_aData[0].nYMax + 1;
			dblYDataSize = m_aData[0].nYMax-m_aData[0].nYMin + 2;
		}
		else
		{
			dblYDataSize = m_aData[0].nYMax - m_aData[0].nYMin;
			dblYMin = m_aData[0].nYMin - dblYDataSize*.2;
			dblYMax = m_aData[0].nYMax + dblYDataSize*.2;
			dblYDataSize = dblYMax - dblYMin;
		}

		dblYPixelSize = rcData.Height()/dblYDataSize;
	}
}

void MLineChartCtrl::DrawBG(HDC hDC)
{
	HBRUSH hBrush = CreateSolidBrush(m_ChartConfig.crBG);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	FillRect(hDC, rcWindow, hBrush);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
}

void MLineChartCtrl::DrawAxisLine(HDC hDC)
{
	// DRAW AXIS LINE
	{
		HPEN hAxisLine = CreatePen(PS_SOLID, 2, m_ChartConfig.crAxis);
		HPEN hOldPen = (HPEN)SelectObject(hDC, hAxisLine);
		
		MoveToEx(hDC, rcData.left, rcData.top, NULL);
		LineTo(hDC, rcData.left, rcData.bottom);
		LineTo(hDC, rcData.right, rcData.bottom);
		
		SelectObject(hDC, hOldPen);
		DeleteObject(hAxisLine);
	}

}

void MLineChartCtrl::DrawAxisX(HDC hDC)
{
	// CREATE FONT
	HFONT hFont, hOldFont;
	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));
	strcpy_s(lf.lfFaceName, "Verdana");
	lf.lfHeight = 13;
	hFont = CreateFontIndirect(&lf);
	hOldFont = (HFONT)SelectObject(hDC, hFont);


	// Text Color
	SetTextColor(hDC, m_ChartConfig.crText);
	SetBkColor(hDC, m_ChartConfig.crTextBG);

	// X축 그리기
	{
		HPEN hAxisLine = CreatePen(PS_SOLID, 1, m_ChartConfig.crGuideLine);
		HPEN hOldPen = (HPEN)SelectObject(hDC, hAxisLine);

		int nAxisRight = rcData.left;
		CString szText;
		for(int i=0; i<nXDataSize; i++)
		{
			MoveToEx(hDC, (int)(rcData.left + dblXIntv*i), (int)rcData.bottom, NULL);
			LineTo(hDC, (int)(rcData.left + dblXIntv*i), (int)rcData.bottom+5);

			szText.Format("%d", i+1);

			if(i == 0 || nAxisRight+5 < rcData.left + dblXIntv*i)
			{
				TextOut(hDC, (int)(rcData.left + dblXIntv*i), (int)rcData.bottom +5, szText, szText.GetLength());

				SIZE size;
				GetTextExtentPoint32(hDC, szText, szText.GetLength(), &size);

				nAxisRight = (int)(rcData.left + dblXIntv*i + size.cx);
			}
		}

		SIZE sizeText;
		GetTextExtentPoint32(hDC, m_ChartConfig.szAxisXNM, m_ChartConfig.szAxisXNM.GetLength(), &sizeText);

		TextOut(hDC, rcWindow.right - sizeText.cx - 5, rcWindow.bottom - sizeText.cy - 5, m_ChartConfig.szAxisXNM, m_ChartConfig.szAxisXNM.GetLength());

		SelectObject(hDC, hOldPen);
		DeleteObject(hAxisLine);
	}

	// DELETE FONT
	SelectObject(hDC, hFont);
	DeleteObject(hFont);

}

void MLineChartCtrl::DrawAxisY(HDC hDC)
{
	SetTextColor(hDC, m_ChartConfig.crText);
	SetBkColor(hDC, m_ChartConfig.crTextBG);

	// Y축 그리기
	{
		HPEN hAxisLine = CreatePen(PS_SOLID, 1, m_ChartConfig.crGuideLine);
		HPEN hOldPen = (HPEN)SelectObject(hDC, hAxisLine);
		CString szText;
		SIZE size;

		{
			// MIN, CENTER, MAX
			MoveToEx(hDC, rcData.left - 4, rcData.top, NULL);
			LineTo(hDC, rcData.right, rcData.top);
			szText.Format(m_ChartConfig.szFormat, (int)dblYMax);
			GetTextExtentPoint32(hDC, szText, szText.GetLength(), &size);
			TextOut(hDC, rcData.left - 6 - size.cx, rcData.top - size.cy/2, szText, szText.GetLength());	// y축에서 6pixel 떨어져서 숫자표시

			MoveToEx(hDC, rcData.left - 4, rcData.CenterPoint().y, NULL);
			LineTo(hDC, rcData.right, rcData.CenterPoint().y);
			szText.Format(m_ChartConfig.szFormat, (int)dblYCenter);
			GetTextExtentPoint32(hDC, szText, szText.GetLength(), &size);
			TextOut(hDC, rcData.left - 6 - size.cx, rcData.CenterPoint().y - size.cy/2, szText, szText.GetLength());

			MoveToEx(hDC, rcData.left - 4, rcData.bottom, NULL);
			LineTo(hDC, rcData.right, rcData.bottom);
			szText.Format(m_ChartConfig.szFormat, (int)dblYMin);
			GetTextExtentPoint32(hDC, szText, szText.GetLength(), &size);
			TextOut(hDC, rcData.left - 6 - size.cx, rcData.bottom - size.cy/2, szText, szText.GetLength());
		}

		if(rcData.Height() > 200)	// MIN-CENTER중간, CENTER-MAX중간
		{
			MoveToEx(hDC, rcData.left - 4, (rcData.CenterPoint().y+rcData.top)/2, NULL);
			LineTo(hDC, rcData.right, (rcData.CenterPoint().y+rcData.top)/2);

			szText.Format(m_ChartConfig.szFormat, (int)(dblYMax+dblYCenter)/2);
			GetTextExtentPoint32(hDC, szText, szText.GetLength(), &size);
			TextOut(hDC, rcData.left - 6 - size.cx, (rcData.top+rcData.CenterPoint().y)/2 - size.cy/2, szText, szText.GetLength());

			MoveToEx(hDC, rcData.left - 4, (rcData.CenterPoint().y+rcData.bottom)/2, NULL);
			LineTo(hDC, rcData.right, (rcData.CenterPoint().y+rcData.bottom)/2);

			szText.Format(m_ChartConfig.szFormat, (int)(dblYMin+dblYCenter)/2);
			GetTextExtentPoint32(hDC, szText, szText.GetLength(), &size);
			TextOut(hDC, rcData.left - 6 - size.cx, (rcData.bottom+rcData.CenterPoint().y)/2 - size.cy/2, szText, szText.GetLength());
		}

		TextOut(hDC, 5, 5, m_ChartConfig.szAxisYNM, m_ChartConfig.szAxisYNM.GetLength());

		SelectObject(hDC, hOldPen);
		DeleteObject(hAxisLine);
	}
}
void MLineChartCtrl::DrawData(HDC hDC)
{
//	static BOOL bRelease = TRUE;
//	static int tCnt = 0;

	// DRAW DATA
	{
		int x, y;

		HPEN hDotPen	= CreatePen(PS_SOLID, 1, m_ChartConfig.crDot);
		HPEN hLinePen	= CreatePen(PS_SOLID, 1, m_ChartConfig.crDataLine[0]);
//		HPEN hOldPen	= (HPEN)SelectObject(hDC, hDotPen);
		HPEN hOldPen	= (HPEN)SelectObject(hDC, hLinePen);

//		for(int i=0; i<m_aData[0].lstData.GetSize(); i++)
//		{
//			int tData = (int)m_aData[0].lstData.GetAt(i)->fIntv;
//			int tWhich = m_aData[0].lstData.GetAt(i)->iWho;
//			int tTH = (int)m_aData[1].lstData.GetAt(i)->fIntv;
//			y = rcData.CenterPoint().y + (int)((dblYCenter - tData)*dblYPixelSize);
//			y = rcData.CenterPoint().y + (int)((dblYCenter - m_aData[0].lstData.GetAt(i)->fIntv)*dblYPixelSize);
//			x = (int)(rcData.left + dblXIntv*(i+1));
//			DrawDotRect(hDC, x, y, 2, 2);
//			/*** GUN ***/
//			if ((tData>tTH) && (bRelease==TRUE))
//			{
//				tCnt++;
//				if (tCnt >= 10)
//				{			
//					CString strData;
//					strData.Format("%d-%d", tWhich, tData);
//					TextOut(hDC, x, y-20, strData, lstrlen(strData));
//					bRelease = FALSE;
//				}
//			}
//			else if (tData<tTH)
//			{
//				bRelease = TRUE;
//				tCnt = 0;
//			}
//		}

		SelectObject(hDC, hLinePen);
		if(m_ChartConfig.bShowDataLine)
		{
			for(int i=0; i<m_aData[0].lstData.GetSize(); i++)
			{
				y = rcData.CenterPoint().y + (int)((dblYCenter - m_aData[0].lstData.GetAt(i)->fIntv)*dblYPixelSize);
				x = (int)(rcData.left + dblXIntv*(i+1));
				if(i == 0)	MoveToEx(hDC, x, y, NULL);
				else		LineTo(hDC, x, y);
			}
		}

		hLinePen = CreatePen(PS_SOLID, 1, m_ChartConfig.crDataLine[1]);
		SelectObject(hDC, hLinePen);	// GUN_MARK
		if(m_ChartConfig.bShowDataLine)
		{
			for(int i=0; i<m_aData[1].lstData.GetSize(); i++)
			{
				y = rcData.CenterPoint().y + (int)((dblYCenter - m_aData[1].lstData.GetAt(i)->fIntv)*dblYPixelSize);
				x = (int)(rcData.left + dblXIntv*(i+1));
				if(i == 0)	MoveToEx(hDC, x, y, NULL);
				else		LineTo(hDC, x, y);
			}
		}

		SelectObject(hDC, hOldPen);
		DeleteObject(hDotPen);
		DeleteObject(hLinePen);
	}
}

void MLineChartCtrl::DrawDotRect(HDC hDC, int x, int y, int nW, int nH)
{
	Rectangle(hDC, x-nW, y-nH, x+nW, y+nH);
}

void MLineChartCtrl::OnSize(UINT nType, int cx, int cy)
{
	CreateMemResource();

	CWnd::OnSize(nType, cx, cy);
}

void MLineChartCtrl::CreateMemResource()
{
	CRect r;
	CDC * pDC = GetDC();

	GetClientRect(r);

	if(m_hMemDC == NULL)
		m_hMemDC = CreateCompatibleDC(pDC->m_hDC);

	if(m_hMemBitmap != NULL)
		DeleteObject(m_hMemBitmap);

	m_hMemBitmap = CreateCompatibleBitmap(pDC->m_hDC, r.Width(), r.Height());
	SelectObject(m_hMemDC, m_hMemBitmap);

	ReleaseDC(pDC);
}


void MLineChartCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_posChart = point;

	Invalidate();

	CWnd::OnMouseMove(nFlags, point);
}
