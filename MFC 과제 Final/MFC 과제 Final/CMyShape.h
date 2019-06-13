#pragma once
class CMyShape
{
public:

	enum {RECT,CIRCLE,CURVE,STAR,SELECT};

	CMyShape();
	~CMyShape();

	CBrush m_brush;
	CPen m_pen;
	COLORREF m_color;
	COLORREF m_out_color;
	bool selected;
	int r, g, b;

	virtual void draw(CDC & dc);
	virtual void set_mouse_down(CPoint pt) = 0;
	virtual void set_mouse_up(CPoint pt) = 0;
	virtual void set_mouse_move(CPoint pt) = 0;
	virtual bool if_inner(CPoint pt) = 0;
	virtual void selected_rect(CDC & dc) = 0;
	// ����-��ȯ, get_lt_rb(lt,rb)
	virtual void get_lt_rb(CPoint & lt,CPoint & rb) = 0;

	virtual void Move_To(CPoint pt) = 0;
};

// 1 ����Ʈ ������ ���� �̵�.
// 2 �巡���ϸ� �̵�.
// 3 �׷��� ��� ���� �̵�.
// mousemove,lbuttonup