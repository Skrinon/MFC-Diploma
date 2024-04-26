
// MFC DiplomaView.h: интерфейс класса CMFCDiplomaView
//

#pragma once


class CMFCDiplomaView : public CView
{
protected: // создать только из сериализации
	CMFCDiplomaView() noexcept;
	DECLARE_DYNCREATE(CMFCDiplomaView)

// Атрибуты
public:
	CMFCDiplomaDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CMFCDiplomaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в MFC DiplomaView.cpp
inline CMFCDiplomaDoc* CMFCDiplomaView::GetDocument() const
   { return reinterpret_cast<CMFCDiplomaDoc*>(m_pDocument); }
#endif

