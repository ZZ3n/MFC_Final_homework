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

CMyGroup::CMyGroup()
{
}

CMyGroup::CMyGroup(CMyShape * new_node)
{
	this -> nodes.AddTail(new_node);
	setting_lt_rb();
}

CMyGroup::~CMyGroup()
{
}

