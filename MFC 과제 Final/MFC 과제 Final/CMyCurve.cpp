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
	TRACE("%d", ind);
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
bool CMyCurve::if_inner(CPoint pt)
{
	POSITION pos = pts.GetHeadPosition();
	CPoint linergn[4];
	int x, y, w, h;
	double angle, theta;
	int ind = 0;
	double PI = 3.141592;
	int dx, dy;
	int LINE_WIDTH = 12;
	while (pos != NULL)
	{
		if (ind == 0)
		{
			x = pts.GetAt(pos).x;
			y = pts.GetAt(pos).y;
			pts.GetNext(pos);
		}
		else
		{
			w = pts.GetAt(pos).x - x;
			h = pts.GetAt(pos).y - y; 
			theta = w ? atan(double(h) / double(w))
				: sin(h) * PI / 2.;
			if (theta < 0)
			{
				theta = theta + 2 * PI;
			}
			angle = (theta + PI / 2.);
			dx = int(LINE_WIDTH * cos(angle));
			dy = int(LINE_WIDTH * sin(angle));

			linergn[0] = CPoint(x + dx, y + dy);
			linergn[1] = CPoint(x - dx, y - dy);
			linergn[2] = CPoint(x + w - dx, y + h - dy);
			linergn[3] = CPoint(x + w + dx, y + h + dy);

			CRgn rgn;
			rgn.CreatePolygonRgn(linergn, 4, WINDING);

			if (rgn.PtInRegion(pt))
				return true;

			x = pts.GetAt(pos).x;
			y = pts.GetAt(pos).y;
			pts.GetNext(pos);
		}

		ind++;
	}

	return false;
}
void CMyCurve::selected_rect(CDC & dc)
{
	CPen tmppen;
	tmppen.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	dc.SelectObject(tmppen);

	CBrush tmpbrush;
	tmpbrush.CreateStockObject(NULL_BRUSH);
	dc.SelectObject(tmpbrush);

	POSITION pos = pts.GetHeadPosition();
	CPoint pt = pts.GetAt(pos);
	CPoint lt, rb;
	lt = pt;
	rb = pt;
	
	while (pos != NULL)
	{
		if (pt.x <= lt.x)
			lt.x = pt.x;
		if (pt.y >= lt.y)
			lt.y = pt.y;

		if (pt.x >= rb.x)
			rb.x = pt.x;
		if (pt.y <= rb.y)
			rb.y = pt.y;

		pt = pts.GetNext(pos);
	}
	
	dc.Rectangle(lt.x - 8, lt.y + 8, rb.x + 8, rb.y- 8);
}
void CMyCurve::get_lt_rb(CPoint & lt, CPoint & rb)
{
	POSITION pos = pts.GetHeadPosition();
	CPoint pt = pts.GetAt(pos);
	lt = pt;
	rb = pt;

	while (pos != NULL)
	{
		if (pt.x <= lt.x)
			lt.x = pt.x;
		if (pt.y >= lt.y)
			lt.y = pt.y;

		if (pt.x >= rb.x)
			rb.x = pt.x;
		if (pt.y <= rb.y)
			rb.y = pt.y;

		pt = pts.GetNext(pos);
	}
	lt.x -= 8;	lt.y += 8;
	rb.x += 8;	rb.y -= 8;

}
