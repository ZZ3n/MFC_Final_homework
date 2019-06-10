#pragma once
#include "CMyShape.h"
class CMyStar :
	public CMyShape
{
public:

	CPoint pts[11];
	CPoint pivot;
	double radius;

	CMyStar();
	~CMyStar();

	virtual void draw(CDC & dc);
	virtual void set_mouse_down(CPoint pt);
	virtual void set_mouse_up(CPoint pt);
	virtual void set_mouse_move(CPoint pt);
};

