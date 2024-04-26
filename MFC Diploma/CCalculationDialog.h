#pragma once

#include "afxdialogex.h"
#include <vector>
#include <map>
#include <string>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

// Use the Gdiplus namespace
using namespace Gdiplus;

class CCalculationDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CCalculationDialog)

public:
    CCalculationDialog(CWnd* pParent = nullptr);  // Standard constructor
    virtual ~CCalculationDialog();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_CALCULATION_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

public:
    BOOL m_bError;             // Variable for the first radio button
    BOOL m_bUncertainty;       // Variable for the second radio button
    CString m_strPathData;     // String to store the path to the data file
    CString m_strPathQuantiles;// String to store the path to the quantiles file
    CString m_strResults;      // String to display calculation results

    CEdit m_editResults;       // Control to display results

    // GDI+ token for startup and shutdown
    ULONG_PTR m_gdiplusToken;

    afx_msg void OnBnClickedRadioError();
    afx_msg void OnBnClickedRadioUncertainty();
    afx_msg void OnBnClickedButtonLoadData();
    afx_msg void OnBnClickedButtonLoadQuantiles();
    afx_msg void OnBnClickedButtonCalculate();

    bool AskForFilePath(CString& filePath, const CString& filter);

    std::vector<double> LoadDataFromFile(const std::string& filepath);
    std::map<int, double> LoadQuantilesFromFile(const std::string& filepath);
    double CalculateMean(const std::vector<double>& data);
    double CalculateStdDev(const std::vector<double>& data, double mean);
    double CalculateTypeAUncertainty(const std::vector<double>& data, double mean);
    double CalculateTypeBUncertainty(double a_minus, double a_plus, char distributionType);
    double CalculateCorrelation(const std::vector<double>& x, const std::vector<double>& y);
    double CalculateCombinedUncertainty(const std::vector<double>& x, const std::vector<double>& y, double uAX, double uAY, double correlation);
    double CalculateConfidenceInterval(double stdDev, double quantile, int sampleSize);
};
