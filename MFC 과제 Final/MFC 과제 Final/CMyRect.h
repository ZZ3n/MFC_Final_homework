#pragma once
#include "CMyShape.h"
class CMyRect :
	public CMyShape
{
public:

	CPoint m_pt1;
	CPoint m_pt2;


	virtual void draw(CDC dc);
	virtual void set_mouse_down(CPoint pt);
	virtual void set_mouse_up(CPoint pt);
	virtual void set_mouse_move(CPoint pt);

	CMyRect();
	~CMyRect();
};

