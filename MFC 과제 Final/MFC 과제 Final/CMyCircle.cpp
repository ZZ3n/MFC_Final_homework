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