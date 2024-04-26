﻿// MainFrm.h: интерфейс класса CMainFrame
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"

class CMainFrame : public CMDIFrameWndEx
{
    DECLARE_DYNAMIC(CMainFrame)

public:
    CMainFrame() noexcept;
    virtual ~CMainFrame();

    // Переопределения
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = nullptr, CCreateContext* pContext = nullptr);

    // Реализация
#ifdef _DEBUG
    virtual void AssertValid() const override;  // Обеспечьте объявление для отладки
    virtual void Dump(CDumpContext& dc) const override;  // Обеспечьте объявление для вывода информации
#endif

protected:  // встроенные члены панели элементов управления
    CMFCMenuBar       m_wndMenuBar;
    CMFCToolBar       m_wndToolBar;
    CMFCStatusBar     m_wndStatusBar;
    CMFCToolBarImages m_UserImages;
    CFileView         m_wndFileView;
    CClassView        m_wndClassView;
    COutputWnd        m_wndOutput;
    CPropertiesWnd    m_wndProperties;

    // Созданные функции схемы сообщений
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnWindowManager();
    afx_msg void OnViewCustomize();
    afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
    afx_msg void OnApplicationLook(UINT id);
    afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
    afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
    afx_msg void OnCalculateError();  // Обработчик для кнопки "Рассчитать погрешность"
    afx_msg void OnOpenCalculationDialog();  // Обработчик для вызова диалога
    DECLARE_MESSAGE_MAP()

    BOOL CreateDockingWindows();
    void SetDockingWindowIcons(BOOL bHiColorIcons);
};
