#include "StdAfx.h"
#include "MLineChartData.h"
#include <math.h>

MLineChartData::MLineChartData(void)
{

}

MLineChartData::~MLineChartData(void)
{
	Clear();
}

int MLineChartData::Add(float fOrigin, float fDest, int iWho)
{
	__ITEM* item = new __ITEM;
	item->fOrigin = fOrigin;
	item->fDest = fDest;
	item->fIntv = fabs(fOrigin-fDest);
//	item->fIntv = fOrigin-fDest;
item->iWho = iWho;	// GUN
	lstData.Add(item);

	if(lstData.GetSize() == 1)
	{
		nYMin = nYMax = item->fIntv;
	}
	else if(item->fIntv < nYMin)
	{
		nYMin = item->fIntv;
	}
	else if(item->fIntv > nYMax)
	{
		nYMax = item->fIntv;
	}
	return (int)lstData.GetSize();
}

void MLineChartData::Clear()
{
	for(int i=lstData.GetSize()-1; i>=0; i--)
	{
		delete lstData.GetAt(i);
	}

	lstData.RemoveAll();
}