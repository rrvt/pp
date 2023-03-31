// CalibrateYdlg dialog


#pragma once


class CalibrateYdlg : public CDialogEx {

  DECLARE_DYNAMIC(CalibrateYdlg)

public:

Cstring   name;
Cstring   nLines;
Cstring   yOffset;
Cstring   yTweak;

CComboBox nameCtl;
CEdit     nLinesCtl;
CEdit     yOffsetCtl;
CEdit     yTweakCtl;

           CalibrateYdlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~CalibrateYdlg();

  virtual BOOL OnInitDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_CalibrateYdlg };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void OnCbnSelchangePrinterlist();
  };
