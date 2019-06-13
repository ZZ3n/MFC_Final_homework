#pragma once
#include "CMyShape.h"
class CMyGroup
{
public:
	CList <CMyShape *> nodes;
	bool g_selected;
	CPoint LT, RB;

	void setting_lt_rb();


	CMyGroup();
	//메모리 누수에 주의하기! G 뒤에 H가 연결됨. \
	 +) G와 H의 메모리가 해제됨.
	CMyGroup(CMyGroup & G, CMyGroup & H);
	CMyGroup(CMyShape * new_node);
	~CMyGroup();
};


/*
addGroup 함수. (inc.addShape)
생성자. -> shape하나당 그룹 한개.
*/

/*
만약 그룹으로 묶는다면.

1. 트리구조
ㄴ Clist 구조로 구현 ( 트리 ) -> X
ㄴ 포인터로 구현. -> O

1-1 . 헤드가 여러개? 아니면 헤드가 하나?
※ 헤드 여러개를 리스트 구조로 관리하거나 -> 이걸로 하자.
※ 아니면 헤드 하나에 리스트 구조로 연결 -> 어차피 똑같음

2. 포함해야할 클래스 변수들.

2-1. 그룹의 갯수를 세는 int형 변수 하나. -> static으로 구현하면 될 듯.

####생각해보니 인스턴스를 여러개 생성하는게 나을 듯 함.
####그러므로 클래스 안에 리스트 구조로 그룹들을 포함 하는 것이 좋을듯 함.
#### e.g. CList <CMyShape*> group;

3. 그룹에 CMyShape를 상속받아야 할까?
ㄴ 그룹에 상속받으면 마우스 클릭.
virtual void set_mouse_down(CPoint pt) = 0;
virtual void set_mouse_up(CPoint pt) = 0;
virtual void set_mouse_move(CPoint pt) = 0;
virtual bool if_inner(CPoint pt) = 0;
virtual void selected_rect(CDC & dc) = 0;
네가지 함수를 구현해야함.

#### 다중선택 구현 -> 움직이는 것 구현. align 구현.
*/