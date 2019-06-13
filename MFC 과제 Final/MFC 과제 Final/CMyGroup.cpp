#include "stdafx.h"
#include "CMyGroup.h"

void CMyGroup::setting_lt_rb()
{
	POSITION pos;
	CPoint _lt, _rb;
	pos = this->nodes.GetHeadPosition();
	nodes.GetAt(pos)->get_lt_rb(this->LT, this->RB);
	while (pos != NULL)
	{
		this->nodes.GetNext(pos)->get_lt_rb(_lt, _rb);
		
		if (_lt.y >= LT.y)
			LT.y = _lt.y;
		if (_lt.x <= LT.x)
			LT.x = _lt.x;

		if (_rb.y <= RB.y)
			RB.y = _rb.y;
		if (_rb.x >= RB.x)
			RB.x = _rb.x;
	}
}

void CMyGroup::selected_group_rect(CDC & dc)
{
	setting_lt_rb();

	CPen tmppen;
	tmppen.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	dc.SelectObject(tmppen);

	CBrush tmpbrush;
	tmpbrush.CreateStockObject(NULL_BRUSH);
	dc.SelectObject(tmpbrush);

	dc.Rectangle(LT.x, LT.y, RB.x, RB.y);
}

CMyGroup::CMyGroup(CMyGroup & G, CMyGroup & H)
{
	POSITION pos;
	pos = this->nodes.GetHeadPosition();
	this->nodes.AddTail(&G.nodes);
	this->nodes.AddTail(&H.nodes);
	this->setting_lt_rb();
	this->g_selected = true;
}

CMyGroup::CMyGroup()
	:g_selected(false)
{
}

CMyGroup::CMyGroup(CMyShape * new_node)
	:g_selected(false)
{
	this -> nodes.AddTail(new_node);
}

CMyGroup::~CMyGroup()
{
}

