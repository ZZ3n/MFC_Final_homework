
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFC 과제 Final.h"
#include "ChildView.h"

#include "CMyRect.h"
#include "CMyCircle.h"
#include "CMyCurve.h"
#include "CMyStar.h"
#include "CMyGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
	: bLButton(false), draw_mode(CMyShape::RECT),bShift(FALSE),num_selected(0)
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
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CChildView::OnUpdateDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CURVE, &CChildView::OnUpdateDrawCurve)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, &CChildView::OnUpdateDrawRect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_STAR, &CChildView::OnUpdateDrawStar)
	ON_COMMAND(ID_ACTION_SELECT, &CChildView::OnActionSelect)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SELECT, &CChildView::OnUpdateActionSelect)
	ON_COMMAND(ID_ACTION_GROUP, &CChildView::OnActionGroup)
	ON_UPDATE_COMMAND_UI(ID_ACTION_GROUP, &CChildView::OnUpdateActionGroup)
	ON_COMMAND(ID_ACTION_UNGROUP, &CChildView::OnActionUngroup)
	ON_UPDATE_COMMAND_UI(ID_ACTION_UNGROUP, &CChildView::OnUpdateActionUngroup)
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
	

	///////////////도형 + 빨간 점선 그림//////////////////
	num_selected = 0;
	POSITION pos = shape_list.GetHeadPosition();
	while (pos != NULL)
	{
		if (shape_list.GetAt(pos)->selected == true)
		{
			shape_list.GetAt(pos)->selected_rect(memDC);
			num_selected++;
		}
		shape_list.GetNext(pos)->draw(memDC);
	}
	////////////////////////////////////////////
	
	CString strEx;
	strEx.Format(_T("Number of Selected Shape : %d"), num_selected);
	memDC.TextOutW(1, 1, strEx,strEx.GetLength());


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
	POSITION pos_shape;
	POSITION pos_group;

	switch (draw_mode)
	{
	case CMyShape::RECT:
		pos_shape = shape_list.AddTail(new CMyRect());
		pos_group = group_list.AddTail( new CMyGroup( shape_list.GetTail() ) );
		break;
	case CMyShape::CURVE:
		pos_shape = shape_list.AddTail(new CMyCurve());
		pos_group = group_list.AddTail(new CMyGroup(shape_list.GetTail()));
		break;
	case CMyShape::CIRCLE:
		pos_shape = shape_list.AddTail(new CMyCircle());
		pos_group = group_list.AddTail(new CMyGroup(shape_list.GetTail()));
		break;
	case CMyShape::STAR:
		pos_shape = shape_list.AddTail(new CMyStar());
		pos_group = group_list.AddTail(new CMyGroup(shape_list.GetTail()));
		break;
	case CMyShape::SELECT:
		pos_shape = shape_list.GetTailPosition();
		POSITION only_one;
		while (pos_shape != NULL)
		{
			if (shape_list.GetAt(pos_shape)->if_inner(point) == TRUE) // 클릭 되었음.
			{
				shape_list.GetAt(pos_shape)->selected = TRUE;
				only_one = pos_shape;
				Invalidate();
				break;
			}
			else
			{
				shape_list.GetPrev(pos_shape);
			}
		}
		//다른 곳이 클릭되었을 경우에. && shift키가 안 눌렸을 경우. 다 지워야 함.
		if (bShift == FALSE)
		{
			pos_shape = shape_list.GetTailPosition();
			while (pos_shape != NULL)
			{
				if (pos_shape == only_one)
				{
					shape_list.GetPrev(pos_shape);
					continue;
				}
				if (shape_list.GetAt(pos_shape)->selected == TRUE) // 선택되었다면.
				{
					shape_list.GetAt(pos_shape)->selected = FALSE; // 지우기.
				}
				shape_list.GetPrev(pos_shape);
			}
			Invalidate();
		}
		
		break;
		
	default:
		break;
	}
	if (draw_mode != CMyShape::SELECT)
		shape_list.GetTail()->set_mouse_down(point);
	bLButton = true;
	SetCapture();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (draw_mode != CMyShape::SELECT)
		shape_list.GetTail()->set_mouse_up(point);
	bLButton = false;
	Invalidate();
	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SHIFT)
		bShift = TRUE;
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SHIFT)
		bShift = FALSE;
	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (bLButton == true)
	{
		if (draw_mode != CMyShape::SELECT)
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


void CChildView::OnActionSelect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	draw_mode = CMyShape::SELECT;
}



void CChildView::OnUpdateDrawCircle(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (draw_mode == CMyShape::CIRCLE)
	{
		//pCmdUI->Enable(false);
		pCmdUI->SetCheck(true);
	}
	else
	{
		pCmdUI->SetCheck(false);
		//pCmdUI->Enable(true);
	}
	
}


void CChildView::OnUpdateDrawCurve(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (draw_mode == CMyShape::CURVE)
	{
		pCmdUI->SetCheck(true);
		//pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->SetCheck(false);
		//pCmdUI->Enable(true);
	}
}


void CChildView::OnUpdateDrawRect(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (draw_mode == CMyShape::RECT)
	{
		pCmdUI->SetCheck(true);
		//pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->SetCheck(false);
		//pCmdUI->Enable(true);
	}
}


void CChildView::OnUpdateDrawStar(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (draw_mode == CMyShape::STAR)
	{
		pCmdUI->SetCheck(true);
		//pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->SetCheck(false);
	//	pCmdUI->Enable(true);
	}
}



void CChildView::OnUpdateActionSelect(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (draw_mode == CMyShape::SELECT)
	{
		pCmdUI->SetCheck(true);
		//pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->SetCheck(false);
		//	pCmdUI->Enable(true);
	}
}


void CChildView::OnActionGroup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	
}


void CChildView::OnUpdateActionGroup(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	if (num_selected >= 2)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}


void CChildView::OnActionUngroup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildView::OnUpdateActionUngroup(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (num_selected >= 1)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}
