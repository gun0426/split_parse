#include "StdAfx.h"
#include "MLineChartConfig.h"

MLineChartConfig::MLineChartConfig(void)
{
	nInitWidth = 10;
	nWidthExtent = 10;

	crDot = RGB(255, 0, 0);
	crDataLine[0] = RGB(255, 0, 0);
	crDataLine[1] = RGB(0, 0, 255);
	crBG = RGB(255, 255, 255);
	crGuideLine = RGB(128, 128, 128);
	crAxis = RGB(0, 0, 0);
	crText = RGB(0, 0, 0);
	crTextBG = RGB(255, 255, 255);

	bShowGuideLine = FALSE;
	bShowDataLine = TRUE;

	bAxisYSensitive = TRUE;
	dblAxisYMin = 0;
	dblAxisYMax = 0;

	nMarginTop = 30;
	nMarginLeft = 50;
	nMarginBottom = 40;
	nMarginRight = 20;

	szAxisXNM = "Axis X";
	szAxisYNM = "Delta ¥Ä";		// "Axis Y";
	szFormat = "%d";			//"%.1f";
}

MLineChartConfig::~MLineChartConfig(void)
{
}
