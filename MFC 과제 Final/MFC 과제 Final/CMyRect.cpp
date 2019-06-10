#include "stdafx.h"
#include "CMyRect.h"


CMyRect::CMyRect()
	: m_pt1(0,0),m_pt2(0,0)
{
}


CMyRect::~CMyRect()
{
}

void CMyRect::draw(CDC & dc)
{
	CMyShape::draw(dc);

	dc.Rectangle(m_pt1.x, m_pt1.y, m_pt2.x, m_pt2.y);
	
}
void CMyRect::set_mouse_down(CPoint pt)
{
	
	m_pt1 = pt;
	
}
void CMyRect::set_mouse_up(CPoint pt)
{
	m_pt2 = pt;
}
void CMyRect::set_mouse_move(CPoint pt)
{
	m_pt2 = pt;
}