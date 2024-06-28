// Get horizontal parameters

#pragma once


// CalibrateXdlg dialog

class CalibrateXdlg : public CDialogEx {

  DECLARE_DYNAMIC(CalibrateXdlg)

public:

Cstring   name;
Cstring   charPerLine;
Cstring   oddPgOffset;
Cstring   evenPgOffset;
Cstring   tweak;

CComboBox nameCtl;
CEdit     charsCtl;
CEdit     oddCtl;
CEdit     evenCtl;
CEdit     tweakCtl;

           CalibrateXdlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~CalibrateXdlg();

  virtual BOOL OnInitDialog();

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_CalibrateXdlg };                     // Dialog Data
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void onSelectPrinter();
  };
