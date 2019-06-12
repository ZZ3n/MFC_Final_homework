#include "stdafx.h"
#include "CMyShape.h"


CMyShape::CMyShape()
{
	selected = FALSE;
	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;
	m_color = RGB(r, g, b);
	m_brush.CreateSolidBrush(m_color);
	m_color = RGB(0.7*r, 0.7*g, 0.7*b);
	m_pen.CreatePen(PS_SOLID, 4, m_color);
}

CMyShape::~CMyShape()
{
}

void CMyShape::draw(CDC & dc)
{
	dc.SelectObject(m_brush);
	dc.SelectObject(m_pen);
}