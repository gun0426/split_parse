#pragma once

#define CHART_DATA_N	10

class MLineChartConfig
{
public:
	MLineChartConfig(void);
public:
	~MLineChartConfig(void);

public:
	int nInitWidth;
	int nWidthExtent;

	COLORREF crDot;
	COLORREF crDataLine[CHART_DATA_N];
	COLORREF crBG;
	COLORREF crGuideLine;
	COLORREF crAxis;
	COLORREF crText;
	COLORREF crTextBG;

	BOOL bShowGuideLine;
	BOOL bShowDataLine;

	BOOL bAxisYSensitive;
	double dblAxisYMin;
	double dblAxisYMax;

	// LEFT, BOTTOM Margin�� �� ������ ǥ�õ�.
	int nMarginTop;
	int nMarginLeft;
	int nMarginBottom;
	int nMarginRight;

	CString szAxisXNM;
	CString szAxisYNM;
	CString szFormat;
};
