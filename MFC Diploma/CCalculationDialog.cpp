// CCalculationDialog.cpp: файл реализации
//

#include "pch.h"
#include "MFC Diploma.h"
#include "afxdialogex.h"
#include "CCalculationDialog.h"
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <atlstr.h> // Для использования CString
#include <numeric>
#include <iostream> 
#define NOMINMAX
#include <windows.h>
#include <GdiPlus.h>
#pragma comment (lib, "Gdiplus.lib")
using namespace Gdiplus;

IMPLEMENT_DYNAMIC(CCalculationDialog, CDialogEx)

CCalculationDialog::CCalculationDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_CALCULATION_DIALOG, pParent),
    m_bError(FALSE),  // По умолчанию выбран Расчет неопределенности
    m_bUncertainty(TRUE),  // Переменная для Расчета погрешности
    m_gdiplusToken(NULL)
{
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
}

CCalculationDialog::~CCalculationDialog()
{
    GdiplusShutdown(m_gdiplusToken);
}

void CCalculationDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_RADIO_UNCERTAINTY, m_bUncertainty);
    DDX_Radio(pDX, IDC_RADIO_ERROR, m_bError);
    DDX_Control(pDX, IDC_EDIT_RESULTS, m_editResults);
}

BEGIN_MESSAGE_MAP(CCalculationDialog, CDialogEx)
    ON_BN_CLICKED(IDC_RADIO_ERROR, &CCalculationDialog::OnBnClickedRadioError)
    ON_BN_CLICKED(IDC_RADIO_UNCERTAINTY, &CCalculationDialog::OnBnClickedRadioUncertainty)
    ON_BN_CLICKED(IDC_BUTTON_LOAD_DATA, &CCalculationDialog::OnBnClickedButtonLoadData)
    ON_BN_CLICKED(IDC_BUTTON_LOAD_QUANTILES, &CCalculationDialog::OnBnClickedButtonLoadQuantiles)
    ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CCalculationDialog::OnBnClickedButtonCalculate)
END_MESSAGE_MAP()

void CCalculationDialog::OnBnClickedRadioError()
{
    m_bError = TRUE;
    m_bUncertainty = FALSE;
    UpdateData(FALSE);
}

void CCalculationDialog::OnBnClickedRadioUncertainty()
{
    m_bError = FALSE;
    m_bUncertainty = TRUE;
    UpdateData(FALSE);
}

void CCalculationDialog::OnBnClickedButtonLoadData()
{
    CString filter = _T("Data Files (*.txt)|*.txt|All Files (*.*)|*.*||");
    if (AskForFilePath(m_strPathData, filter)) {
        SetDlgItemText(IDC_EDIT_PATH_DATA, _T("Выбрано: ") + m_strPathData);
    }
}

void CCalculationDialog::OnBnClickedButtonLoadQuantiles()
{
    CString filter = _T("Quantiles Files (*.txt)|*.txt|All Files (*.*)|*.*||");
    if (AskForFilePath(m_strPathQuantiles, filter)) {
        SetDlgItemText(IDC_EDIT_PATH_QUANTILES, _T("Выбрано: ") + m_strPathQuantiles);
    }
}

void CCalculationDialog::OnBnClickedButtonCalculate()
{
    // Преобразование CString в std::string для функции LoadDataFromFile
    std::string pathData = CT2A(m_strPathData.GetString());
    std::vector<double> data = LoadDataFromFile(pathData);
    if (data.empty()) {
        AfxMessageBox(_T("Data file is empty or contains non-numeric data."));
        return;
    }

    // Преобразование CString в std::string для функции LoadQuantilesFromFile
    std::string pathQuantiles = CT2A(m_strPathQuantiles.GetString());
    std::map<int, double> quantiles = LoadQuantilesFromFile(pathQuantiles);
    if (quantiles.empty()) {
        AfxMessageBox(_T("Quantiles file is empty or incorrectly formatted."));
        return;
    }

    double mean = CalculateMean(data);
    double stdDev = CalculateStdDev(data, mean);
    int sampleSize = static_cast<int>(data.size());

    if (m_bError) {
        auto it = quantiles.find(sampleSize);
        if (it != quantiles.end()) {
            double quantile = it->second;
            double interval = CalculateConfidenceInterval(stdDev, quantile, sampleSize);
            CString result;
            result.Format(_T("Mean: %.2f, StdDev: %.2f, Interval: %.2f"), mean, stdDev, interval);
            m_editResults.SetWindowText(result);
        }
        else {
            CString error;
            error.Format(_T("No suitable quantile found for sample size %d."), sampleSize);
            AfxMessageBox(error);
        }
    }
    else if (m_bUncertainty) {
        if (data.size() > 1) {
            double uA = CalculateTypeAUncertainty(data, mean);
            double uB = CalculateTypeBUncertainty(-1.0, 1.0, 'U');
            CString result;
            result.Format(_T("Mean: %.2f, Type A Uncertainty: %.2f, Type B Uncertainty: %.2f"), mean, uA, uB);
            m_editResults.SetWindowText(result);
        }
        else {
            AfxMessageBox(_T("Not enough data points for uncertainty calculation."));
        }
    }
}


bool CCalculationDialog::AskForFilePath(CString& filePath, const CString& filter)
{
    CFileDialog dlg(TRUE, _T("txt"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filter, this);
    if (dlg.DoModal() == IDOK) {
        filePath = dlg.GetPathName();
        return true;
    }
    return false;
}

std::vector<double> CCalculationDialog::LoadDataFromFile(const std::string& filename) {
    std::vector<double> data;
    std::ifstream inputFile(filename);
    std::string line;
    while (getline(inputFile, line)) {
        std::stringstream ss(line);
        double value;
        while (ss >> value) {
            data.push_back(value);
        }
    }
    return data;
}

std::map<int, double> CCalculationDialog::LoadQuantilesFromFile(const std::string& filename) {
    std::map<int, double> quantiles;
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        int n;
        double t;
        if (ss >> n >> t) {
            quantiles[n] = t;
        }
    }
    return quantiles;
}

double CCalculationDialog::CalculateMean(const std::vector<double>& values) {
    if (values.empty()) return 0.0;
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    return sum / values.size();
}

double CCalculationDialog::CalculateStdDev(const std::vector<double>& values, double mean) {
    if (values.size() < 2) return 0.0;
    double sum = 0.0;
    for (double value : values) {
        sum += (value - mean) * (value - mean);
    }
    return std::sqrt(sum / (values.size() - 1));
}

double CCalculationDialog::CalculateConfidenceInterval(double stdDev, double quantile, int sampleSize) {
    if (sampleSize <= 0) return 0.0;
    return quantile * stdDev / std::sqrt(static_cast<double>(sampleSize));
}

double CCalculationDialog::CalculateTypeAUncertainty(const std::vector<double>& values, double mean) {
    double sum = 0.0;
    for (auto value : values) {
        sum += std::pow(value - mean, 2);
    }
    return std::sqrt(sum / (values.size() * (values.size() - 1)));
}

double CCalculationDialog::CalculateTypeBUncertainty(double a_minus, double a_plus, char distributionType) {
    double u_B = 0.0;
    switch (distributionType) {
    case 'U':
        u_B = (a_plus - a_minus) / std::sqrt(12);
        break;
    case 'T':
        u_B = (a_plus - a_minus) / std::sqrt(24);
        break;
    default:
        u_B = (a_plus - a_minus) / std::sqrt(8); // Просто пример
        break;
    }
    return u_B;
}
