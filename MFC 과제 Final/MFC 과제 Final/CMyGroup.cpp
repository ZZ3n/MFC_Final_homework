#include "stdafx.h"
#include "CMyGroup.h"


CMyGroup::CMyGroup()
{
}


CMyGroup::~CMyGroup()
{
}

/*
���� �׷����� ���´ٸ�.

	1. Ʈ������
		�� Clist ������ ���� ( Ʈ�� ) -> X  
		 �� �����ͷ� ����. -> O

	1-1 . ��尡 ������? �ƴϸ� ��尡 �ϳ�?
		�� ��� �������� ����Ʈ ������ �����ϰų� -> �̰ɷ� ����.
		�� �ƴϸ� ��� �ϳ��� ����Ʈ ������ ���� -> ������ �Ȱ���

	2. �����ؾ��� Ŭ���� ������.
	
	2-1. �׷��� ������ ���� int�� ���� �ϳ�. -> static���� �����ϸ� �� ��.

	####�����غ��� �ν��Ͻ��� ������ �����ϴ°� ���� �� ��.
	####�׷��Ƿ� Ŭ���� �ȿ� ����Ʈ ������ �׷���� ���� �ϴ� ���� ������ ��.
	#### e.g. CList <CMyShape*> group;

	3. �׷쿡 CMyShape�� ��ӹ޾ƾ� �ұ�?
	�� �׷쿡 ��ӹ����� ���콺 Ŭ��.
		virtual void set_mouse_down(CPoint pt) = 0;
		virtual void set_mouse_up(CPoint pt) = 0;
		virtual void set_mouse_move(CPoint pt) = 0;
		virtual bool if_inner(CPoint pt) = 0;
		virtual void selected_rect(CDC & dc) = 0;
	�װ��� �Լ��� �����ؾ���.

	#### ���߼��� ���� -> �����̴� �� ����. align ����.
*/