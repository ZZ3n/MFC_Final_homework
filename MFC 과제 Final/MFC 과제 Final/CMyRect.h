#pragma once
#include "CMyShape.h"
class CMyRect :
	public CMyShape
{
public:

	CPoint m_pt1;
	CPoint m_pt2;


	virtual void draw(CDC & dc);
	virtual void set_mouse_down(CPoint pt);
	virtual void set_mouse_up(CPoint pt);
	virtual void set_mouse_move(CPoint pt);
	virtual bool if_inner(CPoint pt);
	virtual void selected_rect(CDC & dc);
	virtual void get_lt_rb(CPoint & lt, CPoint & rb);
	virtual void Move_To(CPoint pt);
	CMyRect();
	~CMyRect();
};

