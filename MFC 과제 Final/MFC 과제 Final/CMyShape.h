#pragma once
class CMyShape
{
public:

	enum {RECT,CIRCLE,CURVE,STAR};

	CMyShape();
	~CMyShape();

	CBrush m_brush;
	CPen m_pen;
	COLORREF m_color;
	COLORREF m_out_color;
	int r, g, b;

	virtual void draw(CDC & dc);
	virtual void set_mouse_down(CPoint pt) = 0;
	virtual void set_mouse_up(CPoint pt) = 0;
	virtual void set_mouse_move(CPoint pt) = 0;
};

