#pragma once
#include "CMyShape.h"
class CMyCircle :
	public CMyShape
{
public:

	CPoint center;
	int radius;


	CMyCircle();
	~CMyCircle();

	virtual void draw(CDC & dc);
	virtual void set_mouse_down(CPoint pt);
	virtual void set_mouse_up(CPoint pt);
	virtual void set_mouse_move(CPoint pt);

};

