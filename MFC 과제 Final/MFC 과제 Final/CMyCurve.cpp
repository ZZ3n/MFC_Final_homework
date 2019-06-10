#include "stdafx.h"
#include "CMyCurve.h"


CMyCurve::CMyCurve()
{
}


CMyCurve::~CMyCurve()
{
}

void CMyCurve::draw(CDC & dc)
{
	CMyShape::draw(dc);

	POSITION pos = pts.GetHeadPosition();
	int ind = 0;
	while (pos != NULL)
	{
		CPoint pt = pts.GetNext(pos);
		if (ind == 0)
			dc.MoveTo(pt);
		else
			dc.LineTo(pt);
		ind++;
	}

}
void CMyCurve::set_mouse_down(CPoint pt)
{
	pts.AddTail(pt);
}
void CMyCurve::set_mouse_up(CPoint pt)
{
	pts.AddTail(pt);
}
void CMyCurve::set_mouse_move(CPoint pt)
{
	pts.AddTail(pt);
}