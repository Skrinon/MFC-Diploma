// MainFrm.cpp: реализация класса CMainFrame
//

#include "pch.h"
#include "framework.h"
#include "MFC Diploma.h" // Подставьте корректное имя вашего проекта, если оно другое
#include "MainFrm.h"
#include "CCalculationDialog.h" // Убедитесь, что подключен заголовочный файл диалога

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
    ON_WM_CREATE()
    ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
    ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
    ON_COMMAND(ID_CALCULATION_DIALOG, &CMainFrame::OnOpenCalculationDialog) // Пример ID диалога
    ON_COMMAND(IDC_BUTTON_CALCULATE, &CMainFrame::OnCalculateError) // Пример ID кнопки
END_MESSAGE_MAP()

CMainFrame::CMainFrame() noexcept
{
    // TODO: добавьте код инициализации члена
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
        return -1;

    // Создание меню и тулбара, если это необходимо
    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: измените здесь класс окна или стили, модифицируя
    //  структуру CREATESTRUCT
    return CMDIFrameWndEx::PreCreateWindow(cs);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
    // стандартный код для загрузки интерфейса фрейма
    return CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CMDIFrameWndEx::Dump(dc);
}
#endif

void CMainFrame::OnWindowManager()
{
    // Открытие диспетчера окон
}

void CMainFrame::OnViewCustomize()
{
    // Открытие окна настройки интерфейса
}

void CMainFrame::OnOpenCalculationDialog()
{
    // Открытие диалога расчетов
    CCalculationDialog dlg;
    if (dlg.DoModal() == IDOK) {
        // Здесь можно обрабатывать результаты, если это необходимо
    }
}

void CMainFrame::OnCalculateError()
{
    // Обработка нажатия на кнопку "Рассчитать"
    AfxMessageBox(_T("Расчет выполнен."));
}
