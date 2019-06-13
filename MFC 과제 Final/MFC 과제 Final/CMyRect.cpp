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
bool CMyRect::if_inner(CPoint pt)
{
	CPoint lt, rb; // lefttop,rightbottom

	if (m_pt1.x < m_pt2.x)
	{
		lt.x = m_pt1.x;
		rb.x = m_pt2.x;
	}
	else
	{
		lt.x = m_pt2.x;
		rb.x = m_pt1.x;
	}

	if (m_pt1.y > m_pt2.y)
	{
		lt.y = m_pt1.y;
		rb.x = m_pt2.x;
	}
	else
	{
		lt.y = m_pt2.y;
		rb.y = m_pt1.y;
	}

	if (pt.x >= lt.x && pt.x <= rb.x && pt.y >= rb.y && pt.y <= lt.y)
	{
		return true;
	}
	else
		return false;
}
void CMyRect::selected_rect(CDC & dc)
{
	CPoint lt, rb; // lefttop,rightbottom

	if (m_pt1.x < m_pt2.x)
	{
		lt.x = m_pt1.x;
		rb.x = m_pt2.x;
	}
	else
	{
		lt.x = m_pt2.x;
		rb.x = m_pt1.x;
	}

	if (m_pt1.y > m_pt2.y)
	{
		lt.y = m_pt1.y;
		rb.x = m_pt2.x;
	}
	else
	{
		lt.y = m_pt2.y;
		rb.y = m_pt1.y;
	}

	CPen tmppen;
	tmppen.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	dc.SelectObject(tmppen);

	int SPACE = 8;

	CBrush tmpbrush;
	tmpbrush.CreateStockObject(NULL_BRUSH);
	dc.SelectObject(tmpbrush);
	
	dc.Rectangle(lt.x - SPACE, lt.y + SPACE, rb.x + SPACE, rb.y - SPACE);
	
}
void CMyRect::get_lt_rb(CPoint & lt, CPoint & rb)
{
	int SPACE = 8;
	if (m_pt1.x < m_pt2.x)
	{
		lt.x = m_pt1.x;
		rb.x = m_pt2.x;
	}
	else
	{
		lt.x = m_pt2.x;
		rb.x = m_pt1.x;
	}

	if (m_pt1.y > m_pt2.y)
	{
		lt.y = m_pt1.y;
		rb.y = m_pt2.y;
	}
	else
	{
		lt.y = m_pt2.y;
		rb.y = m_pt1.y;
	}

	lt.x -= SPACE; lt.y += SPACE;
	rb.x += SPACE; rb.y -= SPACE;
}

void CMyRect::Move_To(CPoint pt)
{
	m_pt1 += pt;
	m_pt2 += pt;
}