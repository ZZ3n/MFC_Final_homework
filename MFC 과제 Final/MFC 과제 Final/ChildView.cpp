
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
	: bLButton(false), draw_mode(CMyShape::RECT),bShift(FALSE),num_selected(0),bDrag(false)
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
	ON_COMMAND(ID_ALIGN_BRINGBACK, &CChildView::OnAlignBringback)
	ON_COMMAND(ID_ALIGN_BRINGFRONT, &CChildView::OnAlignBringfront)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDOWN()
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
	

	///////////////도형 + 빨간 점선 그림 + seleted calc.//////////////////
	num_selected = 0;
	POSITION pos_group = group_list.GetHeadPosition();
	POSITION posi;
	int num_of_shapes = 0;
	while (pos_group != NULL)
	{
		posi = group_list.GetAt(pos_group)->nodes.GetHeadPosition();
		if (group_list.GetAt(pos_group)->g_selected == TRUE)
		{
			group_list.GetAt(pos_group)->selected_group_rect(memDC);
			num_selected++;
		}
		while (posi != NULL)
		{
			group_list.GetAt(pos_group)->nodes.GetAt(posi)->draw(memDC);
			group_list.GetAt(pos_group)->nodes.GetNext(posi);
		}
		group_list.GetNext(pos_group);
		num_of_shapes++;
	}
	if (bDrag == true)
	{
		CPen tmppen;
		tmppen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		memDC.SelectObject(tmppen);

		CBrush tmpbrush;
		tmpbrush.CreateStockObject(NULL_BRUSH);
		memDC.SelectObject(tmpbrush);

		memDC.Rectangle(drag1.x, drag1.y, drag2.x, drag2.y);
	}
	////////////////////////////////////////////
	
	CString strEx[2];
	CFont font;
	font.CreateFontW(15, 8, 0, 0, 5, 
		false, false, false, DEFAULT_CHARSET,OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("굴림체"));
	memDC.SelectObject(font);
	strEx[0].Format(_T("Number of Shapes: %d"), num_of_shapes);
	strEx[1].Format(_T("Number of Selected: %d"), num_selected);
	memDC.SetBkMode(TRANSPARENT);
	memDC.TextOutW(2, 1, strEx[0],strEx[0].GetLength());
	memDC.TextOutW(2, 13, strEx[1], strEx[1].GetLength());


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
		move1 = point;
		pos_group = group_list.GetTailPosition();
		POSITION only_group;
		POSITION posi;
		bDrag = true;
		while (pos_group != NULL) // 그룹 리스트를 역순회 ( 최근 추가 순 부터 순회 )
		{
			// 그룹 속의 리스트의 헤드 포지션으로 이동.
			posi = group_list.GetAt(pos_group)->nodes.GetTailPosition();
			while (posi != NULL) // 그룹의 list를 역순회 ( 최근 추가 순부터 순회 )
			{
				if (group_list.GetAt(pos_group)->nodes.GetAt(posi)->if_inner(point) == TRUE)
				{
					group_list.GetAt(pos_group)->g_selected = TRUE;
					only_group = pos_group;
					Invalidate();
					bDrag = false; // 밖으로!
					break;
				}
				else
				{
					group_list.GetAt(pos_group)->nodes.GetPrev(posi);
				}
			}
			if (bDrag == false) break; // 밖으로!

			group_list.GetPrev(pos_group);
		} 
		if (bShift == false)	//다른 곳이 클릭되었을 경우에. && shift키가 안 눌렸을 경우. 다 지워야 함.
		{
			pos_group = group_list.GetTailPosition();
			while (pos_group != NULL) // 그룹 역순회 (최근 추가 순부터)
			{
				if (only_group != pos_group) // 선택된 그룹이 아니라면, 선택 취소.
				{
					group_list.GetAt(pos_group)->g_selected = FALSE;
				}

				group_list.GetPrev(pos_group);
			}
			
		}
		if (bDrag == true) // 도형을 누르지 않았음.
		{
			drag1 = point;
			drag2 = point;
		}
		Invalidate();
		/*pos_shape = shape_list.GetTailPosition();
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
		}*/

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
	{
		shape_list.GetTail()->set_mouse_up(point);
		POSITION pos_group = group_list.GetHeadPosition();
		POSITION posi;
		while (pos_group != NULL)
		{
			group_list.GetAt(pos_group)->setting_lt_rb();
			group_list.GetNext(pos_group);
		}
	}
	else
	{
		if (bDrag == false)
		{
			move2 = point;
			CPoint temp = move2 - move1;
			POSITION pos_group = group_list.GetHeadPosition();
			POSITION posi;
			while (pos_group != NULL)
			{
				if (group_list.GetAt(pos_group)->g_selected == TRUE)
				{
					posi = group_list.GetAt(pos_group)->nodes.GetHeadPosition();
					while (posi != NULL)
					{
						group_list.GetAt(pos_group)->nodes.GetAt(posi)->Move_To(temp);
						group_list.GetAt(pos_group)->nodes.GetNext(posi);
					}
				}
				group_list.GetNext(pos_group);
			}
			move1 = point;
		}
		else//(bDrag==True)
		{
			CPoint drag_lt = point, drag_rb = point;
			drag2 = point;

			if (drag1.x < drag2.x)
			{
				drag_lt.x = drag1.x;
				drag_rb.x = drag2.x;
			}
			else
			{
				drag_lt.x = drag2.x;
				drag_rb.x = drag1.x;
			}

			if (drag1.y > drag2.y)
			{
				drag_lt.y = drag1.y;
				drag_rb.y = drag2.y;
			}
			else
			{
				drag_lt.y = drag2.y;
				drag_rb.y = drag1.y;
			}

			POSITION pos_group = group_list.GetHeadPosition();
			POSITION posi;
			while (pos_group != NULL)
			{
				if (group_list.GetAt(pos_group)->LT.x >= drag_lt.x && group_list.GetAt(pos_group)->RB.x <= drag_rb.x
					&& group_list.GetAt(pos_group)->LT.y <= drag_lt.y && group_list.GetAt(pos_group)->RB.y >= drag_rb.y) // 드래그 범위 안에 있음.
				{
					group_list.GetAt(pos_group)->g_selected = true;
				}
				group_list.GetNext(pos_group);
			}
			
		}
	}
	bDrag = false;
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
	if (nChar == VK_DELETE)
	{
		POSITION pos_group = group_list.GetHeadPosition();
		POSITION prev;
		while (pos_group != NULL)
		{
			if (group_list.GetAt(pos_group)->g_selected == TRUE)
			{
				prev = pos_group;
				group_list.GetNext(pos_group);
				group_list.RemoveAt(prev);
			}
			else
				group_list.GetNext(pos_group);
			
		}
		Invalidate();
	}
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
		else
		{
			if (bDrag == false)
			{
				move2 = point;
				CPoint temp = move2 - move1;
				POSITION pos_group = group_list.GetHeadPosition();
				POSITION posi;
				while (pos_group != NULL)
				{
					if (group_list.GetAt(pos_group)->g_selected == TRUE)
					{
						posi = group_list.GetAt(pos_group)->nodes.GetHeadPosition();
						while (posi != NULL)
						{
							group_list.GetAt(pos_group)->nodes.GetAt(posi)->Move_To(temp);
							group_list.GetAt(pos_group)->nodes.GetNext(posi);
						}
					}
					group_list.GetNext(pos_group);
				}
				move1 = point;
			}
			else
			{
				CPoint drag_lt = point, drag_rb = point;
				drag2 = point;

				if (drag1.x < drag2.x)
				{
					drag_lt.x = drag1.x;
					drag_rb.x = drag2.x;
				}
				else
				{
					drag_lt.x = drag2.x;
					drag_rb.x = drag1.x;
				}

				if (drag1.y > drag2.y)
				{
					drag_lt.y = drag1.y;
					drag_rb.x = drag2.x;
				}
				else
				{
					drag_lt.y = drag2.y;
					drag_rb.y = drag1.y;
				}

				POSITION pos_group = group_list.GetHeadPosition();
				while (pos_group != NULL)
				{
					if (group_list.GetAt(pos_group)->LT.x >= drag_lt.x && group_list.GetAt(pos_group)->RB.x <= drag_rb.x
						&& group_list.GetAt(pos_group)->LT.y <= drag_lt.y && group_list.GetAt(pos_group)->RB.y >= drag_rb.y) // 드래그 범위 안에 있음.
					{
						group_list.GetAt(pos_group)->g_selected = true;
					}
					group_list.GetNext(pos_group);
				}
			}
		}

		Invalidate();
	}
	
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnDrawRect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	draw_mode = CMyShape::RECT;
	bDrag = false;
	POSITION pos_group = group_list.GetHeadPosition();
	while (pos_group != NULL)
	{
		group_list.GetAt(pos_group)->g_selected = FALSE;
		group_list.GetNext(pos_group);
	}
	Invalidate();
}


