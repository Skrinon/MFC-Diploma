
// MFC DiplomaView.cpp: реализация класса CMFCDiplomaView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MFC Diploma.h"
#endif

#include "MFC DiplomaDoc.h"
#include "MFC DiplomaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDiplomaView

IMPLEMENT_DYNCREATE(CMFCDiplomaView, CView)

BEGIN_MESSAGE_MAP(CMFCDiplomaView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCDiplomaView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CMFCDiplomaView

CMFCDiplomaView::CMFCDiplomaView() noexcept
{
	// TODO: добавьте код создания

}

CMFCDiplomaView::~CMFCDiplomaView()
{
}

BOOL CMFCDiplomaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CMFCDiplomaView

void CMFCDiplomaView::OnDraw(CDC* /*pDC*/)
{
	CMFCDiplomaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CMFCDiplomaView


void CMFCDiplomaView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCDiplomaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CMFCDiplomaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CMFCDiplomaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CMFCDiplomaView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCDiplomaView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CMFCDiplomaView

#ifdef _DEBUG
void CMFCDiplomaView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDiplomaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDiplomaDoc* CMFCDiplomaView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDiplomaDoc)));
	return (CMFCDiplomaDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CMFCDiplomaView
