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
	// 참조-반환, get_lt_rb(lt,rb)
	virtual void get_lt_rb(CPoint & lt,CPoint & rb) = 0;

	virtual void Move_To(CPoint pt) = 0;
};

// 1 쉬프트 누르면 같이 이동.
// 2 드래그하면 이동.
// 3 그룹일 경우 같이 이동.
// mousemove,lbuttonup