void CChildView::OnDrawStar()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	draw_mode = CMyShape::STAR;
	bDrag = false;
	POSITION pos_group = group_list.GetHeadPosition();
	while (pos_group != NULL)
	{
		group_list.GetAt(pos_group)->g_selected = FALSE;
		group_list.GetNext(pos_group);
	}
	Invalidate();
}


void CChildView::OnDrawCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	draw_mode = CMyShape::CIRCLE;
	bDrag = false;
	POSITION pos_group = group_list.GetHeadPosition();
	while (pos_group != NULL)
	{
		group_list.GetAt(pos_group)->g_selected = FALSE;
		group_list.GetNext(pos_group);
	}
	Invalidate();
}


void CChildView::OnDrawCurve()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	draw_mode = CMyShape::CURVE;
	bDrag = false;
	POSITION pos_group = group_list.GetHeadPosition();
	while (pos_group != NULL)
	{
		group_list.GetAt(pos_group)->g_selected = FALSE;
		group_list.GetNext(pos_group);
	}
	Invalidate();
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
	POSITION prev = NULL;
	POSITION pos_group = group_list.GetTailPosition();
	bool exist_prev = false;
	while (pos_group != NULL)
	{
		if (group_list.GetAt(pos_group)->g_selected == TRUE)
		{
			if (exist_prev == false)
			{
				prev = pos_group;
				exist_prev = true;
				group_list.GetPrev(pos_group);
			}
			else
			{
				group_list.AddTail( 
					new CMyGroup( *(group_list.GetAt(pos_group)), *(group_list.GetAt(prev)) ) 
				);
				group_list.RemoveAt(prev);
				prev = pos_group;
				group_list.GetPrev(pos_group);
				group_list.RemoveAt(prev);
				prev = group_list.GetTailPosition();
			}
		}
		else
			group_list.GetPrev(pos_group);
		if (pos_group == prev)
			break;
		
	}
	Invalidate();
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	POSITION pos_group = group_list.GetTailPosition();
	POSITION psi;
	POSITION prev;
	while (pos_group != NULL)
	{
		if (group_list.GetAt(pos_group)->g_selected == TRUE)
		{
			psi = group_list.GetAt(pos_group)->nodes.GetTailPosition();
			while (psi != NULL)
			{
				group_list.AddTail(new CMyGroup(group_list.GetAt(pos_group)->nodes.GetAt(psi)));
				group_list.GetTail()->setting_lt_rb();
				group_list.GetTail()->g_selected = true;
				prev = psi;
				group_list.GetAt(pos_group)->nodes.GetPrev(psi);
				group_list.GetAt(pos_group)->nodes.RemoveAt(prev);
			}
			prev = pos_group;
			group_list.GetPrev(pos_group);
			group_list.RemoveAt(prev);
			
		}
		else
			group_list.GetPrev(pos_group);

	}
	Invalidate();
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


