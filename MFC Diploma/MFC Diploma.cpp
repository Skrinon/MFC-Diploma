// MFCDiploma.cpp: определение класса CMFCDiplomaApp
//

#include "pch.h"
#include "framework.h"
#include "MFC Diploma.h"
#include "CCalculationDialog.h"
#include <gdiplus.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;

// Диалоговое окно "О программе"
class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg() noexcept;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
public:
    enum { IDD = IDD_ABOUTBOX };
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void CMFCDiplomaApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

BEGIN_MESSAGE_MAP(CMFCDiplomaApp, CWinAppEx)
    ON_COMMAND(ID_APP_ABOUT, &CMFCDiplomaApp::OnAppAbout)
END_MESSAGE_MAP()

ULONG_PTR gdiplusToken;

CMFCDiplomaApp::CMFCDiplomaApp() noexcept
    : m_bHiColorIcons(TRUE),
    m_nAppLook(0)
{
    SetAppID(_T("MFCDiploma.AppID.NoVersion"));
}

CMFCDiplomaApp theApp;

BOOL CMFCDiplomaApp::InitInstance()
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinAppEx::InitInstance();

    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    SetRegistryKey(_T("Моя организация"));
    LoadStdProfileSettings(4);

    CCalculationDialog dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK) {
        // обработка OK
    }
    else if (nResponse == IDCANCEL) {
        // обработка Cancel
    }

    return FALSE;
}

int CMFCDiplomaApp::ExitInstance()
{
    GdiplusShutdown(gdiplusToken);
    return CWinAppEx::ExitInstance();
}

void CMFCDiplomaApp::PreLoadState()
{
}

void CMFCDiplomaApp::LoadCustomState()
{
}

void CMFCDiplomaApp::SaveCustomState()
{
}