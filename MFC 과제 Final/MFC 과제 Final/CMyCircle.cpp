#include "stdafx.h"
#include "CMyCircle.h"


CMyCircle::CMyCircle()
	:radius(0),center(0,0)
{
}


CMyCircle::~CMyCircle()
{
}

void CMyCircle::draw(CDC & dc)
{
	CMyShape::draw(dc);

	dc.Ellipse(center.x - radius, center.y - radius, 
		center.x + radius, center.y + radius);
}
void CMyCircle::set_mouse_down(CPoint pt)
{
	center = pt;
}
void CMyCircle::set_mouse_up(CPoint pt)
{
	radius = sqrt((pt.x - center.x) * (pt.x - center.x)
		+ (pt.y - center.y) * (pt.y - center.y));
}
void CMyCircle::set_mouse_move(CPoint pt)
{
	radius = sqrt((pt.x - center.x) * (pt.x - center.x)
		+ (pt.y - center.y) * (pt.y - center.y));
}
bool CMyCircle::if_inner(CPoint pt)
{
	double dist2;
	dist2 = sqrt((pt.x - center.x)*(pt.x - center.x) +
		(pt.y - center.y)*(pt.y - center.y));
	if (dist2 <= radius)
		return true;
	else
		return false;
}
void CMyCircle::selected_rect(CDC & dc)
{
	CPen tmppen;
	tmppen.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	dc.SelectObject(tmppen);

	CBrush tmpbrush;
	tmpbrush.CreateStockObject(NULL_BRUSH);
	dc.SelectObject(tmpbrush);

	dc.Rectangle(center.x - radius - 5,center.y + radius + 5,
		center.x + radius + 5,center.y - radius - 5);
}