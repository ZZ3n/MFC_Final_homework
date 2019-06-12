#include "stdafx.h"
#include "CMyStar.h"



CMyStar::CMyStar()
	:radius(0),pivot(0,0)
{
}


CMyStar::~CMyStar()
{
}

void CMyStar::draw(CDC & dc)
{
	CMyShape::draw(dc);
	double PI = 3.141592;
	double s_radius = //Á¤È®ÇÑ ºñ·Ê¸¦ ¸ÂÃç¼­.
		cos(PI * 2.0 / 5.0) / cos(PI / 5.0) * radius;
	for (int i = 0; i < 10; i += 2)
	{
		//points[i].x = (long)(25*cos((double)(i*72*Pi)/360.0));
		pts[i].x = pivot.x +
			(long)(s_radius*sin((double)(i * 72 * PI) / 360.0));
					
		pts[i].y = pivot.y +
			(long)(s_radius*cos((double)(i * 72 * PI) / 360.0));

		pts[i+1].x = pivot.x +
			(long)(radius*sin((double)((i+1) * 72 * PI) / 360.0));

		pts[i+1].y = pivot.y +
			(long)(radius*cos((double)((i+1) * 72 * PI) / 360.0));

	}
	pts[10] = pts[0];

	CRgn rgnstar;
	rgnstar.CreatePolygonRgn(pts, 11, WINDING);
	TRACE("%f",radius);
	dc.Polygon(pts, 10);

}
void CMyStar::set_mouse_down(CPoint pt)
{
	pivot = pt;
}
void CMyStar::set_mouse_up(CPoint pt)
{
	radius = sqrt((pt.x - pivot.x) * (pt.x - pivot.x)
		+ (pt.y - pivot.y) * (pt.y - pivot.y));
}
void CMyStar::set_mouse_move(CPoint pt)
{
	radius = sqrt((pt.x - pivot.x) * (pt.x - pivot.x)
		+ (pt.y - pivot.y) * (pt.y - pivot.y));
}
bool CMyStar::if_inner(CPoint pt)
{
	CRgn rgn;
	rgn.CreatePolygonRgn(pts, 11, WINDING);
	return rgn.PtInRegion(pt);
}
void CMyStar::selected_rect(CDC & dc)
{
	CPen tmppen;
	tmppen.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	dc.SelectObject(tmppen);

	CBrush tmpbrush;
	tmpbrush.CreateStockObject(NULL_BRUSH);
	dc.SelectObject(tmpbrush);

	CPoint lt, rb;
	lt.y = pts[5].y - 5;
	lt.x = pts[7].x - 5;
	rb.y = pts[1].y + 5;
	rb.x = pts[3].x + 5;

	dc.Rectangle(lt.x,lt.y,rb.x,rb.y);
}