void CChildView::OnAlignBringback()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	POSITION pos_group = group_list.GetHeadPosition();
	POSITION prev;
	while (pos_group != NULL)
	{
		if (group_list.GetAt(pos_group)->g_selected == true)
		{
			group_list.AddHead(new CMyGroup());
			group_list.GetHead()->g_selected = true;
			group_list.GetHead()->nodes.AddTail(&(group_list.GetAt(pos_group)->nodes));
			group_list.GetHead()->setting_lt_rb();
			prev = pos_group;
			group_list.GetNext(pos_group);
			group_list.RemoveAt(prev);
		}
		else
			group_list.GetNext(pos_group);
	}
	Invalidate();
}


void CChildView::OnAlignBringfront()
{
	POSITION pos_group = group_list.GetTailPosition();
	POSITION prev;
	while (pos_group != NULL)
	{
		if (group_list.GetAt(pos_group)->g_selected == true)
		{
			group_list.AddTail(new CMyGroup());
			group_list.GetTail()->g_selected = true;
			group_list.GetTail()->nodes.AddTail(&(group_list.GetAt(pos_group)->nodes));
			group_list.GetTail()->setting_lt_rb();
			prev = pos_group;
			group_list.GetPrev(pos_group);
			group_list.RemoveAt(prev);
		}
		else
			group_list.GetPrev(pos_group);
	}
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CMenu menu;
	menu.LoadMenuW(IDR_MAINFRAME);
	CMenu* pMenu = menu.GetSubMenu(4); // 최상위 메뉴에서 0부터 시작해서 4가 표시할 메뉴
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
}



void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnRButtonDown(nFlags, point);
}
