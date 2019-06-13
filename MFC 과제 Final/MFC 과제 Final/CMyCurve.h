#pragma once
#include "CMyShape.h"
class CMyCurve :
	public CMyShape
{
public:

	CList<CPoint> pts;

	CMyCurve();
	~CMyCurve();

	virtual void draw(CDC & dc);
	virtual void set_mouse_down(CPoint pt);
	virtual void set_mouse_up(CPoint pt);
	virtual void set_mouse_move(CPoint pt);
	virtual bool if_inner(CPoint pt);
	virtual void selected_rect(CDC & dc);
	virtual void get_lt_rb(CPoint & lt, CPoint & rb);
	virtual void Move_To(CPoint pt);
};

