#include "stdafx.h"
#include "CMyShape.h"

int CMyShape::num_shape = 0;

CMyShape::CMyShape()
{
	srand(time(NULL));
	num_shape++;
	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;
	m_color = RGB(r, g, b);

	m_brush.CreateSolidBrush(m_color);
	m_pen.CreatePen(PS_SOLID, 3, m_color);
}

CMyShape::~CMyShape()
{
	num_shape--;
}

void CMyShape::draw(CDC & dc)
{
	dc.SelectObject(m_brush);
	dc.SelectObject(m_pen);
}