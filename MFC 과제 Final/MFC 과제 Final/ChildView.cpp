
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFC 과제 Final.h"
#include "ChildView.h"

#include "CMyRect.h"
#include "CMyCircle.h"
#include "CMyCurve.h"
#include "CMyStar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
	: bLButton(false), draw_mode(CMyShape::RECT)
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_RECT, &CChildView::OnDrawRect)
	ON_COMMAND(ID_DRAW_STAR, &CChildView::OnDrawStar)
	ON_COMMAND(ID_DRAW_CIRCLE, &CChildView::OnDrawCircle)
	ON_COMMAND(ID_DRAW_CURVE, &CChildView::OnDrawCurve)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	CRect rect;
	GetClientRect(rect);
	int w = rect.Width();
	int h = rect.Height();

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, w, h);
	memDC.SelectObject(bmp);
	memDC.Rectangle(0,0,w,h);

	///////////////사전처리/////////////////////

	////////////////////////////////////////////
	

	///////////////그리는 부분//////////////////
	POSITION pos = shape_list.GetHeadPosition();
	while (pos != NULL)
	{
		shape_list.GetNext(pos)->draw(memDC);
	}
	////////////////////////////////////////////

	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);
}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CWnd::OnEraseBkgnd(pDC);
	return true;
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	POSITION pos;
	switch (draw_mode)
	{
	case CMyShape::RECT:
		pos = shape_list.AddTail(new CMyRect());
		break;
	case CMyShape::CURVE:
		pos = shape_list.AddTail(new CMyCurve());
		break;
	case CMyShape::CIRCLE:
		pos = shape_list.AddTail(new CMyCircle());
		break;
	case CMyShape::STAR:
		pos = shape_list.AddTail(new CMyStar());
		break;
	default:
		break;
	}
	
	shape_list.GetTail()->set_mouse_down(point);
	bLButton = true;
	SetCapture();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	shape_list.GetTail()->set_mouse_up(point);
	bLButton = false;
	Invalidate();
	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (bLButton == true)
	{
		shape_list.GetTail()->set_mouse_move(point);
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnDrawRect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	draw_mode = CMyShape::RECT;
	
}


void CChildView::OnDrawStar()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	draw_mode = CMyShape::STAR;
}


void CChildView::OnDrawCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	draw_mode = CMyShape::CIRCLE;
}


void CChildView::OnDrawCurve()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	draw_mode = CMyShape::CURVE;
}
